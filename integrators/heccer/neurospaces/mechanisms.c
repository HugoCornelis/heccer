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

#include <neurospaces/function.h>
#include <neurospaces/pidinstack.h>
#include <neurospaces/treespacetraversal.h>

#include "heccer/addressing.h"
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
#define STATUS_CONSTANT_NERNST -10
#define STATUS_NON_POOL_FOR_NERNST -11


static int ConnectionSource2Target(struct MathComponentData * pmcd, struct MathComponent * pmc);

static
int
MathComponentDataStatusSet(struct MathComponentData * pmcd, int iStatus);

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
solver_channel_persistent_steadystate_dualtau_processor(struct TreespaceTraversal *ptstr, void *pvUserdata);

static
int
solver_channel_persistent_steadystate_tau_processor(struct TreespaceTraversal *ptstr, void *pvUserdata);

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
MathComponentDataStatusSet(struct MathComponentData * pmcd, int iStatus)
{
    //- set default result : current status

    int iResult = pmcd->iStatus;

    //- if everything still ok

    if (iResult > 0)
    {
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

		MathComponentDataStatusSet(pmcd, STATUS_OVERFLOW);
	    }
	}
    }

    //- else

    else
    {
	//- abort the traversal, fatal failure

	//t the current serial and type cursor give an indication
	//t of what model component caused the failure

	MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE);
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
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE);

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
		   ? &ppgc->gc.parameters.gkForward
		   : &ppgc->gc.parameters.gkBackward);

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
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE);

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- otherwise

    else
    {
	//- an error

	MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE);

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
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

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
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE);

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
		   ? &ppgc->gc.parameters.gkForward
		   : &ppgc->gc.parameters.gkBackward);

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
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE);

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

	    pcac->pac.ac.parameters.dBasalLevel = dBasalLevel;

	    //- time constant, B in EDS1994

	    double dTau = SymbolParameterResolveValue(phsle, "Tau", ptstr->ppist);

	    pcac->pac.ac.parameters.dTau = dTau;

	    if (dBasalLevel == FLT_MAX
		|| dTau == FLT_MAX)
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE);

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- otherwise

    else
    {
	//- an error

	MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE);
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
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE);

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
		   ? &ppgc->gc.parameters.gkForward
		   : &ppgc->gc.parameters.gkBackward);

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
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE);

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- otherwise

    else
    {
	//- an error

	MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE);

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

    struct symtab_HSolveListElement *phsle = TstrGetActual(ptstr);

    //- get user data

    struct MathComponentData * pmcd = (struct MathComponentData *)pvUserdata;

    //- get current math component

    struct MathComponent * pmc = pmcd->pmc;

    struct ChannelPersistentSteadyStateDualTau * pcpsdt
	= (struct ChannelPersistentSteadyStateDualTau *)pmc;

    //- if conceptual gate

    if (instanceof_conceptual_gate(phsle))
    {
	if (pmcd->iStatus == 1)
	{
	    //- initialize table pointers

	    pcpsdt->iFirstTable = -1;
	    pcpsdt->iSecondTable = -1;

	    //- get powers

	    double dFirstPower = SymbolParameterResolveValue(phsle, "iFirstPower", ptstr->ppist);
	    int iFirstPower = dFirstPower;
	    pcpsdt->iFirstPower = iFirstPower;

	    double dSecondPower = SymbolParameterResolveValue(phsle, "iSecondPower", ptstr->ppist);
	    int iSecondPower = dSecondPower;
	    pcpsdt->iSecondPower = iSecondPower;

	    //- get initial states

	    double dFirstInitActivation = SymbolParameterResolveValue(phsle, "dFirstInitActivation", ptstr->ppist);
	    pcpsdt->dFirstInitActivation = dFirstInitActivation;

	    double dSecondInitActivation = SymbolParameterResolveValue(phsle, "dSecondInitActivation", ptstr->ppist);
	    pcpsdt->dSecondInitActivation = dSecondInitActivation;

	    //- get steady states

	    double dFirstSteadyState = SymbolParameterResolveValue(phsle, "dFirstSteadyState", ptstr->ppist);
	    pcpsdt->parameters1.dSteadyState = dFirstSteadyState;

	    double dSecondSteadyState = SymbolParameterResolveValue(phsle, "dSecondSteadyState", ptstr->ppist);
	    pcpsdt->parameters2.dSteadyState = dSecondSteadyState;

	    if (dFirstPower == FLT_MAX
		|| dFirstInitActivation == FLT_MAX
		|| dFirstSteadyState == FLT_MAX
		|| dSecondPower == FLT_MAX
		|| dSecondInitActivation == FLT_MAX
		|| dSecondSteadyState == FLT_MAX)
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE);

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- if gate kinetic

    else if (instanceof_gate_kinetic(phsle))
    {
	//! 2: tau 1
	//! 3: tau 2

	if (pmcd->iStatus == 2
	    || pmcd->iStatus == 3)
	{
	    struct dualtaucomponent * pdtc
		= (pmcd->iStatus == 2
		   ? &pcpsdt->parameters1.tau
		   : &pcpsdt->parameters2.tau);

	    //- get Multiplier = 35.0e3

	    double dMultiplier = SymbolParameterResolveValue(phsle, "dMultiplier", ptstr->ppist);

	    pdtc->dMultiplier = dMultiplier;

	    //- get DeNominatorOffset = 0.0

	    double dDeNominatorOffset = SymbolParameterResolveValue(phsle, "dDeNominatorOffset", ptstr->ppist);

	    pdtc->dDeNominatorOffset = dDeNominatorOffset;

	    //- get MembraneOffset = 5.0e-3

	    double dMembraneOffset = SymbolParameterResolveValue(phsle, "dMembraneOffset", ptstr->ppist);

	    pdtc->dMembraneOffset = dMembraneOffset;

	    //- get TauDenormalizer = -10.0e-3

	    double dTauDenormalizer = SymbolParameterResolveValue(phsle, "dTauDenormalizer", ptstr->ppist);

	    pdtc->dTauDenormalizer = dTauDenormalizer;

	    if (dMultiplier == FLT_MAX
		|| dDeNominatorOffset == FLT_MAX
		|| dMembraneOffset == FLT_MAX
		|| dTauDenormalizer == FLT_MAX)
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE);

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- otherwise

    else
    {
	//- an error

	MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE);

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

    struct symtab_HSolveListElement *phsle = TstrGetActual(ptstr);

    //- get user data

    struct MathComponentData * pmcd = (struct MathComponentData *)pvUserdata;

    //- get current math component

    struct MathComponent * pmc = pmcd->pmc;

    struct ChannelPersistentSteadyStateTau * pcpst
	= (struct ChannelPersistentSteadyStateTau *)pmc;

    //- if conceptual gate

    if (instanceof_conceptual_gate(phsle))
    {
	if (pmcd->iStatus == 1)
	{
	    //- initialize table pointer

	    pcpst->iTable = -1;

	    //- get power

	    double dPower = SymbolParameterResolveValue(phsle, "POWER", ptstr->ppist);
	    int iPower = dPower;
	    pcpst->iPower = iPower;

	    //- get initial states

	    double dInitActivation = SymbolParameterResolveValue(phsle, "state_init", ptstr->ppist);
	    pcpst->dInitActivation = dInitActivation;

	    if (dPower == FLT_MAX
		|| dInitActivation == FLT_MAX)
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE);

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- if gate kinetic

    else if (instanceof_gate_kinetic(phsle))
    {
	if (pmcd->iStatus == 2)
	{
	    struct single_steady_state * pss = &pcpst->parameters.ss;

	    //- get Nominator

	    double dNominator = SymbolParameterResolveValue(phsle, "dNominator", ptstr->ppist);

	    pss->dNominator = dNominator;

	    //- get Multiplier1

	    double dMultiplier1 = SymbolParameterResolveValue(phsle, "dMultiplier1", ptstr->ppist);

	    pss->dMultiplier1 = dMultiplier1;

	    //- get MembraneOffset1

	    double dMembraneOffset1 = SymbolParameterResolveValue(phsle, "dMembraneOffset1", ptstr->ppist);

	    pss->dMembraneOffset1 = dMembraneOffset1;

	    //- get TauDenormalizer1

	    double dTauDenormalizer1 = SymbolParameterResolveValue(phsle, "dTauDenormalizer1", ptstr->ppist);

	    pss->dTauDenormalizer1 = dTauDenormalizer1;

	    //- get Multiplier2

	    double dMultiplier2 = SymbolParameterResolveValue(phsle, "dMultiplier2", ptstr->ppist);

	    pss->dMultiplier2 = dMultiplier2;

	    //- get MembraneOffset2

	    double dMembraneOffset2 = SymbolParameterResolveValue(phsle, "dMembraneOffset2", ptstr->ppist);

	    pss->dMembraneOffset2 = dMembraneOffset2;

	    //- get TauDenormalizer2

	    double dTauDenormalizer2 = SymbolParameterResolveValue(phsle, "dTauDenormalizer2", ptstr->ppist);

	    pss->dTauDenormalizer2 = dTauDenormalizer2;

	    if (dNominator == FLT_MAX
		|| dMultiplier1 == FLT_MAX
		|| dMembraneOffset1 == FLT_MAX
		|| dTauDenormalizer1 == FLT_MAX
		|| dMultiplier2 == FLT_MAX
		|| dMembraneOffset2 == FLT_MAX
		|| dTauDenormalizer2 == FLT_MAX)
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else if (pmcd->iStatus == 3)
	{
	    struct single_time_constant * ptc = &pcpst->parameters.tc;

	    //- get Nominator

	    double dNominator = SymbolParameterResolveValue(phsle, "dNominator", ptstr->ppist);

	    ptc->dNominator = dNominator;

	    //- get DeNominatorOffset

	    double dDeNominatorOffset = SymbolParameterResolveValue(phsle, "dDeNominatorOffset", ptstr->ppist);

	    ptc->dDeNominatorOffset = dDeNominatorOffset;

	    //- get MembraneOffset

	    double dMembraneOffset = SymbolParameterResolveValue(phsle, "dMembraneOffset", ptstr->ppist);

	    ptc->dMembraneOffset = dMembraneOffset;

	    //- get TauDenormalizer

	    double dTauDenormalizer = SymbolParameterResolveValue(phsle, "dTauDenormalizer", ptstr->ppist);

	    ptc->dTauDenormalizer = dTauDenormalizer;

	    if (dNominator == FLT_MAX
		|| dDeNominatorOffset == FLT_MAX
		|| dMembraneOffset == FLT_MAX
		|| dTauDenormalizer == FLT_MAX)
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE);

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- otherwise

    else
    {
	//- an error

	MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE);

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
solver_channel_steadystate_steppedtau_processor(struct TreespaceTraversal *ptstr, void *pvUserdata)
{
    //- set default result : ok

    int iResult = TSTR_PROCESSOR_SUCCESS;

    //- get actual symbol

    struct symtab_HSolveListElement *phsle = TstrGetActual(ptstr);

    //- get user data

    struct MathComponentData * pmcd = (struct MathComponentData *)pvUserdata;

    //- get current math component

    struct MathComponent * pmc = pmcd->pmc;

    struct ChannelSteadyStateSteppedTau * pcpsdt
	= (struct ChannelSteadyStateSteppedTau *)pmc;

    //- if conceptual gate

    if (instanceof_conceptual_gate(phsle))
    {
	if (pmcd->iStatus == 1)
	{
	    //- initialize table pointer

	    pcpsdt->iFirstTable = -1;

	    //- get power

	    double dFirstPower = SymbolParameterResolveValue(phsle, "POWER", ptstr->ppist);
	    int iFirstPower = dFirstPower;
	    pcpsdt->iFirstPower = iFirstPower;

	    //- get initial state

	    double dFirstInitActivation = SymbolParameterResolveValue(phsle, "state_init", ptstr->ppist);
	    pcpsdt->dFirstInitActivation = dFirstInitActivation;

	    if (dFirstPower == FLT_MAX
		|| dFirstInitActivation == FLT_MAX)
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else if (pmcd->iStatus == 8)
	{
	    //- initialize table pointer

	    pcpsdt->iSecondTable = -1;

	    //- get power

	    double dSecondPower = SymbolParameterResolveValue(phsle, "POWER", ptstr->ppist);
	    int iSecondPower = dSecondPower;
	    pcpsdt->iSecondPower = iSecondPower;

	    //- get initial state

	    double dSecondInitActivation = SymbolParameterResolveValue(phsle, "state_init", ptstr->ppist);
	    pcpsdt->dSecondInitActivation = dSecondInitActivation;

	    if (dSecondPower == FLT_MAX
		|| dSecondInitActivation == FLT_MAX)
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE);

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

		//- get Multiplier

		double dMultiplier = SymbolParameterResolveValue(phsle, "Multiplier", ptstr->ppist);

		pa->dMultiplier = dMultiplier;

		//- get MembraneDependenceOffset

		double dMembraneDependenceOffset = SymbolParameterResolveValue(phsle, "MembraneDependenceOffset", ptstr->ppist);

		pa->dMembraneDependenceOffset = dMembraneDependenceOffset;

		//- get dDeNominatorOffset

		double dDeNominatorOffset = SymbolParameterResolveValue(phsle, "DeNominatorOffset", ptstr->ppist);

		pa->dDeNominatorOffset = dDeNominatorOffset;

		//- get MembraneOffset

		double dMembraneOffset = SymbolParameterResolveValue(phsle, "MembraneOffset", ptstr->ppist);

		pa->dMembraneOffset = dMembraneOffset;

		//- get TauDenormalizer

		double dTauDenormalizer = SymbolParameterResolveValue(phsle, "TauDenormalizer", ptstr->ppist);

		pa->dTauDenormalizer = dTauDenormalizer;

		if (dMultiplier == FLT_MAX
		    || dMembraneDependenceOffset == FLT_MAX
		    || dDeNominatorOffset == FLT_MAX
		    || dMembraneOffset == FLT_MAX
		    || dTauDenormalizer == FLT_MAX)
		{
		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

		    iResult = TSTR_PROCESSOR_ABORT;
		}
	    }
	    else
	    {
		struct dual_steadystate_kinetic_part_b * pb = &pdsk->b;

		//- get Multiplier

		double dMultiplier = SymbolParameterResolveValue(phsle, "Multiplier", ptstr->ppist);

		pb->dMultiplier = dMultiplier;

		//- get MembraneDependenceOffset

		double dMembraneDependenceOffset = SymbolParameterResolveValue(phsle, "MembraneDependenceOffset", ptstr->ppist);

		pb->dMembraneDependenceOffset = dMembraneDependenceOffset;

		//- get TauDenormalizer

		double dTauDenormalizer = SymbolParameterResolveValue(phsle, "TauDenormalizer", ptstr->ppist);

		pb->dTauDenormalizer = dTauDenormalizer;

		if (dMultiplier == FLT_MAX
		    || dMembraneDependenceOffset == FLT_MAX
		    || dTauDenormalizer == FLT_MAX)
		{
		    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

		    iResult = TSTR_PROCESSOR_ABORT;
		}
	    }
	}
	else if (pmcd->iStatus == 9)
	{
	    struct SteppedTimeConstantParameters * pdtc
		= &pcpsdt->tc_parameters;

	    //- get threshold

	    double dThreshold = SymbolParameterResolveValue(phsle, "Threshold", ptstr->ppist);

	    pdtc->a.dThreshold = dThreshold;

	    //- get LowTarget

	    double dLowTarget = SymbolParameterResolveValue(phsle, "LowTarget", ptstr->ppist);

	    pdtc->a.dLowTarget = dLowTarget;

	    //- get HighTarget

	    double dHighTarget = SymbolParameterResolveValue(phsle, "HighTarget", ptstr->ppist);

	    pdtc->a.dHighTarget = dHighTarget;

	    if (dThreshold == FLT_MAX
		|| dLowTarget == FLT_MAX
		|| dHighTarget == FLT_MAX)
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else if (pmcd->iStatus == 10)
	{
	    struct SteppedTimeConstantParameters * pdtc
		= &pcpsdt->tc_parameters;

	    //- get DeNominatorOffset

	    double dDeNominatorOffset = SymbolParameterResolveValue(phsle, "DeNominatorOffset", ptstr->ppist);

	    pdtc->b.dDeNominatorOffset = dDeNominatorOffset;

	    //- get MembraneOffset

	    double dMembraneOffset = SymbolParameterResolveValue(phsle, "MembraneOffset", ptstr->ppist);

	    pdtc->b.dMembraneOffset = dMembraneOffset;

	    //- get TauDenormalizer

	    double dTauDenormalizer = SymbolParameterResolveValue(phsle, "TauDenormalizer", ptstr->ppist);

	    pdtc->b.dTauDenormalizer = dTauDenormalizer;

	    if (dDeNominatorOffset == FLT_MAX
		|| dMembraneOffset == FLT_MAX
		|| dTauDenormalizer == FLT_MAX)
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

		iResult = TSTR_PROCESSOR_ABORT;
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE);

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

    //- otherwise

    else
    {
	//- an error

	MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE);

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

	int iNeurospaces = PidinStackToSerial(ptstr->ppist);

	pmc->iSerial = ADDRESSING_NEUROSPACES_2_HECCER(iNeurospaces);
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
    case MATH_TYPE_ChannelSteadyStateSteppedTau:
    {
	//- get maximal conductance

	double dMaximalConductance = SymbolParameterResolveScaledValue(phsle, "GMAX", ptstr->ppist);

	//- get reversal potential

	double dReversalPotential = SymbolParameterResolveValue(phsle, "Ek", ptstr->ppist);

	if (dMaximalConductance == FLT_MAX
	    || dReversalPotential == FLT_MAX)
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

	    iResult = TSTR_PROCESSOR_ABORT;
	}

	//- determine link with math component that computes the
	//- reversal potential, if any

	int iReversalPotential = -1;

	if (SymbolHasNernstEk(phsle, ptstr->ppist))
	{
	    //- currently the nernst intermediary always comes after the channel

	    //! this can be dependent on the other functions present, notably mgblocking.

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
	else if (iType == MATH_TYPE_ChannelActConc)
	{
	    struct ChannelActConc * pcac = (struct ChannelActConc *)pmc;

	    pcac->dMaximalConductance = dMaximalConductance;

	    pcac->dReversalPotential = dReversalPotential;

	    pcac->iReversalPotential = iReversalPotential;

	    pcac->iPool = -1;

	    //m contributes to this concentration pool, -1 for none, boolean indicator only.

	    struct symtab_IOList *piolPool
		= SymbolResolveInput(phsle, ptstr->ppist, "concen", 0);

	    if (piolPool)
	    {
		//t this is a hack to get things to work right now,
		//t see TODOs in neurospaces

		//t this hack will not work when components are in different groups or so

		int iSerialDifference
		    = piolPool->hsle.smapPrincipal.iParent - phsle->smapPrincipal.iParent;

		int iPool = PidinStackToSerial(ptstr->ppist) + iSerialDifference;

		pcac->pac.ac.iActivator = ADDRESSING_NEUROSPACES_2_HECCER(iPool);
	    }
	    else
	    {
		pcac->pac.ac.iActivator = -1;
	    }
	}
	else
	{
	    MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_TYPE);

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
		MathComponentDataStatusSet(pmcd, STATUS_UNKNOWN_ERROR);

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    TstrDelete(ptstrChannel);

	    //- advance to the next math component

	    pmcd->pmc = MathComponentNext(pmcd->pmc);

	    pmcd->iCurrentType++;
	}

	//- if there is a nernst function

	int iFunctions = 1;

	if (SymbolHasNernstEk(phsle, ptstr->ppist))
	{
	    struct InternalNernst * pin = (struct InternalNernst *)pmc;

	    //- get Ek parameter

	    struct symtab_Parameters *pparEk
		= SymbolGetParameter(phsle, "Ek", ptstr->ppist);

	    //- get nernst function

	    struct symtab_Function *pfunNernst
		= ParameterGetFunction(pparEk);

	    //- fetch parameters

	    struct symtab_Parameters *pparCIn
		= FunctionGetParameter(pfunNernst, "Cin");
	    struct symtab_Parameters *pparCOut
		= FunctionGetParameter(pfunNernst, "Cout");
	    struct symtab_Parameters *pparValency
		= FunctionGetParameter(pfunNernst, "valency");
	    struct symtab_Parameters *pparT
		= FunctionGetParameter(pfunNernst, "T");

	    if (!pparCIn
		|| !pparCOut
		|| !pparValency
		|| !pparT)
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

		iResult = TSTR_PROCESSOR_ABORT;

		break;
	    }

	    //- calculate parameter values

	    double dCIn = ParameterResolveValue(pparCIn, ptstr->ppist);
	    double dCOut = ParameterResolveValue(pparCOut, ptstr->ppist);
	    double dValency = ParameterResolveValue(pparValency, ptstr->ppist);
	    double dT = ParameterResolveValue(pparT, ptstr->ppist);

	    if (dCIn == FLT_MAX
		|| dCOut == FLT_MAX
		|| dValency == FLT_MAX
		|| dT == FLT_MAX)
	    {
		MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

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

	    //! neurospaces contains support to evaluate simple functions

	    pin->dInitPotential = SymbolParameterResolveValue(phsle, "Ek", ptstr->ppist);

	    //- find concentration that determines the nernst potential

	    struct symtab_HSolveListElement *phslePool
		= SymbolResolveParameterFunctionalInput
		  (phsle, ptstr->ppist, "Ek", "Cin", 0);

	    //- if found

	    if (phslePool)
	    {
		if (!instanceof_pool(phslePool))
		{
		    MathComponentDataStatusSet(pmcd, STATUS_NON_POOL_FOR_NERNST);

		    iResult = TSTR_PROCESSOR_ABORT;

		    break;
		}

		//t this is a hack to get things to work right now,
		//t see TODOs in neurospaces

		//t this hack will not work when components are in different groups or so

		int iSerialDifference
		    = phslePool->smapPrincipal.iParent - phsle->smapPrincipal.iParent;

		int iPool = PidinStackToSerial(ptstr->ppist) + iSerialDifference;
		int iNernst = PidinStackToSerial(ptstr->ppist) + iFunctions;

		iPool = ADDRESSING_NEUROSPACES_2_HECCER(iPool);
		iNernst = ADDRESSING_NEUROSPACES_2_HECCER(iNernst);

		pin->iInternal = iPool;

		//- register the channel as a flux contributor

		pmcd->ppiConnectors[pmcd->iConnectors][0] = iPool;
		pmcd->ppiConnectors[pmcd->iConnectors][1] = iNernst;

		pmcd->iConnectors++;
	    }
	    else
	    {
		//t fallback to constant nernst, requires changes in the typer

		MathComponentDataStatusSet(pmcd, STATUS_CONSTANT_NERNST);

		iResult = TSTR_PROCESSOR_ABORT;

		break;
	    }

	    //- advance to the next math component

	    pmcd->pmc = MathComponentNext(pmcd->pmc);

	    pmcd->iCurrentType++;

	    iFunctions++;
	}

	//t mgblocking

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
	    MathComponentDataStatusSet(pmcd, STATUS_UNRESOLVABLE_PARAMETERS);

	    iResult = TSTR_PROCESSOR_ABORT;
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
	    struct symtab_IOList *piolExternal
		= SymbolResolveInput(phsle, ptstr->ppist, "Ik", iInput);

	    if (piolExternal)
	    {
		if (!instanceof_channel(&piolExternal->hsle))
		{
		    MathComponentDataStatusSet(pmcd, STATUS_NON_CHANNEL_OUTPUTS_IK);

		    iResult = TSTR_PROCESSOR_ABORT;

		    break;
		}

		//t this is a hack to get things to work right now,
		//t see TODOs in neurospaces

		//t this hack will not work when components are in different groups or so

		int iSerialDifference
		    = piolExternal->hsle.smapPrincipal.iParent - phsle->smapPrincipal.iParent;

		int iChannel = PidinStackToSerial(ptstr->ppist) + iSerialDifference;
		int iPool = PidinStackToSerial(ptstr->ppist);

		iChannel = ADDRESSING_NEUROSPACES_2_HECCER(iChannel);
		iPool = ADDRESSING_NEUROSPACES_2_HECCER(iPool);

		pexdec->piExternal[iInput] = iChannel;

		//- register the channel as a flux contributor

		pmcd->ppiConnectors[pmcd->iConnectors][0] = iChannel;
		pmcd->ppiConnectors[pmcd->iConnectors][1] = iPool;

		pmcd->iConnectors++;
	    }
	    else
	    {
		pexdec->piExternal[iInput] = -1;
	    }
	}

	//- check for to many contributors

	struct symtab_IOList *piolExternal
	    = SymbolResolveInput(phsle, ptstr->ppist, "Ik", iInput);

	if (piolExternal)
	{
	    MathComponentDataStatusSet(pmcd, STATUS_MANY_CHANNELS);

	    iResult = TSTR_PROCESSOR_ABORT;
	}

	//- advance to the next math component

	pmcd->pmc = MathComponentNext(pmcd->pmc);

	pmcd->iCurrentType++;

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

	MathComponentDataStatusSet(pmcd, STATUS_CONSISTENCY);

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

	    MathComponentDataStatusSet(pmcd, STATUS_MANY_POOLS);

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
		//- MATH_TYPE_ChannelAct: only one gate (nap)

		iType = MATH_TYPE_ChannelAct;
	    }
	    else if (strncasecmp(pcName, "km", strlen("km")) == 0)
	    {
		//t MATH_TYPE_ChannelPersistentSteadyStateTau: steady state with two parts (km)

		iType = MATH_TYPE_ChannelPersistentSteadyStateTau;
	    }
	    else if (strncasecmp(pcName, "kh", strlen("kh")) == 0)
	    {
		//- MATH_TYPE_ChannelPersistentSteadyStateDualTau: tau with two parts ? (kh)

		iType = MATH_TYPE_ChannelPersistentSteadyStateDualTau;
	    }
	    else if (strncasecmp(pcName, "kdr", strlen("kdr")) == 0)
	    {
		//t MATH_TYPE_ChannelSteadyStateSteppedTau: steady state with 2x2 parts, tau with 2 parts (kdr)

		iType = MATH_TYPE_ChannelSteadyStateSteppedTau;
	    }
	    else if (strncasecmp(pcName, "kc", strlen("kc")) == 0
		     || strncasecmp(pcName, "k2", strlen("k2")) == 0)
	    {
		//t when the concen was not bound, the test above fails.
		//t need a separate name for the concen gate or so

		iType = MATH_TYPE_ChannelActConc;
	    }
	    else
	    {
		//- is an activating - inactivating channel

		iType = MATH_TYPE_ChannelActInact;
	    }
	}

	//- if the channel has a nernst function

	//t need a separate loop for registering the type or so.

	if (SymbolHasNernstEk(phsle, ptstr->ppist))
	{
	    if (!MathComponentDataTypeRegister(pmcd, iType))
	    {
		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    //t differentiate between internal and external nernst,
	    //t possibly also differentiate with constant nernst

	    iType = MATH_TYPE_InternalNernst;
	}

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
				MathComponentDataStatusSet(&mcd, STATUS_CONSISTENCY);

				iResult = FALSE;
			    }
			}
			else
			{
			    MathComponentDataStatusSet(&mcd, STATUS_MEMORY);

			    iResult = FALSE;
			}
		    }
		    else
		    {
			MathComponentDataStatusSet(&mcd, STATUS_MEMORY);

			iResult = FALSE;
		    }
		}
		else
		{
		    MathComponentDataStatusSet(&mcd, STATUS_MEMORY);

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

	if (mcd.iStatus < 0)
	{
	    fprintf(stderr, "cellsolver_getmathcomponents() returned error code %i\n", mcd.iStatus);
	    fprintf(stderr, "last processed mathcomponent is %i\n", mcd.iCurrentType);
	    fprintf(stderr, "external error return is %i\n", iResult);
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

/* 	    //- or */

/* 	    else */
/* 	    { */
/* 		//- an error */

/*      MathComponentDataStatusSet(pmcd, STATUS_CONSISTENCY); */

/* 		iResult = FALSE; */
/* 	    } */

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
    else
    {
	//t segv

	((int *)0)[0] = 0;
    }

    //- return result

    return(pfResult);
}


