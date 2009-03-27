//
// Heccer : a compartmental solver that implements efficient Crank-Nicolson
// integration for neuronal models.
//

//////////////////////////////////////////////////////////////////////////////
//'
//' Heccer : testbed C implementation
//'
//' Copyright (C) 2006-2008 Hugo Cornelis
//'
//' functional ideas ..	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//' coding ............	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//////////////////////////////////////////////////////////////////////////////


#include <string.h>

#include "heccer/heccer.h"
#include "heccer/vm.h"


struct HeccerCommandInfo
{
    /// operation value

    int iValue;

    /// name of command

    char *pcName;

    /// length of command (number of operands + 1)

    int iLength;

    /// number of secondary operands, expressed in doubles

    int iSecondaries;

    /// sizeof secondaries

    int iSecondariesSize;
};


struct HeccerCommandTable
{
    /// initialization status

    int iStatus;

    /// number of commands

    int iCommands;

    /// -1 means no formatted output

    int iFormatted;

    /// command info

    struct HeccerCommandInfo * phci;
};


static struct HeccerCommandInfo phciCops[] =
{
    {	HECCER_COP_FORWARD_ELIMINATION,		"FORWARD_ELIMINATION",		2 * sizeof(int), },
    {	HECCER_COP_BACKWARD_SUBSTITUTION,	"BACKWARD_SUBSTITUTION",	2 * sizeof(int), },
    {	HECCER_COP_FINISH_ROW,			"FINISH_ROW",			1 * sizeof(int), },
    {	HECCER_COP_FINISH,			"FINISH",			1 * sizeof(int), },
    {	HECCER_COP_SET_DIAGONAL,		"SET_DIAGONAL",			1 * sizeof(int), },
    {	HECCER_COP_NEXT_ROW,			"NEXT_ROW",			1 * sizeof(int), },
    {    -1,	NULL,	-1,	},
};


static struct HeccerCommandTable hctCops =
{
    0,
    sizeof(phciCops) / sizeof(struct HeccerCommandInfo) - 1,
    0,
    phciCops,
};


static struct HeccerCommandInfo phciMops[] =
{
    {	HECCER_MOP_CALLOUT,			"CALLOUT",			1 * sizeof(int),					0,	sizeof(struct MatsCallout),	},
#ifdef USE_ID_DISASSEM
    {	HECCER_MOP_COMPARTMENT,			"COMPARTMENT",			2 * sizeof(int),					4,	sizeof(struct MatsCompartment),	},
#else
    {	HECCER_MOP_COMPARTMENT,			"COMPARTMENT",			1 * sizeof(int),					4,	sizeof(struct MatsCompartment),	},
#endif
    {	HECCER_MOP_CONCEPTGATE,			"CONCEPTGATE",			sizeof(struct MopsSingleGateConcept),			1,	sizeof(struct MatsSingleGateConcept),	},
    {	HECCER_MOP_EVENTGENERATE,		"EVENTGENERATE",		sizeof(struct MopsEventGenerate),			2,	sizeof(struct MatsEventGenerate),	},
    {	HECCER_MOP_EXPONENTIALDECAY,		"EXPONENTIALDECAY",		sizeof(struct MopsExponentialDecay),			1,	sizeof(struct MatsExponentialDecay),	},
    {	HECCER_MOP_FINISH,			"FINISH",			1 * sizeof(int),					0,	0,	},
    {	HECCER_MOP_FLUXPOOL,			"FLUXPOOL",			sizeof(struct MopsFluxPool),				1,	sizeof(struct MatsFluxPool),	},
    {	HECCER_MOP_INITIALIZECHANNEL,		"INITIALIZECHANNEL",		sizeof(struct MopsInitializeChannel),			0,	0,	},
    {	HECCER_MOP_INITIALIZECHANNELEREV,	"INITIALIZECHANNELEREV",	sizeof(struct MopsInitializeChannelErev),			0,	0,	},
    {	HECCER_MOP_LOADVOLTAGETABLE,		"LOADVOLTAGETABLE",		sizeof(struct MopsVoltageTableDependency),		0,	0,	},
    {	HECCER_MOP_REGISTERCHANNELCURRENT, 	"REGISTERCHANNELCURRENT",	sizeof(struct MopsRegisterChannelCurrent),		0,	0,	},
    {	HECCER_MOP_UPDATECOMPARTMENTCURRENT, 	"UPDATECOMPARTMENTCURRENT",	sizeof(struct MopsUpdateCompartmentCurrent),		0,	0,	},
    {   HECCER_MOP_AGGREGATECURRENT,		"AGGREGATECURRENT",		sizeof(struct MopsAggregateCurrent),			0,	0,	},
    {   HECCER_MOP_INTERNALNERNST,		"INTERNALNERNST",		sizeof(struct MopsInternalNernst),			1,	sizeof(struct MatsInternalNernst),	},
    {   HECCER_MOP_SPRINGMASS,			"SPRINGMASS",			sizeof(struct MopsSpringMass),				3,	sizeof(struct MatsSpringMass),	},
    {   HECCER_MOP_STORESINGLECHANNELCURRENT,	"STORESINGLECHANNELCURRENT",    sizeof(struct MopsStoreSingleChannelCurrent),           2,      sizeof(struct MatsStoreSingleChannelCurrent),	},
    {    -1,	NULL,	-1,	},
};


static struct HeccerCommandTable hctMops =
{
    0,
    sizeof(phciMops) / sizeof(struct HeccerCommandInfo) - 1,
    1,
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
 void *pvOperands,
 struct HeccerCommandTable *phct,
 int iStart,
 int iEnd,
 FILE *pfile);


/// 
/// 
/// \arg phci array with info
/// \arg iOp operation to lookup
/// 
/// \return struct HeccerCommandInfo *
/// 
///	info on command
/// 
/// \brief lookup info on given command.
/// \details 
/// 

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

    /// \note binary search

    //- search until the range to search in becomes invalid

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


/// 
/// 
/// \arg pvm heccer vm.
/// \arg pfile stdio file.
/// \arg iSelection selection to dump.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Dump VM functions.
/// \details 
/// 

int HeccerVMDump(struct VM *pvm, FILE *pfile, int iSelection)
{
    //- set default result : ok

    int iResult = TRUE;

    //- dump compartment operations

    if (iSelection & HECCER_DUMP_VM_COMPARTMENT_OPERATIONS)
    {
	int iCops = pvm->iCops;

	int *piCops = pvm->piCops;

	/// \note cops are allocated as integers, dump array expects char's,
	/// \note so that is why we have to multiply here.

	HeccerVMDumpOperators("Compartment operations", pvm, &piCops[0], NULL, &hctCops, 0, iCops * sizeof(int), pfile);
    }

    //- dump mechanism data

    if (iSelection & HECCER_DUMP_VM_MECHANISM_DATA)
    {
	int iMats = pvm->iMats;

	void *pdMats = pvm->pdMats;

/* 	HeccerVMDumpData("Mechanism data", pvm, pdMats, NULL, 0, iMats, pfile); */
    }

    //- dump mechanism operations

    if (iSelection & HECCER_DUMP_VM_MECHANISM_OPERATIONS)
    {
	int iMops = pvm->iMops;

	int *piMops = (int *)pvm->pvMops;

	HeccerVMDumpOperators("Mechanism operations", pvm, &piMops[0], pvm->pdMats, &hctMops, 0, iMops, pfile);
    }

/*     //- dump channel to pool fluxes */

/*     if (iSelection & HECCER_DUMP_VM_CHANNEL_POOL_FLUXES) */
/*     { */
/* 	int i; */

/* 	for (i = 0 ; i < pvm->iFluxes ; i++) */
/* 	{ */
/* 	    fprintf(pfile, "VM Fluxes (pdFluxes[%i]) : (%g)\n", i, pvm->pdFluxes[i]); */
/* 	} */
/*     } */

    //- compartment data : diagonals

    if (iSelection & HECCER_DUMP_VM_COMPARTMENT_MATRIX_DIAGONALS)
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

    //- results : aggregators

    if (iSelection & HECCER_DUMP_VM_AGGREGATORS)
    {
	int i;

	for (i = 0 ; i < pvm->iAggregators ; i++)
	{
	    fprintf(pfile, "VM Membrane Aggregator results (pdAggregators[%i]) : (%g)\n", i, pvm->pdAggregators[i]);
	}
    }

    //- return result

    return(iResult);
}


/// 
/// 
/// \arg pvm heccer vm.
/// \arg piArray array to print
/// \arg iSize size of one array entry
/// \arg phct table with info on array to print
/// \arg iStart start index
/// \arg iEnd ending index
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief print operations in given array according to given info array.
/// \details 
/// 
/// \note  length of operations is ignored at the moment
/// 

static
int
HeccerVMDumpOperators
(char * pcDescription,
 struct VM *pvm,
 int piOperators[],
 void *pvOperands,
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

    //- initial line count is zero

    int iLineCount = 0;

    //- loop from start to end

    /// \note dump array expects char's but goes over the array as if they
    /// \note are int's.

    /// \todo fix char's int's mismatch somehow.

    int i;

    for (i = iStart; i < iEnd; )
    {
	char pcOutput1[500];
	char pcOutput2[500];

	//- get current command

	int iCommand = piOperators[i / sizeof(int)];

	//- lookup info for current operand

	struct HeccerCommandInfo *phciCurrent
	    = HeccerCommandInfoLookup(phct, iCommand);

	int iCommandLength = phciCurrent->iLength;

	//- print counter

	sprintf(pcOutput1, "%5.5i ::", iLineCount);

/* 	//- print numerical info */

/* 	fprintf(pcOutput2, " %i", iCommand); */

/* 	strcat(pcOutput1, pcOutput2); */

	//- if found

	if (phciCurrent)
	{
	    //- print name of operator

	    sprintf(pcOutput2, " %s", phciCurrent->pcName);

	    strcat(pcOutput1, pcOutput2);

	    //- if operand length is valid

	    if (iCommandLength >= 2)
	    {
		if (phct->iFormatted)
		{
		    /// \todo so only for five doubles ...

		    char pc[100] = "";

		    {
			void *pv = (void *)&piOperators[i / sizeof(int) + 1];

#ifdef USE_ID_DISASSEM
			if (phciCurrent->iValue == HECCER_MOP_COMPARTMENT)
			{
			    sprintf(pc, " [%i]", piOperators[i]);
			}
			else
#endif
			    if (phciCurrent->iValue == HECCER_MOP_INITIALIZECHANNEL)
			{
			    struct MopsInitializeChannel *pmops
				= (struct MopsInitializeChannel *)&piOperators[i / sizeof(int)];

			    sprintf(pc, " %g %g", pmops->dReversalPotential, pmops->dMaximalConductance);
			}
			else if (phciCurrent->iValue == HECCER_MOP_EXPONENTIALDECAY)
			{
			    struct MopsExponentialDecay *pmops
				= (struct MopsExponentialDecay *)&piOperators[i / sizeof(int)];

			    sprintf(pc, " %g %g %g\n\t\t\t", pmops->dBeta, pmops->dSteadyState, pmops->dTau);

			    uMC2Mat *puExternal = &pmops->puExternal[0];

			    int k;

			    char pc2[100];

			    for (k = 0 ; k < EXPONENTIALDECAY_CONTRIBUTORS ; k++)
			    {
				if (puExternal[k].pdValue)
				{
				    sprintf(pc2, " (%g)", *puExternal[k].pdValue);
				}
				else
				{
				    sprintf(pc2, " (nil)");
				}

				strcat(pc, pc2);
			    }
			}
			else if (phciCurrent->iValue == HECCER_MOP_CONCEPTGATE)
			{
			    struct MopsSingleGateConcept *pmops
				= (struct MopsSingleGateConcept *)&piOperators[i / sizeof(int)];

			    if (pmops->uState.pdValue)
			    {
				sprintf(pc, " %i %i (%g)", pmops->iTableIndex, pmops->iPower, *pmops->uState.pdValue);
			    }
			    else
			    {
				sprintf(pc, " %i %i (nil)", pmops->iTableIndex, pmops->iPower);
			    }
			}
			else if (phciCurrent->iValue == HECCER_MOP_INTERNALNERNST)
			{
			    struct MopsInternalNernst *pmops
				= (struct MopsInternalNernst *)&piOperators[i / sizeof(int)];

			    sprintf(pc, " %g %g", pmops->dConstant, pmops->dExternal);

			    int k;

			    char pc2[100];

			    for (k = 0 ; k < 1 ; k++)
			    {
				if (pmops->uInternal.pdValue)
				{
				    sprintf(pc2, " (%g)", *pmops->uInternal.pdValue);
				}
				else
				{
				    sprintf(pc2, " (nil)");
				}

				strcat(pc, pc2);
			    }
			}
			else if (phciCurrent->iValue == HECCER_MOP_INITIALIZECHANNELEREV)
			{
			    struct MopsInitializeChannelErev *pmops
				= (struct MopsInitializeChannelErev *)&piOperators[i / sizeof(int)];

			    if (pmops->uReversalPotential.pdValue)
			    {
				sprintf(pc, " (%g)", *pmops->uReversalPotential.pdValue);
			    }
			    else
			    {
				sprintf(pc, "(nil)");
			    }

			    char pc2[100];

			    sprintf(pc2, " %g", pmops->dMaximalConductance);

			    strcat(pc, pc2);
			}
			else if (phciCurrent->iValue == HECCER_MOP_SPRINGMASS)
			{
			    struct MopsSpringMass *pmops
				= (struct MopsSpringMass *)&piOperators[i / sizeof(int)];

			    if (pmops->pdEvents
				&& pmops->pdEvents[0])
			    {
				sprintf(pc, " %i %g %i %i %g", pmops->iEvent, pmops->pdEvents[pmops->iEvent], pmops->iDiscreteTarget, pmops->iTable, pmops->dFrequency);
			    }
			    else
			    {
				sprintf(pc, " %i (nil) %i %i %g", pmops->iEvent, pmops->iDiscreteTarget, pmops->iTable, pmops->dFrequency);
			    }
			}
			else if (phciCurrent->iValue == HECCER_MOP_EVENTGENERATE)
			{
			    struct MopsEventGenerate *pmops
				= (struct MopsEventGenerate *)&piOperators[i / sizeof(int)];

			    if (pmops->uSource.pdValue == (double *)-1)
			    {
				sprintf(pc, " (%s) %g %g %i", "dVm", pmops->dThreshold, pmops->dRefractoryReset, pmops->iTable);
			    }
			    else if (pmops->uSource.pdValue)
			    {
				sprintf(pc, " (%g) %g %g %i", *pmops->uSource.pdValue, pmops->dThreshold, pmops->dRefractoryReset, pmops->iTable);
			    }
			    else
			    {
				sprintf(pc, " (nil) %g %g %i", pmops->dThreshold, pmops->dRefractoryReset, pmops->iTable);
			    }
			}
			else if (phciCurrent->iValue == HECCER_MOP_AGGREGATECURRENT)
			{
			    struct MopsAggregateCurrent *pmops
				= (struct MopsAggregateCurrent *)&piOperators[i / sizeof(int)];

			    sprintf(pc, " %i (%g)", pmops->iIndex, pvm->pdAggregators[pmops->iIndex]);
			}
		    }

		    sprintf(pcOutput2, "%s", pc);

		    strcat(pcOutput1, pcOutput2);
		}
		else
		{
		    //- print operands numerically

		    int j;

		    for (j = sizeof(int) ; j < iCommandLength ; j += sizeof(int))
		    {
			int iOperand;

			//- get current operand

			iOperand = piOperators[(i + j) / sizeof(int)];

			sprintf(pcOutput2, " %4i", iOperand);

			strcat(pcOutput1, pcOutput2);
		    }
		}

		//- if a secondary operands array is given

		if (pvOperands)
		{
		    if (phciCurrent->iSecondaries)
		    {
			sprintf(pcOutput2, "\t\t\t\t\t\t\t");

			strcat(pcOutput1, pcOutput2);

			double *pdOperands = (double *)pvOperands;

			int iSecondary;

			for (iSecondary = 0; iSecondary < phciCurrent->iSecondaries; iSecondary++)
			{
			    sprintf(pcOutput2, " %g", pdOperands[iSecondary]);

			    strcat(pcOutput1, pcOutput2);
			}
		    }

		    pvOperands = (void *)&((char *)pvOperands)[phciCurrent->iSecondariesSize];
		}
	    }
	}
	else
	{
	    fprintf(pfile, " Error: %4i command not found in command table", iCommand);
	}

	//- terminate line

	fprintf(pfile, "%s\n", pcOutput1);

	//- increment line count

	iLineCount++;

	//- add size of operands

	if (phciCurrent && iCommandLength >= 2)
	{
	    i += iCommandLength;
	}
	else
	{
	    i += sizeof(int);
	}
    }

    //- return result

    return(iResult);
}


