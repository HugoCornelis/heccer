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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <neurospaces/pidinstack.h>
#include <neurospaces/treespacetraversal.h>

#include "heccer/compartment.h"
#include "heccer/intermediary.h"
#include "heccer/mathcomponent.h"
#include "heccer/neurospaces/heccer.h"
#include "heccer/neurospaces/mechanisms.h"
#include "heccer/service.h"


struct MathComponentData
{
    //m solution engine

    struct Heccer *pheccer;

    //m compartment number

    int iCompartment;

    //m compartment 2 mechanism convertor

    int *piC2m;

    //m current compartment

    struct symtab_HSolveListElement *phsleCompartment;

    struct PidinStack *ppistCompartment;

    //m array of all math component types

    int iDescendants;

    int iCurrentType;

    int *piTypes;

    //m current mathcomponent

    struct MathComponent * pmc;

    //m number of spikegens

    int iSpikeGens;

    //m operational status: positive is positive, negative is negative (error)

    int iStatus;

    //m channels that contribute to a pool

    int iConnectors;

    int **ppiConnectors;

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


static int ConnectionSource2Target(struct MathComponentData * pmcd, struct MathComponent * pmc);

static
int
MathComponentDataTypeRegister(struct MathComponentData * pmcd, int iType);

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
solver_mathcomponent_finalizer(struct TreespaceTraversal *ptstr, void *pvUserdata);

static
int
solver_mathcomponent_processor(struct TreespaceTraversal *ptstr, void *pvUserdata);

static int cellsolver_getmathcomponents(struct Heccer *pheccer, struct TranslationService *pts);

static int cellsolver_linkmathcomponents(struct Heccer * pheccer, struct MathComponentData * pmcd);

static
TreespaceTraversalProcessor *
Type2Processor(int iType);


static int ConnectionSource2Target(struct MathComponentData * pmcd, struct MathComponent * pmc)
{
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
MathComponentDataTypeRegister(struct MathComponentData * pmcd, int iType)
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

		pmcd->iStatus = STATUS_OVERFLOW;
	    }
	}
    }

    //- else

    else
    {
	//- abort the traversal, fatal failure

	//t the current serial and type cursor give an indication
	//t of what model component caused the failure

	pmcd->iStatus = STATUS_UNKNOWN_TYPE;
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

    struct symtab_HSolveListElement *phsle = TstrGetActual(ptstr);

    //- get user data

    struct MathComponentData * pmcd = (struct MathComponentData *)pvUserdata;

    //- get current math component

    struct MathComponent * pmc = pmcd->pmc;

    struct ChannelAct * pca = (struct ChannelAct *)pmc;

    //- if conceptual gate

    if (instanceof_conceptual_gate(phsle))
    {
	if (pmcd->iStatus == 1)
	{
	    struct PoweredGateConcept * ppgc = &pca->pgc;

	    //- get power

	    double dPower = SymbolParameterResolveValue(phsle, "POWER", ptstr->ppist);

	    int iPower = dPower;

	    ppgc->iPower = iPower;

	    //- get initial state

	    double dInitActivation = SymbolParameterResolveValue(phsle, "state_init", ptstr->ppist);

	    ppgc->gc.dInitActivation = dInitActivation;

	    if (dPower == FLT_MAX
		|| dInitActivation == FLT_MAX)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else
	{
	    pmcd->iStatus = STATUS_UNKNOWN_TYPE;

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- if gate kinetic

    else if (instanceof_gate_kinetic(phsle))
    {
	//! 2: forward, act
	//! 3: backward, act

	if (pmcd->iStatus == 2
	    || pmcd->iStatus == 3)
	{
	    struct PoweredGateConcept * ppgc = &pca->pgc;

	    struct GateKinetic *pgk
		= (pmcd->iStatus == 2
		   ? &ppgc->gc.gkForward
		   : &ppgc->gc.gkBackward);

	    //- initialize table index

	    ppgc->gc.iTable = -1;

	    //- get Multiplier = 35.0e3

	    double dMultiplier = SymbolParameterResolveValue(phsle, "Multiplier", ptstr->ppist);

	    pgk->dMultiplier = dMultiplier;

	    //- get MembraneDependence = 0.0

	    double dMembraneDependence = SymbolParameterResolveValue(phsle, "MembraneDependence", ptstr->ppist);

	    pgk->dMembraneDependence = dMembraneDependence;

	    //- get Nominator = -1.0

	    double dNominator = SymbolParameterResolveValue(phsle, "Nominator", ptstr->ppist);

	    int iNominator = dNominator;

	    pgk->iNominator = iNominator;

	    //- get DeNominatorOffset = 0.0

	    double dDeNominatorOffset = SymbolParameterResolveValue(phsle, "DeNominatorOffset", ptstr->ppist);

	    pgk->dDeNominatorOffset = dDeNominatorOffset;

	    //- get MembraneOffset = 5.0e-3

	    double dMembraneOffset = SymbolParameterResolveValue(phsle, "MembraneOffset", ptstr->ppist);

	    pgk->dMembraneOffset = dMembraneOffset;

	    //- get TauDenormalizer = -10.0e-3

	    double dTauDenormalizer = SymbolParameterResolveValue(phsle, "TauDenormalizer", ptstr->ppist);

	    pgk->dTauDenormalizer = dTauDenormalizer;

	    if (dMultiplier == FLT_MAX
		|| dMembraneDependence == FLT_MAX
		|| dNominator == FLT_MAX
		|| dDeNominatorOffset == FLT_MAX
		|| dMembraneOffset == FLT_MAX
		|| dTauDenormalizer == FLT_MAX)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else
	{
	    pmcd->iStatus = STATUS_UNKNOWN_TYPE;

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- otherwise

    else
    {
	//- an error

	pmcd->iStatus = STATUS_UNKNOWN_TYPE;

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
solver_channel_activation_concentration_processor(struct TreespaceTraversal *ptstr, void *pvUserdata)
{
    //- set default result : ok

    int iResult = TSTR_PROCESSOR_SUCCESS;

    //- get actual symbol

    struct symtab_HSolveListElement *phsle = TstrGetActual(ptstr);

    //- get user data

    struct MathComponentData * pmcd = (struct MathComponentData *)pvUserdata;

    //- get current math component

    struct MathComponent * pmc = pmcd->pmc;

    struct ChannelActConc * pcac = (struct ChannelActConc *)pmc;

    //- if conceptual gate

    if (instanceof_conceptual_gate(phsle))
    {
	if (pmcd->iStatus == 1)
	{
	    //- initial table index

	    pcac->pgc.gc.iTable = -1;

	    //- get power

	    double dPower = SymbolParameterResolveValue(phsle, "POWER", ptstr->ppist);

	    int iPower = dPower;

	    pcac->pgc.iPower = iPower;

	    //- get initial state

	    double dInitActivation = SymbolParameterResolveValue(phsle, "state_init", ptstr->ppist);

	    pcac->pgc.gc.dInitActivation = dInitActivation;

	    if (dPower == FLT_MAX
		|| dInitActivation == FLT_MAX)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else if (pmcd->iStatus == 4)
	{
	    //- initial table index

	    pcac->pac.ac.iTable = -1;

	    //- get power

	    double dPower = SymbolParameterResolveValue(phsle, "POWER", ptstr->ppist);

	    int iPower = dPower;

	    pcac->pac.iPower = iPower;

	    //- get initial state

	    double dInitActivation = SymbolParameterResolveValue(phsle, "state_init", ptstr->ppist);

	    pcac->pac.ac.dInitActivation = dInitActivation;

	    if (dPower == FLT_MAX
		|| dInitActivation == FLT_MAX)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else
	{
	    pmcd->iStatus = STATUS_UNKNOWN_TYPE;

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- if gate kinetic

    else if (instanceof_gate_kinetic(phsle))
    {
	//! 2: forward, act
	//! 3: backward, act
	//! 5: forward, inact
	//! 6: backward, inact

	if (pmcd->iStatus == 2
	    || pmcd->iStatus == 3)
	{
	    struct PoweredGateConcept * ppgc = &pcac->pgc;

	    struct GateKinetic *pgk
		= (pmcd->iStatus == 2
		   ? &ppgc->gc.gkForward
		   : &ppgc->gc.gkBackward);

	    //- initialize table index

	    ppgc->gc.iTable = -1;

	    //- get Multiplier = 35.0e3

	    double dMultiplier = SymbolParameterResolveValue(phsle, "Multiplier", ptstr->ppist);

	    pgk->dMultiplier = dMultiplier;

	    //- get MembraneDependence = 0.0

	    double dMembraneDependence = SymbolParameterResolveValue(phsle, "MembraneDependence", ptstr->ppist);

	    pgk->dMembraneDependence = dMembraneDependence;

	    //- get Nominator = -1.0

	    double dNominator = SymbolParameterResolveValue(phsle, "Nominator", ptstr->ppist);

	    int iNominator = dNominator;

	    pgk->iNominator = iNominator;

	    //- get DeNominatorOffset = 0.0

	    double dDeNominatorOffset = SymbolParameterResolveValue(phsle, "DeNominatorOffset", ptstr->ppist);

	    pgk->dDeNominatorOffset = dDeNominatorOffset;

	    //- get MembraneOffset = 5.0e-3

	    double dMembraneOffset = SymbolParameterResolveValue(phsle, "MembraneOffset", ptstr->ppist);

	    pgk->dMembraneOffset = dMembraneOffset;

	    //- get TauDenormalizer = -10.0e-3

	    double dTauDenormalizer = SymbolParameterResolveValue(phsle, "TauDenormalizer", ptstr->ppist);

	    pgk->dTauDenormalizer = dTauDenormalizer;

	    if (dMultiplier == FLT_MAX
		|| dMembraneDependence == FLT_MAX
		|| dNominator == FLT_MAX
		|| dDeNominatorOffset == FLT_MAX
		|| dMembraneOffset == FLT_MAX
		|| dTauDenormalizer == FLT_MAX)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else
	{
	    pmcd->iStatus = STATUS_UNKNOWN_TYPE;

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- if activator

    else if (instanceof_concentration_gate_kinetic(phsle))
    {
	//- if forward

	if (pmcd->iStatus == 5)
	{
	    //- basal level, A in EDS1994

	    double dBasalLevel = SymbolParameterResolveValue(phsle, "Base", ptstr->ppist);

	    pcac->pac.ac.dBasalLevel = dBasalLevel;

	    //- time constant, B in EDS1994

	    double dTau = SymbolParameterResolveValue(phsle, "Tau", ptstr->ppist);

	    pcac->pac.ac.dTau = dTau;

	    if (dBasalLevel == FLT_MAX
		|| dTau == FLT_MAX)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else
	{
	    pmcd->iStatus = STATUS_UNKNOWN_TYPE;

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- otherwise

    else
    {
	//- an error

	pmcd->iStatus = STATUS_UNKNOWN_TYPE;
    }

    //- if no error

    if (pmcd->iStatus > 0)
    {
	//- increment the status to indicate what component we have processed

	pmcd->iStatus++;

	if (pmcd->iStatus == 6)
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

    struct symtab_HSolveListElement *phsle = TstrGetActual(ptstr);

    //- get user data

    struct MathComponentData * pmcd = (struct MathComponentData *)pvUserdata;

    //- get current math component

    struct MathComponent * pmc = pmcd->pmc;

    struct ChannelActInact * pcai = (struct ChannelActInact *)pmc;

    //- if conceptual gate

    if (instanceof_conceptual_gate(phsle))
    {
	if (pmcd->iStatus == 1
	    || pmcd->iStatus == 4)
	{
	    struct PoweredGateConcept * ppgc
		= pmcd->iStatus == 1
		  ? &pcai->pgcActivation
		  : &pcai->pgcInactivation;

	    //- get power

	    double dPower = SymbolParameterResolveValue(phsle, "POWER", ptstr->ppist);

	    int iPower = dPower;

	    ppgc->iPower = iPower;

	    //- get initial state

	    double dInitActivation = SymbolParameterResolveValue(phsle, "state_init", ptstr->ppist);

	    ppgc->gc.dInitActivation = dInitActivation;

	    if (dPower == FLT_MAX
		|| dInitActivation == FLT_MAX)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else
	{
	    pmcd->iStatus = STATUS_UNKNOWN_TYPE;

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- if gate kinetic

    else if (instanceof_gate_kinetic(phsle))
    {
	//! 2: forward, act
	//! 3: backward, act
	//! 5: forward, inact
	//! 6: backward, inact

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
		   ? &ppgc->gc.gkForward
		   : &ppgc->gc.gkBackward);

	    //- initialize table index

	    ppgc->gc.iTable = -1;

	    //- get Multiplier = 35.0e3

	    double dMultiplier = SymbolParameterResolveValue(phsle, "Multiplier", ptstr->ppist);

	    pgk->dMultiplier = dMultiplier;

	    //- get MembraneDependence = 0.0

	    double dMembraneDependence = SymbolParameterResolveValue(phsle, "MembraneDependence", ptstr->ppist);

	    pgk->dMembraneDependence = dMembraneDependence;

	    //- get Nominator = -1.0

	    double dNominator = SymbolParameterResolveValue(phsle, "Nominator", ptstr->ppist);

	    int iNominator = dNominator;

	    pgk->iNominator = iNominator;

	    //- get DeNominatorOffset = 0.0

	    double dDeNominatorOffset = SymbolParameterResolveValue(phsle, "DeNominatorOffset", ptstr->ppist);

	    pgk->dDeNominatorOffset = dDeNominatorOffset;

	    //- get MembraneOffset = 5.0e-3

	    double dMembraneOffset = SymbolParameterResolveValue(phsle, "MembraneOffset", ptstr->ppist);

	    pgk->dMembraneOffset = dMembraneOffset;

	    //- get TauDenormalizer = -10.0e-3

	    double dTauDenormalizer = SymbolParameterResolveValue(phsle, "TauDenormalizer", ptstr->ppist);

	    pgk->dTauDenormalizer = dTauDenormalizer;

	    if (dMultiplier == FLT_MAX
		|| dMembraneDependence == FLT_MAX
		|| dNominator == FLT_MAX
		|| dDeNominatorOffset == FLT_MAX
		|| dMembraneOffset == FLT_MAX
		|| dTauDenormalizer == FLT_MAX)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else
	{
	    pmcd->iStatus = STATUS_UNKNOWN_TYPE;

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- otherwise

    else
    {
	//- an error

	pmcd->iStatus = STATUS_UNKNOWN_TYPE;

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
solver_mathcomponent_finalizer(struct TreespaceTraversal *ptstr, void *pvUserdata)
{
    //- set default result : ok

    int iResult = TSTR_PROCESSOR_SUCCESS;

    //- get actual symbol

    struct symtab_HSolveListElement *phsle = TstrGetActual(ptstr);

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

    struct symtab_HSolveListElement *phsle = TstrGetActual(ptstr);

    //- get user data

    struct MathComponentData * pmcd = (struct MathComponentData *)pvUserdata;

    //- get pointer to intermediary

    struct Heccer *pheccer = pmcd->pheccer;

    //- get current math component

    struct MathComponent * pmc = pmcd->pmc;

    int iType;

    //- if structure only

    if (instanceof_group(phsle)
	|| instanceof_segment(phsle)
	|| instanceof_v_segment(phsle))
    {
	//- ok, skip

	iType = -2;
    }

    //- if gate and related

    else if (instanceof_gate_kinetic(phsle)
	     || instanceof_conceptual_gate(phsle)
	     || instanceof_concentration_gate_kinetic(phsle))
    {
	//- ok, skip

	iType = -2;
    }

    //- else

    else
    {
	//- get type of math component

	iType = pmcd->piTypes[pmcd->iCurrentType];

	//- register the type in the math component array

	pmc->iType = iType;

	//- register serial

	pmc->iSerial = PidinStackToSerial(ptstr->ppist);
    }

    //- depending on the type

    switch (iType)
    {
	//- for a channel

    case MATH_TYPE_ChannelAct:
    {
	//t segv

	((int *)0)[0] = 0;
	break;
    }
    case MATH_TYPE_ChannelActInact:
    case MATH_TYPE_ChannelActConc:
    {
	//- get maximal conductance

	double dMaximalConductance = SymbolParameterResolveScaledValue(phsle, "GMAX", ptstr->ppist);

	//- get reversal potential

	double dReversalPotential = SymbolParameterResolveValue(phsle, "Ek", ptstr->ppist);

	if (dMaximalConductance == FLT_MAX
	    || dReversalPotential == FLT_MAX)
	{
	    pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

	    iResult = TSTR_PROCESSOR_ABORT;
	}

	//- set values

	if (iType == MATH_TYPE_ChannelActInact)
	{
	    struct ChannelActInact * pcai = (struct ChannelActInact *)pmc;

	    pcai->dMaximalConductance = dMaximalConductance;

	    pcai->dReversalPotential = dReversalPotential;

	    pcai->iPool = -1;
	}
	else if (iType == MATH_TYPE_ChannelActConc)
	{
	    struct ChannelActConc * pcac = (struct ChannelActConc *)pmc;

	    pcac->dMaximalConductance = dMaximalConductance;

	    pcac->dReversalPotential = dReversalPotential;

	    pcac->iPool = -1;

	    //m contributes to this concentration pool, -1 for none, boolean indicator only.

	    struct symtab_IOList *piolPool
		= SymbolResolveInput(phsle, ptstr->ppist, "concen", 0);

	    if (piolPool)
	    {
		//t this is a hack to get things to work right now,
		//t see TODOs in neurospaces

		//t this hack will not work when components are grouped or so

		int iSerialDifference
		    = piolPool->hsle.smapPrincipal.iParent - phsle->smapPrincipal.iParent;

		pcac->pac.ac.iActivator = PidinStackToSerial(ptstr->ppist) + iSerialDifference;
	    }
	}
	else
	{
	    pmcd->iStatus = STATUS_UNKNOWN_TYPE;

	    iResult = TSTR_PROCESSOR_ABORT;
	}

	//- if no errors yet

	if (pmcd->iStatus > 0)
	{
	    //! push and pop, the quick hack

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
		pmcd->iStatus = STATUS_UNKNOWN_ERROR;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    TstrDelete(ptstrChannel);

	    //- advance to the next math component

	    pmcd->pmc = MathComponentNext(pmcd->pmc);

	    pmcd->iCurrentType++;
	}
	break;
    }

    //- for an exponential

    case MATH_TYPE_ExponentialDecay:
    {
	//- get math component data

	struct ExponentialDecay * pexdec
	    = (struct ExponentialDecay *)pmc;

	//- get initial value

	double dInitValue = SymbolParameterResolveValue(phsle, "concen_init", ptstr->ppist);

	//- get beta

	double dBeta = SymbolParameterResolveScaledValue(phsle, "BETA", ptstr->ppist);

	//- get steady state

	double dSteadyState = SymbolParameterResolveValue(phsle, "BASE", ptstr->ppist);

	//- get tau

	double dTau = SymbolParameterResolveValue(phsle, "TAU", ptstr->ppist);

	if (dInitValue == FLT_MAX
	    || dBeta == FLT_MAX
	    || dSteadyState == FLT_MAX
	    || dTau == FLT_MAX)
	{
	    pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

	    iResult = TSTR_PROCESSOR_ABORT;
	}

	//- set values

	pexdec->dInitValue = dInitValue;
	pexdec->dBeta = dBeta;
	pexdec->dSteadyState = dSteadyState;
	pexdec->dTau = dTau;

	//- find contributing channels

	pexdec->iExternal = -1;

	int iInput = 0;

	struct symtab_IOList *piolExternal
	    = SymbolResolveInput(phsle, ptstr->ppist, "Ik", iInput);

	while (piolExternal)
	{
	    if (!instanceof_channel(&piolExternal->hsle))
	    {
		pmcd->iStatus = STATUS_NON_CHANNEL_OUTPUTS_IK;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    //t this is a hack to get things to work right now,
	    //t see TODOs in neurospaces

	    //t this hack will not work when components are grouped or so

	    int iSerialDifference
		= piolExternal->hsle.smapPrincipal.iParent - phsle->smapPrincipal.iParent;

	    int iChannel = PidinStackToSerial(ptstr->ppist) + iSerialDifference;

	    pexdec->iExternal = iChannel;

	    //- register the channel as a flux contributor

	    pmcd->ppiConnectors[pmcd->iConnectors][0] = iChannel;
	    pmcd->ppiConnectors[pmcd->iConnectors][1] = PidinStackToSerial(ptstr->ppist);

	    pmcd->iConnectors++;

	    //- next contributing channel

	    iInput++;

	    piolExternal = SymbolResolveInput(phsle, ptstr->ppist, "Ik", iInput);

	    //t multiple contributors are not supported yet

	    if (piolExternal)
	    {
		pmcd->iStatus = STATUS_MANY_CHANNELS;

		iResult = TSTR_PROCESSOR_ABORT;

		break;
	    }
	}

	//- advance to the next math component

	pmcd->pmc = MathComponentNext(pmcd->pmc);

	pmcd->iCurrentType++;

	break;
    }

    //- for a channel given as steady state and stepped tau

    case MATH_TYPE_ChannelSteadyStateSteppedTau:
    {
	//- get math component data

	struct ChannelSteadyStateSteppedTau *pcsst
	    = (struct ChannelSteadyStateSteppedTau *)pmc;

	//- advance to the next math component

	pmcd->pmc = MathComponentNext(pmcd->pmc);

	pmcd->iCurrentType++;

	//t not implemented

	//t segv

	((int *)0)[0] = 0;

	break;
    }

    //- for a persistent channel given as steady state and tau

    case MATH_TYPE_ChannelPersistentSteadyStateTau:
    {
	//- get math component data

	struct ChannelPersistentSteadyStateTau *pcpst
	    = (struct ChannelPersistentSteadyStateTau *)pmc;

	//- advance to the next math component

	pmcd->pmc = MathComponentNext(pmcd->pmc);

	pmcd->iCurrentType++;

	//t not implemented

	//t segv

	((int *)0)[0] = 0;

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

	pmcd->iStatus = STATUS_CONSISTENCY;

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

    struct symtab_HSolveListElement *phsle = TstrGetActual(ptstr);

    //- get user data

    struct MathComponentData * pmcd = (struct MathComponentData *)pvUserdata;

    //- get pointer to intermediary

    struct Heccer *pheccer = pmcd->pheccer;

    //- set default type : error

    int iType = INT_MAX;

    //- if structure only

    if (instanceof_group(phsle)
	|| instanceof_segment(phsle)
	|| instanceof_v_segment(phsle))
    {
	//- ok, skip

	iType = -2;
    }

    //- if gate and related

    else if (instanceof_gate_kinetic(phsle)
	     || instanceof_conceptual_gate(phsle)
	     || instanceof_concentration_gate_kinetic(phsle))
    {
	//- ok, skip

	iType = -2;
    }

    //- pool

    else if (instanceof_pool(phsle))
    {
	//- ok, register

	iType = MATH_TYPE_ExponentialDecay;
    }

    //- channel

    else if (instanceof_channel(phsle))
    {
	//- if channel has multiple concentration dependencies

	struct symtab_IOList *piolPool1
	    = SymbolResolveInput(phsle, ptstr->ppist, "concen", 1);

	if (piolPool1)
	{
	    //- abort the traversal

	    pmcd->iStatus = STATUS_MANY_POOLS;

	    iResult = TSTR_PROCESSOR_ABORT;
	}

	//- if channel has concentration dependency

	struct symtab_IOList *piolPool0
	    = SymbolResolveInput(phsle, ptstr->ppist, "concen", 0);

	if (piolPool0)
	{
	    //- is a concentration dependent channel

	    iType = MATH_TYPE_ChannelActConc;
	}

	//- else

	else
	{
	    //t this needs to be worked out:

	    //- get name of channel

	    char * pcName = SymbolGetName(phsle);

	    //t check for other types

	    if (strncasecmp(pcName, "nap", strlen("nap")) == 0)
	    {
		//t MATH_TYPE_ChannelAct: only one gate (nap)

		iType = MATH_TYPE_ChannelAct;
	    }
	    else if (strncasecmp(pcName, "km", strlen("km")) == 0)
	    {
		//t MATH_TYPE_ChannelPersistentSteadyStateTau: steady state with two parts (km)

		iType = MATH_TYPE_ChannelPersistentSteadyStateTau;
	    }
	    else if (strncasecmp(pcName, "kh", strlen("kh")) == 0)
	    {
		//t MATH_TYPE_ChannelPersistentSteadyStateDualTau: tau with two parts ? (kh)

		iType = MATH_TYPE_ChannelPersistentSteadyStateDualTau;
	    }
	    else if (strncasecmp(pcName, "kdr", strlen("kdr")) == 0)
	    {
		//t MATH_TYPE_ChannelSteadyStateSteppedTau: steady state with 2x2 parts, tau with 2 parts (kdr)

		iType = MATH_TYPE_ChannelSteadyStateSteppedTau;
	    }
	    else
	    {
		//- is an activating - inactivating channel

		iType = MATH_TYPE_ChannelActInact;
	    }
	}

	//t check functions in parameters

	//t MATH_TYPE_Nernst
	//t MATH_TYPE_MGBlocker

	//t check for attachments (synchans)
    }

    //- register type

    if (!MathComponentDataTypeRegister(pmcd, iType))
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

	    //m solution engine

	    pheccer,

	    //m compartment number

	    0,

	    //m compartment 2 mechanism convertor

	    NULL,

	    //m current compartment

	    NULL,

	    NULL,

	    //m array of all math component types

	    0,

	    0,

	    NULL,

	    //m current mathcomponent

	    NULL,

	    //m number of spikegens

	    0,

	    //m operational status: positive is positive, negative is negative (error)

	    1,

	    //m channels that contribute to a pool

	    //! to set the iPool boolean indicator

	    0,

	    NULL,

	};

	//t should try to get rid of this allocation somehow

#define MAXIMUM_NUMBER_OF_CHANNEL_CONTRIBUTORS 10000

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

	//t to remove this 'opportunistic hack', neurospaces should
	//t (1) serve the model a bit cleaner,
	//t (2) by incorporating the functions into the symbol hierarchy.
	//t See relevant comments in symbol hierarchy.

#define MAXIMUM_NUMBER_OF_FUNCTIONS 10000

	//! + 1 for '-1' terminator

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

		if (MathComponentDataTypeRegister(&mcd, -1))
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

			    //t not sure if recycling is still allowed ...

			    ptstr->iStatus = TSTR_STATUS_NEW;
			    ptstr->pfProcesor = solver_mathcomponent_processor;
			    ptstr->pfFinalizer = solver_mathcomponent_finalizer;
			    ptstr->pvFinalizer = (void *)&mcd;

			    iResult = TstrGo(ptstr, phsleModel);

			    //- register number of math components

			    pmca->iMathComponents = mcd.iCurrentType;

			    //- do a consistency check on the types encountered during the two traversals

			    if (mcd.piTypes[mcd.iCurrentType] != -1)
			    {
				mcd.iStatus = STATUS_CONSISTENCY;

				iResult = FALSE;
			    }
			}
			else
			{
			    mcd.iStatus = STATUS_MEMORY;

			    iResult = FALSE;
			}
		    }
		    else
		    {
			mcd.iStatus = STATUS_MEMORY;

			iResult = FALSE;
		    }
		}
		else
		{
		    mcd.iStatus = STATUS_MEMORY;

		    iResult = FALSE;
		}
	    }
	}

	//t sort the registry

	//- link the mathcomponents together

	iResult = iResult && cellsolver_linkmathcomponents(pheccer, &mcd);

	//- delete treespace traversal

	TstrDelete(ptstr);

	//t decide if we want to keep piTypes or not, it might
	//t be useful to keep.

	//- delete channel contributors registry

	{
	    int i;

	    for (i = 0 ; i < MAXIMUM_NUMBER_OF_CHANNEL_CONTRIBUTORS ; i++)
	    {
		free(mcd.ppiConnectors[i]);
	    }

	    free(mcd.ppiConnectors);
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

	    if (pcac->pac.ac.iActivator != -1)
	    {
		int iActivator = MathComponentArrayLookupSerial(pmca, pcac->pac.ac.iActivator);

		pcac->pac.ac.iActivator = iActivator;
	    }

	    //- or

	    else
	    {
		//- an error

		pmcd->iStatus = STATUS_CONSISTENCY;

		iResult = FALSE;
	    }

	    break;
	}
	case MATH_TYPE_ExponentialDecay:
	{
	    struct ExponentialDecay * pexdec = (struct ExponentialDecay *)pmc;

	    int iExternalSerial = pexdec->iExternal;

	    if (iExternalSerial != -1)
	    {
		int iExternalIndex = MathComponentArrayLookupSerial(pmca, iExternalSerial);

		pexdec->iExternal = iExternalIndex;
	    }
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
/* 	pfResult = solver_channel_steadystate_steppedtau_processor; */
    }
    else if (iType == MATH_TYPE_ChannelPersistentSteadyStateTau)
    {
/* 	pfResult = solver_channel_persistent_steadystate_tau_processor; */
    }
    else if (iType == MATH_TYPE_ChannelPersistentSteadyStateDualTau)
    {
/* 	pfResult = solver_channel_persistent_steadystate_dualtau_processor; */
    }
    else if (iType == MATH_TYPE_ChannelAct)
    {
	pfResult = solver_channel_activation_processor;
    }
    else
    {
	//t segv

	((int *)0)[0] = 0;
    }

    //- return result

    return(pfResult);
}


