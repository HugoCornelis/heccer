//
// Heccer : a compartmental solver that implements efficient Crank-Nicolson
// integration for neuronal models.
//

//////////////////////////////////////////////////////////////////////////////
//'
//' Heccer : testbed C implementation
//'
//' Copyright (C) 2006-2007 Hugo Cornelis
//'
//' functional ideas ..	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//' coding ............	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//////////////////////////////////////////////////////////////////////////////


#include "heccer/heccer.h"
#include "heccer/vm.h"


struct HeccerCommandInfo
{
    //m operation value

    int iValue;

    //m name of command

    char *pcName;

    //m length of command (number of operands + 1)

    int iLength;

    //m number of following commands in this command

    int iCommands;

    //m sprintf format string

    char *pcFormat;
};


struct HeccerCommandTable
{
    //m initialization status

    int iStatus;

    //m number of commands

    int iCommands;

    //m command info

    struct HeccerCommandInfo * phci;
};


static struct HeccerCommandInfo phciCops[] =
{
    {	HECCER_COP_FORWARD_ELIMINATION,		"HECCER_COP_FORWARD_ELIMINATION",	2 * sizeof(int),	-1,	NULL, },
    {	HECCER_COP_BACKWARD_SUBSTITUTION,	"HECCER_COP_BACKWARD_SUBSTITUTION",	2 * sizeof(int),	-1,	NULL, },
    {	HECCER_COP_FINISH_ROW,			"HECCER_COP_FINISH_ROW",		1 * sizeof(int),	-1,	NULL, },
    {	HECCER_COP_FINISH,			"HECCER_COP_FINISH",			1 * sizeof(int),	-1,	NULL, },
    {	HECCER_COP_SET_DIAGONAL,		"HECCER_COP_SET_DIAGONAL",		1 * sizeof(int),	-1,	NULL, },
    {	HECCER_COP_NEXT_ROW,			"HECCER_COP_NEXT_ROW",			1 * sizeof(int),	-1,	NULL, },
    {    -1,	NULL,	-1,	-1,	NULL,	},
};


static struct HeccerCommandTable hctCops =
{
    0,
    sizeof(phciCops) / sizeof(struct HeccerCommandInfo) - 1,
    phciCops,
};


static struct HeccerCommandInfo phciMops[] =
{
    {	HECCER_MOP_CALLOUT,		"HECCER_MOP_CALLOUT",			1 * sizeof(int),	-1,	NULL, },
    {	HECCER_MOP_COMPARTMENT,		"HECCER_MOP_COMPARTMENT",		1 * sizeof(int),	-1,	NULL, },
    {	HECCER_MOP_CONCEPTGATE,		"HECCER_MOP_CONCEPTGATE",		sizeof(struct MopsSingleGateConcept),	2,     NULL, },
    {	HECCER_MOP_EXPONENTIALDECAY,	"HECCER_MOP_EXPONENTIALDECAY",		sizeof(struct MopsExponentialDecay),	-1,	" %g %g %g", },
    {	HECCER_MOP_FINISH,		"HECCER_MOP_FINISH",			1 * sizeof(int),	-1,	NULL, },
    {	HECCER_MOP_FLUXPOOL,		"HECCER_MOP_FLUXPOOL",			sizeof(struct MopsFluxPool),	1,	NULL, },
    {	HECCER_MOP_INITIALIZECHANNEL,	"HECCER_MOP_INITIALIZECHANNEL",		sizeof(struct MopsChannel),	1,	" %g %g", },
    {	HECCER_MOP_LOADVOLTAGETABLE,	"HECCER_MOP_LOADVOLTAGETABLE",		sizeof(struct MopsVoltageTableDependence),	-1,	NULL, },
    {	HECCER_MOP_REGISTERCHANNELCURRENT, "HECCER_MOP_REGISTERCHANNELCURRENT",	sizeof(struct MopsRegisterChannelCurrent),	-1,	NULL, },
    {	HECCER_MOP_UPDATECOMPARTMENTCURRENT, "HECCER_MOP_UPDATECOMPARTMENTCURRENT", sizeof(struct MopsUpdateCompartmentCurrent),	-1,	NULL, },
    {    -1,	NULL,	-1,	-1,	NULL,	},
};


static struct HeccerCommandTable hctMops =
{
    0,
    sizeof(phciMops) / sizeof(struct HeccerCommandInfo) - 1,
    phciMops,
};


static int operator_comparator(const void *pv1,const void *pv2)
{
    struct HeccerCommandInfo *phci1 = (struct HeccerCommandInfo *)pv1;
    struct HeccerCommandInfo *phci2 = (struct HeccerCommandInfo *)pv2;

    return(phci1->iValue < phci2->iValue
	   ? -1
	   : phci1->iValue > phci2->iValue ? 1 : 0);
}


static void SortTable(struct HeccerCommandTable *phct)
{
    int iEntries = 0;

    while (phct->phci[iEntries].pcName != NULL)
    {
	iEntries++;
    }

    phct->iCommands = iEntries;

    qsort
	((void *)phct->phci,
	 phct->iCommands,
	 sizeof(struct HeccerCommandInfo),
	 operator_comparator);

    phct->iStatus |= 1;
}


//f static prototypes

static
struct HeccerCommandInfo *
HeccerCommandInfoLookup
(struct HeccerCommandTable *phct,
 int iOp);

static int
HeccerVMDumpOperators
(char * pcDescription,
 struct VM *pvm,
 int piArray[],
 struct HeccerCommandTable *phct,
 int iStart,
 int iEnd,
 FILE *pfile);


/// ***************************************************************************
///
/// NAME : HeccerCommandInfoLookup()
///
/// SHORT : lookup info on given command
///
/// PARAMETERS : 
///
///	phci....: array with info
///	iOp.....: operation to lookup
///
/// RETURN : struct HeccerCommandInfo * : info on command
///
/// DESCRIPTION : lookup info on given command
///
/// ***************************************************************************

static
struct HeccerCommandInfo *
HeccerCommandInfoLookup
(struct HeccerCommandTable *phct,
 int iOp)
{
    //- set default result : not found

    struct HeccerCommandInfo *phciResult = NULL;

    //- init top and bottom counters

    int iLower = 0;
    int iUpper = phct->iCommands - 1;

    if (!(phct->iStatus & 1))
    {
	SortTable(phct);
    }

    iLower = 0;
    iUpper = phct->iCommands - 1;

    //! binary search

    //- search untill the range to search in becomes invalid

    while (iUpper - iLower >= 0)
    {
	//- determine the middle of the search range

	int iMiddle = (iLower + iUpper) / 2;

	//- get pointer to this command info entry

        struct HeccerCommandInfo *phci = &phct->phci[iMiddle];

	//- set result and break out loop if search value is found here

	if (iOp == phci->iValue)
	{
	    phciResult = phci;

	    break;
	}

	//- set a new lower or upper limit

	if (iOp > phci->iValue)
	{
	    iLower = iMiddle + 1;
	}
	else
	{
	    iUpper = iMiddle - 1;
	}
    }

    //- return result

    return(phciResult);
}


/// **************************************************************************
///
/// SHORT: HeccerVMDump()
///
/// ARGS.:
///
///	pvm........: heccer vm.
///	pfile......: stdio file.
///	iSelection.: selection to dump.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Dump VM functions.
///
/// **************************************************************************

int HeccerVMDump(struct VM *pvm, FILE *pfile, int iSelection)
{
    //- set default result : ok

    int iResult = TRUE;

    //- dump compartment data

    if (iSelection & HECCER_DUMP_VM_COMPARTMENT_DATA)
    {
	//! nothing here
    }

    //- dump compartment operations

    if (iSelection & HECCER_DUMP_VM_COMPARTMENT_OPERATIONS)
    {
	int iCops = pvm->iCops;

	int *piCops = pvm->piCops;

	//! cops are allocated as integers, dump array expects char's,
	//! so that is why we have to multiply here.

	HeccerVMDumpOperators("Compartment operations", pvm, &piCops[0], &hctCops, 0, iCops * sizeof(int), pfile);
    }

    //- dump mechanism data

    if (iSelection & HECCER_DUMP_VM_MECHANISM_DATA)
    {
	int iMats = pvm->iMats;

	void *pvMats = pvm->pvMats;

/* 	HeccerVMDumpData("Mechanism data", pvm, pvMats, NULL, 0, iMats, pfile); */
    }

    //- dump mechanism operations

    if (iSelection & HECCER_DUMP_VM_MECHANISM_OPERATIONS)
    {
	int iMops = pvm->iMops;

	int *piMops = (int *)pvm->pvMops;

	HeccerVMDumpOperators("Mechanism operations", pvm, &piMops[0], &hctMops, 0, iMops, pfile);
    }

    //- compartment data : diagonals

    if (iSelection & HECCER_DUMP_VM_COMPARTMENT_MATRIX)
    {
	int i;

	for (i = 0 ; i < pvm->iDiagonals ; i++)
	{
	    fprintf(pfile, "VM Diagonals (pdDiagonals[%i]) : (%g)\n", i, pvm->pdDiagonals[i]);
	}
    }

    //- compartment data : axial resistances

    if (iSelection & HECCER_DUMP_VM_COMPARTMENT_MATRIX)
    {
	int i;

	for (i = 0 ; i < pvm->iAxres ; i++)
	{
	    fprintf(pfile, "VM Axial Resistances (pdAxres[%i]) : (%g)\n", i, pvm->pdAxres[i]);
	}
    }

    //- results : intermediate

    if (iSelection & HECCER_DUMP_VM_COMPARTMENT_MATRIX)
    {
	int i;

	for (i = 0 ; i < pvm->iResults ; i++)
	{
	    fprintf(pfile, "VM Axial Resistances (pdResults[%i]) : (%g)\n", i, pvm->pdResults[i]);
	}
    }

    //- results : membrane potentials

    if (iSelection & HECCER_DUMP_VM_COMPARTMENT_MATRIX)
    {
	int i;

	for (i = 0 ; i < pvm->iVms ; i++)
	{
	    fprintf(pfile, "VM Membrane Potentials (pdVms[%i]) : (%g)\n", i, pvm->pdVms[i]);
	}
    }

/*     //m mechanism operations */

/*     //t data type unspecified */

/*     void *pvMops; */

/*     //m mechanism data */

/*     //t data type unspecified */

/*     void *pvMats; */

    //- return result

    return(iResult);
}


/// ***************************************************************************
///
/// NAME : HeccerVMDumpOperators()
///
/// SHORT : print operations in given array according to given info array
///
/// PARAMETERS : 
///
///	pvm.....: heccer vm.
///	piArray.: array to print
///	iSize...: size of one array entry
///	phct....: table with info on array to print
///	iStart..: start index
///	iEnd....: ending index
///
/// RETURN : int
///
///	success of operation.
///
/// DESCRIPTION : print operations in given array.
///
/// NOTE : length of operations is ignored at the moment
///
/// ***************************************************************************

static
int
HeccerVMDumpOperators
(char * pcDescription,
 struct VM *pvm,
 int piArray[],
 struct HeccerCommandTable *phct,
 int iStart,
 int iEnd,
 FILE *pfile)
{
    //- set default result : ok

    int iResult = TRUE;

    //- give the banner

    fprintf(pfile, "%s\n", pcDescription);

    fprintf(pfile, "-----\n");

    //- loop from start to end

    //! dump array expects char's but goes over the array as if they
    //! are int's.

    //t fix char's int's mismatch somehow.

    int i;

    for (i = iStart; i < iEnd; )
    {
	int iCommand;
	struct HeccerCommandInfo *phciCurrent = NULL;

	//- get current command

	iCommand = piArray[i / sizeof(int)];

	//- lookup info for current operand

	phciCurrent = HeccerCommandInfoLookup(phct, iCommand);

	//- print numerical info

	fprintf(pfile, "%5.5i :: %i", i / sizeof(int), iCommand);

	//- if found

	if (phciCurrent)
	{
	    //- if operand length is valid

	    if (phciCurrent->iLength >= 2)
	    {
		if (phciCurrent->pcFormat)
		{
		    //t so only for two doubles ...

		    char pc[100];
		    int j;

		    for (j = sizeof(int) ; j < phciCurrent->iLength ;)
		    {
			double *pd = (double *)&piArray[(i + j) / sizeof(int)];

			sprintf(pc, phciCurrent->pcFormat, pd[0], pd[1]);

			j += sizeof(double) + sizeof(double);
		    }

		    fprintf(pfile, "%s", pc);
		}
		else
		{
		    //- print operands numerically

		    int j;

		    for (j = sizeof(int) ; j < phciCurrent->iLength ; j += sizeof(int))
		    {
			int iOperand;

			//- get current operand

			iOperand = piArray[(i + j) / sizeof(int)];

			fprintf(pfile, " %4i", iOperand);
		    }
		}
	    }

	    //- print name of operator

	    fprintf
		(pfile,
		 "\t\t\t%s",
		 phciCurrent->pcName);

	    //- if operand length is valid

	    if (phciCurrent->iLength >= 2)
	    {
		if (phciCurrent->pcFormat)
		{
		    //t so only for two doubles ...

		    char pc[100];
		    int j;

		    for (j = sizeof(int) ; j < phciCurrent->iLength ;)
		    {
			double *pd = (double *)&piArray[(i + j) / sizeof(int)];

			sprintf(pc, phciCurrent->pcFormat, pd[0], pd[1]);

			j += sizeof(double) + sizeof(double);
		    }

		    fprintf(pfile, "%s", pc);
		}
		else
		{
		    //- print operands numerically

		    int j;

		    for (j = sizeof(int) ; j < phciCurrent->iLength ; j += sizeof(int))
		    {
			int iOperand;

			//- get current operand

			iOperand = piArray[(i + j) / sizeof(int)];

			fprintf(pfile, " %4i", iOperand);
		    }
		}
	    }
	}

	//- terminate line

	fprintf(pfile, "\n");

	//- add size of operands

	if (phciCurrent && phciCurrent->iLength >= 2)
	{
	    i += phciCurrent->iLength;
	}
	else
	{
	    i += sizeof(int);
	}
    }

    //- return result

    return(iResult);
}


