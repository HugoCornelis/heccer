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

#include "heccer/compartment.h"
#include "heccer/heccer.h"


/// **************************************************************************
///
/// SHORT: HeccerMechanismBuildIndex()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Index intermediary mechanism structures.
///
///	The index can afterwards be used for lookups, see
///	HeccerMechanismLookup().
///
/// **************************************************************************

int HeccerMechanismBuildIndex(struct Heccer *pheccer)
{
    //- set default result : success

    int iResult = TRUE;

    //- set default result : start of mechanisms

    struct MathComponent *pmc = (struct MathComponent *)pheccer->inter.pvMechanism;

    //- allocate the index

    struct MathComponent **ppmcIndex
	= (struct MathComponent **)calloc(pheccer->inter.iMechanisms, sizeof(struct MathComponent *));

    if (!ppmcIndex)
    {
	return(FALSE);
    }

    pheccer->inter.ppmcIndex = ppmcIndex;

    //- loop over all mechanisms

    int i;

    for (i = 0 ; i < pheccer->inter.iMechanisms ; i++)
    {
	//- initialize the index

	ppmcIndex[i] = pmc;

	//- look at mechanism type

	int iType = pmc->iType;

	switch (iType)
	{
	    //- for a callout

	case MATH_TYPE_CallOut_conductance_current:
	{
	    //- get type specific data

	    struct Callout *pcall = (struct Callout *)pmc;

	    RETREIVE_MATH_COMPONENT(pmc,pcall,(struct Callout *));

	    break;
	}

	//- for an regular channel with activation and inactivation

	case MECHANISM_TYPE_ChannelActInact:
	{
	    //- get type specific data

	    struct ChannelActInact *pcai = (struct ChannelActInact *)pmc;

	    RETREIVE_MATH_COMPONENT(pmc,pcai,(struct ChannelActInact *));

	    break;
	}

	//- for a channel with a potential and a concentration dependence

	case MECHANISM_TYPE_ChannelActConc:
	{
	    //- get type specific data

	    struct ChannelActConc *pcac = (struct ChannelActConc *)pmc;

	    RETREIVE_MATH_COMPONENT(pmc,pcac,(struct ChannelActConc *));

	    break;
	}

	//- for an exponential decaying variable

	case MECHANISM_TYPE_ExponentialDecay:
	{
	    //- get type specific data

	    struct ExponentialDecay *pexdec = (struct ExponentialDecay *)pmc;

	    RETREIVE_MATH_COMPONENT(pmc,pexdec,(struct ExponentialDecay *));

	    break;
	}
	default:
	{
	    //t HeccerError(number, message, varargs);

	    fprintf
		(stderr,
		 "Heccer the hecc : unknown pmc->iType (%i)\n", iType);
	    break;
	}
	}
    }

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerMechanismCompile()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Compile the intermediary of the mechanisms to byte code.
///
/// NOTE.:
///
///	Compartment leak is a current, so it is considered to be a
///	mechanism.
///
/// **************************************************************************

int HeccerMechanismCompile(struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    //- first build the mechanism index

    if (!HeccerMechanismBuildIndex(pheccer))
    {
	return(FALSE);
    }

    //v time step

    double dt;

    //v number of operators and operands

    int iMops;
    int iMats;

    //- for backward euler integration

    if (pheccer->ho.iOptions & HECCER_OPTION_BACKWARD_EULER)
    {
	//- remember to do full time step

	dt = pheccer->dStep;
    }

    //- else : crank-nicholson

    else
    {
	//- halve the time step

	dt = pheccer->dStep / 2.0;
    }

    //- first count, next compile the following block

    int iCountCompile;

    //- first counting by setting array to NULL

    void *pvMops = NULL;

    void *pvMats = NULL;

    for (iCountCompile = 0 ; iCountCompile < 2 ; iCountCompile++)
    {
	//- counters always start at zero

	iMops = 0;

	iMats = 0;

	//v actual concentration number

	int iConcentrations = 0;

	//- loop over all compartments via their schedule number

	int iSchedule;

	for (iSchedule = 0 ; iSchedule < pheccer->inter.iCompartments ; iSchedule++)
	{
	    //- fill in compartment operation

	    SETMOP_COMPARTMENT(pvMops, iMops);

	    //! Em/Rm
	    //! injected current
	    //! dt/cm
	    //! diagonal
	    //!
	    //! injected current needs a separate entry for interfacing.

	    //- get intermediary number for the current compartment

	    int iIntermediary = pheccer->indexers.md.piBackward[iSchedule];

	    //- retreive compartment constants

	    double dCm = pheccer->inter.pcomp[iIntermediary].dCm;

	    double dEm = pheccer->inter.pcomp[iIntermediary].dEm;

	    //t perhaps better to do current injection with a
	    //t hardcoded injector callout ?

	    double dInject = pheccer->inter.pcomp[iIntermediary].dInject;

	    double dRm = pheccer->inter.pcomp[iIntermediary].dRm;

	    //- fill in compartment constants

	    //! note : pdDiagonals was computed with schedule numbers.

	    //t these need an extra check, probably wrong.

	    //t perhaps need to split SETMAT_COMPARTMENT in SETMAT_COMPARTMENT_START
	    //t and SETMAT_COMPARTMENT_FINISH
	    //t between those two, we compile in the mechanisms.

	    SETMAT_COMPARTMENT(pvMats, iMats, dEm / dRm, dInject, dt / dCm, pheccer->vm.pdDiagonals[iSchedule]);

	    //- loop over mechanisms for this compartment

	    int iMechanism;

	    int iStart = iIntermediary == 0 ? 0 : pheccer->inter.piC2m[iIntermediary - 1];

	    if (iStart > pheccer->inter.iMechanisms)
	    {
		//t HeccerError(number, message, varargs);

		fprintf
		    (stderr,
		     "Heccer the hecc : trying to fetch mechanism number %i, which is out of range\n",
		     iStart);

		//- return error

		return(FALSE);
	    }

	    //- lookup the start of the mechanisms for this compartment

	    struct MathComponent *pmc = HeccerMechanismLookup(pheccer, iStart);

	    for (iMechanism = iStart ;
		 iMechanism < pheccer->inter.piC2m[iIntermediary] ;
		 iMechanism++)
	    {
		//- look at mechanism type

		int iType = pmc->iType;

		switch (iType)
		{
		    //- for a callout

		case MATH_TYPE_CallOut_conductance_current:
		{
		    //- get type specific data

		    struct Callout *pcall = (struct Callout *)pmc;

		    RETREIVE_MATH_COMPONENT(pmc,pcall,(struct Callout *));

		    SETMOP_CALLOUT(pvMops, iMops);

		    SETMAT_CALLOUT(pvMats, iMats, pcall);

		    break;
		}

		//- for a regular channel with activation and inactivation

		case MECHANISM_TYPE_ChannelActInact:
		{
		    //- get type specific data

		    struct ChannelActInact *pcai = (struct ChannelActInact *)pmc;

		    RETREIVE_MATH_COMPONENT(pmc,pcai,(struct ChannelActInact *));

		    SETMOP_INITIALIZECHANNEL(pvMops, iMops, pcai->dMaximalConductance, pcai->dReversalPotential);

		    //- tabulate the channel

		    //- tabulate activation, Genesis X
		    //- create forward table, Genesis A, alpha, create backward table, Genesis B, alpha + beta

		    int iTabulatedActivation
			= HeccerDiscretizeGateConcept(pheccer, &pcai->pgcActivation.gc);

		    SETMOP_LOADVOLTAGETABLE(pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(pvMops, iMops, pcai->pgcActivation.gc.iTable, pcai->pgcActivation.iPower,NULL);

		    //! at the beginning of a simulation, you would expect this to be the steady state value

		    SETMAT_POWEREDGATECONCEPT(pvMats, iMats, pcai->pgcActivation.gc.dInitActivation);

		    //- tabulate inactivation, Genesis Y
		    //- create forward table, Genesis A, alpha, create backward table, Genesis B, alpha + beta

		    int iTabulatedInactivation
			= HeccerDiscretizeGateConcept(pheccer, &pcai->pgcInactivation.gc);

		    SETMOP_POWEREDGATECONCEPT(pvMops, iMops, pcai->pgcInactivation.gc.iTable, pcai->pgcInactivation.iPower,NULL);

		    //! at the beginning of a simulation, you would expect this to be the steady state value

		    SETMAT_POWEREDGATECONCEPT(pvMats, iMats, pcai->pgcInactivation.gc.dInitActivation);

		    SETMOP_UPDATECOMPARTMENTCURRENT(pvMops, iMops);

		    //t retabulate cannot be done yet, do not know yet how many tables

		    //- register pool index

		    //t for reasons of easy initialization, this should be a check for zero.
		    //t this means that I have to offset all mechanisms with 1
		    //t (mmm, the hines solver did the same, but for other reasons).

		    if (pcai->iPool != -1)
		    {
			SETMOP_REGISTERCHANNELCURRENT(pvMops, iMops);

/* 			SETMOP_FLUXPOOL(pvMops, iMops, pcai->iPool); */

			SETMOP_FLUXPOOL(pvMops, iMops, iConcentrations);
		    }

		    //- register result from tabulation for outcome of this function

		    iResult = iResult && iTabulatedActivation && iTabulatedInactivation;

		    break;
		}

		//- for a channel with a potential and a concentration dependence

		case MECHANISM_TYPE_ChannelActConc:
		{
		    //- get type specific data

		    struct ChannelActConc *pcac = (struct ChannelActConc *)pmc;

		    RETREIVE_MATH_COMPONENT(pmc,pcac,(struct ChannelActConc *));

		    SETMOP_INITIALIZECHANNEL(pvMops, iMops, pcac->dMaximalConductance, pcac->dReversalPotential);

		    //- tabulate the membrane dependence

		    //- tabulate membrane dependence, Genesis X
		    //- create forward table, Genesis A, alpha, create backward table, Genesis B, alpha + beta

		    int iTabulatedMembraneDependence
			= HeccerDiscretizeGateConcept(pheccer, &pcac->pgc.gc);

		    SETMOP_LOADVOLTAGETABLE(pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(pvMops, iMops, pcac->pgc.gc.iTable, pcac->pgc.iPower,NULL);

		    //! at the beginning of a simulation, you would expect this to be the steady state value

		    SETMAT_POWEREDGATECONCEPT(pvMats, iMats, pcac->pgc.gc.dInitActivation);

		    //- tabulate concentration dependence, Genesis Z
		    //- create forward table, Genesis A, alpha, create backward table, Genesis B, alpha + beta

		    int iTabulatedBasalActivator
			= HeccerDiscretizeBasalActivator(pheccer, &pcac->pac.ac);

		    //! gate computations are just fetching things from tables, and
		    //! multiplying the conductances, so it is not relevant if these
		    //! computations are done for membrane potential dependent gates or
		    //! concentration dependent gates.

		    //t lookup and add solved dependence, depends on iConcentrations

		    //t not pdFluxes, but the concentration itself is required.

		    double *pdState = pheccer->vm.pdFluxes ? &pheccer->vm.pdFluxes[iConcentrations] : NULL;

		    SETMOP_POWEREDGATECONCEPT(pvMops, iMops, pcac->pac.ac.iTable, pcac->pac.iPower,pdState);

		    //! at the beginning of a simulation, you would expect this to be the steady state value

		    SETMAT_POWEREDGATECONCEPT(pvMats, iMats, pcac->pac.ac.dInitActivation);

		    SETMOP_UPDATECOMPARTMENTCURRENT(pvMops, iMops);

		    //t retabulate cannot be done yet, do not know yet how many tables

		    //- register pool index

		    //t for reasons of easy initialization, this should be a check for zero.
		    //t this means that I have to offset all mechanisms with 1
		    //t (mmm, the hines solver did the same, but for other reasons).

		    if (pcac->iPool != -1)
		    {
			SETMOP_REGISTERCHANNELCURRENT(pvMops, iMops);

/* 			SETMOP_FLUXPOOL(pvMops, iMops, pcai->iPool); */

			SETMOP_FLUXPOOL(pvMops, iMops, iConcentrations);
		    }

		    //- register result from tabulation for outcome of this function

		    iResult = iResult && iTabulatedMembraneDependence && iTabulatedBasalActivator;

		    break;
		}

		//- for an exponential decaying variable

		case MECHANISM_TYPE_ExponentialDecay:
		{
		    //- get type specific data

		    struct ExponentialDecay *pexdec = (struct ExponentialDecay *)pmc;

		    RETREIVE_MATH_COMPONENT(pmc,pexdec,(struct ExponentialDecay *));

		    SETMOP_EXPONENTIALDECAY(pvMops, iMops, pheccer->dStep * pexdec->dBeta, pexdec->dSteadyState, 1 + pheccer->dStep / (2 * pexdec->dTau));

		    SETMAT_EXPONENTIALDECAY(pvMats, iMats, pexdec->dInitValue);

		    //- increment concentration index

		    iConcentrations++;

		    break;
		}
		default:
		{
		    //t HeccerError(number, message, varargs);

		    fprintf
			(stderr,
			 "Heccer the hecc : unknown pmc->iType (%i)\n", iType);
		    break;
		}
		}
	    }
	}

	//- sanity : is next compartment's mechanism invalid ?

	if (pheccer->inter.piC2m[iSchedule] != -1)
	{
	    fprintf
		(stderr,
		 "Heccer the hecc : mechanisms found after last compartment's mechanism\n");

	    return(FALSE);
	}

	//- finish all operations

	SETMOP_FINISH(pvMops, iMops);

	//- if we were counting during the previous loop

	if (!pheccer->vm.pvMops)
	{
	    //- prepare for compilation : allocate ->pvMops and ->pvMats, set counters

	    pheccer->vm.pvMops = (void *)calloc(iMops, 1);

	    pvMops = pheccer->vm.pvMops;

	    pheccer->vm.iMops = iMops;

	    pheccer->vm.pvMats = (void *)calloc(iMats, 1);

	    pvMats = pheccer->vm.pvMats;

	    pheccer->vm.iMats = iMats;

	    pheccer->vm.pdFluxes = (double *)calloc(iConcentrations, sizeof(double));

	    pheccer->vm.iFluxes = iConcentrations;
	}
    }

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerMechanismLink()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Link mechanism operations.
///
///	Link mechanism operations:
///
///	HECCER_MOP_FLUXPOOL: mechanism index to flux index.
///
/// **************************************************************************

int HeccerMechanismLink(struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    int *piMop = (int *)pheccer->vm.pvMops;

    void *pvMats = pheccer->vm.pvMats;

    //v actual concentration number

    int iConcentrations = 0;

    //- loop over mechanism operators

    while (piMop[0] == HECCER_MOP_COMPARTMENT)
    {
	//- go to next operator

	piMop = &piMop[1];

	//- get compartment mechanism data

	struct MatsCompartment *pmatsc
	    = (struct MatsCompartment *)pvMats;

	pvMats = (void *)&((struct MatsCompartment *)pvMats)[1];

	//- loop over mechanism operators

	while (piMop[0] > HECCER_MOP_COMPARTMENT_BARRIER)
	{
	    //- look at next mechanism

	    switch (piMop[0])
	    {
		//- for a call out

	    case HECCER_MOP_CALLOUT:
	    {
		//- go to next operator

		piMop = &piMop[1];

		//- go to next type specific data

		struct MatsCallout * pcall = (struct MatsCallout *)pvMats;

		pvMats = (void *)&((struct MatsCallout *)pvMats)[1];

		break;
	    }

	    //- for single channel initialization

	    case HECCER_MOP_INITIALIZECHANNEL:
	    {
		//- go to next operator

		struct MopsChannel *pmops = (struct MopsChannel *)piMop;

		piMop = (int *)&pmops[1];

		break;
	    }

	    //- to compute a channel's conductance

	    case HECCER_MOP_STORECHANNELCONDUCTANCE:
	    {
		//- go to next operator

		piMop = &piMop[1];

		//- store the current conductance

		struct MatsChannel * pmats = (struct MatsChannel *)pvMats;

		//- go to next type specific data

		pvMats = (void *)&pmats[1];

		break;
	    }

	    //- for a new membrane potential

	    case HECCER_MOP_LOADVOLTAGETABLE:
	    {
		//- go to next operator

		struct MopsVoltageTableDependence *pmops = (struct MopsVoltageTableDependence *)piMop;

		piMop = (int *)&pmops[1];

		break;
	    }

	    //- for a conceptual gate (HH alike, with powers)

	    case HECCER_MOP_CONCEPTGATE:
	    {
		//- go to next operator

		struct MopsSingleGateConcept *pmops = (struct MopsSingleGateConcept *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsSingleGateConcept * pmats = (struct MatsSingleGateConcept *)pvMats;

		pvMats = (void *)&pmats[1];

		break;
	    }

	    //- register single channel contribution

	    case HECCER_MOP_REGISTERCHANNELCURRENT:
	    {
		//- go to next operator

		piMop = &piMop[1];

		break;
	    }

	    //- add channel contribution to compartmental currents

	    case HECCER_MOP_UPDATECOMPARTMENTCURRENT:
	    {
		//- go to next operator

		struct MopsUpdateCompartmentCurrent *pmops = (struct MopsUpdateCompartmentCurrent *)piMop;

		piMop = (int *)&pmops[1];

		break;
	    }

	    //- compute exponential decay, mostly an ion concentration

	    case HECCER_MOP_EXPONENTIALDECAY:
	    {
		//- go to next operator

		struct MopsExponentialDecay *pmops = (struct MopsExponentialDecay *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsExponentialDecay * pmats = (struct MatsExponentialDecay *)pvMats;

		pvMats = (void *)&pmats[1];

		//- go to next concentration pool

		iConcentrations++;

		break;
	    }

	    //- register current contribution to a pool

	    case HECCER_MOP_FLUXPOOL:
	    {
		//- go to next operator

		struct MopsFluxPool *pmops = (struct MopsFluxPool *)piMop;

		piMop = (int *)&pmops[1];

		break;
	    }
	    default:
	    {
		//t HeccerError(number, message, varargs);

		fprintf
		    (stderr,
		     "Heccer the hecc : unknown mechanism operation (%i)\n", piMop[0]);

		//! the best we can do is advance the pointer with one

		piMop = &piMop[1];

		break;
	    }
	    }
	}
    }

    //- check sanity of operator array

    if (piMop[0] != HECCER_MOP_FINISH)
    {
	//t add something like HeccerError(number, message, varargs);

	fprintf
	    (stderr,
	     "Heccer the hecc : piMop[0] is %i, should be %i\n",
	     piMop[0],
	     HECCER_MOP_FINISH);

	//t depending on options, bail out

	//t set status : illegal mop hecc.
    }

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerMechanismLookup()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	iMechanism: mechanism number to lookup.
///
/// RTN..: struct MathComponent *
///
///	mechanism structure, NULL for failure.
///
/// DESCR: Lookup the mechanism with the given number.
///
///	First call HeccerMechanismBuildIndex().
///
/// **************************************************************************

struct MathComponent *
HeccerMechanismLookup(struct Heccer *pheccer, int iMechanism)
{
    //- set default result : using the index

    struct MathComponent *pmcResult
	= pheccer->inter.ppmcIndex[iMechanism];

    //- return result

    return(pmcResult);
}


/// **************************************************************************
///
/// SHORT: HeccerMechanismSolveCN()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Perform the mechanisms operators once.
///
/// **************************************************************************

int HeccerMechanismSolveCN(struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    int *piMop = (int *)pheccer->vm.pvMops;

    //- get access to variables and results

    double *pdVm = &pheccer->vm.pdVms[0];

    void *pvMats = pheccer->vm.pvMats;

    double *pdFluxes = pheccer->vm.pdFluxes;

    double *pdResults = &pheccer->vm.pdResults[0];

    //- zero out all fluxes

    //t should check how this can be replaced with regular operators,
    //t and if so, if it gives an additional performance gain.

    int i;

    for (i = 0 ; i < pheccer->vm.iFluxes ; i++)
    {
	pheccer->vm.pdFluxes[i] = 0.0;
    }

    //v actual concentration number

    int iConcentrations = 0;

    //- loop over mechanism operators

    while (piMop[0] == HECCER_MOP_COMPARTMENT)
    {
	//- go to next operator

	piMop = &piMop[1];

	//- get compartment mechanism data

	struct MatsCompartment *pmatsc
	    = (struct MatsCompartment *)pvMats;

	pvMats = (void *)&((struct MatsCompartment *)pvMats)[1];

	//- get membrane potential

	double dVm = pdVm[0];

	//- initialize current with leak and injected

	double dCurrent = pmatsc->dLeak + pmatsc->dInjected;

	//- initial total conductance is zero

	double dConductances = 0;

	//- single channel contribution is zero

	double dChannelConductance = 0.0;

	double dReversalPotential = 0.0;

	//- loop over mechanism operators

	while (piMop[0] > HECCER_MOP_COMPARTMENT_BARRIER)
	{
	    //v single channel current (if applicable)

	    double dSingleChannelCurrent;

	    //- look at next mechanism

/* 	//t mechanisms could go here (preferred cause it groups the */
/* 	//t mechanism data for the leak). */

	    switch (piMop[0])
	    {
		//- for a call out

	    case HECCER_MOP_CALLOUT:
	    {
		//- go to next operator

		piMop = &piMop[1];

		//- go to next type specific data

		struct MatsCallout * pcall = (struct MatsCallout *)pvMats;

		pvMats = (void *)&((struct MatsCallout *)pvMats)[1];

		//- get function pointer

		struct Callout * pco = (struct Callout *)pcall->pco;

		ExternalFunction * pef = pco->pef;

		//- fill in internal results

		struct InternalResults * pir = pco->pir;

		pir->dVm = dVm;

		//- call the function

		struct ExternalResults * per = pco->per;

		int iResult = (*pef)(pco, pheccer, pir, per);

		//- handle external results

		dConductances += per->dConductance;

		dCurrent += per->dCurrent;

		//t check signaling

		break;
	    }

	    //- for single channel initialization

	    case HECCER_MOP_INITIALIZECHANNEL:
	    {
		//- go to next operator

		struct MopsChannel *pmops = (struct MopsChannel *)piMop;

		piMop = (int *)&pmops[1];

		//- load channel variables

		dChannelConductance = pmops->dMaximalConductance;

		dReversalPotential = pmops->dReversalPotential;

		break;
	    }

	    //- to compute a channel's conductance

	    case HECCER_MOP_STORECHANNELCONDUCTANCE:
	    {
		//- go to next operator

		piMop = &piMop[1];

		//- store the current conductance

		struct MatsChannel * pmats = (struct MatsChannel *)pvMats;

		pmats->dChannelConductance = dChannelConductance;

		//- go to next type specific data

		pvMats = (void *)&pmats[1];

		break;
	    }

	    //- for a new membrane potential

	    case HECCER_MOP_LOADVOLTAGETABLE:
	    {
		//- go to next operator

		struct MopsVoltageTableDependence *pmops = (struct MopsVoltageTableDependence *)piMop;

		piMop = (int *)&pmops[1];

		//t this is a nop for the moment, but when table
		//t rearrangements get in, this should load the
		//t table pointed to by the current membrane potential.

		break;
	    }

	    //- for a conceptual gate (HH alike, with powers)

	    case HECCER_MOP_CONCEPTGATE:
	    {
		//- go to next operator

		struct MopsSingleGateConcept *pmops = (struct MopsSingleGateConcept *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsSingleGateConcept * pmats = (struct MatsSingleGateConcept *)pvMats;

		pvMats = (void *)&pmats[1];

		//- get type specific constants and variables

		int iPower = pmops->iPower;

		int iTable = pmops->iTableIndex;

		double *pdState = pmops->pdState;

		double dActivation = pmats->dActivation;

		//- fetch tables

		//t table rearrangements

		struct HeccerTabulatedGate *phtg = &pheccer->tgt.phtg[iTable];

		double *pdForward = phtg->pdForward;
		double *pdBackward = phtg->pdBackward;

		double dState;

		//- for a concentration dependent gate

		//t two cases: gate is dependent on membrane potential,
		//t or gate is dependent on an internally solved variable.
		//t
		//t so I actually only need an offset into mats, which
		//t is supposedly given by the mechanism number +
		//t subnumber

		if (pdState)
		{
		    //- state is concentration

		    dState = 0.0;
		}

		//- else is a membrane dependent gate

		else
		{
		    //- state is membrane potential

		    //t move this to load membrane potential
		    //t need LOADVOLTAGETABLE or LOADVOLTAGEINDEX

		    dState = dVm;
		}

		//- discretize and offset the state

		int iIndex = (dState - phtg->hi.dStart) / phtg->hi.dStep;

		if (iIndex < 0)
		{
		    iIndex = 0;
		}
		else if (iIndex >= phtg->iEntries)
		{
		    iIndex = phtg->iEntries - 1;
		}

		//- fetch forward and backward gate rates

		double dForward = pdForward[iIndex];
		double dBackward = pdBackward[iIndex];

		//t move to channel rearrangements

		dBackward = 1.0 + pheccer->dStep / 2.0 * dBackward;

		dForward = pheccer->dStep * dForward;

		//- compute gate activation state

		dActivation = (dActivation * (2.0 - dBackward) + dForward) / dBackward;

		//- and store it for the next cycle

		pmats->dActivation = dActivation;

		//- apply gate power, multiply with conductance (note:
		//- also changes units)

		if (iPower == 1)
		{
		    dChannelConductance = dChannelConductance * dActivation;
		}
		else if (iPower == 2)
		{
		    dChannelConductance *= dActivation * dActivation;
		}
		else if (iPower == 3)
		{
		    dChannelConductance *= dActivation * dActivation * dActivation;
		}
		else if (iPower == 4)
		{
		    dActivation *= dActivation;
		    dChannelConductance *= dActivation * dActivation;
		}
		else if (iPower == 5)
		{
		    dChannelConductance *= dActivation;
		    dActivation *= dActivation;
		    dActivation *= dActivation;
		    dChannelConductance *= dActivation;
		}
		else if (iPower == 6)
		{
		    dActivation *= dActivation;
		    dChannelConductance *= dActivation;
		    dActivation *= dActivation;
		    dChannelConductance *= dActivation;
		}
		else
		{
		    *(int *)0 = 0;
		}

		break;
	    }

	    //- register single channel contribution

	    case HECCER_MOP_REGISTERCHANNELCURRENT:
	    {
		//- go to next operator

		piMop = &piMop[1];

		//- compute conductance for matrix left side

		dSingleChannelCurrent = dChannelConductance * (dReversalPotential - dVm);

		break;
	    }

	    //- add channel contribution to compartmental currents

	    case HECCER_MOP_UPDATECOMPARTMENTCURRENT:
	    {
		//- go to next operator

		struct MopsUpdateCompartmentCurrent *pmops = (struct MopsUpdateCompartmentCurrent *)piMop;

		piMop = (int *)&pmops[1];

		//- compute conductance for matrix left side

		dConductances += dChannelConductance;

		//- compute current for matrix right side

		dCurrent += dChannelConductance * dReversalPotential;

		break;
	    }

	    //- compute exponential decay, mostly an ion concentration

	    case HECCER_MOP_EXPONENTIALDECAY:
	    {
		//- go to next operator

		struct MopsExponentialDecay *pmops = (struct MopsExponentialDecay *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsExponentialDecay * pmats = (struct MatsExponentialDecay *)pvMats;

		pvMats = (void *)&pmats[1];

		double dBeta = pmops->dBeta;

		double dSteadyState = pmops->dSteadyState;

		double dTau = pmops->dTau;

		double dState = pmats->dState;

		//- fetch external contribution

		double dExternal = pdFluxes[iConcentrations];

		//- exponential decay

		dState = dSteadyState + ((dState - dSteadyState) * (2.0 - dTau) + (dExternal * dBeta)) / dTau;

		//- go to next concentration pool

		iConcentrations++;

		break;
	    }

	    //- register current contribution to a pool

	    case HECCER_MOP_FLUXPOOL:
	    {
		//- go to next operator

		struct MopsFluxPool *pmops = (struct MopsFluxPool *)piMop;

		piMop = (int *)&pmops[1];

		//- register contribution

		pdFluxes[pmops->iPool] += dSingleChannelCurrent;

		break;
	    }
	    default:
	    {
		//t HeccerError(number, message, varargs);

		fprintf
		    (stderr,
		     "Heccer the hecc : unknown mechanism operation (%i)\n", piMop[0]);

		//! the best we can do is advance the pointer with one

		piMop = &piMop[1];

		break;
	    }
	    }
	}
		
	//- for single compartment neurons

	if (pheccer->vm.iVms == 1)
	{
	    //- compute the membrane potential right here

	    //t differentiation needed between CN and BE ?

	    double dResult = ((dVm + dCurrent * pmatsc->dCapacity)
			      / (dConductances * pmatsc->dCapacity + pmatsc->dDiagonal));

	    pdVm[0] = dResult + dResult - pdVm[0];
	}

	//- for multiple compartment neurons

	else
	{
	    //- compute results for the morphology matrix

	    //- right side

	    pdResults[0] = dVm + dCurrent * pmatsc->dCapacity;

	    //- left side

	    pdResults[1] = dConductances * pmatsc->dCapacity + pmatsc->dDiagonal;

	    pdResults += 2;
	}

	//- go to next compartment

	pdVm++;
    }

    //- check sanity of operator array

    if (piMop[0] != HECCER_MOP_FINISH)
    {
	//t add something like HeccerError(number, message, varargs);

	fprintf
	    (stderr,
	     "Heccer the hecc : piMop[0] is %i, should be %i\n",
	     piMop[0],
	     HECCER_MOP_FINISH);

	//t depending on options, bail out

	//t set status : illegal mop hecc.
    }

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerMechanismSort()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Sort mechanisms according to different characteristics.
///
///	Mechanisms are sorted using a regular quicksort.  A full order
///	is enforced by looking at the serial identification number in
///	the intermediary (as last resort for unordered mechanisms).
///
/// NOTE.:
///
///	Compartment leak is a current, so it is considered to be a
///	mechanism.
///
/// **************************************************************************

int HeccerMechanismSort(struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    //- loop over all compartments

    int iCompartmentSchedule;

    for (iCompartmentSchedule = 0 ; iCompartmentSchedule < pheccer->inter.iCompartments ; iCompartmentSchedule++)
    {
	//- get model number for this compartment

	int iCompartmentModel = pheccer->indexers.md.piBackward[iCompartmentSchedule];

	//- loop over all the mechanisms for this compartment

	int iMechanismModel;

	for (iMechanismModel = pheccer->inter.piC2m[iCompartmentModel] ;
	     iMechanismModel < pheccer->inter.piC2m[iCompartmentModel + 1] ;
	     iMechanismModel++)
	{
	    //t build array with mechanism references into the intermediary

	    //t because of the structure of the intermediary, we do
	    //t not need this, do we ?
	}
    }

    //t qsort mechanisms per compartment

    //t sort on Ek, see adaptive time step paper and hsolve implementation.

    //- return result

    return(iResult);
}


