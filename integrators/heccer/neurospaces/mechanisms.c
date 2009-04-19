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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <neurospaces/components/attachment.h>
#include <neurospaces/function.h>
#include <neurospaces/parsersupport.h>
#include <neurospaces/pidinstack.h>
#include <neurospaces/treespacetraversal.h>

#include "heccer/addressing.h"
#include "heccer/compartment.h"
#include "heccer/intermediary.h"
#include "heccer/mathcomponent.h"
#include "heccer/neurospaces/heccer.h"
#include "heccer/neurospaces/mechanisms.h"
#include "heccer/service.h"


/* struct TableAllocatorData */
/* { */
/*     /// symbol with value array */

/*     struct symtab_HSolveListElement *phsle; */

/*     /// context of the symbol */

/*     struct PidinStack *ppist; */
/* }; */




/*
 * A structure for storing error states.
 *
 */
#define MATH_COMPONENT_MAX_ERRORS 20

struct MathComponentError
{

    int iStatus;
  
    char * pcError;

};


struct MathComponentErrorReport
{

    int iNumErrors;

    struct MathComponentError mce[MATH_COMPONENT_MAX_ERRORS];

};


struct MathComponentData
{
    /// solution engine

    struct Heccer *pheccer;

    /// compartment number

    int iCompartment;

    /// compartment 2 mechanism convertor

    int *piC2m;

    /// current compartment

    struct symtab_HSolveListElement *phsleCompartment;

    struct PidinStack *ppistCompartment;

    /// array of all math component types

    int iDescendants;

    int iCurrentType;

    int *piTypes;

    /// current mathcomponent

    struct MathComponent * pmc;

    /// number of spikegens

    int iSpikeGens;

    /// operational status: positive is positive, negative is negative (error)

    int iStatus;

    char pcContext[1000];

    char *pcMessage;

    /// channels that contribute to a pool

    int iConnectors;

    int **ppiConnectors;


    struct MathComponentErrorReport mcer;

    

};


#define STATUS_OVERFLOW -1
#define STATUS_UNKNOWN_TYPE -2
#define STATUS_MANY_POOLS -3
#define STATUS_MEMORY -4
#define STATUS_CONSISTENCY -5
#define STATUS_UNRESOLVABLE_PARAMETERS -6
#define STATUS_MANY_CHANNELS -7
#define STATUS_UNKNOWN_ERROR -8
#define STATUS_NON_CHANNEL_OUTPUTS_IK -9
#define STATUS_CONSTANT_NERNST -10
#define STATUS_NON_POOL_FOR_NERNST -11
#define STATUS_ILLEGAL_PARAMETER_VALUES -12
#define STATUS_UNQUALIFIABLE_FILENAME -13
#define STATUS_UNKNOWN_CHANNEL_TYPE1 -14
#define STATUS_UNKNOWN_CHANNEL_TYPE2 -15
#define STATUS_UNKNOWN_CHANNEL_TYPE3 -16

static
char *ppcStatusMessages[] =
{
    NULL,
    "overflow",
    "unknown mechanism type found in the intracellular mechanisms of the model",
    "many_pools: channels can have at most one concentration dependency",
    "out of memory",
    "found an internal inconsistency during typing of the model intracellular mechanisms",
    "unresolvable parameters: the model container does not associate a numerical value with one of the parameters",
    "many_channels: an exponential decay concentration pool had to many channel feeds (max is EXPONENTIALDECAY_CONTRIBUTORS)" ,
    "unknown_error during channel examination",
    "non_channel_outputs_ik: something feeds a current to a pool, but it is not a channel while it should",
    "constant_nernst: the nerst equation must be connected to an internal concentration pool",
    "non_pool_for_nernst: the internal concentration of a nerst equation is not connected to a concentration pool",
    "illegal_parameter_values: some parameters have values that don't make sense from a mathematical viewpoint",
    "unqualifiable_filename: a parameter filename cannot be resolved to an existing file",
    "cannot determine the value of a channel type parameter",
    "unknown_channel_type2",
    "unknown_channel_type3",
    NULL,
};


static int ConnectionSource2Target(struct MathComponentData * pmcd, struct MathComponent * pmc);

static
int
MathComponentDataStatusSet(struct MathComponentData * pmcd, int iStatus, struct PidinStack *ppist);

static
int
MathComponentDataTypeRegister(struct MathComponentData * pmcd, int iType, struct PidinStack *ppist);

/* static */
/* double */
/* TableAllocatorProcessor(struct TableAllocatorData *ptd, int iValue); */

static
int
solver_channel_activation_concentration_processor(struct TreespaceTraversal *ptstr, void *pvUserdata);

static
int
solver_channel_activation_processor(struct TreespaceTraversal *ptstr, void *pvUserdata);

static
int
solver_channel_activation_inactivation_processor(struct TreespaceTraversal *ptstr, void *pvUserdata);

static
int
solver_channel_persistent_steadystate_dualtau_processor(struct TreespaceTraversal *ptstr, void *pvUserdata);

static
int
solver_channel_persistent_steadystate_tau_processor(struct TreespaceTraversal *ptstr, void *pvUserdata);

static
int
solver_channel_springmass_processor(struct TreespaceTraversal *ptstr, void *pvUserdata);

static
int
solver_channel_steadystate_steppedtau_processor(struct TreespaceTraversal *ptstr, void *pvUserdata);

static
int
solver_mathcomponent_finalizer(struct TreespaceTraversal *ptstr, void *pvUserdata);

static
int
solver_mathcomponent_processor(struct TreespaceTraversal *ptstr, void *pvUserdata);

static int cellsolver_getmathcomponents(struct Heccer *pheccer, struct TranslationService *pts);

static int cellsolver_linkmathcomponents(struct Heccer * pheccer, struct MathComponentData * pmcd);

static
TreespaceTraversalProcessor *
Type2Processor(int iType);



static
int
MathComponentError(struct MathComponentData * pmcd, int iStatus, char *pcError);


static
int
MathComponentPrintErrorReport(struct MathComponentData * pmcd);






static int ConnectionSource2Target(struct MathComponentData * pmcd, struct MathComponent * pmc)
{
    /// \todo I think this function can be removed completely, because the
    /// \todo connectivity can be translated directly from the model in
    /// \todo neurospaces, no need for this indirection.

    //- set default result : none

    int iResult = -1;

    //- loop over the contributors

    int iChannelContributors = pmcd->iConnectors;

    int **ppiChannelContributors = pmcd->ppiConnectors;

    int i;

    for (i = 0 ; i < iChannelContributors ; i++)
    {
	//- if found

	if (ppiChannelContributors[i][0] == pmc->iSerial)
	{
	    //- set result

	    iResult = ppiChannelContributors[i][1];

	    //- break searching loop

	    break;
	}
    }

    //- return result

    return(iResult);
}


static
int
MathComponentDataStatusSet(struct MathComponentData * pmcd, int iStatus, struct PidinStack *ppist)
{
    //- set default result: current status

    int iResult = pmcd->iStatus;

    //- if everything still ok

    if (iResult > 0)
    {
	//- get string from context

	PidinStackString(ppist, pmcd->pcContext, sizeof(pmcd->pcContext));

	//- set new status

	pmcd->iStatus = iStatus;

	//- set result: new status

	iResult = pmcd->iStatus;
    }

    //- return result

    return(iResult);
}


static
int
MathComponentDataTypeRegister(struct MathComponentData * pmcd, int iType, struct PidinStack *ppist)
{
    //- if we were able to determine the type

    if (iType != INT_MAX)
    {
	//- if we were allowed to skip this component

	if (iType == -2)
	{
	}

	//- else

	else
	{
	    //- if no overflow

	    if (pmcd->iCurrentType < pmcd->iDescendants)
	    {
		//- set the type in the array

		pmcd->piTypes[pmcd->iCurrentType] = iType;

		pmcd->iCurrentType++;
	    }

	    //- else

	    else
	    {
		//- abort the traversal, fatal failure

		MathComponentDataStatusSet(pmcd, STATUS_OVERFLOW, ppist);
	    }
	}
    }

    //- else

    else
    {
	//- abort the traversal, fatal failure

	/// \todo the current serial and type cursor give an indication
	/// \todo of what model component caused the failure

	MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ppist);
    }

    return(1);
}


static
int
solver_channel_activation_processor(struct TreespaceTraversal *ptstr, void *pvUserdata)
{
    //- set default result : ok

    int iResult = TSTR_PROCESSOR_SUCCESS;

    //- get actual symbol

    struct symtab_HSolveListElement *phsle = (struct symtab_HSolveListElement *)TstrGetActual(ptstr);

    //- get user data

    struct MathComponentData * pmcd = (struct MathComponentData *)pvUserdata;

    //- get current math component

    struct MathComponent * pmc = pmcd->pmc;

    struct ChannelAct * pca = (struct ChannelAct *)pmc;

    //- if conceptual gate

    if (instanceof_h_h_gate(phsle))
    {
	if (pmcd->iStatus == 1)
	{
	    struct PoweredGateConcept * ppgc = &pca->pgc;

	    //- get power

	    double dPower = SymbolParameterResolveValue(phsle, ptstr->ppist, "POWER");

	    int iPower = dPower;

	    ppgc->iPower = iPower;

	    //- get initial state

	    double dInitActivation = SymbolParameterResolveValue(phsle, ptstr->ppist, "state_init");

	    ppgc->gc.dInitActivation = dInitActivation;

	    if (dPower == FLT_MAX)
	    {

		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					   ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"POWER");

		iResult = TSTR_PROCESSOR_ABORT;
	

	    }
	    else if( dInitActivation == FLT_MAX)
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS,ptstr->ppist);


		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"state_init");

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    double dEntries = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_NUMBER_OF_TABLE_ENTRIES");

	    if (dEntries != FLT_MAX)
	    {
		ppgc->gc.htg.iEntries = dEntries;

		ppgc->gc.htg.hi.dStart = pmcd->pheccer->ho.dIntervalStart;
		ppgc->gc.htg.hi.dEnd = pmcd->pheccer->ho.dIntervalEnd;
		ppgc->gc.htg.hi.dStep = (ppgc->gc.htg.hi.dEnd - ppgc->gc.htg.hi.dStart) / ppgc->gc.htg.iEntries;;

/* 		ppgc->gc.htg.hi.dStart = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_TABLE_START"); */
/* 		ppgc->gc.htg.hi.dEnd = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_TABLE_END"); */
/* 		ppgc->gc.htg.hi.dStep = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_TABLE_STEP"); */
	    }
	    else
	    {
		ppgc->gc.htg.iEntries = INT_MAX;
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ptstr->ppist);


	    MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,"Unknown Type of Object");
	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- if gate kinetic

    else if (instanceof_gate_kinetic(phsle))
    {
	/// \note 2: forward, act
	/// \note 3: backward, act

	if (pmcd->iStatus == 2
	    || pmcd->iStatus == 3)
	{
	    struct PoweredGateConcept * ppgc = &pca->pgc;

	    struct GateKinetic *pgk
		= (pmcd->iStatus == 2
		   ? &ppgc->gc.parameters.gkA
		   : &ppgc->gc.parameters.gkB);

	    //- initialize table index

	    ppgc->gc.iTable = -1;

	    //- if a hardcoded table is present

	    double dHasTable = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_Has_Table");

	    int iHasTable = 0;

	    if (dHasTable != FLT_MAX)
	    {
		iHasTable = dHasTable;
	    }

	    if (iHasTable)
	    {
/* 		printf("warning: iHasTable has value %i\n", iHasTable); */

	    }

	    if (ppgc->gc.htg.iEntries != INT_MAX)
	    {
/* 		if (ppgc->gc.htg.hi.dStart != FLT_MAX */
/* 		    && ppgc->gc.htg.hi.dEnd != FLT_MAX */
/* 		    && ppgc->gc.htg.hi.dStep != FLT_MAX) */
		if (1)
		{
		    double *pdTable = (double *)calloc(ppgc->gc.htg.iEntries, sizeof(*pdTable));

		    int i;

		    for (i = 0 ; i < ppgc->gc.htg.iEntries ; i++)
		    {
			char pcTable[50];

			sprintf(pcTable, "table[%i]", i);

			double d = SymbolParameterResolveValue(phsle, ptstr->ppist, pcTable);

			if (d != FLT_MAX)
			{
			    pdTable[i] = d;
			}
			else
			{
			    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

			    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,pcTable);

			    iResult = TSTR_PROCESSOR_ABORT;

			    break;
			}
		    }

		    /// \todo would prefer to have all tests for pmcd->iStatus at the same place

		    if (pmcd->iStatus == 2)
		    {
			ppgc->gc.htg.pdA = pdTable;
		    }
		    else
		    {
			ppgc->gc.htg.pdB = pdTable;
		    }
		}
		else
		{
		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS,ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"HH_Has_Table");

		    iResult = TSTR_PROCESSOR_ABORT;
		}
	    }

	    //- else parameterized

	    else
	    {
		//- get HH_AB_Scale = 35.0e3

		double dHHScale = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_AB_Scale");

		pgk->dHHScale = dHHScale;

		//- get HH_AB_Mult = 0.0

		double dHHMult = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_AB_Mult");

		pgk->dHHMult = dHHMult;

		//- get HH_AB_Factor_Flag = -1.0

		double dHHFactorFlag = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_AB_Factor_Flag");

		int iHHFactorFlag = dHHFactorFlag;

		pgk->iHHFactorFlag = iHHFactorFlag;

		//- get HH_AB_Add = 0.0

		double dHHAdd = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_AB_Add");

		pgk->dHHAdd = dHHAdd;

		//- get HH_AB_Offset_E = 5.0e-3

		double dHHOffsetE = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_AB_Offset_E");

		pgk->dHHOffsetE = dHHOffsetE;

		//- get HH_AB_Tau = -10.0e-3

		double dHHTau = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_AB_Tau");

		pgk->dHHTau = dHHTau;

		if (dHHScale == FLT_MAX ){


		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS,ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"HH_AB_Scale");

		    iResult = TSTR_PROCESSOR_ABORT;


		}
		

		if (dHHMult == FLT_MAX ){

		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"HH_AB_Mult");

		    iResult = TSTR_PROCESSOR_ABORT;


		}
		 

		if(dHHFactorFlag == FLT_MAX ){



		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS,ptstr->ppist);


		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"HH_AB_Factor_Flag");

		    iResult = TSTR_PROCESSOR_ABORT;


		}
		

		if (dHHAdd == FLT_MAX ){


		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS,ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"HH_AB_Add");

		    iResult = TSTR_PROCESSOR_ABORT;


		}
		

		if (dHHOffsetE == FLT_MAX) {


		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS,ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"HH_AB_Offset_E");

		    iResult = TSTR_PROCESSOR_ABORT;


		}
		

		if(dHHTau == FLT_MAX)
		{
		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS,ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"HH_AB_Tau");

		    iResult = TSTR_PROCESSOR_ABORT;
		}
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,"Unknown Object Type.");

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- otherwise

    else
    {
	//- an error

	MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ptstr->ppist);

	MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,"Unknown Object Type.");

	iResult = TSTR_PROCESSOR_ABORT;
    }

    //- if no error

    if (pmcd->iStatus > 0)
    {
	//- increment the status to indicate what component we have processed

	pmcd->iStatus++;

	if (pmcd->iStatus == 4)
	{
	    pmcd->iStatus = 1;
	}
    }

    //- return result

    return(iResult);
}


/* static */
/* double */
/* TableAllocatorProcessor(struct TableAllocatorData *ptd, int iValue) */
/* { */
/*     //- construct parameter name */

/*     char pcValue[100]; */

/*     sprintf(pcValue, "value[%i]", iValue); */

/*     //- resolve value */

/*     double dResult = SymbolParameterResolveValue(ptd->phsle, ptd->ppist, pcValue); */

/*     //- return result */

/*     return(dResult); */
/* } */


static
int
solver_channel_activation_concentration_processor(struct TreespaceTraversal *ptstr, void *pvUserdata)
{
    //- set default result : ok

    int iResult = TSTR_PROCESSOR_SUCCESS;

    //- get actual symbol

    struct symtab_HSolveListElement *phsle = (struct symtab_HSolveListElement *)TstrGetActual(ptstr);

    //- get user data

    struct MathComponentData * pmcd = (struct MathComponentData *)pvUserdata;

    //- get current math component

    struct MathComponent * pmc = pmcd->pmc;

    struct ChannelActConc * pcac = (struct ChannelActConc *)pmc;

    //- if conceptual gate

    if (instanceof_h_h_gate(phsle))
    {
	if (pmcd->iStatus == 1)
	{
	    //- initial table index

	    pcac->pgc.gc.iTable = -1;

	    //- get power

	    double dPower = SymbolParameterResolveValue(phsle, ptstr->ppist, "POWER");

	    int iPower = dPower;

	    pcac->pgc.iPower = iPower;

	    //- get initial state

	    double dInitActivation = SymbolParameterResolveValue(phsle, ptstr->ppist, "state_init");

	    pcac->pgc.gc.dInitActivation = dInitActivation;

	    if (dPower == FLT_MAX)
	    {

		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS,ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"POWER");

		iResult = TSTR_PROCESSOR_ABORT;

	    }




	    if( dInitActivation == FLT_MAX)
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS,ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"state_init");

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    double dEntries = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_NUMBER_OF_TABLE_ENTRIES");

	    if (dEntries != FLT_MAX)
	    {
		pcac->pgc.gc.htg.iEntries = dEntries;

		pcac->pgc.gc.htg.hi.dStart = pmcd->pheccer->ho.dIntervalStart;
		pcac->pgc.gc.htg.hi.dEnd = pmcd->pheccer->ho.dIntervalEnd;
		pcac->pgc.gc.htg.hi.dStep = (pcac->pgc.gc.htg.hi.dEnd - pcac->pgc.gc.htg.hi.dStart) / pcac->pgc.gc.htg.iEntries;;

/* 		pcac->pgc.gc.htg.hi.dStart = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_TABLE_START"); */
/* 		pcac->pgc.gc.htg.hi.dEnd = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_TABLE_END"); */
/* 		pcac->pgc.gc.htg.hi.dStep = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_TABLE_STEP"); */
	    }
	    else
	    {
		pcac->pgc.gc.htg.iEntries = INT_MAX;
	    }
	}
	else if (pmcd->iStatus == 4)
	{
	    //- initial table index

	    pcac->pac.ca.iTable = -1;

	    //- get power

	    double dPower = SymbolParameterResolveValue(phsle, ptstr->ppist, "POWER");

	    int iPower = dPower;

	    pcac->pac.iPower = iPower;

	    //- get initial state

	    double dInitActivation = SymbolParameterResolveValue(phsle, ptstr->ppist, "state_init");

	    pcac->pac.ca.dInitActivation = dInitActivation;


	    if (dPower == FLT_MAX)
	    {

		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS,ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"POWER");

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    if( dInitActivation == FLT_MAX)
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS,ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"state_init");

		iResult = TSTR_PROCESSOR_ABORT;
	    }



	    double dEntries = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_NUMBER_OF_TABLE_ENTRIES");

	    if (dEntries != FLT_MAX)
	    {
		pcac->pac.ca.htg.iEntries = dEntries;

		pcac->pac.ca.htg.hi.dStart = pmcd->pheccer->ho.dConcentrationGateStart;
		pcac->pac.ca.htg.hi.dEnd = pmcd->pheccer->ho.dConcentrationGateEnd;
		pcac->pac.ca.htg.hi.dStep = (pcac->pac.ca.htg.hi.dEnd - pcac->pac.ca.htg.hi.dStart) / pcac->pac.ca.htg.iEntries;;

/* 		pcac->pac.ca.htg.hi.dStart = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_TABLE_START"); */
/* 		pcac->pac.ca.htg.hi.dEnd = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_TABLE_END"); */
/* 		pcac->pac.ca.htg.hi.dStep = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_TABLE_STEP"); */
	    }
	    else
	    {
		pcac->pac.ca.htg.iEntries = INT_MAX;
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,"Unknown Object Type.");

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- if gate kinetic

    else if (instanceof_gate_kinetic(phsle))
    {
	/// \note 2: forward, act
	/// \note 3: backward, act

	if (pmcd->iStatus == 2
	    || pmcd->iStatus == 3)
	{
	    struct PoweredGateConcept * ppgc = &pcac->pgc;

	    struct GateKinetic *pgk
		= (pmcd->iStatus == 2
		   ? &ppgc->gc.parameters.gkA
		   : &ppgc->gc.parameters.gkB);

	    //- initialize table index

	    ppgc->gc.iTable = -1;

	    double dHasTable = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_Has_Table");

	    int iHasTable = 0;

	    if (dHasTable != FLT_MAX)
	    {
		iHasTable = dHasTable;
	    }

	    if (iHasTable)
	    {
/* 		printf("warning: iHasTable has value %i\n", iHasTable); */

	    }

	    if (ppgc->gc.htg.iEntries != INT_MAX)
	    {
/* 		if (ppgc->gc.htg.hi.dStart != FLT_MAX */
/* 		    && ppgc->gc.htg.hi.dEnd != FLT_MAX */
/* 		    && ppgc->gc.htg.hi.dStep != FLT_MAX) */
		if (1)
		{
		    double *pdTable = (double *)calloc(ppgc->gc.htg.iEntries, sizeof(*pdTable));

		    int i;

		    for (i = 0 ; i < ppgc->gc.htg.iEntries ; i++)
		    {
			char pcTable[50];

			sprintf(pcTable, "table[%i]", i);

			double d = SymbolParameterResolveValue(phsle, ptstr->ppist, pcTable);

			if (d != FLT_MAX)
			{
			    pdTable[i] = d;
			}
			else
			{
			    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
						       ptstr->ppist);

			    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,pcTable);

			    iResult = TSTR_PROCESSOR_ABORT;

			    break;
			}
		    }

		    /// \todo would prefer to have all tests for pmcd->iStatus at the same place

		    if (pmcd->iStatus == 2)
		    {
			ppgc->gc.htg.pdA = pdTable;
		    }
		    else
		    {
			ppgc->gc.htg.pdB = pdTable;
		    }
		}
		else
		{
		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,
				       "HH_NUMBER_OF_TABLE_ENTRIES");

		    iResult = TSTR_PROCESSOR_ABORT;
		}
	    }

	    //- else parameterized

	    else
	    {
		//- get HH_AB_Scale = 35.0e3

		double dHHScale = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_AB_Scale");

		pgk->dHHScale = dHHScale;

		//- get HH_AB_Mult = 0.0

		double dHHMult = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_AB_Mult");

		pgk->dHHMult = dHHMult;

		//- get HH_AB_Factor_Flag = -1.0

		double dHHFactorFlag = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_AB_Factor_Flag");

		int iHHFactorFlag = dHHFactorFlag;

		pgk->iHHFactorFlag = iHHFactorFlag;

		//- get HH_AB_Add = 0.0

		double dHHAdd = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_AB_Add");

		pgk->dHHAdd = dHHAdd;

		//- get HH_AB_Offset_E = 5.0e-3

		double dHHOffsetE = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_AB_Offset_E");

		pgk->dHHOffsetE = dHHOffsetE;

		//- get HH_AB_Tau = -10.0e-3

		double dHHTau = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_AB_Tau");

		pgk->dHHTau = dHHTau;

		if( dHHScale == FLT_MAX )
		{

		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"HH_AB_Scale");

		    iResult = TSTR_PROCESSOR_ABORT;


		}
		if( dHHMult == FLT_MAX )
		{


		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"HH_AB_Mult");

		    iResult = TSTR_PROCESSOR_ABORT;


		}
		if( dHHFactorFlag == FLT_MAX )
		{


		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"HH_AB_Factor_Flag");

		    iResult = TSTR_PROCESSOR_ABORT;


		}
		if( dHHAdd == FLT_MAX )
		{

		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"HH_AB_Add");

		    iResult = TSTR_PROCESSOR_ABORT;

		}
		if( dHHOffsetE == FLT_MAX )
		{

		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"HH_AB_Offset_E");

		    iResult = TSTR_PROCESSOR_ABORT;


		}
		if( dHHTau == FLT_MAX )
		{

		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"HH_AB_Tau");

		    iResult = TSTR_PROCESSOR_ABORT;
		}
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ptstr->ppist);
		    
	    MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,"Unknown Object Type.");

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- if activator

    else if (instanceof_concentration_gate_kinetic(phsle))
    {
	//- if forward

	/// \note 5: tau / base, conc

        /// \note or

	/// \note 5: forward, conc
	/// \note 6: backward, conc

	if (pmcd->iStatus == 5
	    || pmcd->iStatus == 6)
	{
	    //- initialize table index

	    pcac->pac.ca.iTable = -1;

	    double dHasTable = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_Has_Table");

	    int iHasTable = 0;

	    if (dHasTable != FLT_MAX)
	    {
		iHasTable = dHasTable;
	    }

	    if (iHasTable)
	    {
/* 		printf("warning: iHasTable has value %i\n", iHasTable); */

	    }

	    if (pcac->pac.ca.htg.iEntries != INT_MAX)
	    {
/* 		if (pcac->pac.ca.htg.hi.dStart != FLT_MAX */
/* 		    && pcac->pac.ca.htg.hi.dEnd != FLT_MAX */
/* 		    && pcac->pac.ca.htg.hi.dStep != FLT_MAX) */
		if (1)
		{
		    double *pdTable = (double *)calloc(pcac->pac.ca.htg.iEntries, sizeof(*pdTable));

		    int i;

		    for (i = 0 ; i < pcac->pac.ca.htg.iEntries ; i++)
		    {
			char pcTable[50];

			sprintf(pcTable, "table[%i]", i);

			double d = SymbolParameterResolveValue(phsle, ptstr->ppist, pcTable);

			if (d != FLT_MAX)
			{
			    pdTable[i] = d;
			}
			else
			{
			    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

			    iResult = TSTR_PROCESSOR_ABORT;

			    break;
			}
		    }

		    /// \todo would prefer to have all tests for pmcd->iStatus at the same place

		    if (pmcd->iStatus == 5)
		    {
			pcac->pac.ca.htg.pdA = pdTable;
		    }
		    else
		    {
			pcac->pac.ca.htg.pdB = pdTable;
		    }
		}
		else
		{
		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

		    iResult = TSTR_PROCESSOR_ABORT;
		}
	    }

	    //- else parameterized

	    else
	    {
		//- basal level, A in EDS1994

		double dBasalLevel = SymbolParameterResolveValue(phsle, ptstr->ppist, "Base");

		pcac->pac.ca.parameters.dBasalLevel = dBasalLevel;

		//- time constant, B in EDS1994

		double dTau = SymbolParameterResolveValue(phsle, ptstr->ppist, "Tau");

		pcac->pac.ca.parameters.dTau = dTau;

		if (dBasalLevel == FLT_MAX)
		{
		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"Base");

		    iResult = TSTR_PROCESSOR_ABORT;
		}



		if ( dTau == FLT_MAX )
		{

		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"Tau");

		    iResult = TSTR_PROCESSOR_ABORT;		  

		}

	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, 
				       ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,"Unknown Object Type.");

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- otherwise

    else
    {
	//- an error

	MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE,ptstr->ppist);

	MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,
			   "Unknown Object Type, not a concentration gate.");
    }

    //- if no error

    if (pmcd->iStatus > 0)
    {
	//- increment the status to indicate what component we have processed

	pmcd->iStatus++;

	/// \note status can go up to 6 for tau-base concentration gates
	/// \note and to 7 for tabulated concentration gates

	if (pmcd->iStatus == 7)
	{
	    pmcd->iStatus = 1;
	}
    }

    //- return result

    return(iResult);
}


static
int
solver_channel_activation_inactivation_processor(struct TreespaceTraversal *ptstr, void *pvUserdata)
{
    //- set default result : ok

    int iResult = TSTR_PROCESSOR_SUCCESS;

    //- get actual symbol

    struct symtab_HSolveListElement *phsle = (struct symtab_HSolveListElement *)TstrGetActual(ptstr);

    //- get user data

    struct MathComponentData * pmcd = (struct MathComponentData *)pvUserdata;

    //- get current math component

    struct MathComponent * pmc = pmcd->pmc;

    struct ChannelActInact * pcai = (struct ChannelActInact *)pmc;

    //- if conceptual gate

    if (instanceof_h_h_gate(phsle))
    {
	if (pmcd->iStatus == 1
	    || pmcd->iStatus == 4)
	{
	    struct PoweredGateConcept * ppgc
		= pmcd->iStatus == 1
		? &pcai->pgcActivation
		: &pcai->pgcInactivation;

	    //- get power

	    double dPower = SymbolParameterResolveValue(phsle, ptstr->ppist, "POWER");

	    int iPower = dPower;

	    ppgc->iPower = iPower;

	    //- get initial state

	    double dInitActivation = SymbolParameterResolveValue(phsle, ptstr->ppist, "state_init");

	    ppgc->gc.dInitActivation = dInitActivation;

	    if (dPower == FLT_MAX)
	    {

		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					   ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"POWER");

		iResult = TSTR_PROCESSOR_ABORT;

	    }


	    if(dInitActivation == FLT_MAX)
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					   ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"state_init");

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    double dEntries = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_NUMBER_OF_TABLE_ENTRIES");

	    if (dEntries != FLT_MAX)
	    {
		ppgc->gc.htg.iEntries = dEntries;

		ppgc->gc.htg.hi.dStart = pmcd->pheccer->ho.dIntervalStart;
		ppgc->gc.htg.hi.dEnd = pmcd->pheccer->ho.dIntervalEnd;
		ppgc->gc.htg.hi.dStep = (ppgc->gc.htg.hi.dEnd - ppgc->gc.htg.hi.dStart) / ppgc->gc.htg.iEntries;;

/* 		ppgc->gc.htg.hi.dStart = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_TABLE_START"); */
/* 		ppgc->gc.htg.hi.dEnd = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_TABLE_END"); */
/* 		ppgc->gc.htg.hi.dStep = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_TABLE_STEP"); */
	    }
	    else
	    {
		ppgc->gc.htg.iEntries = INT_MAX;
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,"Unknown Object Type, not an HH gate.");

	    iResult = TSTR_PROCESSOR_ABORT;

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- if gate kinetic

    else if (instanceof_gate_kinetic(phsle))
    {
	/// \note 2: forward, act
	/// \note 3: backward, act
	/// \note 5: forward, inact
	/// \note 6: backward, inact

	if (pmcd->iStatus == 2
	    || pmcd->iStatus == 3
	    || pmcd->iStatus == 5
	    || pmcd->iStatus == 6)
	{
	    struct PoweredGateConcept * ppgc
		= (pmcd->iStatus == 2
		   || pmcd->iStatus == 3
		   ? &pcai->pgcActivation
		   : &pcai->pgcInactivation);

	    struct GateKinetic *pgk
		= (pmcd->iStatus == 2
		   || pmcd->iStatus == 5
		   ? &ppgc->gc.parameters.gkA
		   : &ppgc->gc.parameters.gkB);

	    //- initialize table index

	    ppgc->gc.iTable = -1;

	    double dHasTable = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_Has_Table");

	    int iHasTable = 0;

	    if (dHasTable != FLT_MAX)
	    {
		iHasTable = dHasTable;
	    }

	    if (iHasTable)
	    {
/* 		printf("warning: iHasTable has value %i\n", iHasTable); */

	    }

	    if (ppgc->gc.htg.iEntries != INT_MAX)
	    {
/* 		if (ppgc->gc.htg.hi.dStart != FLT_MAX */
/* 		    && ppgc->gc.htg.hi.dEnd != FLT_MAX */
/* 		    && ppgc->gc.htg.hi.dStep != FLT_MAX) */
		if (1)
		{
		    double *pdTable = (double *)calloc(ppgc->gc.htg.iEntries, sizeof(*pdTable));

		    int i;

		    for (i = 0 ; i < ppgc->gc.htg.iEntries ; i++)
		    {
			char pcTable[50];

			sprintf(pcTable, "table[%i]", i);

			double d = SymbolParameterResolveValue(phsle, ptstr->ppist, pcTable);

			if (d != FLT_MAX)
			{
			    pdTable[i] = d;
			}
			else
			{
			    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
						       ptstr->ppist);

			    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,pcTable);

			    iResult = TSTR_PROCESSOR_ABORT;

			    break;
			}
		    }

		    /// \todo would prefer to have all tests for pmcd->iStatus at the same place

		    if (pmcd->iStatus == 2
			|| pmcd->iStatus == 5)
		    {   /// \todo store number of entries in the table
			ppgc->gc.htg.pdA = pdTable;
		    }
		    else
		    {   /// \todo compare number of entries with stored number
			ppgc->gc.htg.pdB = pdTable;
		    }
		}
		else
		{
		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,
				       "HH_NUMBER_OF_TABLE_ENTRIES");

		    iResult = TSTR_PROCESSOR_ABORT;
		}
	    }

	    //- else parameterized

	    else
	    {
		//- get HH_AB_Scale = 35.0e3

		double dHHScale = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_AB_Scale");

		pgk->dHHScale = dHHScale;

		//- get HH_AB_Mult = 0.0

		double dHHMult = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_AB_Mult");

		pgk->dHHMult = dHHMult;

		//- get HH_AB_FactorFlag = -1.0

		double dHHFactorFlag = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_AB_Factor_Flag");

		int iHHFactorFlag = dHHFactorFlag;

		pgk->iHHFactorFlag = iHHFactorFlag;

		//- get HH_AB_Add = 0.0

		double dHHAdd = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_AB_Add");

		pgk->dHHAdd = dHHAdd;

		//- get HH_AB_Offset_E = 5.0e-3

		double dHHOffsetE = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_AB_Offset_E");

		pgk->dHHOffsetE = dHHOffsetE;

		//- get HH_AB_Tau = -10.0e-3

		double dHHTau = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_AB_Tau");

		pgk->dHHTau = dHHTau;



		if (dHHScale == FLT_MAX)
		{

		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"HH_AB_Scale");

		    iResult = TSTR_PROCESSOR_ABORT;

		}

		if(dHHMult == FLT_MAX)
		{

		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"HH_AB_Mult");

		    iResult = TSTR_PROCESSOR_ABORT;

		}

		    
		if(dHHFactorFlag == FLT_MAX)
		{


		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"HH_AB_Factor_Flag");

		    iResult = TSTR_PROCESSOR_ABORT;


		}


		if(dHHAdd == FLT_MAX)
		{


		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"HH_AB_Add");

		    iResult = TSTR_PROCESSOR_ABORT;


		}
		    

		if(dHHOffsetE == FLT_MAX)
		{


		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"HH_AB_Offset_E");

		    iResult = TSTR_PROCESSOR_ABORT;


		}


		if(dHHTau == FLT_MAX)
		{
		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"HH_AB_Tau");

		    iResult = TSTR_PROCESSOR_ABORT;
		}
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,
			       "Unknown Object Type, not a gate kinetic.");

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- otherwise

    else
    {
	//- an error

	MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ptstr->ppist);

	MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,
			   "Unknown Object Type, not a gate kinetic.");

	iResult = TSTR_PROCESSOR_ABORT;
    }

    //- if no error

    if (pmcd->iStatus > 0)
    {
	//- increment the status to indicate what component we have processed

	pmcd->iStatus++;

	if (pmcd->iStatus == 7)
	{
	    pmcd->iStatus = 1;
	}
    }

    //- return result

    return(iResult);
}


static
int
solver_channel_persistent_steadystate_dualtau_processor(struct TreespaceTraversal *ptstr, void *pvUserdata)
{
    //- set default result : ok

    int iResult = TSTR_PROCESSOR_SUCCESS;

    //- get actual symbol

    struct symtab_HSolveListElement *phsle = (struct symtab_HSolveListElement *)TstrGetActual(ptstr);

    //- get user data

    struct MathComponentData * pmcd = (struct MathComponentData *)pvUserdata;

    //- get current math component

    struct MathComponent * pmc = pmcd->pmc;

    struct ChannelPersistentSteadyStateDualTau * pcpsdt
	= (struct ChannelPersistentSteadyStateDualTau *)pmc;

    //- if conceptual gate

    if (instanceof_h_h_gate(phsle))
    {
	if (pmcd->iStatus == 1)
	{
	    //- initialize table pointers

	    pcpsdt->iFirstTable = -1;
	    pcpsdt->iSecondTable = -1;

	    //- get powers

	    double dFirstPower = SymbolParameterResolveValue(phsle, ptstr->ppist, "iFirstPower");
	    int iFirstPower = dFirstPower;
	    pcpsdt->iFirstPower = iFirstPower;

	    double dSecondPower = SymbolParameterResolveValue(phsle, ptstr->ppist, "iSecondPower");
	    int iSecondPower = dSecondPower;
	    pcpsdt->iSecondPower = iSecondPower;

	    //- get initial states

	    double dFirstInitActivation = SymbolParameterResolveValue(phsle, ptstr->ppist, "dFirstInitActivation");
	    pcpsdt->dFirstInitActivation = dFirstInitActivation;

	    double dSecondInitActivation = SymbolParameterResolveValue(phsle, ptstr->ppist, "dSecondInitActivation");
	    pcpsdt->dSecondInitActivation = dSecondInitActivation;

	    //- get steady states

	    double dFirstSteadyState = SymbolParameterResolveValue(phsle, ptstr->ppist, "dFirstSteadyState");
	    pcpsdt->parameters1.dSteadyState = dFirstSteadyState;

	    double dSecondSteadyState = SymbolParameterResolveValue(phsle, ptstr->ppist, "dSecondSteadyState");
	    pcpsdt->parameters2.dSteadyState = dSecondSteadyState;



	    if (dFirstPower == FLT_MAX)
	    {

		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					   ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"iFirstPower");

		iResult = TSTR_PROCESSOR_ABORT;

	    }

	    if(dFirstInitActivation == FLT_MAX)
	    {

		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					   ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"dFirstInitActivation");

		iResult = TSTR_PROCESSOR_ABORT;

	    }

		

	    if(dFirstSteadyState == FLT_MAX)
	    {


		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					   ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"dFirstSteadyState");

		iResult = TSTR_PROCESSOR_ABORT;

	    }
	       

	    if(dSecondPower == FLT_MAX)
	    {

		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					   ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"iSecondPower");

		iResult = TSTR_PROCESSOR_ABORT;

	    }
	     

	    if(dSecondInitActivation == FLT_MAX)
	    {

		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					   ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"dSecondInitActivation");

		iResult = TSTR_PROCESSOR_ABORT;

	    }
	       

	    if(dSecondSteadyState == FLT_MAX)
	    {

		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					   ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"dSecondSteadyState");

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,
			       "Unknown Object Type, not gate kinetic.");

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- if gate kinetic

    else if (instanceof_gate_kinetic(phsle))
    {
	/// \note 2: tau 1
	/// \note 3: tau 2

	if (pmcd->iStatus == 2
	    || pmcd->iStatus == 3)
	{
	    struct dualtaucomponent * pdtc
		= (pmcd->iStatus == 2
		   ? &pcpsdt->parameters1.tau
		   : &pcpsdt->parameters2.tau);

	    double dHasTable = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_Has_Table");

	    int iHasTable = 0;

	    if (dHasTable != FLT_MAX)
	    {
		iHasTable = dHasTable;
	    }

	    if (iHasTable)
	    {
		printf("warning: iHasTable has value %i\n", iHasTable);

	    }
	    else
	    {
		//- get Multiplier = 35.0e3

		double dMultiplier = SymbolParameterResolveValue(phsle, ptstr->ppist, "dMultiplier");

		pdtc->dMultiplier = dMultiplier;

		//- get DeNominatorOffset = 0.0

		double dDeNominatorOffset = SymbolParameterResolveValue(phsle, ptstr->ppist, "dDeNominatorOffset");

		pdtc->dDeNominatorOffset = dDeNominatorOffset;

		//- get MembraneOffset = 5.0e-3

		double dMembraneOffset = SymbolParameterResolveValue(phsle, ptstr->ppist, "dMembraneOffset");

		pdtc->dMembraneOffset = dMembraneOffset;

		//- get TauDenormalizer = -10.0e-3

		double dTauDenormalizer = SymbolParameterResolveValue(phsle, ptstr->ppist, "dTauDenormalizer");

		pdtc->dTauDenormalizer = dTauDenormalizer;


		if (dMultiplier == FLT_MAX)
		{

		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"dMultiplier");

		    iResult = TSTR_PROCESSOR_ABORT;

		}

		 

		if(dDeNominatorOffset == FLT_MAX)
		{

		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"dDeNominatorOffset");

		    iResult = TSTR_PROCESSOR_ABORT;

		}
		    

		if(dMembraneOffset == FLT_MAX)
		{

		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"dMembraneOffset");

		    iResult = TSTR_PROCESSOR_ABORT;

		}




		if(dTauDenormalizer == FLT_MAX)
		{
		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"dTauDenormalizer");

		    iResult = TSTR_PROCESSOR_ABORT;
		}
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,
			       "Unknown Object Type, not a gate kinetic.");

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- otherwise

    else
    {
	//- an error

	MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ptstr->ppist);

	MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,"Unknown Object Type, not a gate kinetic.");

	iResult = TSTR_PROCESSOR_ABORT;
    }

    //- if no error

    if (pmcd->iStatus > 0)
    {
	//- increment the status to indicate what component we have processed

	pmcd->iStatus++;

	if (pmcd->iStatus == 4)
	{
	    pmcd->iStatus = 1;
	}
    }

    //- return result

    return(iResult);
}


static
int
solver_channel_persistent_steadystate_tau_processor(struct TreespaceTraversal *ptstr, void *pvUserdata)
{
    //- set default result : ok

    int iResult = TSTR_PROCESSOR_SUCCESS;

    //- get actual symbol

    struct symtab_HSolveListElement *phsle = (struct symtab_HSolveListElement *)TstrGetActual(ptstr);

    //- get user data

    struct MathComponentData * pmcd = (struct MathComponentData *)pvUserdata;

    //- get current math component

    struct MathComponent * pmc = pmcd->pmc;

    struct ChannelPersistentSteadyStateTau * pcpst
	= (struct ChannelPersistentSteadyStateTau *)pmc;

    //- if conceptual gate

    if (instanceof_h_h_gate(phsle))
    {
	if (pmcd->iStatus == 1)
	{
	    //- initialize table pointer

	    pcpst->iTable = -1;

	    //- get power

	    double dPower = SymbolParameterResolveValue(phsle, ptstr->ppist, "POWER");
	    int iPower = dPower;
	    pcpst->iPower = iPower;

	    //- get initial states

	    double dInitActivation = SymbolParameterResolveValue(phsle, ptstr->ppist, "state_init");
	    pcpst->dInitActivation = dInitActivation;

	    if (dPower == FLT_MAX)
	    {

		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					   ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"POWER");

		iResult = TSTR_PROCESSOR_ABORT;

	    }

	    if(dInitActivation == FLT_MAX)
	    {

		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					   ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"state_init");

		iResult = TSTR_PROCESSOR_ABORT;

	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,"Unknown Object Type, not an HH gate.");

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- if gate kinetic

    else if (instanceof_gate_kinetic(phsle))
    {
	if (pmcd->iStatus == 2)
	{
	    struct single_steady_state * pss = &pcpst->parameters.ss;

	    double dHasTable = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_Has_Table");

	    int iHasTable = 0;

	    if (dHasTable != FLT_MAX)
	    {
		iHasTable = dHasTable;
	    }

	    if (iHasTable)
	    {
		printf("warning: iHasTable has value %i\n", iHasTable);

	    }
	    else
	    {
		//- get Nominator

		double dNominator = SymbolParameterResolveValue(phsle, ptstr->ppist, "dNominator");

		pss->dNominator = dNominator;

		//- get Multiplier1

		double dMultiplier1 = SymbolParameterResolveValue(phsle, ptstr->ppist, "dMultiplier1");

		pss->dMultiplier1 = dMultiplier1;

		//- get MembraneOffset1

		double dMembraneOffset1 = SymbolParameterResolveValue(phsle, ptstr->ppist, "dMembraneOffset1");

		pss->dMembraneOffset1 = dMembraneOffset1;

		//- get TauDenormalizer1

		double dTauDenormalizer1 = SymbolParameterResolveValue(phsle, ptstr->ppist, "dTauDenormalizer1");

		pss->dTauDenormalizer1 = dTauDenormalizer1;

		//- get Multiplier2

		double dMultiplier2 = SymbolParameterResolveValue(phsle, ptstr->ppist, "dMultiplier2");

		pss->dMultiplier2 = dMultiplier2;

		//- get MembraneOffset2

		double dMembraneOffset2 = SymbolParameterResolveValue(phsle, ptstr->ppist, "dMembraneOffset2");

		pss->dMembraneOffset2 = dMembraneOffset2;

		//- get TauDenormalizer2

		double dTauDenormalizer2 = SymbolParameterResolveValue(phsle, ptstr->ppist, "dTauDenormalizer2");

		pss->dTauDenormalizer2 = dTauDenormalizer2;

		if (dNominator == FLT_MAX)
		{

		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"dNominator");

		    iResult = TSTR_PROCESSOR_ABORT;

		}
		  

		if(dMultiplier1 == FLT_MAX)
		{

		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"dMultiplier1");

		    iResult = TSTR_PROCESSOR_ABORT;

		}
		    

		if(dMembraneOffset1 == FLT_MAX)
		{

		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"dMembraneOffset1");

		    iResult = TSTR_PROCESSOR_ABORT;

		}
		   

		if(dTauDenormalizer1 == FLT_MAX)
		{

		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"dTauDenormalizer1");

		    iResult = TSTR_PROCESSOR_ABORT;

		}

		
		if(dMultiplier2 == FLT_MAX)
		{

		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"dMultiplier2");

		    iResult = TSTR_PROCESSOR_ABORT;

		}
		    


		if(dMembraneOffset2 == FLT_MAX)
		{

		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"dMembraneOffset2");

		    iResult = TSTR_PROCESSOR_ABORT;

		}
		    

		if(dTauDenormalizer2 == FLT_MAX)
		{
		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"dTauDenormalizer2");

		    iResult = TSTR_PROCESSOR_ABORT;
		}
	    }
	}
	else if (pmcd->iStatus == 3)
	{
	    struct single_time_constant * ptc = &pcpst->parameters.tc;

	    double dHasTable = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_Has_Table");

	    int iHasTable = 0;

	    if (dHasTable != FLT_MAX)
	    {
		iHasTable = dHasTable;
	    }

	    if (iHasTable)
	    {
		printf("warning: iHasTable has value %i\n", iHasTable);

	    }
	    else
	    {
		//- get Nominator

		double dNominator = SymbolParameterResolveValue(phsle, ptstr->ppist, "dNominator");

		ptc->dNominator = dNominator;

		//- get DeNominatorOffset

		double dDeNominatorOffset = SymbolParameterResolveValue(phsle, ptstr->ppist, "dDeNominatorOffset");

		ptc->dDeNominatorOffset = dDeNominatorOffset;

		//- get MembraneOffset

		double dMembraneOffset = SymbolParameterResolveValue(phsle, ptstr->ppist, "dMembraneOffset");

		ptc->dMembraneOffset = dMembraneOffset;

		//- get TauDenormalizer

		double dTauDenormalizer = SymbolParameterResolveValue(phsle, ptstr->ppist, "dTauDenormalizer");

		ptc->dTauDenormalizer = dTauDenormalizer;

		if (dNominator == FLT_MAX)
		{


		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"dTauDenormalizer");

		    iResult = TSTR_PROCESSOR_ABORT;
		}

		
		  

		if(dDeNominatorOffset == FLT_MAX)
		{

		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"dDeNominatorOffset");

		    iResult = TSTR_PROCESSOR_ABORT;
		}


		

		 


		if(dMembraneOffset == FLT_MAX)
		{


		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"dMembraneOffset");

		    iResult = TSTR_PROCESSOR_ABORT;


		}


		if(dTauDenormalizer == FLT_MAX)
		{
		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"dTauDenormalizer");

		    iResult = TSTR_PROCESSOR_ABORT;
		}
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,
			       "Unknown Object Type, not a gate kinetic.");

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- otherwise

    else
    {
	//- an error

	MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ptstr->ppist);

	MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,"Unknown Object Type, not a gate kinetic.");

	iResult = TSTR_PROCESSOR_ABORT;
    }

    //- if no error

    if (pmcd->iStatus > 0)
    {
	//- increment the status to indicate what component we have processed

	pmcd->iStatus++;

	if (pmcd->iStatus == 4)
	{
	    pmcd->iStatus = 1;
	}
    }

    //- return result

    return(iResult);
}


static
int
solver_channel_springmass_processor(struct TreespaceTraversal *ptstr, void *pvUserdata)
{
    //- set default result : ok

    int iResult = TSTR_PROCESSOR_SUCCESS;

    //- get actual symbol

    struct symtab_HSolveListElement *phsle = (struct symtab_HSolveListElement *)TstrGetActual(ptstr);

    //- get user data

    struct MathComponentData * pmcd = (struct MathComponentData *)pvUserdata;

    //- get current math component

    struct MathComponent * pmc = pmcd->pmc;

    struct ChannelSpringMass * pcsm
	= (struct ChannelSpringMass *)pmc;

    //- if domain mapper

    if (instanceof_attachment(phsle))
    {
	if (pmcd->iStatus == 1
	    || pmcd->iStatus == 2)
	{
	    //- get filename of event list

	    /// \todo should use ParameterResolveSymbol()

	    struct symtab_Parameters *pparEvents
		= SymbolFindParameter(phsle, ptstr->ppist, "EVENT_FILENAME");

	    if (pparEvents)
	    {
		char *pcEvents = ParameterGetString(pparEvents);

		/// \todo hardcoded connection with the neurospaces model container.
		/// \todo filename qualification must come in a separate software component.

		char *pcEventsQualified
		    = NeurospacesQualifyFilename(pmcd->pheccer->pts->ptsd->pneuro, pcEvents);

		if (pcEvents && !pcEventsQualified)
		{
		    MathComponentDataStatusSet(pmcd, STATUS_UNQUALIFIABLE_FILENAME, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNQUALIFIABLE_FILENAME,pcEvents);


		    iResult = TSTR_PROCESSOR_ABORT;
		}

		pcsm->pcEventTimes = pcEventsQualified;
	    }

	    /// \todo not sure yet about connectivity, needs a separate pass
	    /// \todo as in the genesis/hsolve/neurospaces implementation.

	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,
			       "Unknown Object Type, invalid file attachment.");

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- if equation

    else if (instanceof_equation_exponential(phsle))
    {
	if (pmcd->iStatus == 1
	    || pmcd->iStatus == 2)
	{
	    //- initialize table pointer

	    pcsm->iTable = -1;

	    //- get first time constants

	    double dTau1 = SymbolParameterResolveValue(phsle, ptstr->ppist, "TAU1");
	    pcsm->parameters.dTau1 = dTau1;

	    double dTau2 = SymbolParameterResolveValue(phsle, ptstr->ppist, "TAU2");
	    pcsm->parameters.dTau2 = dTau2;

	    /// \todo perhaps if only tau1 is defined, I should make tau2
	    /// \todo equal to tau1 and treat it as a single exponential

	    if (dTau1 == FLT_MAX)
	    {

		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"Tau1");

		iResult = TSTR_PROCESSOR_ABORT;

	    }


	    if(dTau2 == FLT_MAX)
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"Tau2");

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    //- get initial states

	    double dInitX = SymbolParameterResolveValue(phsle, ptstr->ppist, "state_init_x");

	    if (dInitX == FLT_MAX)
	    {
		pcsm->dInitX = 0;
	    }
	    else
	    {
		pcsm->dInitX = dInitX;
	    }

	    double dInitY = SymbolParameterResolveValue(phsle, ptstr->ppist, "state_init_y");

	    if (dInitY == FLT_MAX)
	    {
		pcsm->dInitY = 0;
	    }
	    else
	    {
		pcsm->dInitY = dInitY;
	    }

	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,"Invalid Type, Unknown Equation.");

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    /// \todo have to do attachment points

    //- otherwise

    else
    {
	//- an error

	MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ptstr->ppist);

	MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,"Invalid Type, Unknown Equation.");

	iResult = TSTR_PROCESSOR_ABORT;
    }

    //- if no error

    if (pmcd->iStatus > 0)
    {
	//- increment the status to indicate what component we have processed

	pmcd->iStatus++;

	if (pmcd->iStatus == 2)
	{
	    pmcd->iStatus = 1;
	}
    }

    //- return result

    return(iResult);
}


static
int
solver_channel_steadystate_steppedtau_processor(struct TreespaceTraversal *ptstr, void *pvUserdata)
{
    //- set default result : ok

    int iResult = TSTR_PROCESSOR_SUCCESS;

    //- get actual symbol

    struct symtab_HSolveListElement *phsle = (struct symtab_HSolveListElement *)TstrGetActual(ptstr);

    //- get user data

    struct MathComponentData * pmcd = (struct MathComponentData *)pvUserdata;

    //- get current math component

    struct MathComponent * pmc = pmcd->pmc;

    struct ChannelSteadyStateSteppedTau * pcpsdt
	= (struct ChannelSteadyStateSteppedTau *)pmc;

    //- if conceptual gate

    if (instanceof_h_h_gate(phsle))
    {
	if (pmcd->iStatus == 1)
	{
	    //- initialize table pointer

	    pcpsdt->iFirstTable = -1;

	    //- get power

	    double dFirstPower = SymbolParameterResolveValue(phsle, ptstr->ppist, "POWER");
	    int iFirstPower = dFirstPower;
	    pcpsdt->iFirstPower = iFirstPower;

	    //- get initial state

	    double dFirstInitActivation = SymbolParameterResolveValue(phsle, ptstr->ppist, "state_init");
	    pcpsdt->dFirstInitActivation = dFirstInitActivation;

	    if (dFirstPower == FLT_MAX)
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					   ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"POWER");

		iResult = TSTR_PROCESSOR_ABORT;
	    }


	    if( dFirstInitActivation == FLT_MAX)
	    {

		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					   ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"state_init");

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else if (pmcd->iStatus == 8)
	{
	    //- initialize table pointer

	    pcpsdt->iSecondTable = -1;

	    //- get power

	    double dSecondPower = SymbolParameterResolveValue(phsle, ptstr->ppist, "POWER");
	    int iSecondPower = dSecondPower;
	    pcpsdt->iSecondPower = iSecondPower;

	    //- get initial state

	    double dSecondInitActivation = SymbolParameterResolveValue(phsle, ptstr->ppist, "state_init");
	    pcpsdt->dSecondInitActivation = dSecondInitActivation;

	    if (dSecondPower == FLT_MAX)
	    {

		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					   ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"POWER (dSecondPower)");

		iResult = TSTR_PROCESSOR_ABORT;

	    }

	    

	    if(dSecondInitActivation == FLT_MAX)
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					   ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,
				   "state_init (dSecondInitActivation)");

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,"Unknown Object Type, not an HH gate.");

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- if gate kinetic

    else if (instanceof_gate_kinetic(phsle))
    {
	if (pmcd->iStatus == 2
	    || pmcd->iStatus == 5)
	{
	}
	else if (pmcd->iStatus == 3
		 || pmcd->iStatus == 4
		 || pmcd->iStatus == 6
		 || pmcd->iStatus == 7)
	{
	    struct DualSteadyStateParameters * pdtc
		= &pcpsdt->ss_parameters;

	    struct dual_steadystate_kinetic * pdsk
		= ((pmcd->iStatus == 3
		    || pmcd->iStatus == 4)
		   ? &pdtc->first
		   : &pdtc->second);

	    if (pmcd->iStatus == 3
		|| pmcd->iStatus == 6)
	    {
		struct dual_steadystate_kinetic_part_a * pa = &pdsk->a;

		double dHasTable = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_Has_Table");

		int iHasTable = 0;

		if (dHasTable != FLT_MAX)
		{
		    iHasTable = dHasTable;
		}

		if (iHasTable)
		{
		    printf("warning: iHasTable has value %i\n", iHasTable);

		}
		else
		{
		    //- get Multiplier

		    double dMultiplier = SymbolParameterResolveValue(phsle, ptstr->ppist, "Multiplier");

		    pa->dMultiplier = dMultiplier;

		    //- get MembraneDependenceOffset

		    double dMembraneDependenceOffset = SymbolParameterResolveValue(phsle, ptstr->ppist, "MembraneDependenceOffset");

		    pa->dMembraneDependenceOffset = dMembraneDependenceOffset;

		    //- get dDeNominatorOffset

		    double dDeNominatorOffset = SymbolParameterResolveValue(phsle, ptstr->ppist, "DeNominatorOffset");

		    pa->dDeNominatorOffset = dDeNominatorOffset;

		    //- get MembraneOffset

		    double dMembraneOffset = SymbolParameterResolveValue(phsle, ptstr->ppist, "MembraneOffset");

		    pa->dMembraneOffset = dMembraneOffset;

		    //- get TauDenormalizer

		    double dTauDenormalizer = SymbolParameterResolveValue(phsle, ptstr->ppist, "TauDenormalizer");

		    pa->dTauDenormalizer = dTauDenormalizer;

		    if (dMultiplier == FLT_MAX)
		    {

			MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
						   ptstr->ppist);

			MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"Multiplier");

			iResult = TSTR_PROCESSOR_ABORT;

		    }


		    if(dMembraneDependenceOffset == FLT_MAX)
		    {

			MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
						   ptstr->ppist);

			MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,
					   "MembraneDependenceOffset");

			iResult = TSTR_PROCESSOR_ABORT;

		    }


		    if(dDeNominatorOffset == FLT_MAX)
		    {

			MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
						   ptstr->ppist);

			MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,
					   "DeNominatorOffset");

			iResult = TSTR_PROCESSOR_ABORT;

		    }

		    if(dMembraneOffset == FLT_MAX)
		    {

			MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
						   ptstr->ppist);

			MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"MembraneOffset");
			

			iResult = TSTR_PROCESSOR_ABORT;		      

		    }

		    if(dTauDenormalizer == FLT_MAX)
		    {
			MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
						   ptstr->ppist);

			MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"TauDenormalizer");

			iResult = TSTR_PROCESSOR_ABORT;
		    }
		}
	    }
	    else
	    {
		struct dual_steadystate_kinetic_part_b * pb = &pdsk->b;

		double dHasTable = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_Has_Table");

		int iHasTable = 0;

		if (dHasTable != FLT_MAX)
		{
		    iHasTable = dHasTable;
		}

		if (iHasTable)
		{
		    printf("warning: iHasTable has value %i\n", iHasTable);

		}
		else
		{
		    //- get Multiplier

		    double dMultiplier = SymbolParameterResolveValue(phsle, ptstr->ppist, "Multiplier");

		    pb->dMultiplier = dMultiplier;

		    //- get MembraneDependenceOffset

		    double dMembraneDependenceOffset = SymbolParameterResolveValue(phsle, ptstr->ppist, "MembraneDependenceOffset");

		    pb->dMembraneDependenceOffset = dMembraneDependenceOffset;

		    //- get TauDenormalizer

		    double dTauDenormalizer = SymbolParameterResolveValue(phsle, ptstr->ppist, "TauDenormalizer");

		    pb->dTauDenormalizer = dTauDenormalizer;

		    if (dMultiplier == FLT_MAX)
		    {
			MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
						   ptstr->ppist);

			MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"Multiplier");

			iResult = TSTR_PROCESSOR_ABORT;
		    }

		    

		    if(dMembraneDependenceOffset == FLT_MAX)
		    {

			MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
						   ptstr->ppist);

			MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,
					   "MembraneDependenceOffset");

			iResult = TSTR_PROCESSOR_ABORT;
		    }


		    if(dTauDenormalizer == FLT_MAX)
		    {
			MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
						   ptstr->ppist);

			MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"TauDenormalizer");

			iResult = TSTR_PROCESSOR_ABORT;
		    }
		}
	    }
	}
	else if (pmcd->iStatus == 9)
	{
	    struct SteppedTimeConstantParameters * pdtc
		= &pcpsdt->tc_parameters;

	    double dHasTable = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_Has_Table");

	    int iHasTable = 0;

	    if (dHasTable != FLT_MAX)
	    {
		iHasTable = dHasTable;
	    }

	    if (iHasTable)
	    {
		printf("warning: iHasTable has value %i\n", iHasTable);

	    }
	    else
	    {
		//- get threshold

		double dThreshold = SymbolParameterResolveValue(phsle, ptstr->ppist, "Threshold");

		pdtc->a.dThreshold = dThreshold;

		//- get LowTarget

		double dLowTarget = SymbolParameterResolveValue(phsle, ptstr->ppist, "LowTarget");

		pdtc->a.dLowTarget = dLowTarget;

		//- get HighTarget

		double dHighTarget = SymbolParameterResolveValue(phsle, ptstr->ppist, "HighTarget");

		pdtc->a.dHighTarget = dHighTarget;

		if (dThreshold == FLT_MAX)
		{
		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"Threshold");

		    iResult = TSTR_PROCESSOR_ABORT;
		}


		if( dLowTarget == FLT_MAX )
		{
		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"LowTarget");

		    iResult = TSTR_PROCESSOR_ABORT;
		}


		if( dHighTarget == FLT_MAX)
		{
		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"HighTarget");

		    iResult = TSTR_PROCESSOR_ABORT;
		}
	    }
	}
	else if (pmcd->iStatus == 10)
	{
	    struct SteppedTimeConstantParameters * pdtc
		= &pcpsdt->tc_parameters;

	    double dHasTable = SymbolParameterResolveValue(phsle, ptstr->ppist, "HH_Has_Table");

	    int iHasTable = 0;

	    if (dHasTable != FLT_MAX)
	    {
		iHasTable = dHasTable;
	    }

	    if (iHasTable)
	    {
		printf("warning: iHasTable has value %i\n", iHasTable);

	    }
	    else
	    {
		//- get DeNominatorOffset

		double dDeNominatorOffset = SymbolParameterResolveValue(phsle, ptstr->ppist, "DeNominatorOffset");

		pdtc->b.dDeNominatorOffset = dDeNominatorOffset;

		//- get MembraneOffset

		double dMembraneOffset = SymbolParameterResolveValue(phsle, ptstr->ppist, "MembraneOffset");

		pdtc->b.dMembraneOffset = dMembraneOffset;

		//- get TauDenormalizer

		double dTauDenormalizer = SymbolParameterResolveValue(phsle, ptstr->ppist, "TauDenormalizer");

		pdtc->b.dTauDenormalizer = dTauDenormalizer;

		if (dDeNominatorOffset == FLT_MAX)
		{
		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"DeNominatorOffset");

		    iResult = TSTR_PROCESSOR_ABORT;

		}


		if( dMembraneOffset == FLT_MAX )
		{
		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"MembraneOffset");

		    iResult = TSTR_PROCESSOR_ABORT;

		}
		


		if( dTauDenormalizer == FLT_MAX)
		{

		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, 
					       ptstr->ppist);

		    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"TauDenormalizer");

		    iResult = TSTR_PROCESSOR_ABORT;

		}
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,
			       "Unknown Object Type, not a gate kinetic.");

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- otherwise

    else
    {
	//- an error

	MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ptstr->ppist);

	MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,"Unknown Object Type, not a gate kinetic.");

	iResult = TSTR_PROCESSOR_ABORT;
    }

    //- if no error

    if (pmcd->iStatus > 0)
    {
	//- increment the status to indicate what component we have processed

	pmcd->iStatus++;

	if (pmcd->iStatus == 11)
	{
	    pmcd->iStatus = 1;
	}
    }

    //- return result

    return(iResult);
}


static
int
solver_mathcomponent_finalizer(struct TreespaceTraversal *ptstr, void *pvUserdata)
{
    //- set default result : ok

    int iResult = TSTR_PROCESSOR_SUCCESS;

    //- get actual symbol

    struct symtab_HSolveListElement *phsle = (struct symtab_HSolveListElement *)TstrGetActual(ptstr);

    if (instanceof_cell(phsle))
    {
	printf("warning: cell found during solver_mathcomponent_finalizer()\n");

	int iBreak = 1;
    }

    //- get user data

    struct MathComponentData * pmcd = (struct MathComponentData *)pvUserdata;

    //- if segment

    if (instanceof_segment(phsle))
    {
	//- fill in compartment to mechanism convertor

	pmcd->piC2m[pmcd->iCompartment] = pmcd->iCurrentType;

	//- increment compartment counter

	pmcd->iCompartment++;
    }

    //- return result

    return(iResult);
}


static
int
solver_mathcomponent_processor(struct TreespaceTraversal *ptstr, void *pvUserdata)
{
    //- set default result : ok

    int iResult = TSTR_PROCESSOR_SUCCESS;

    //- get actual symbol

    struct symtab_HSolveListElement *phsle = (struct symtab_HSolveListElement *)TstrGetActual(ptstr);

    if (instanceof_cell(phsle))
    {
	printf("warning: cell found during solver_mathcomponent_processor()\n");

	int iBreak = 1;
    }

    //- get user data

    struct MathComponentData * pmcd = (struct MathComponentData *)pvUserdata;

    //- get pointer to intermediary

    struct Heccer *pheccer = pmcd->pheccer;

    //- get current math component

    struct MathComponent * pmc = pmcd->pmc;

    int iType;

    //- if on the algorithm axis

    if (instanceof_algorithm_symbol(phsle))
    {
	//- ok, skip

	iType = -2;
    }

    //- if structure only

    else if (instanceof_group(phsle)
	     || instanceof_segment(phsle)
	     || instanceof_v_segment(phsle))
    {
	//- ok, skip

	iType = -2;
    }

    //- if gate and related

    else if (instanceof_gate_kinetic(phsle)
	     || instanceof_h_h_gate(phsle)
	     || instanceof_concentration_gate_kinetic(phsle)
	     || instanceof_equation_exponential(phsle))
    {
	//- ok, skip

	iType = -2;
    }

    //- if simulation domain related

    else if (instanceof_attachment(phsle))
    {
	//- if a spikegen

	struct symtab_Attachment *patta = (struct symtab_Attachment *)phsle;

	if (AttachmentPointIsOutgoing(patta))
	{
	    //- get type of math component

	    iType = pmcd->piTypes[pmcd->iCurrentType];

	    //- register the type in the math component array

	    pmc->iType = iType;

	    //- register serial

	    int iNeurospaces = PidinStackToSerial(ptstr->ppist);

	    pmc->iSerial = ADDRESSING_NEUROSPACES_2_HECCER(iNeurospaces);

#ifdef HECCER_SOURCE_TYPING

	    double dModelSourceType
		= SymbolParameterResolveValue(phsle, ptstr->ppist, "MODEL_SOURCE_TYPE");

	    if (dModelSourceType != FLT_MAX)
	    {
		pmc->iModelSourceType = dModelSourceType;
	    }
	    else
	    {
		pmc->iModelSourceType = -1;
	    }

#endif

	}

	//- if a synapse

	else
	{
	    //- ok, skip

	    /// \note this will be taken care of during compilation of the projections.

	    iType = -2;
	}
    }

    //- else

    else
    {
	//- default: we do not process this component

	int iProcess = 0;

	//- if passive-only mode and this is a synchan

	if (pheccer->ho.iOptions & HECCER_OPTION_PASSIVE_SYNCHANS)
	{
	    if (instanceof_channel(phsle)
		&& SymbolHasEquation(phsle, ptstr->ppist))
	    {
		//- ok, process

		iProcess = 1;
	    }
	}

	//- else, active mode

	else
	{
	    //- ok, process everything

	    iProcess = 1;
	}

	//- if we must process this component

	if (iProcess)
	{
	    //- get type of math component

	    iType = pmcd->piTypes[pmcd->iCurrentType];

	    //- register the type in the math component array

	    pmc->iType = iType;

	    //- register serial

	    int iNeurospaces = PidinStackToSerial(ptstr->ppist);

	    pmc->iSerial = ADDRESSING_NEUROSPACES_2_HECCER(iNeurospaces);

#ifdef HECCER_SOURCE_TYPING

	    double dModelSourceType
		= SymbolParameterResolveValue(phsle, ptstr->ppist, "MODEL_SOURCE_TYPE");

	    if (dModelSourceType != FLT_MAX)
	    {
		pmc->iModelSourceType = dModelSourceType;
	    }
	    else
	    {
		pmc->iModelSourceType = -1;
	    }

#endif

	}
	else
	{
	    iType = -2;
	}
    }

    //- depending on the type

    switch (iType)
    {
	//- for a channel

    case MATH_TYPE_ChannelAct:
    case MATH_TYPE_ChannelActConc:
    case MATH_TYPE_ChannelActInact:
    case MATH_TYPE_ChannelPersistentSteadyStateDualTau:
    case MATH_TYPE_ChannelPersistentSteadyStateTau:
    case MATH_TYPE_ChannelSpringMass:
    case MATH_TYPE_ChannelSteadyStateSteppedTau:
    {
	//- get maximal conductance

	double dMaximalConductance = SymbolParameterResolveScaledValue(phsle, ptstr->ppist, "G_MAX");

	//- get reversal potential

	double dReversalPotential = SymbolParameterResolveValue(phsle, ptstr->ppist, "Erev");

	if (dMaximalConductance == FLT_MAX)
	{

	    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"G_MAX");

	    iResult = TSTR_PROCESSOR_ABORT;

	}

        if(dReversalPotential == FLT_MAX)
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"Erev");

	    iResult = TSTR_PROCESSOR_ABORT;
	}

	//- determine link with math component that computes the
	//- reversal potential, if any

	int iReversalPotential = -1;

	if (SymbolHasNernstErev(phsle, ptstr->ppist))
	{
	    //- currently the nernst intermediary always comes after the channel

	    /// \note this can be dependent on the other functions present, notably mgblocking.

	    iReversalPotential = pmc->iSerial + 1;
	}

	//- set values

	if (iType == MATH_TYPE_ChannelAct)
	{
	    struct ChannelAct * pca = (struct ChannelAct *)pmc;

	    pca->dMaximalConductance = dMaximalConductance;

	    pca->dReversalPotential = dReversalPotential;

	    pca->iReversalPotential = iReversalPotential;

	    pca->iPool = -1;
	}
	else if (iType == MATH_TYPE_ChannelActInact)
	{
	    struct ChannelActInact * pcai = (struct ChannelActInact *)pmc;

	    pcai->dMaximalConductance = dMaximalConductance;

	    pcai->dReversalPotential = dReversalPotential;

	    pcai->iReversalPotential = iReversalPotential;

	    pcai->iPool = -1;
	}
	else if (iType == MATH_TYPE_ChannelPersistentSteadyStateDualTau)
	{
	    struct ChannelPersistentSteadyStateDualTau * pcpsdt = (struct ChannelPersistentSteadyStateDualTau *)pmc;

	    pcpsdt->dMaximalConductance = dMaximalConductance;

	    pcpsdt->dReversalPotential = dReversalPotential;

	    pcpsdt->iReversalPotential = iReversalPotential;

	    pcpsdt->iPool = -1;
	}
	else if (iType == MATH_TYPE_ChannelPersistentSteadyStateTau)
	{
	    struct ChannelPersistentSteadyStateTau * pcpst = (struct ChannelPersistentSteadyStateTau *)pmc;

	    pcpst->dMaximalConductance = dMaximalConductance;

	    pcpst->dReversalPotential = dReversalPotential;

	    pcpst->iReversalPotential = iReversalPotential;

	    pcpst->iPool = -1;
	}
	else if (iType == MATH_TYPE_ChannelSteadyStateSteppedTau)
	{
	    struct ChannelSteadyStateSteppedTau * pcsst = (struct ChannelSteadyStateSteppedTau *)pmc;

	    pcsst->dMaximalConductance = dMaximalConductance;

	    pcsst->dReversalPotential = dReversalPotential;

	    pcsst->iReversalPotential = iReversalPotential;

	    pcsst->iPool = -1;
	}
	else if (iType == MATH_TYPE_ChannelSpringMass)
	{
	    struct ChannelSpringMass * pcsm = (struct ChannelSpringMass *)pmc;

	    pcsm->dMaximalConductance = dMaximalConductance;

	    pcsm->dReversalPotential = dReversalPotential;

	    pcsm->iReversalPotential = iReversalPotential;

	    pcsm->iPool = -1;

	    //- get endogenous activation frequency

	    double dFrequency = SymbolParameterResolveValue(phsle, ptstr->ppist, "FREQUENCY");

	    /// \todo this case should actually be handled by neurospaces ?

	    if (dFrequency == FLT_MAX)
	    {
		dFrequency = 0;
	    }

	    pcsm->dFrequency = dFrequency;

	    /// \todo not sure about this one
	    ///
	    /// \todo I think, because it is a low level component for I/O to the model, the setting
	    /// \todo should not be done over neurospaces, but over ssp parameter settings.

	    pcsm->pdEventTimes = NULL;
	}
	else if (iType == MATH_TYPE_ChannelActConc)
	{
	    struct ChannelActConc * pcac = (struct ChannelActConc *)pmc;

	    pcac->dMaximalConductance = dMaximalConductance;

	    pcac->dReversalPotential = dReversalPotential;

	    pcac->iReversalPotential = iReversalPotential;

	    pcac->iPool = -1;

	    /// contributes to this concentration pool, -1 for none, boolean indicator only.

	    struct PidinStack *ppistPool
		= SymbolResolveInput(phsle, ptstr->ppist, "concen", 0);

	    if (ppistPool)
	    {
/* 		/// \todo this is a hack to get things to work right now, */
/* 		/// \todo see TODOs in neurospaces */

/* 		/// \todo this hack will not work when components are in different groups or so */

/* 		int iSerialDifference */
/* 		    = piolPool->hsle.smapPrincipal.iParent - phsle->smapPrincipal.iParent; */

		int iPool = PidinStackToSerial(ppistPool);

		pcac->pac.ca.iActivator = ADDRESSING_NEUROSPACES_2_HECCER(iPool);

		PidinStackFree(ppistPool);

	    }
	    else
	    {
		pcac->pac.ca.iActivator = -1;
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNKNOWN_TYPE,"Unknown Channel Type");

	    iResult = TSTR_PROCESSOR_ABORT;
	}

	//- if no errors yet

	if (pmcd->iStatus > 0)
	{
	    /// \note push and pop, the quick hack

	    int iStatus = pmcd->iStatus;

	    pmcd->iStatus = 1;

	    //- if traverse channel descendants

	    TreespaceTraversalProcessor * pfProcesor = Type2Processor(iType);

	    struct TreespaceTraversal * ptstrChannel
		= TstrNew
		(ptstr->ppist,
		 NULL,
		 NULL,
		 pfProcesor,
		 (void *)pmcd,
		 ptstr->pfFinalizer,
		 ptstr->pvFinalizer);

	    iResult = TstrGo(ptstrChannel, phsle);

	    if (iResult == 1)
	    {
		pmcd->iStatus = iStatus;

		iResult = TSTR_PROCESSOR_FAILURE;
	    }
	    else
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_ERROR, ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNKNOWN_ERROR,"Invalid Channel");

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    TstrDelete(ptstrChannel);

	    //- advance to the next math component

	    pmcd->pmc = MathComponentNext(pmcd->pmc);

	    pmcd->iCurrentType++;

	    pmc = pmcd->pmc;
	}

	//- if there is a nernst function

	int iFunctions = 1;

	if (SymbolHasNernstErev(phsle, ptstr->ppist))
	{
	    struct InternalNernst * pin = (struct InternalNernst *)pmc;

	    int iNernst = PidinStackToSerial(ptstr->ppist);

	    iNernst = ADDRESSING_NEUROSPACES_2_HECCER(iNernst) + iFunctions;

	    //- set type and serial

	    pin->mc.iType = MATH_TYPE_InternalNernst;
	    pin->mc.iSerial = iNernst;

#ifdef HECCER_SOURCE_TYPING

	    double dModelSourceType
		= SymbolParameterResolveValue(phsle, ptstr->ppist, "MODEL_SOURCE_TYPE");

	    if (dModelSourceType != FLT_MAX)
	    {
		pin->mc.iModelSourceType = dModelSourceType;
	    }
	    else
	    {
		pin->mc.iModelSourceType = -1;
	    }

#endif

	    //- get Erev parameter

	    struct symtab_Parameters *pparErev
		= SymbolGetParameter(phsle, ptstr->ppist, "Erev");

	    //- get nernst function
	    struct PidinStack *ppistNernst = 
	      ParameterContextGetFunctionContext(pparErev,ptstr->ppist);


	    struct symtab_Function *pfunNernst = NULL;

	    if(ppistNernst)
	    {

	      pfunNernst = ParameterContextGetFunction(pparErev,ptstr->ppist);

	    }
	    else
	    {

	      pfunNernst = ParameterGetFunction(pparErev);

	    }

	      
	    //- fetch parameters

	    struct symtab_Parameters *pparCIn
		= FunctionGetParameter(pfunNernst, "Cin");
	    struct symtab_Parameters *pparCOut
		= FunctionGetParameter(pfunNernst, "Cout");
	    struct symtab_Parameters *pparValency
		= FunctionGetParameter(pfunNernst, "valency");
	    struct symtab_Parameters *pparT
		= FunctionGetParameter(pfunNernst, "T");

	    if (!pparCIn)
	    {

		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"Cin");
		
		iResult = TSTR_PROCESSOR_ABORT;
		
		break;
	      
	    }

	    if(!pparCOut)
	    {

		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"Cout");
		
		iResult = TSTR_PROCESSOR_ABORT;

		break;

	    }
	    

	    if(!pparValency)
	    {

		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"valency");
		
		iResult = TSTR_PROCESSOR_ABORT;

		break;

	    }


	    if(!pparT)
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"T");
		
		iResult = TSTR_PROCESSOR_ABORT;

		break;
	    }

	    //- calculate parameter values
	    
	    double dCIn = ParameterResolveValue(pparCIn, 
						(ppistNernst) ? ppistNernst:ptstr->ppist);
	    double dCOut = ParameterResolveValue(pparCOut,
						 (ppistNernst) ? ppistNernst:ptstr->ppist);
	    double dValency = ParameterResolveValue(pparValency,
						    (ppistNernst) ? ppistNernst:ptstr->ppist);
	    double dT = ParameterResolveValue(pparT,
					      (ppistNernst) ? ppistNernst:ptstr->ppist);

	    if (dCIn == FLT_MAX)
	    {

		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"Cin");
		
		iResult = TSTR_PROCESSOR_ABORT;

		break;
	    }
	     

	    if (dCOut == FLT_MAX)
	    {

		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"Cout");
		
		iResult = TSTR_PROCESSOR_ABORT;

		break;

	    }
	     
	    if( dValency == FLT_MAX )
	    {

		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"valency");
		
		iResult = TSTR_PROCESSOR_ABORT;

		break;

	    }
    

	    if(dT == FLT_MAX)
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

		MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"T");
		
		iResult = TSTR_PROCESSOR_ABORT;

		break;
	    }

/* SI units */
#define GAS_CONSTANT	8.314			/* (V * C)/(deg K * mol) */
#define FARADAY		9.6487e4			/* C / mol */
#define ZERO_CELSIUS	273.15			/* deg */
#define R_OVER_F        8.6171458e-5		/* volt/deg */
#define F_OVER_R        1.1605364e4		/* deg/volt */

	    //- calculate (genesis style) nernst constant

	    double dConstant = R_OVER_F * (dT + ZERO_CELSIUS) / dValency;

	    //- fill in values

	    pin->dConstant = dConstant;
	    pin->dExternal = dCOut;

	    /// \note neurospaces contains support to evaluate simple functions

	    pin->dInitPotential = SymbolParameterResolveValue(phsle,ptstr->ppist,"Erev");

	    //- find concentration that determines the nernst potential

	    struct symtab_HSolveListElement *phslePool
		= SymbolResolveParameterFunctionalInput
		  (phsle, ptstr->ppist, "Erev", "Cin", 0);

	    //- if found

	    if (phslePool)
	    {
		if (!instanceof_pool(phslePool))
		{
		    MathComponentDataStatusSet(pmcd, STATUS_NON_POOL_FOR_NERNST, ptstr->ppist);

		    MathComponentError(pmcd,STATUS_NON_POOL_FOR_NERNST,
				       "Object with inputs Erev and Cin is not a Pool");

		    iResult = TSTR_PROCESSOR_ABORT;

		    break;
 		} 

		/// \todo this is a hack to get things to work right now,
		/// \todo see TODOs in neurospaces

		/// \todo this hack will not work when components are in different groups or so

		int iSerialDifference
		    = phslePool->smapPrincipal.iParent - phsle->smapPrincipal.iParent;

		int iPool = PidinStackToSerial(ptstr->ppist) + iSerialDifference;

		iPool = ADDRESSING_NEUROSPACES_2_HECCER(iPool);

		pin->iInternal = iPool;

		//- register the channel as a flux contributor

		pmcd->ppiConnectors[pmcd->iConnectors][0] = iPool;
		pmcd->ppiConnectors[pmcd->iConnectors][1] = iNernst;

		pmcd->iConnectors++;
	    }
	    else
	    {
		/// \todo fallback to constant nernst, requires changes in the typer

		MathComponentDataStatusSet(pmcd, STATUS_CONSTANT_NERNST, ptstr->ppist);

		MathComponentError(pmcd,STATUS_CONSTANT_NERNST,
				   "Pool falls back on constant nerst potential");

		iResult = TSTR_PROCESSOR_ABORT;

		break;
	    }

	    //- advance to the next math component

	    pmcd->pmc = MathComponentNext(pmcd->pmc);

	    pmcd->iCurrentType++;

	    pmc = pmcd->pmc;

	    iFunctions++;
	}

	/// \todo mgblocking

	break;
    }

    //- for an exponential

    case MATH_TYPE_ExponentialDecay:
    {
	//- get math component data

	struct ExponentialDecay * pexdec
	    = (struct ExponentialDecay *)pmc;

	//- get initial value

	double dInitValue = SymbolParameterResolveValue(phsle, ptstr->ppist, "concen_init");

	//- get beta

	double dBeta = SymbolParameterResolveScaledValue(phsle, ptstr->ppist, "BETA");

	//- get steady state

	double dSteadyState = SymbolParameterResolveValue(phsle, ptstr->ppist, "BASE");

	//- get tau

	double dTau = SymbolParameterResolveValue(phsle, ptstr->ppist, "TAU");

	if ( dInitValue == FLT_MAX )
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"concen_init");
	    
	    iResult = TSTR_PROCESSOR_ABORT;
	}

	if( dBeta == FLT_MAX )
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"BETA");
	    
	    iResult = TSTR_PROCESSOR_ABORT;
	}


	if( dSteadyState == FLT_MAX )
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"BASE");
	    
	    iResult = TSTR_PROCESSOR_ABORT;
	}
	

	if( dTau == FLT_MAX )
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"TAU");
	    
	    iResult = TSTR_PROCESSOR_ABORT;
	}

	if (dInitValue == 0
	    || dBeta == 0)
	{
	    MathComponentDataStatusSet(pmcd, STATUS_ILLEGAL_PARAMETER_VALUES, ptstr->ppist);

	    iResult = TSTR_PROCESSOR_ABORT;

	    fprintf(stdout, "STATUS_ILLEGAL_PARAMETER_VALUES for the following:\n");

	    PidinStackTo_stdout(ptstr->ppist);
	}

	if (1 / dInitValue == 0
	    || 1 / dBeta == 0)
	{
	    MathComponentDataStatusSet(pmcd, STATUS_ILLEGAL_PARAMETER_VALUES, ptstr->ppist);

	    iResult = TSTR_PROCESSOR_ABORT;

	    fprintf(stdout, "STATUS_ILLEGAL_PARAMETER_VALUES for the following:\n");

	    PidinStackTo_stdout(ptstr->ppist);
	}

	//- set values

	pexdec->dInitValue = dInitValue;
	pexdec->dBeta = dBeta;
	pexdec->dSteadyState = dSteadyState;
	pexdec->dTau = dTau;

	//- find contributing channels

	int iInput;

	for (iInput = 0 ; iInput < EXPONENTIALDECAY_CONTRIBUTORS ; iInput++)
	{
	    struct PidinStack *ppistExternal
		= SymbolResolveInput(phsle, ptstr->ppist, "I", iInput);

	    if (ppistExternal)
	    {
		struct symtab_HSolveListElement *phsleExternal
		    = PidinStackLookupTopSymbol(ppistExternal);

		if (!instanceof_channel(phsleExternal))
		{
		    MathComponentDataStatusSet(pmcd, STATUS_NON_CHANNEL_OUTPUTS_IK, ptstr->ppist);

		    MathComponentError(pmcd,STATUS_NON_CHANNEL_OUTPUTS_IK,"Cannot resolve channel input \'I\'");

		    iResult = TSTR_PROCESSOR_ABORT;

		    break;
		}

/* 		/// \todo this is a hack to get things to work right now, */
/* 		/// \todo see TODOs in neurospaces */

/* 		/// \todo this hack will not work when components are in different groups or so */

/* 		int iSerialDifference */
/* 		    = piolExternal->hsle.smapPrincipal.iParent - phsle->smapPrincipal.iParent; */

		int iChannel = PidinStackToSerial(ppistExternal);
		int iPool = PidinStackToSerial(ptstr->ppist);

		iChannel = ADDRESSING_NEUROSPACES_2_HECCER(iChannel);
		iPool = ADDRESSING_NEUROSPACES_2_HECCER(iPool);

		pexdec->piExternal[iInput] = iChannel;

		//- register the channel as a flux contributor

		pmcd->ppiConnectors[pmcd->iConnectors][0] = iChannel;
		pmcd->ppiConnectors[pmcd->iConnectors][1] = iPool;

		pmcd->iConnectors++;

		PidinStackFree(ppistExternal);

	    }
	    else
	    {
		pexdec->piExternal[iInput] = -1;
	    }
	}

	//- check for to many contributors

	struct PidinStack *ppistExternal
	    = SymbolResolveInput(phsle, ptstr->ppist, "I", iInput);

	if (ppistExternal)
	{
	    MathComponentDataStatusSet(pmcd, STATUS_MANY_CHANNELS, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_MANY_CHANNELS,
			       "Cannot resolve external channel input \'I\'");
	  
	    iResult = TSTR_PROCESSOR_ABORT;

	    PidinStackFree(ppistExternal);
	}

	//- advance to the next math component

	pmcd->pmc = MathComponentNext(pmcd->pmc);

	pmcd->iCurrentType++;

	pmc = pmcd->pmc;

	break;
    }

    //- for a spike generator

    case MATH_TYPE_SpikeGenerator:
    {
	/// \todo for spikegens: initialize struct SpikeGenerator

	//- get math component data

	struct SpikeGenerator * psg
	    = (struct SpikeGenerator *)pmc;

	//- get refractory time

	double dRefractory = SymbolParameterResolveValue(phsle, ptstr->ppist, "REFRACTORY");

	//- get spiking threshold

	double dThreshold = SymbolParameterResolveValue(phsle, ptstr->ppist, "THRESHOLD");

	//- get reset value, FLT_MAX for none

	double dReset = SymbolParameterResolveValue(phsle, ptstr->ppist, "RESET");

	//- unset table in event distributor with targets, will be
	//- filled when projections are compiled

	int iTable = INT_MAX;

	if (dRefractory == FLT_MAX)
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"REFRACTORY");

	    iResult = TSTR_PROCESSOR_ABORT;
	}
	 
	if(dThreshold == FLT_MAX)
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS, ptstr->ppist);

	    MathComponentError(pmcd,STATUS_UNRESOLVABLE_PARAMETERS,"THRESHOLD");

	    iResult = TSTR_PROCESSOR_ABORT;
	}

	if (dRefractory <= 0)
	{
	    MathComponentDataStatusSet(pmcd, STATUS_ILLEGAL_PARAMETER_VALUES, ptstr->ppist);

	    iResult = TSTR_PROCESSOR_ABORT;

	    fprintf(stdout, "STATUS_ILLEGAL_PARAMETER_VALUES for the following:\n");

	    PidinStackTo_stdout(ptstr->ppist);
	}

	//- set values

	psg->dRefractory = dRefractory;
	psg->dThreshold = dThreshold;
	psg->dReset = dReset;
	psg->iTable = iTable;

	//- advance to the next math component

	pmcd->pmc = MathComponentNext(pmcd->pmc);

	pmcd->iCurrentType++;

	pmc = pmcd->pmc;

	break;
    }

    //- for skipped components

    case -2:
    {
	//- nothing registered, nothing done

	break;
    }

    //- otherwise

    default:
    {
	//- type consistency error

	MathComponentDataStatusSet(pmcd, STATUS_CONSISTENCY, ptstr->ppist);

	MathComponentError(pmcd,STATUS_CONSISTENCY,"Spike Generator is not consistent.");
      
	iResult = TSTR_PROCESSOR_ABORT;

	break;
    }
    }

    //- return result

    return(iResult);
}


static
int
solver_mathcomponent_typer(struct TreespaceTraversal *ptstr, void *pvUserdata)
{
    //- set default result : ok

    int iResult = TSTR_PROCESSOR_SUCCESS;

    //- get actual symbol

    struct symtab_HSolveListElement *phsle = (struct symtab_HSolveListElement *)TstrGetActual(ptstr);

    if (instanceof_cell(phsle))
    {
	printf("warning: cell found during solver_mathcomponent_typer()\n");

	int iBreak = 1;
    }

    //- get user data

    struct MathComponentData * pmcd = (struct MathComponentData *)pvUserdata;

    //- get pointer to intermediary

    struct Heccer *pheccer = pmcd->pheccer;

    //- set default type : error

    int iType = INT_MAX;

    //- if on the algorithm axis

    if (instanceof_algorithm_symbol(phsle))
    {
	//- ok, skip

	iType = -2;
    }

    //- if structure only

    else if (instanceof_group(phsle)
	     || instanceof_segment(phsle)
	     || instanceof_v_segment(phsle))
    {
	//- ok, skip

	iType = -2;
    }

    //- if gate and related

    else if (instanceof_gate_kinetic(phsle)
	     || instanceof_h_h_gate(phsle)
	     || instanceof_concentration_gate_kinetic(phsle)
	     || instanceof_equation_exponential(phsle))
    {
	//- ok, skip

	iType = -2;
    }

    //- if simulation domain related

    else if (instanceof_attachment(phsle))
    {
	//- if a spikegen

	struct symtab_Attachment *patta = (struct symtab_Attachment *)phsle;

	if (AttachmentPointIsOutgoing(patta))
	{
	    //- ok, register

	    iType = MATH_TYPE_SpikeGenerator;
	}

	//- if a synapse

	else
	{
	    //- ok, skip

	    /// \note this will be taken care of during compilation of the projections.

	    iType = -2;
	}
    }

    //- pool

    else if (instanceof_pool(phsle))
    {
	//- if passive-only mode

	if (pheccer->ho.iOptions & HECCER_OPTION_PASSIVE_SYNCHANS)
	{
	    //- ok, skip

	    iType = -2;
	}

	//- if active mode

	else
	{
	    //- ok, register

	    iType = MATH_TYPE_ExponentialDecay;
	}
    }

    //- channel

    else if (instanceof_channel(phsle))
    {
	/// \todo clearly there should be global filter for this: given a
	/// \todo component, should we process it or not ?  This filter should
	/// \todo then be used by the other functions too, to see what must go
	/// \todo to the intermediary.

	//- default: we do not process channels

	int iProcess = 0;

	//- if passive-only mode and this is a synchan

	if (pheccer->ho.iOptions & HECCER_OPTION_PASSIVE_SYNCHANS)
	{
	    if (SymbolHasEquation(phsle, ptstr->ppist))
	    {
		//- ok, process

		iProcess = 1;
	    }
	}

	//- else, active mode

	else
	{
	    //- ok, process everything

	    iProcess = 1;
	}

	//- if we must process this channel

	if (iProcess)
	{
	    struct symtab_Parameters *pparType
		= SymbolFindParameter(phsle, ptstr->ppist, "CHANNEL_TYPE");

	    if (pparType
		|| SymbolHasEquation(phsle, ptstr->ppist))
	    {
		char *pcType = pparType ? ParameterGetString(pparType) : NULL;

		//- check if channel has an exponential equation

		int iEquation = SymbolHasEquation(phsle, ptstr->ppist);

		//- if channel has multiple concentration dependencies

		struct PidinStack *ppistPool1
		    = SymbolResolveInput(phsle, ptstr->ppist, "concen", 1);

		if (ppistPool1)
		{
		    //- abort the traversal

		    MathComponentDataStatusSet(pmcd, STATUS_MANY_POOLS, ptstr->ppist);

		    MathComponentError(pmcd,STATUS_MANY_POOLS,
				       "Canot resolve channel input 'concen'");

		    iResult = TSTR_PROCESSOR_ABORT;

		    PidinStackFree(ppistPool1);

		}

		if (pcType && strncasecmp(pcType, "ChannelPersistentSteadyStateTau", strlen("ChannelPersistentSteadyStateTau")) == 0)
		{
		    /// \todo MATH_TYPE_ChannelPersistentSteadyStateTau: steady state with two parts (km)

		    iType = MATH_TYPE_ChannelPersistentSteadyStateTau;
		}
		else if (pcType && strncasecmp(pcType, "ChannelPersistentSteadyStateDualTau", strlen("ChannelPersistentSteadyStateDualTau")) == 0)
		{
		    //- MATH_TYPE_ChannelPersistentSteadyStateDualTau: tau with two parts ? (kh)

		    iType = MATH_TYPE_ChannelPersistentSteadyStateDualTau;
		}
		else if (pcType && strncasecmp(pcType, "ChannelSteadyStateSteppedTau", strlen("ChannelSteadyStateSteppedTau")) == 0)
		{
		    /// \todo MATH_TYPE_ChannelSteadyStateSteppedTau: steady state with 2x2 parts, tau with 2 parts (kdr)

		    iType = MATH_TYPE_ChannelSteadyStateSteppedTau;
		}
		else if (pcType && strncasecmp(pcType, "ChannelActConc", strlen("ChannelActConc")) == 0)
		{
		    /// \todo when the concen was not bound, the test above fails.
		    /// \todo need a separate name for the concen gate or so

		    iType = MATH_TYPE_ChannelActConc;
		}
		else if (pcType && strncasecmp(pcType, "ChannelActInact", strlen("ChannelActInact")) == 0)
		{
		    /// \todo when the concen was not bound, the test above fails.
		    /// \todo need a separate name for the concen gate or so

		    iType = MATH_TYPE_ChannelActInact;
		}
		else if (pcType && strncasecmp(pcType, "ChannelAct", strlen("ChannelAct")) == 0)
		{
		    //- MATH_TYPE_ChannelAct: only one gate (nap)

		    iType = MATH_TYPE_ChannelAct;
		}
		else
		{
		    //- if the channel has an exponential equation

		    if (iEquation)
		    {
			//- type is springmass channel

			iType = MATH_TYPE_ChannelSpringMass;
		    }
		    else
		    {
			//- abort the traversal

			HeccerError
			    (pheccer,
			     NULL,
			     "solver_mathcomponent_typer() cannot determine channel type for %s (is the CHANNEL_TYPE parameter valid ?).",
			     SymbolGetName(phsle));

			MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_CHANNEL_TYPE1, 
						   ptstr->ppist);

			
			MathComponentPrintErrorReport(pmcd);

			iResult = TSTR_PROCESSOR_ABORT;
		    }
		}

		//- if the channel has a nernst function

		/// \todo need a separate loop for registering the type or so.

		if (SymbolHasNernstErev(phsle, ptstr->ppist))
		{
		    if (!MathComponentDataTypeRegister(pmcd, iType, ptstr->ppist))
		    {
			iResult = TSTR_PROCESSOR_ABORT;
		    }

		    /// \todo differentiate between internal and external nernst,
		    /// \todo possibly also differentiate with constant nernst

		    iType = MATH_TYPE_InternalNernst;
		}

		/// \todo MATH_TYPE_MGBlocker

		/// \todo check for attachments (synchans)
	    }
	    else
	    {
		//- abort the traversal

		HeccerError
		    (pheccer,
		     NULL,
		     "solver_mathcomponent_typer() cannot determine channel type for %s (is the CHANNEL_TYPE parameter present ?).",
		     SymbolGetName(phsle));

		MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_CHANNEL_TYPE3, ptstr->ppist);


		MathComponentPrintErrorReport(pmcd);

		iResult = TSTR_PROCESSOR_ABORT;

		/// \todo deal with channels that are linked with a table
		/// \todo generated externally (using genesis2)
	    }
	}
	else
	{
	    iType = -2;
	}
    }

    //- register type

    if (!MathComponentDataTypeRegister(pmcd, iType, ptstr->ppist))
    {
	iResult = TSTR_PROCESSOR_ABORT;
    }

    //- return result

    return(iResult);
}


static int cellsolver_getmathcomponents(struct Heccer *pheccer, struct TranslationService *pts)
{
    //- set default result : ok

    int iResult = TRUE;

    //- allocate pidin stack pointing to root

    struct PidinStack *ppistRoot = pts->ptsd->ppistRoot;

    struct symtab_HSolveListElement *phsleRoot = pts->ptsd->phsleRoot;

    //- get model context to solve

    struct PidinStack *ppistModel
	= SymbolPrincipalSerial2Context(phsleRoot, ppistRoot, pts->ptsd->iModel);

    if (ppistModel)
    {
	//- lookup symbol

	struct symtab_HSolveListElement *phsleModel
	    = PidinStackLookupTopSymbol(ppistModel);

	//- determine size of math component array

	struct MathComponentData mcd = {

	    /// solution engine

	    pheccer,

	    /// compartment number

	    0,

	    /// compartment 2 mechanism convertor

	    NULL,

	    /// current compartment

	    NULL,

	    NULL,

	    /// array of all math component types

	    0,

	    0,

	    NULL,

	    /// current mathcomponent

	    NULL,

	    /// number of spikegens

	    0,

	    /// operational status: positive is positive, negative is negative (error)

	    1,

	    "",

	    "",

	    /// channels that contribute to a pool

	    /// \note to set the iPool boolean indicator

	    0,

	    NULL,

	};

	/// \todo should try to get rid of this allocation somehow

#define MAXIMUM_NUMBER_OF_CHANNEL_CONTRIBUTORS 100000

	{
	    mcd.ppiConnectors = (int **)calloc(MAXIMUM_NUMBER_OF_CHANNEL_CONTRIBUTORS, sizeof(int *));

	    int i;

	    for (i = 0 ; i < MAXIMUM_NUMBER_OF_CHANNEL_CONTRIBUTORS ; i++)
	    {
		mcd.ppiConnectors[i] = (int *)calloc(2, sizeof(int));
	    }
	}

	//- get descendants

	int iDescendants = SymbolGetPrincipalNumOfSuccessors(phsleModel);

	//- allow maximally this number of functions

	/// \todo to remove this 'opportunistic hack', neurospaces should
	/// \todo (1) serve the model a bit cleaner,
	/// \todo (2) by incorporating the functions into the symbol hierarchy.
	/// \todo See relevant comments in symbol hierarchy.

#define MAXIMUM_NUMBER_OF_FUNCTIONS 100000

	/// \note + 1 for '-1' terminator

	iDescendants += MAXIMUM_NUMBER_OF_FUNCTIONS + 1;

	//- allocate types array

	mcd.iDescendants = iDescendants;

	mcd.piTypes = (int *)calloc(iDescendants, sizeof(int));

	//- set compartment 2 mechanism convertor

	mcd.piC2m = pheccer->inter.piC2m;

	//- traverse solved components, register types

	struct TreespaceTraversal *ptstr
	    = TstrNew
	    (ppistModel,
	     NULL,
	     NULL,
	     solver_mathcomponent_typer,
	     (void *)&mcd,
	     NULL,
	     NULL);

	iResult = TstrGo(ptstr, phsleModel);

	if (mcd.iStatus > 0)
	{
	    //- if there were mechanisms found

	    if (mcd.iCurrentType > 0)
	    {
		//- register type terminator

		if (MathComponentDataTypeRegister(&mcd, -1, ptstr->ppist))
		{
		    //- allocate math component array

		    struct MathComponentArray * pmca
			= (struct MathComponentArray *)calloc(1, sizeof(struct MathComponentArray));

		    if (pmca)
		    {
			if (MathComponentArrayCallocData(pmca, mcd.piTypes))
			{
			    //- register math component array with the intermediary

			    pheccer->inter.pmca = pmca;

			    //- traverse solved components, initialize intermediary

			    mcd.iCurrentType = 0;

			    mcd.pmc = pmca->pmc;

			    /// \todo not sure if recycling is still allowed ...

			    ptstr->iStatus = TSTR_STATUS_NEW;
			    ptstr->pfProcessor = solver_mathcomponent_processor;
			    ptstr->pfFinalizer = solver_mathcomponent_finalizer;
			    ptstr->pvFinalizer = (void *)&mcd;

			    iResult = TstrGo(ptstr, phsleModel);

			    //- register number of math components

			    pmca->iMathComponents = mcd.iCurrentType;

			    //- do a consistency check on the types encountered during the two traversals

			    if (mcd.piTypes[mcd.iCurrentType] != -1)
			    {
				MathComponentDataStatusSet(&mcd, STATUS_CONSISTENCY, ptstr->ppist);

				MathComponentError(&mcd,STATUS_CONSISTENCY,
						   "Number of model math components during processing does not match with number during typing.");

				iResult = FALSE;
			    }
			}
			else
			{
			    MathComponentDataStatusSet(&mcd, STATUS_MEMORY, ptstr->ppist);

			    MathComponentError(&mcd,STATUS_MEMORY,"Memory Allocation Error");

			    iResult = FALSE;
			}
		    }
		    else
		    {
		   
			MathComponentDataStatusSet(&mcd, STATUS_MEMORY, ptstr->ppist);

			MathComponentError(&mcd,STATUS_MEMORY,"Memory Allocation Error");

			iResult = FALSE;
		    }
		}
		else
		{
		    MathComponentDataStatusSet(&mcd, STATUS_MEMORY, ptstr->ppist);

		    MathComponentError(&mcd,STATUS_MEMORY,"Memory Allocation Error");

		    iResult = FALSE;
		}
	    }
	}

	/// \todo sort the registry

	//- link the mathcomponents together

	iResult = iResult && cellsolver_linkmathcomponents(pheccer, &mcd);

	//- delete treespace traversal

	TstrDelete(ptstr);

	/// \todo decide if we want to keep piTypes or not, it might
	/// \todo be useful to keep.

	//- delete channel contributors registry

	{
	    int i;

	    for (i = 0 ; i < MAXIMUM_NUMBER_OF_CHANNEL_CONTRIBUTORS ; i++)
	    {
		free(mcd.ppiConnectors[i]);
	    }

	    free(mcd.ppiConnectors);
	}

	if (mcd.iStatus < 0)
	{
	    HeccerError
		(pheccer,
		 NULL,
		 "extracting the model from the model-container at %s "
		 "[cellsolver_getmathcomponents() returned error code (%i, %s),"
		 " last processed mathcomponent is %i,"
		 " external error return is %i.]",
		 mcd.pcContext,
		 mcd.iStatus,
		 ppcStatusMessages[- mcd.iStatus],
		 mcd.iCurrentType,
		 iResult);

	    fprintf(stderr,"%s","\n\n");

	    MathComponentPrintErrorReport(&mcd);
	   

	}
    }
    else
    {
	iResult = FALSE;
    }

    //- return result

    return(iResult);
}


static int cellsolver_linkmathcomponents(struct Heccer * pheccer, struct MathComponentData * pmcd)
{
    //- set default result : ok

    int iResult = TRUE;

    //- if there are no math components

    struct Intermediary *pinter = &pheccer->inter;

    struct MathComponentArray * pmca = pinter->pmca;

    if (!pmca)
    {
	//- linking is trivial

	return(TRUE);
    }

    //- loop over all mathcomponents

    struct MathComponent * pmc = pmca->pmc;

    int iMathComponent;

    for (iMathComponent = 0 ; iMathComponent < pmca->iMathComponents ; iMathComponent++)
    {
	//- get type of math component

	int iType = pmc->iType;

	switch (iType)
	{
	case MATH_TYPE_ChannelAct:
	{
	    struct ChannelAct * pca = (struct ChannelAct *)pmc;

	    //- if channel in contributors registry

	    pca->iPool = ConnectionSource2Target(pmcd, pmc);

	    int iPoolSerial = pca->iPool;

	    if (iPoolSerial != -1)
	    {
		//- translate the contributee serial

		int iPoolIndex = MathComponentArrayLookupSerial(pmca, iPoolSerial);

		pca->iPool = iPoolIndex;
	    }

	    //- if solved reversal potential

	    if (pca->iReversalPotential != -1)
	    {
		//- translate the serial to an index

		int iReversalPotential = MathComponentArrayLookupSerial(pmca, pca->iReversalPotential);

		pca->iReversalPotential = iReversalPotential;
	    }

	    break;
	}
	case MATH_TYPE_ChannelActInact:
	{
	    struct ChannelActInact * pcai = (struct ChannelActInact *)pmc;

	    //- if channel in contributors registry

	    pcai->iPool = ConnectionSource2Target(pmcd, pmc);

	    int iPoolSerial = pcai->iPool;

	    if (iPoolSerial != -1)
	    {
		//- translate the contributee serial

		int iPoolIndex = MathComponentArrayLookupSerial(pmca, iPoolSerial);

		pcai->iPool = iPoolIndex;
	    }

	    //- if solved reversal potential

	    if (pcai->iReversalPotential != -1)
	    {
		//- translate the serial to an index

		int iReversalPotential = MathComponentArrayLookupSerial(pmca, pcai->iReversalPotential);

		pcai->iReversalPotential = iReversalPotential;
	    }

	    break;
	}
	case MATH_TYPE_ChannelPersistentSteadyStateDualTau:
	{
	    struct ChannelPersistentSteadyStateDualTau * pcpsdt = (struct ChannelPersistentSteadyStateDualTau *)pmc;

	    //- if channel in contributors registry

	    pcpsdt->iPool = ConnectionSource2Target(pmcd, pmc);

	    int iPoolSerial = pcpsdt->iPool;

	    if (iPoolSerial != -1)
	    {
		//- translate the contributee serial

		int iPoolIndex = MathComponentArrayLookupSerial(pmca, iPoolSerial);

		pcpsdt->iPool = iPoolIndex;
	    }

	    //- if solved reversal potential

	    if (pcpsdt->iReversalPotential != -1)
	    {
		//- translate the serial to an index

		int iReversalPotential = MathComponentArrayLookupSerial(pmca, pcpsdt->iReversalPotential);

		pcpsdt->iReversalPotential = iReversalPotential;
	    }

	    break;
	}
	case MATH_TYPE_ChannelPersistentSteadyStateTau:
	{
	    struct ChannelPersistentSteadyStateTau * pcpst = (struct ChannelPersistentSteadyStateTau *)pmc;

	    //- if channel in contributors registry

	    pcpst->iPool = ConnectionSource2Target(pmcd, pmc);

	    int iPoolSerial = pcpst->iPool;

	    if (iPoolSerial != -1)
	    {
		//- translate the contributee serial

		int iPoolIndex = MathComponentArrayLookupSerial(pmca, iPoolSerial);

		pcpst->iPool = iPoolIndex;
	    }

	    //- if solved reversal potential

	    if (pcpst->iReversalPotential != -1)
	    {
		//- translate the serial to an index

		int iReversalPotential = MathComponentArrayLookupSerial(pmca, pcpst->iReversalPotential);

		pcpst->iReversalPotential = iReversalPotential;
	    }

	    break;
	}
	case MATH_TYPE_ChannelSteadyStateSteppedTau:
	{
	    struct ChannelSteadyStateSteppedTau * pcsst = (struct ChannelSteadyStateSteppedTau *)pmc;

	    //- if channel in contributors registry

	    pcsst->iPool = ConnectionSource2Target(pmcd, pmc);

	    int iPoolSerial = pcsst->iPool;

	    if (iPoolSerial != -1)
	    {
		//- translate the contributee serial

		int iPoolIndex = MathComponentArrayLookupSerial(pmca, iPoolSerial);

		pcsst->iPool = iPoolIndex;
	    }

	    //- if solved reversal potential

	    if (pcsst->iReversalPotential != -1)
	    {
		//- translate the serial to an index

		int iReversalPotential = MathComponentArrayLookupSerial(pmca, pcsst->iReversalPotential);

		pcsst->iReversalPotential = iReversalPotential;
	    }

	    break;
	}
	case MATH_TYPE_ChannelSpringMass:
	{
	    struct ChannelSpringMass * pcsm = (struct ChannelSpringMass *)pmc;

	    //- if channel in contributors registry

	    pcsm->iPool = ConnectionSource2Target(pmcd, pmc);

	    int iPoolSerial = pcsm->iPool;

	    if (iPoolSerial != -1)
	    {
		//- translate the contributee serial

		int iPoolIndex = MathComponentArrayLookupSerial(pmca, iPoolSerial);

		pcsm->iPool = iPoolIndex;
	    }

	    //- if solved reversal potential

	    if (pcsm->iReversalPotential != -1)
	    {
		//- translate the serial to an index

		int iReversalPotential = MathComponentArrayLookupSerial(pmca, pcsm->iReversalPotential);

		pcsm->iReversalPotential = iReversalPotential;
	    }

	    break;
	}
	case MATH_TYPE_ChannelActConc:
	{
	    struct ChannelActConc * pcac = (struct ChannelActConc *)pmc;

	    //- if channel in contributors registry

	    pcac->iPool = ConnectionSource2Target(pmcd, pmc);

	    int iPoolSerial = pcac->iPool;

	    if (iPoolSerial != -1)
	    {
		int iPoolIndex = MathComponentArrayLookupSerial(pmca, iPoolSerial);

		pcac->iPool = iPoolIndex;
	    }

	    //- translate iActivator

	    if (pcac->pac.ca.iActivator != -1)
	    {
		int iActivator = MathComponentArrayLookupSerial(pmca, pcac->pac.ca.iActivator);

		pcac->pac.ca.iActivator = iActivator;
	    }

/* 	    //- or */

/* 	    else */
/* 	    { */
/* 		//- an error */

/*      MathComponentDataStatusSet(pmcd, STATUS_CONSISTENCY); , ptstr->ppist */

/* 		iResult = FALSE; */
/* 	    } */

     //- if solved reversal potential

     if (pcac->iReversalPotential != -1)
 {
     //- translate the serial to an index

     int iReversalPotential = MathComponentArrayLookupSerial(pmca, pcac->iReversalPotential);

     pcac->iReversalPotential = iReversalPotential;
 }

	    break;
	}
	case MATH_TYPE_InternalNernst:
	{
	    struct InternalNernst * pin = (struct InternalNernst *)pmc;

	    //- if solved internal concentration

	    /// \note must not be -1

	    if (pin->iInternal != -1)
	    {
		//- translate the serial to an index

		int iInternal = MathComponentArrayLookupSerial(pmca, pin->iInternal);

		pin->iInternal = iInternal;
	    }

	    break;
	}
	case MATH_TYPE_ExponentialDecay:
	{
	    struct ExponentialDecay * pexdec = (struct ExponentialDecay *)pmc;

	    int i;

	    for (i = 0 ; i < EXPONENTIALDECAY_CONTRIBUTORS ; i++)
	    {
		int iExternalSerial = pexdec->piExternal[i];

		if (iExternalSerial != -1)
		{
		    int iExternalIndex = MathComponentArrayLookupSerial(pmca, iExternalSerial);

		    pexdec->piExternal[i] = iExternalIndex;
		}
	    }
	    break;
	}
	case MATH_TYPE_SpikeGenerator:
	{
	    struct SpikeGenerator * psg = (struct SpikeGenerator *)pmc;

	    //- ok

	    break;
	}
	default:
	{
	    iResult = FALSE;

	    break;
	}
	}

	if (iResult)
	{
	    //- advance to the next math component

	    pmc = MathComponentNext(pmc);
	}
    }

    //- return result

    return(iResult);
}


int HeccerNeurospacesMechanisms2MathComponents(struct TranslationService *pts)
{
    //- set the service function pointer to cellsolver_getmathcomponents()

    pts->mechanisms_inspector = cellsolver_getmathcomponents;

    //- return result

    return(1);
}


static
TreespaceTraversalProcessor *
Type2Processor(int iType)
{
    //- set default result : none

    TreespaceTraversalProcessor *pfResult = NULL;

    if (iType == MATH_TYPE_ChannelActInact)
    {
	pfResult = solver_channel_activation_inactivation_processor;
    }
    else if (iType == MATH_TYPE_ChannelActConc)
    {
	pfResult = solver_channel_activation_concentration_processor;
    }
    else if (iType == MATH_TYPE_ChannelSteadyStateSteppedTau)
    {
	pfResult = solver_channel_steadystate_steppedtau_processor;
    }
    else if (iType == MATH_TYPE_ChannelPersistentSteadyStateTau)
    {
	pfResult = solver_channel_persistent_steadystate_tau_processor;
    }
    else if (iType == MATH_TYPE_ChannelPersistentSteadyStateDualTau)
    {
	pfResult = solver_channel_persistent_steadystate_dualtau_processor;
    }
    else if (iType == MATH_TYPE_ChannelAct)
    {
	pfResult = solver_channel_activation_processor;
    }
    else if (iType == MATH_TYPE_ChannelSpringMass)
    {
	pfResult = solver_channel_springmass_processor;
    }
    else
    {
	/// \todo segv

	((int *)0)[0] = 0;
    }

    //- return result

    return(pfResult);
}







static
int
MathComponentError(struct MathComponentData * pmcd, int iStatus, char *pcError)
{

    if(!pmcd || pmcd->mcer.iNumErrors == MATH_COMPONENT_MAX_ERRORS)
	return 0;

    pmcd->mcer.mce[ pmcd->mcer.iNumErrors ].iStatus = iStatus; 

    pmcd->mcer.mce[ pmcd->mcer.iNumErrors ].pcError = pcError;

     
    pmcd->mcer.iNumErrors++; 



    return 1;


}


static
int
MathComponentPrintErrorReport(struct MathComponentData * pmcd)
{


    int i;


    fprintf(stderr,"%d errors for context: %s\n",pmcd->mcer.iNumErrors , pmcd->pcContext);


    for( i = 0; i < pmcd->mcer.iNumErrors; i++ )
    {

	switch( pmcd->mcer.mce[i].iStatus )
	{

	case STATUS_UNRESOLVABLE_PARAMETERS:
	    fprintf(stderr,"\tUnresolvable Parameter: %s\n", pmcd->mcer.mce[i].pcError);
	    break;



	default:
	    fprintf(stderr,"\tError: %s\n", pmcd->mcer.mce[i].pcError);
	}
    


    }


    return 1;
}

