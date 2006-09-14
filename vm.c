//
// Heccer : a compartmental solver that implements efficient Crank-Nicolson
// integration for neuronal models.
//

//////////////////////////////////////////////////////////////////////////////
//'
//' Heccer : testbed C implementation
//'
//' Copyright (C) 2006 Hugo Cornelis
//'
//' functional ideas ..	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//' coding ............	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//////////////////////////////////////////////////////////////////////////////


#include "vm.h"


struct HeccerCommandInfo
{
    //m operation value

    int iValue;

    //m name of command

    char *pcName;

    //m length of command (number of operands + 1)

    int iLength;
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


struct HeccerCommandInfo phciCops[] =
{
    {	HECCER_COP_FORWARD_ELIMINATION,		"HECCER_COP_FORWARD_ELIMINATION",	2, },
    {	HECCER_COP_BACKWARD_SUBSTITUTION,	"HECCER_COP_BACKWARD_SUBSTITUTION",	2, },
    {	HECCER_COP_CALC_RESULTS,		"HECCER_COP_CALC_RESULTS",		1, },
    {	HECCER_COP_FINISH,			"HECCER_COP_FINISH",			1, },
    {	HECCER_COP_SET_DIAGONAL,		"HECCER_COP_SET_DIAGONAL",		1, },
    {	HECCER_COP_SKIP_DIAGONAL,		"HECCER_COP_SKIP_DIAGONAL",		1, },
    {    -1,	NULL,	-1,	},
};


struct HeccerCommandTable hctCops =
{
    0,
    sizeof(phciCops) / sizeof(struct HeccerCommandInfo) - 1,
    phciCops,
};


struct HeccerCommandInfo phciMops[] =
{
    {	HECCER_MOP_COMPARTMENT,		"HECCER_MOP_COMPARTMENT",		1, },
    {	HECCER_MOP_FINISH,		"HECCER_MOP_FINISH",			1, },
    {    -1,	NULL,	-1,	},
};


struct HeccerCommandTable hctMops =
{
    0,
    sizeof(phciMops) / sizeof(struct HeccerCommandInfo) - 1,
    phciMops,
};


static int compare(const void *pv1,const void *pv2)
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
	 compare);

    phct->iStatus |= 1;
}


//f static prototypes

static
struct HeccerCommandInfo *
HeccerCommandInfoLookup
(struct HeccerCommandTable *phct,
 int iOp);

static int
HeccerVMDumpArray
(char * pcDescription,
 struct VM *pvm,
 int piArray[],
 int iSize,
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
///	pvm...: heccer vm.
///	pfile.: stdio file.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Dump VM functions.
///
/// **************************************************************************

int HeccerVMDump(struct VM *pvm, FILE *pfile)
{
    //- set default result : ok

    int iResult = TRUE;

    //- dump compartment operations

    int iCops = pvm->iCops;

    int *piCops = pvm->piCops;

    HeccerVMDumpArray("Compartment operations", pvm, &piCops[0], sizeof(piCops[0]), &hctCops, 0, iCops, pfile);

    //- dump mechanism operations

    int iMops = pvm->iMops;

    int *piMops = (int *)pvm->pvMops;

    HeccerVMDumpArray("Mechanism operations", pvm, &piMops[0], sizeof(piMops[0]), &hctMops, 0, iMops, pfile);

    //- compartment data : diagonals

    int i;

    for (i = 0 ; i < pvm->iDiagonals ; i++)
    {
	fprintf(pfile, "VM Diagonals (pdDiagonals[%i]) : (%g)\n", i, pvm->pdDiagonals[i]);
    }

    //- compartment data : axial resistances

    for (i = 0 ; i < pvm->iAxres ; i++)
    {
	fprintf(pfile, "VM Axial Resistances (pdAxres[%i]) : (%g)\n", i, pvm->pdAxres[i]);
    }

    //- results : intermediate

    for (i = 0 ; i < pvm->iResults ; i++)
    {
	fprintf(pfile, "VM Axial Resistances (pdResults[%i]) : (%g)\n", i, pvm->pdResults[i]);
    }

    //- results : membrane potentials

    for (i = 0 ; i < pvm->iVms ; i++)
    {
	fprintf(pfile, "VM Membrane Potentials (pdVms[%i]) : (%g)\n", i, pvm->pdVms[i]);
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
/// NAME : HeccerVMDumpArray()
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
HeccerVMDumpArray
(char * pcDescription,
 struct VM *pvm,
 int piArray[],
 int iSize,
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

    int i;

    for (i = iStart ; i < iEnd ; )
    {
	int iCommand;
	struct HeccerCommandInfo *phciCurrent = NULL;

	//- get current command

	if (iSize == sizeof(int))
	{
	    iCommand = piArray[i];
	}
	else if (iSize == sizeof(short))
	{
	    iCommand = piArray[i];
	}

	//- lookup info for current operand

	phciCurrent = HeccerCommandInfoLookup(phct, iCommand);

	//- print numerical info

	fprintf(pfile, "%5.5i :: %i", i, iCommand);

	//- if found

	if (phciCurrent)
	{
	    //- if operand length is valid

	    if (phciCurrent->iLength >= 2)
	    {
		//- print operands numerically

		int j;

		for (j = 1 ; j < phciCurrent->iLength ; j++)
		{
		    int iOperand;

		    //- get current operand

		    if (iSize == sizeof(int))
		    {
			iOperand = piArray[i + j];
		    }
		    else if (iSize == sizeof(short))
		    {
			iOperand = ((short *)piArray)[i + j];
		    }

		    fprintf(pfile, " %4i", iOperand);
		}
	    }

	    //- print name of operator

	    fprintf
		(pfile,
		 "\t%s%s%s",
		 phciCurrent->iLength >= 2 ? "" : "\t",
		 phciCurrent->iLength >= 4 ? "" : "\t",
		 phciCurrent->pcName);

	    //- if operand length is valid

	    if (phciCurrent->iLength >= 2)
	    {
		//- print operands numerically

		int j;

		for (j = 1 ; j < phciCurrent->iLength ; j++)
		{
		    int iOperand;

		    //- get current operand

		    if (iSize == sizeof(int))
		    {
			iOperand = piArray[i + j];
		    }
		    else if (iSize == sizeof(short))
		    {
			iOperand = ((short *)piArray)[i + j];
		    }

		    fprintf(pfile, " %4i", iOperand);
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
	    i++;
	}
    }

    //- return result

    return(iResult);
}


