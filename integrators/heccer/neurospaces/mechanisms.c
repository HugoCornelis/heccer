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

    //m current compartment

    struct symtab_HSolveListElement *phsleCompartment;

    struct PidinStack *ppistCompartment;

    //m number of math components

    int iMathComponents;

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
};


#define STATUS_OVERFLOW -1
#define STATUS_UNKNOWN_TYPE -2
#define STATUS_MANY_POOLS -3
#define STATUS_MEMORY -4
#define STATUS_CONSISTENCY -5
#define STATUS_UNRESOLVABLE_PARAMETERS -6
#define STATUS_MANY_CHANNELS -7
#define STATUS_UNKNOWN_ERROR -8


static
int
MathComponentDataTypeRegister(struct MathComponentData * pmcd, int iType);

static
int
solver_mathcomponent_processor(struct TreespaceTraversal *ptstr, void *pvUserdata);

static int cellsolver_getmathcomponents(struct Heccer *pheccer, struct TranslationService *pts);

static int cellsolver_linkmathcomponents(struct Heccer *pheccer);

/* static int cellsolver_setupmechanisms(struct Heccer *pheccer); */


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
	if (pmcd->iStatus == 1)
	{
	    //- get power

	    struct symtab_Parameters * pparPower
		= SymbolGetParameter(phsle, "POWER", ptstr->ppist);

	    if (!pparPower)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    int iPower = ParameterResolveValue(pparPower, ptstr->ppist);

	    pcai->pgcActivation.iPower = iPower;

	    //- get initial state

	    struct symtab_Parameters * pparStateInit
		= SymbolGetParameter(phsle, "state_init", ptstr->ppist);

	    if (!pparStateInit)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    double dInitActivation = ParameterResolveValue(pparStateInit, ptstr->ppist);

	    pcai->pgcActivation.gc.dInitActivation = dInitActivation;
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
	//- if forward

	if (pmcd->iStatus == 2)
	{
	    //- initial table index

	    pcai->pgcActivation.gc.iTable = -1;

	    //- get Multiplier = 35.0e3

	    struct symtab_Parameters * pparMultiplier
		= SymbolGetParameter(phsle, "Multiplier", ptstr->ppist);

	    if (!pparMultiplier)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    double dMultiplier = ParameterResolveValue(pparMultiplier, ptstr->ppist);

	    pcai->pgcActivation.gc.gkForward.dMultiplier = dMultiplier;

	    //- get MembraneDependence = 0.0

	    struct symtab_Parameters * pparMembraneDependence
		= SymbolGetParameter(phsle, "MembraneDependence", ptstr->ppist);

	    if (!pparMembraneDependence)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    double dMembraneDependence = ParameterResolveValue(pparMembraneDependence, ptstr->ppist);

	    pcai->pgcActivation.gc.gkForward.dMembraneDependence = dMembraneDependence;

	    //- get Nominator = -1.0

	    struct symtab_Parameters * pparNominator
		= SymbolGetParameter(phsle, "Nominator", ptstr->ppist);

	    if (!pparNominator)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    int iNominator = ParameterResolveValue(pparNominator, ptstr->ppist);

	    pcai->pgcActivation.gc.gkForward.iNominator = iNominator;

	    //- get DeNominatorOffset = 0.0

	    struct symtab_Parameters * pparDeNominatorOffset
		= SymbolGetParameter(phsle, "DeNominatorOffset", ptstr->ppist);

	    if (!pparDeNominatorOffset)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    double dDeNominatorOffset = ParameterResolveValue(pparDeNominatorOffset, ptstr->ppist);

	    pcai->pgcActivation.gc.gkForward.dDeNominatorOffset = dDeNominatorOffset;

	    //- get MembraneOffset = 5.0e-3

	    struct symtab_Parameters * pparMembraneOffset
		= SymbolGetParameter(phsle, "MembraneOffset", ptstr->ppist);

	    if (!pparMembraneOffset)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    double dMembraneOffset = ParameterResolveValue(pparMembraneOffset, ptstr->ppist);

	    pcai->pgcActivation.gc.gkForward.dMembraneOffset = dMembraneOffset;

	    //- get TauDenormalizer = -10.0e-3

	    struct symtab_Parameters * pparTauDenormalizer
		= SymbolGetParameter(phsle, "TauDenormalizer", ptstr->ppist);

	    if (!pparTauDenormalizer)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    double dTauDenormalizer = ParameterResolveValue(pparTauDenormalizer, ptstr->ppist);

	    pcai->pgcActivation.gc.gkForward.dTauDenormalizer = dTauDenormalizer;

	}

	//- if backward

	else if (pmcd->iStatus == 3)
	{
	    pcai->pgcActivation.gc.iTable = -1;

	    //- get Multiplier = 7.0e3

	    struct symtab_Parameters * pparMultiplier
		= SymbolGetParameter(phsle, "Multiplier", ptstr->ppist);

	    if (!pparMultiplier)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    double dMultiplier = ParameterResolveValue(pparMultiplier, ptstr->ppist);

	    pcai->pgcActivation.gc.gkBackward.dMultiplier = dMultiplier;

	    //- get MembraneDependence = 0.0

	    struct symtab_Parameters * pparMembraneDependence
		= SymbolGetParameter(phsle, "MembraneDependence", ptstr->ppist);

	    if (!pparMembraneDependence)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    double dMembraneDependence = ParameterResolveValue(pparMembraneDependence, ptstr->ppist);

	    pcai->pgcActivation.gc.gkBackward.dMembraneDependence = dMembraneDependence;

	    //- get Nominator = -1.0

	    struct symtab_Parameters * pparNominator
		= SymbolGetParameter(phsle, "Nominator", ptstr->ppist);

	    if (!pparNominator)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    int iNominator = ParameterResolveValue(pparNominator, ptstr->ppist);

	    pcai->pgcActivation.gc.gkBackward.iNominator = iNominator;

	    //- get DeNominatorOffset = 0.0

	    struct symtab_Parameters * pparDeNominatorOffset
		= SymbolGetParameter(phsle, "DeNominatorOffset", ptstr->ppist);

	    if (!pparDeNominatorOffset)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    double dDeNominatorOffset = ParameterResolveValue(pparDeNominatorOffset, ptstr->ppist);

	    pcai->pgcActivation.gc.gkBackward.dDeNominatorOffset = dDeNominatorOffset;

	    //- get MembraneOffset = 65.0e-3

	    struct symtab_Parameters * pparMembraneOffset
		= SymbolGetParameter(phsle, "MembraneOffset", ptstr->ppist);

	    if (!pparMembraneOffset)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    double dMembraneOffset = ParameterResolveValue(pparMembraneOffset, ptstr->ppist);

	    pcai->pgcActivation.gc.gkBackward.dMembraneOffset = dMembraneOffset;

	    //- get TauDenormalizer = 20.0e-3

	    struct symtab_Parameters * pparTauDenormalizer
		= SymbolGetParameter(phsle, "TauDenormalizer", ptstr->ppist);

	    if (!pparTauDenormalizer)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    double dTauDenormalizer = ParameterResolveValue(pparTauDenormalizer, ptstr->ppist);

	    pcai->pgcActivation.gc.gkBackward.dTauDenormalizer = dTauDenormalizer;

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

	    struct symtab_Parameters * pparPower
		= SymbolGetParameter(phsle, "POWER", ptstr->ppist);

	    if (!pparPower)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    int iPower = ParameterResolveValue(pparPower, ptstr->ppist);

	    pcac->pgc.iPower = iPower;

	    //- get initial state

	    struct symtab_Parameters * pparStateInit
		= SymbolGetParameter(phsle, "state_init", ptstr->ppist);

	    if (!pparStateInit)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    double dInitActivation = ParameterResolveValue(pparStateInit, ptstr->ppist);

	    pcac->pgc.gc.dInitActivation = dInitActivation;
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
	//- if forward

	if (pmcd->iStatus == 2)
	{
	    //- get Multiplier = 35.0e3

	    struct symtab_Parameters * pparMultiplier
		= SymbolGetParameter(phsle, "Multiplier", ptstr->ppist);

	    if (!pparMultiplier)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    double dMultiplier = ParameterResolveValue(pparMultiplier, ptstr->ppist);

	    pcac->pgc.gc.gkForward.dMultiplier = dMultiplier;

	    //- get MembraneDependence = 0.0

	    struct symtab_Parameters * pparMembraneDependence
		= SymbolGetParameter(phsle, "MembraneDependence", ptstr->ppist);

	    if (!pparMembraneDependence)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    double dMembraneDependence = ParameterResolveValue(pparMembraneDependence, ptstr->ppist);

	    pcac->pgc.gc.gkForward.dMembraneDependence = dMembraneDependence;

	    //- get Nominator = -1.0

	    struct symtab_Parameters * pparNominator
		= SymbolGetParameter(phsle, "Nominator", ptstr->ppist);

	    if (!pparNominator)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    int iNominator = ParameterResolveValue(pparNominator, ptstr->ppist);

	    pcac->pgc.gc.gkForward.iNominator = iNominator;

	    //- get DeNominatorOffset = 0.0

	    struct symtab_Parameters * pparDeNominatorOffset
		= SymbolGetParameter(phsle, "DeNominatorOffset", ptstr->ppist);

	    if (!pparDeNominatorOffset)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    double dDeNominatorOffset = ParameterResolveValue(pparDeNominatorOffset, ptstr->ppist);

	    pcac->pgc.gc.gkForward.dDeNominatorOffset = dDeNominatorOffset;

	    //- get MembraneOffset = 5.0e-3

	    struct symtab_Parameters * pparMembraneOffset
		= SymbolGetParameter(phsle, "MembraneOffset", ptstr->ppist);

	    if (!pparMembraneOffset)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    double dMembraneOffset = ParameterResolveValue(pparMembraneOffset, ptstr->ppist);

	    pcac->pgc.gc.gkForward.dMembraneOffset = dMembraneOffset;

	    //- get TauDenormalizer = -10.0e-3

	    struct symtab_Parameters * pparTauDenormalizer
		= SymbolGetParameter(phsle, "TauDenormalizer", ptstr->ppist);

	    if (!pparTauDenormalizer)
	    {
		pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    double dTauDenormalizer = ParameterResolveValue(pparTauDenormalizer, ptstr->ppist);

	    pcac->pgc.gc.gkForward.dTauDenormalizer = dTauDenormalizer;

	}
	else
	{
	    pmcd->iStatus = STATUS_UNKNOWN_TYPE;

	    iResult = TSTR_PROCESSOR_ABORT;
	}
    }

/*     //- if activator */

/*     else if (instanceof_activator(phsle)) */
/*     { */
/* 	//- if forward */

/* 	if (pmcd->iStatus == 3) */
/* 	{ */
/*     //m initial value, commonly steady state */

/*     double dInitActivation; */

/*     //m corresponding index in tables, set to -1 for initialization. */

/*     int iTable; */

/*     //m basal level, A in EDS1994 */

/*     double dBasalLevel; */

/*     //m time constant, B in EDS1994 */

/*     double dTau; */

/*     //m is activated by the output of this mechanism, must be filled in */

/*     int iActivator; */
/* 	} */
/* 	else */
/* 	{ */
/* 	    pmcd->iStatus = STATUS_UNKNOWN_TYPE; */

/* 	    iResult = TSTR_PROCESSOR_ABORT; */
/* 	} */
/*     } */

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

    //- get type of math component

    int iType = pmcd->piTypes[pmcd->iCurrentType];

    //- register the type in the math component array

    pmc->iType = iType;

    //- register serial

    pmc->iSerial = ptstr->iSerialPrincipal;

    //- depending on the type

    switch (iType)
    {
	//- for a channel

    case MATH_TYPE_ChannelActInact:
    case MATH_TYPE_ChannelActConc:
    {
	//- get maximal conductance

	struct symtab_Parameters * pparMaximalConductance
	    = SymbolGetParameter(phsle, "GMAX", ptstr->ppist);

	if (!pparMaximalConductance)
	{
	    pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

	    iResult = TSTR_PROCESSOR_ABORT;
	}

	double dMaximalConductance = ParameterResolveScaledValue(pparMaximalConductance, ptstr->ppist);

	//- get reversal potential

	struct symtab_Parameters * pparReversalPotential
	    = SymbolGetParameter(phsle, "Ek", ptstr->ppist);

	if (!pparReversalPotential)
	{
	    pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

	    iResult = TSTR_PROCESSOR_ABORT;
	}

	double dReversalPotential = ParameterResolveValue(pparReversalPotential, ptstr->ppist);

	//- set values

	if (iType == MATH_TYPE_ChannelActInact)
	{
	    struct ChannelActInact * pcai = (struct ChannelActInact *)pmc;

	    pcai->dMaximalConductance = dMaximalConductance;

	    pcai->dReversalPotential = dReversalPotential;
	}
	else if (iType == MATH_TYPE_ChannelActConc)
	{
	    struct ChannelActConc * pcac = (struct ChannelActConc *)pmc;

	    pcac->dMaximalConductance = dMaximalConductance;

	    pcac->dReversalPotential = dReversalPotential;

	    struct symtab_IOList *piolPool0
		= SymbolResolveInput(phsle, ptstr->ppist, "concen", 0);

	    //t this is a hack to get things to work right now,
	    //t see TODOs in neurospaces

	    //t this hack will not work when components are grouped or so

	    int iSerialDifference
		= piolPool0->hsle.smapPrincipal.iParent - phsle->smapPrincipal.iParent;

	    //t perhaps must be a + ?, but I guess not

	    pcac->iPool = ptstr->iSerialPrincipal - iSerialDifference;
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

	    struct TreespaceTraversal *ptstr
		= TstrNew
		  (ptstr->ppist,
		   NULL,
		   NULL,
		   (iType == MATH_TYPE_ChannelActInact)
		   ? solver_channel_activation_inactivation_processor
		   : solver_channel_activation_concentration_processor,
		   (void *)pmcd,
		   NULL,
		   NULL);

	    iResult = TstrGo(ptstr,phsle);

	    if (iResult)
	    {
		pmcd->iStatus = iStatus;

		iResult = TSTR_PROCESSOR_FAILURE;
	    }
	    else
	    {
		pmcd->iStatus = STATUS_UNKNOWN_ERROR;

		iResult = TSTR_PROCESSOR_ABORT;
	    }

	    TstrDelete(ptstr);

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

	struct symtab_Parameters * pparInitValue
	    = SymbolGetParameter(phsle, "concen_init", ptstr->ppist);

	if (!pparInitValue)
	{
	    pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

	    iResult = TSTR_PROCESSOR_ABORT;
	}

	double dInitValue = ParameterResolveValue(pparInitValue, ptstr->ppist);

	//- get beta

	struct symtab_Parameters * pparBeta
	    = SymbolGetParameter(phsle, "BETA", ptstr->ppist);

	if (!pparBeta)
	{
	    pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

	    iResult = TSTR_PROCESSOR_ABORT;
	}

	double dBeta = ParameterResolveValue(pparBeta, ptstr->ppist);

	//- get steady state

	struct symtab_Parameters * pparSteadyState
	    = SymbolGetParameter(phsle, "BASE", ptstr->ppist);

	if (!pparSteadyState)
	{
	    pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

	    iResult = TSTR_PROCESSOR_ABORT;
	}

	double dSteadyState = ParameterResolveValue(pparSteadyState, ptstr->ppist);

	//- get tau

	struct symtab_Parameters * pparTau
	    = SymbolGetParameter(phsle, "TAU", ptstr->ppist);

	if (!pparTau)
	{
	    pmcd->iStatus = STATUS_UNRESOLVABLE_PARAMETERS;

	    iResult = TSTR_PROCESSOR_ABORT;
	}

	double dTau = ParameterResolveValue(pparTau, ptstr->ppist);

	//- set values

	pexdec->dInitValue = dInitValue;
	pexdec->dBeta = dBeta;
	pexdec->dSteadyState = dSteadyState;
	pexdec->dTau = dTau;

	//- find contributing channels

	int iInput;

	struct symtab_IOList *piolExternal
	    = SymbolResolveInput(phsle, ptstr->ppist, "Ik", 0);

	for (iInput = 0 ; piolExternal ; iInput++)
	{
	    //t this is a hack to get things to work right now,
	    //t see TODOs in neurospaces

	    //t this hack will not work when components are grouped or so

	    int iSerialDifference
		= piolExternal->hsle.smapPrincipal.iParent - phsle->smapPrincipal.iParent;

	    //t perhaps must be a + ?, but I guess not

	    pexdec->iExternal = ptstr->iSerialPrincipal - iSerialDifference;

	    //- next contributing channel

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

    //t probably can do bookkeeping here for ->piC2m[]

    //- get actual symbol

    struct symtab_HSolveListElement *phsle = TstrGetActual(ptstr);

    //- get user data

    struct MathComponentData * pmcd = (struct MathComponentData *)pvUserdata;

    //- get pointer to intermediary

    struct Heccer *pheccer = pmcd->pheccer;

    //- set default type : error

    int iType = INT_MAX;

    //- if gate and related

    if (instanceof_gate_kinetic(phsle))
    {
	//- ok, skip

	iType = -1;
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
	    //- is an activating - inactivating channel

	    iType = MATH_TYPE_ChannelActInact;
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

	    //m current compartment

	    NULL,

	    NULL,

	    //m number of math components

	    0,

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
	};

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

			//t not sure if recycling is still allowed ...

			ptstr->pfProcesor = solver_mathcomponent_processor;

			iResult = TstrGo(ptstr, phsleModel);

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

	//- delete treespace traversal

	TstrDelete(ptstr);

	//t decide if we want to keep piTypes or not, it might
	//t be useful to keep.

	//- link the mathcomponents together

	iResult = iResult && cellsolver_linkmathcomponents(pheccer);

/* 	//- produce a piC2m array */

/* 	iResult = iResult && cellsolver_setupmechanisms(pheccer); */
    }
    else
    {
	iResult = FALSE;
    }

    //- return result

    return(iResult);
}


static int cellsolver_linkmathcomponents(struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    //! this can never fail: multiple parent and multiple root
    //! diagnosis is left to the minimum degree logic.

    //- loop over all compartments

    struct Intermediary *pinter = &pheccer->inter;

    //- return result

    return(iResult);
}


/* static int cellsolver_setupmechanisms(struct Heccer *pheccer) */
/* { */
/*     //t here have to correct, I guess, not sure. */

/*     struct Intermediary *pinter = &pheccer->inter; */

/*     //- return result */

/*     return(pinter->piC2m != NULL); */
/* } */


int HeccerNeurospacesMechanisms2MathComponents(struct TranslationService *pts)
{
    //- set the service function pointer to cellsolver_getmathcomponents()

    pts->mechanisms_inspector = cellsolver_getmathcomponents;

    //- return result

    return(1);
}


