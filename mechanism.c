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


#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heccer/compartment.h"
#include "heccer/heccer.h"


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

    if (!HeccerIntermediaryBuildIndex(pheccer))
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

    //- first count, then index, next compile the following block

    int iMopNumber;
    int iMatNumber;

    int iCountIndexCompile;

    void *pvMops = NULL;
    void *pvMats = NULL;
    void **ppvMopsIndex = NULL;
    void **ppvMatsIndex = NULL;
    int *piMC2Mop = NULL;
    int *piMC2Mat = NULL;

    for (iCountIndexCompile = 0 ; iCountIndexCompile < 3 ; iCountIndexCompile++)
    {
	//- counters always start at zero

	iMopNumber = 0;
	iMatNumber = 0;

	iMops = 0;

	iMats = 0;

	//- loop over all compartments via their schedule number

	int iSchedule;

	for (iSchedule = 0 ; iSchedule < pheccer->inter.iCompartments ; iSchedule++)
	{
	    //- fill in compartment operation

	    SETMOP_COMPARTMENT(ppvMopsIndex, iMopNumber, pvMops, iMops);

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

	    SETMAT_COMPARTMENT(ppvMatsIndex, iMatNumber, pvMats, iMats, dEm / dRm, dInject, dt / dCm, pheccer->vm.pdDiagonals[iSchedule]);

	    //- loop over mechanisms for this compartment

	    int iMathComponent;

	    int iStart = iIntermediary == 0 ? 0 : pheccer->inter.piC2m[iIntermediary - 1];

	    if (pheccer->inter.pmca && iStart > pheccer->inter.pmca->iMathComponents)
	    {
		//t HeccerError(number, message, varargs);

		fprintf
		    (stderr,
		     "Heccer the hecc : trying to fetch math component number %i, which is out of range\n",
		     iStart);

		//- return error

		return(FALSE);
	    }

	    //- lookup the start of the mechanisms for this compartment

	    struct MathComponent *pmc = HeccerIntermediaryLookup(pheccer, iStart);

	    for (iMathComponent = iStart ;
		 iMathComponent < pheccer->inter.piC2m[iIntermediary] ;
		 iMathComponent++)
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

		    pmc = MathComponentNext(&pcall->mc);

		    SETMOP_CALLOUT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMAT_CALLOUT(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, pcall);

		    break;
		}

		//- for a nernst operation with internal variable concentration

		case MATH_TYPE_InternalNernst:
		{
		    //- get type specific data

		    struct InternalNernst * pin = (struct InternalNernst *)pmc;

		    pmc = MathComponentNext(&pin->mc);

		    //- get math component number

		    int iMathComponentActivator = pin->iInternal;

		    double *pdState = NULL;

		    if (iMathComponentActivator != -1)
		    {
			//- convert math component to mat number, convert mat number to mat addressable

			int iMatsActivator = piMC2Mat ? piMC2Mat[iMathComponentActivator] : -1;

			//! every such a cast must be resolved during linking, see HeccerMechanismLink().

			pdState = (double *)iMatsActivator;
		    }

		    SETMOP_INTERNALNERNST(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pin->dConstant, pin->dExternal, pdState);

		    SETMAT_INTERNALNERNST(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, pin->dInitPotential);

		    break;
		}

		//- for a channel with only activation

		case MATH_TYPE_ChannelAct:
		{
		    //- get type specific data

		    struct ChannelAct *pca = (struct ChannelAct *)pmc;

		    pmc = MathComponentNext(&pca->mc);

		    //- for a constant reversal potential

		    if (pca->iReversalPotential == -1)
		    {
			SETMOP_INITIALIZECHANNEL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pca->dMaximalConductance, pca->dReversalPotential);
		    }

		    //- else a solved reversal potential

		    else
		    {
			//- get math component number

			int iMathComponentReversalPotential = pca->iReversalPotential;

			double *pdReversalPotential = NULL;

			if (iMathComponentReversalPotential != -1)
			{
			    //- convert math component to mat number, convert mat number to mat addressable

			    int iMatsReversalPotential = piMC2Mat ? piMC2Mat[iMathComponentReversalPotential] : -1;

			    //! every such a cast must be resolved during linking, see HeccerMechanismLink().

			    pdReversalPotential = (double *)iMatsReversalPotential;
			}

			SETMOP_INITIALIZECHANNELEK(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pca->dMaximalConductance, pdReversalPotential);
		    }

		    //- tabulate the channel

		    //- tabulate activation, Genesis X
		    //- create forward table, Genesis A, alpha, create backward table, Genesis B, alpha + beta

		    int iTabulated
			= HeccerDiscretizeGateConcept(pheccer, &pca->pgc.gc);

		    SETMOP_LOADVOLTAGETABLE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pca->pgc.gc.iTable, pca->pgc.iPower,NULL);

		    //! at the beginning of a simulation, you would expect this to be the steady state value

		    SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, pca->pgc.gc.dInitActivation);

		    SETMOP_UPDATECOMPARTMENTCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    //t retabulate cannot be done yet, do not know yet how many tables

		    //- register pool index

		    //t for reasons of easy initialization, this should be a check for zero.
		    //t this means that I have to offset all mechanisms with 1
		    //t (mmm, the hines solver did the same, but for other reasons).

		    if (pca->iPool != -1)
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_FLUXPOOL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			//! initial flux is assumed to be zero, always

			SETMAT_FLUXPOOL(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, 0.0);

		    }

		    //- register result from tabulation for outcome of this function

		    iResult = iResult && iTabulated;

		    break;
		}

		//- for a regular channel with activation and inactivation

		case MATH_TYPE_ChannelActInact:
		{
		    //- get type specific data

		    struct ChannelActInact *pcai = (struct ChannelActInact *)pmc;

		    pmc = MathComponentNext(&pcai->mc);

		    //- for a constant reversal potential

		    if (pcai->iReversalPotential == -1)
		    {
			SETMOP_INITIALIZECHANNEL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcai->dMaximalConductance, pcai->dReversalPotential);
		    }

		    //- else a solved reversal potential

		    else
		    {
			//- get math component number

			int iMathComponentReversalPotential = pcai->iReversalPotential;

			double *pdReversalPotential = NULL;

			if (iMathComponentReversalPotential != -1)
			{
			    //- convert math component to mat number, convert mat number to mat addressable

			    int iMatsReversalPotential = piMC2Mat ? piMC2Mat[iMathComponentReversalPotential] : -1;

			    //! every such a cast must be resolved during linking, see HeccerMechanismLink().

			    pdReversalPotential = (double *)iMatsReversalPotential;
			}

			SETMOP_INITIALIZECHANNELEK(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcai->dMaximalConductance, pdReversalPotential);
		    }

		    //- tabulate the channel

		    //- tabulate activation, Genesis X
		    //- create forward table, Genesis A, alpha, create backward table, Genesis B, alpha + beta

		    int iTabulatedActivation
			= HeccerDiscretizeGateConcept(pheccer, &pcai->pgcActivation.gc);

		    SETMOP_LOADVOLTAGETABLE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcai->pgcActivation.gc.iTable, pcai->pgcActivation.iPower,NULL);

		    //! at the beginning of a simulation, you would expect this to be the steady state value

		    SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, pcai->pgcActivation.gc.dInitActivation);

		    //- tabulate inactivation, Genesis Y
		    //- create forward table, Genesis A, alpha, create backward table, Genesis B, alpha + beta

		    int iTabulatedInactivation
			= HeccerDiscretizeGateConcept(pheccer, &pcai->pgcInactivation.gc);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcai->pgcInactivation.gc.iTable, pcai->pgcInactivation.iPower,NULL);

		    //! at the beginning of a simulation, you would expect this to be the steady state value

		    SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, pcai->pgcInactivation.gc.dInitActivation);

		    SETMOP_UPDATECOMPARTMENTCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    //t retabulate cannot be done yet, do not know yet how many tables

		    //- register pool index

		    //t for reasons of easy initialization, this should be a check for zero.
		    //t this means that I have to offset all mechanisms with 1
		    //t (mmm, the hines solver did the same, but for other reasons).

		    if (pcai->iPool != -1)
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_FLUXPOOL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			//! initial flux is assumed to be zero, always

			SETMAT_FLUXPOOL(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, 0.0);

		    }

		    //- register result from tabulation for outcome of this function

		    iResult = iResult && iTabulatedActivation && iTabulatedInactivation;

		    break;
		}

		//- for a channel with a potential and an external dependence

		case MATH_TYPE_ChannelActConc:
		{
		    //- get type specific data

		    struct ChannelActConc *pcac = (struct ChannelActConc *)pmc;

		    pmc = MathComponentNext(&pcac->mc);

		    //- for a constant reversal potential

		    if (pcac->iReversalPotential == -1)
		    {
			SETMOP_INITIALIZECHANNEL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcac->dMaximalConductance, pcac->dReversalPotential);
		    }

		    //- else a solved reversal potential

		    else
		    {
			//- get math component number

			int iMathComponentReversalPotential = pcac->iReversalPotential;

			double *pdReversalPotential = NULL;

			if (iMathComponentReversalPotential != -1)
			{
			    //- convert math component to mat number, convert mat number to mat addressable

			    int iMatsReversalPotential = piMC2Mat ? piMC2Mat[iMathComponentReversalPotential] : -1;

			    //! every such a cast must be resolved during linking, see HeccerMechanismLink().

			    pdReversalPotential = (double *)iMatsReversalPotential;
			}

			SETMOP_INITIALIZECHANNELEK(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcac->dMaximalConductance, pdReversalPotential);
		    }

		    //- tabulate the membrane dependence

		    //- tabulate membrane dependence, Genesis X
		    //- create forward table, Genesis A, alpha, create backward table, Genesis B, alpha + beta

		    int iTabulatedMembraneDependence
			= HeccerDiscretizeGateConcept(pheccer, &pcac->pgc.gc);

		    SETMOP_LOADVOLTAGETABLE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcac->pgc.gc.iTable, pcac->pgc.iPower,NULL);

		    //! at the beginning of a simulation, you would expect this to be the steady state value

		    SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, pcac->pgc.gc.dInitActivation);

		    //- tabulate concentration dependence, Genesis Z
		    //- create forward table, Genesis A, alpha, create backward table, Genesis B, alpha + beta

		    int iTabulatedBasalActivator
			= HeccerDiscretizeBasalActivator(pheccer, &pcac->pac.ac);

		    //! gate computations are just fetching things from tables, and
		    //! multiplying the conductances, so it is not relevant if these
		    //! computations are done for membrane potential dependent gates or
		    //! concentration dependent gates.

		    //- get math component number

		    int iMathComponentActivator = pcac->pac.ac.iActivator;

		    double *pdState = NULL;

		    if (iMathComponentActivator != -1)
		    {
			//- convert math component to mat number, convert mat number to mat addressable

			int iMatsActivator = piMC2Mat ? piMC2Mat[iMathComponentActivator] : -1;

			//! every such a cast must be resolved during linking, see HeccerMechanismLink().

			pdState = (double *)iMatsActivator;
		    }

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcac->pac.ac.iTable, pcac->pac.iPower, pdState);

		    //! at the beginning of a simulation, you would expect this to be the steady state value

		    SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, pcac->pac.ac.dInitActivation);

		    SETMOP_UPDATECOMPARTMENTCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    //t retabulate cannot be done yet, do not know yet how many tables

		    //- register pool index

		    //t for reasons of easy initialization, this should be a check for zero.
		    //t this means that I have to offset all mechanisms with 1
		    //t (mmm, the hines solver did the same, but for other reasons).

		    if (pcac->iPool != -1)
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_FLUXPOOL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			//! initial flux is assumed to be zero, always

			SETMAT_FLUXPOOL(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, 0.0);

		    }

		    //- register result from tabulation for outcome of this function

		    iResult = iResult && iTabulatedMembraneDependence && iTabulatedBasalActivator;

		    break;
		}

		//- for an exponential decaying variable

		case MATH_TYPE_ExponentialDecay:
		{
		    //- get type specific data

		    struct ExponentialDecay *pexdec = (struct ExponentialDecay *)pmc;

		    pmc = MathComponentNext(&pexdec->mc);

		    double *ppdExternal[EXPONENTIALDECAY_CONTRIBUTORS];

		    int i;

		    for (i = 0 ; i < EXPONENTIALDECAY_CONTRIBUTORS ; i++)
		    {
			//- get math component number

			int iContributor = pexdec->piExternal[i];

			if (iContributor != -1)
			{
			    //- convert math component to mat number, convert mat number to mat addressable

			    int iMatsExternal = piMC2Mat ? piMC2Mat[iContributor] : -1;

			    //! every such a cast must be resolved during linking, see HeccerMechanismLink().

			    ppdExternal[i] = (double *)iMatsExternal;
			}
			else
			{
			    ppdExternal[i] = NULL;
			}
		    }

		    SETMOP_EXPONENTIALDECAY(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pheccer->dStep * pexdec->dBeta, pexdec->dSteadyState, 1 + pheccer->dStep / (2 * pexdec->dTau), ppdExternal);

		    SETMAT_EXPONENTIALDECAY(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, pexdec->dInitValue);

		    break;
		}

		//- for a channel specified as steady state and a stepped tau

		case MATH_TYPE_ChannelSteadyStateSteppedTau:
		{
		    //- get type specific data

		    struct ChannelSteadyStateSteppedTau *pcsst = (struct ChannelSteadyStateSteppedTau *)pmc;

		    pmc = MathComponentNext(&pcsst->mc);

		    //- for a constant reversal potential

		    if (pcsst->iReversalPotential == -1)
		    {
			SETMOP_INITIALIZECHANNEL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcsst->dMaximalConductance, pcsst->dReversalPotential);
		    }

		    //- else a solved reversal potential

		    else
		    {
			//- get math component number

			int iMathComponentReversalPotential = pcsst->iReversalPotential;

			double *pdReversalPotential = NULL;

			if (iMathComponentReversalPotential != -1)
			{
			    //- convert math component to mat number, convert mat number to mat addressable

			    int iMatsReversalPotential = piMC2Mat ? piMC2Mat[iMathComponentReversalPotential] : -1;

			    //! every such a cast must be resolved during linking, see HeccerMechanismLink().

			    pdReversalPotential = (double *)iMatsReversalPotential;
			}

			SETMOP_INITIALIZECHANNELEK(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcsst->dMaximalConductance, pdReversalPotential);
		    }

		    //- tabulate the channel

		    int iTabulated = HeccerChannelSteadyStateSteppedTauTabulate(pcsst, pheccer);

		    SETMOP_LOADVOLTAGETABLE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcsst->iFirstTable, pcsst->iFirstPower, NULL);

		    //! at the beginning of a simulation, you would expect this to be the steady state value

		    SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, pcsst->dFirstInitActivation);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcsst->iSecondTable, pcsst->iSecondPower, NULL);

		    SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, pcsst->dSecondInitActivation);

		    SETMOP_UPDATECOMPARTMENTCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    //t retabulate cannot be done yet, do not know yet how many tables

		    //- register pool index

		    //t for reasons of easy initialization, this should be a check for zero.
		    //t this means that I have to offset all mechanisms with 1
		    //t (mmm, the hines solver did the same, but for other reasons).

		    if (pcsst->iPool != -1)
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_FLUXPOOL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			//! initial flux is assumed to be zero, always

			SETMAT_FLUXPOOL(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, 0.0);

		    }

		    //- register result from tabulation for outcome of this function

		    iResult = iResult && iTabulated;

		    break;
		}

		//- for a persistent channel specified as steady state and two tau constants

		case MATH_TYPE_ChannelPersistentSteadyStateDualTau:
		{
		    //- get type specific data

		    struct ChannelPersistentSteadyStateDualTau *pcpsdt = (struct ChannelPersistentSteadyStateDualTau *)pmc;

		    pmc = MathComponentNext(&pcpsdt->mc);

		    //- for a constant reversal potential

		    if (pcpsdt->iReversalPotential == -1)
		    {
			SETMOP_INITIALIZECHANNEL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcpsdt->dMaximalConductance, pcpsdt->dReversalPotential);
		    }

		    //- else a solved reversal potential

		    else
		    {
			//- get math component number

			int iMathComponentReversalPotential = pcpsdt->iReversalPotential;

			double *pdReversalPotential = NULL;

			if (iMathComponentReversalPotential != -1)
			{
			    //- convert math component to mat number, convert mat number to mat addressable

			    int iMatsReversalPotential = piMC2Mat ? piMC2Mat[iMathComponentReversalPotential] : -1;

			    //! every such a cast must be resolved during linking, see HeccerMechanismLink().

			    pdReversalPotential = (double *)iMatsReversalPotential;
			}

			SETMOP_INITIALIZECHANNELEK(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcpsdt->dMaximalConductance, pdReversalPotential);
		    }

		    //- tabulate the channel

		    int iTabulated = HeccerChannelPersistentSteadyStateDualTauTabulate(pcpsdt, pheccer);

		    SETMOP_LOADVOLTAGETABLE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcpsdt->iFirstTable, pcpsdt->iFirstPower, NULL);

		    //! at the beginning of a simulation, you would expect this to be the steady state value

		    SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, pcpsdt->dFirstInitActivation);

		    SETMOP_UPDATECOMPARTMENTCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_INITIALIZECHANNEL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcpsdt->dMaximalConductance, pcpsdt->dReversalPotential);

		    SETMOP_LOADVOLTAGETABLE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcpsdt->iSecondTable, pcpsdt->iSecondPower, NULL);

		    SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, pcpsdt->dSecondInitActivation);

		    SETMOP_UPDATECOMPARTMENTCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    //t retabulate cannot be done yet, do not know yet how many tables

		    //- register pool index

		    //t for reasons of easy initialization, this should be a check for zero.
		    //t this means that I have to offset all mechanisms with 1
		    //t (mmm, the hines solver did the same, but for other reasons).

		    if (pcpsdt->iPool != -1)
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_FLUXPOOL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			//! initial flux is assumed to be zero, always

			SETMAT_FLUXPOOL(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, 0.0);

		    }

		    //- register result from tabulation for outcome of this function

		    iResult = iResult && iTabulated;

		    break;
		}

		//- for a persistent channel specified as steady state and a tau

		case MATH_TYPE_ChannelPersistentSteadyStateTau:
		{
		    //- get type specific data

		    struct ChannelPersistentSteadyStateTau *pcpst = (struct ChannelPersistentSteadyStateTau *)pmc;

		    pmc = MathComponentNext(&pcpst->mc);

		    //- for a constant reversal potential

		    if (pcpst->iReversalPotential == -1)
		    {
			SETMOP_INITIALIZECHANNEL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcpst->dMaximalConductance, pcpst->dReversalPotential);
		    }

		    //- else a solved reversal potential

		    else
		    {
			//- get math component number

			int iMathComponentReversalPotential = pcpst->iReversalPotential;

			double *pdReversalPotential = NULL;

			if (iMathComponentReversalPotential != -1)
			{
			    //- convert math component to mat number, convert mat number to mat addressable

			    int iMatsReversalPotential = piMC2Mat ? piMC2Mat[iMathComponentReversalPotential] : -1;

			    //! every such a cast must be resolved during linking, see HeccerMechanismLink().

			    pdReversalPotential = (double *)iMatsReversalPotential;
			}

			SETMOP_INITIALIZECHANNELEK(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcpst->dMaximalConductance, pdReversalPotential);
		    }

		    //- tabulate the channel

		    int iTabulated = HeccerChannelPersistentSteadyStateTauTabulate(pcpst, pheccer);

		    SETMOP_LOADVOLTAGETABLE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcpst->iTable, pcpst->iPower, NULL);

		    //! at the beginning of a simulation, you would expect this to be the steady state value

		    SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, pcpst->dInitActivation);

		    SETMOP_UPDATECOMPARTMENTCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    //t retabulate cannot be done yet, do not know yet how many tables

		    //- register pool index

		    //t for reasons of easy initialization, this should be a check for zero.
		    //t this means that I have to offset all mechanisms with 1
		    //t (mmm, the hines solver did the same, but for other reasons).

		    if (pcpst->iPool != -1)
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_FLUXPOOL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			//! initial flux is assumed to be zero, always

			SETMAT_FLUXPOOL(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, 0.0);

		    }

		    //- register result from tabulation for outcome of this function

		    iResult = iResult && iTabulated;

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

	//! so pheccer->inter.piC2m can be NULL if no compartments have been found.

	if (pheccer->inter.piC2m
	    && pheccer->inter.piC2m[iSchedule] != -1)
	{
	    //t HeccerError(number, message, varargs);

	    fprintf
		(stderr,
		 "Heccer the hecc : mechanisms found after last compartment's mechanism\n");

	    return(FALSE);
	}

	//- finish all operations

	SETMOP_FINISH(ppvMopsIndex, iMopNumber, pvMops, iMops);

	//- if we were counting during the previous loop

	if (iCountIndexCompile == 0)
	{
	    pheccer->vm.iMopNumber = iMopNumber;

	    pheccer->vm.ppvMopsIndex = (void **)calloc(iMopNumber + 1, sizeof(void *));

	    ppvMopsIndex = pheccer->vm.ppvMopsIndex;

	    pheccer->vm.iMatNumber = iMatNumber;

	    pheccer->vm.ppvMatsIndex = (void **)calloc(iMatNumber + 1, sizeof(void *));

	    ppvMatsIndex = pheccer->vm.ppvMatsIndex;

	    if (pheccer->inter.pmca)
	    {
		//! note that this one does not index compartments, only the mechanism math components.

		pheccer->vm.piMC2Mat = (int *)calloc(pheccer->inter.pmca->iMathComponents + 1, sizeof(int *));

		piMC2Mat = pheccer->vm.piMC2Mat;

		pheccer->vm.piMC2Mop = (int *)calloc(pheccer->inter.pmca->iMathComponents + 1, sizeof(int *));

		piMC2Mop = pheccer->vm.piMC2Mop;
	    }
	}

	//- if we were indexing during the previous loop

	else if (iCountIndexCompile == 1)
	{
	    //- prepare for compilation : allocate operators and addressables

	    pheccer->vm.pvMops = (void *)calloc(iMops, 1);

	    pvMops = pheccer->vm.pvMops;

	    pheccer->vm.iMops = iMops;

	    pheccer->vm.pvMats = (void *)calloc(iMats, 1);

	    pvMats = pheccer->vm.pvMats;

	    pheccer->vm.iMats = iMats;
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

	    //- for a nernst operation with internal variable concentration

	    case HECCER_MOP_INTERNALNERNST:
	    {
		//- go to next operator

		struct MopsInternalNernst *pmops = (struct MopsInternalNernst *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsInternalNernst * pnernst = (struct MatsInternalNernst *)pvMats;

		pvMats = (void *)&((struct MatsInternalNernst *)pvMats)[1];

		//- get index of internal concentration

		double *pdInternal = pmops->pdInternal;

		//- if still an index

		if (pdInternal)
		{
		    //- convert index to pointer

		    int iInternal = (int)pdInternal;

		    if (iInternal == -1)
		    {
			//t HeccerError(number, message, varargs);

			fprintf
			    (stderr,
			     "Heccer the hecc : cannot resolve link for a solved dependence (at %i)\n",
			     &piMop[-1] - (int *)pheccer->vm.pvMops);

			return(FALSE);
		    }

		    //t I guess this can go wrong, not sure

		    double *pdConcentration = (double *)pheccer->vm.ppvMatsIndex[iInternal];

		    //- store solved internal concentration

		    pmops->pdInternal = pdConcentration;
		}

		break;
	    }

	    //- for single channel initialization

	    case HECCER_MOP_INITIALIZECHANNEL:
	    {
		//- go to next operator

		struct MopsInitializeChannel *pmops = (struct MopsInitializeChannel *)piMop;

		piMop = (int *)&pmops[1];

		break;
	    }

	    //- for single channel initialization with variable reversal potential

	    case HECCER_MOP_INITIALIZECHANNELEK:
	    {
		//- go to next operator

		struct MopsInitializeChannelEk *pmops = (struct MopsInitializeChannelEk *)piMop;

		piMop = (int *)&pmops[1];

		//- get index of reversal potential

		double *pdReversalPotential = pmops->pdReversalPotential;

		//- if still an index

		if (pdReversalPotential)
		{
		    //- convert index to pointer

		    int iReversalPotential = (int)pdReversalPotential;

		    if (iReversalPotential == -1)
		    {
			//t HeccerError(number, message, varargs);

			fprintf
			    (stderr,
			     "Heccer the hecc : cannot resolve link for a solved dependence (at %i)\n",
			     &piMop[-1] - (int *)pheccer->vm.pvMops);

			return(FALSE);
		    }

		    //t I guess this can go wrong, not sure

		    double *pdNernst = (double *)pheccer->vm.ppvMatsIndex[iReversalPotential];

		    //- store solved nernst potential

		    pmops->pdReversalPotential = pdNernst;
		}

		break;
	    }

	    //- to compute a channel's conductance

	    case HECCER_MOP_STORECHANNELCONDUCTANCE:
	    {
		//- go to next operator

		piMop = &piMop[1];

		//- store the current conductance

		struct MatsStoreChannelConductance * pmats = (struct MatsStoreChannelConductance *)pvMats;

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

		//- get possibly solved dependence

		double *pdState = pmops->pdState;

		//- if still an index

		if (pdState)
		{
		    //- convert index to pointer

		    int iMatsActivator = (int)pdState;

		    if (iMatsActivator == -1)
		    {
			//t HeccerError(number, message, varargs);

			fprintf
			    (stderr,
			     "Heccer the hecc : cannot resolve link for a solved dependence (at %i)\n",
			     &piMop[-1] - (int *)pheccer->vm.pvMops);

			return(FALSE);
		    }

		    double *pdMatsActivator = (double *)pheccer->vm.ppvMatsIndex[iMatsActivator];

		    //- store solved dependence

		    pmops->pdState = pdMatsActivator;
		}

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

		//- get possibly solved external flux contributions

		int i;

		for (i = 0 ; i < EXPONENTIALDECAY_CONTRIBUTORS ; i++)
		{
		    double *pdExternal = pmops->ppdExternal[i];

		    //- if still an index

		    if (pdExternal)
		    {
			//- convert index to pointer

			int iExternal = (int)pdExternal;

			if (iExternal == -1)
			{
			    //t HeccerError(number, message, varargs);

			    fprintf
				(stderr,
				 "Heccer the hecc : cannot resolve link for a solved dependence (at %i)\n",
				 &piMop[-1] - (int *)pheccer->vm.pvMops);

			    return(FALSE);
			}

			double *pdFlux = (double *)pheccer->vm.ppvMatsIndex[iExternal];

			//- store solved external flux contribution

			pmops->ppdExternal[i] = pdFlux;
		    }
		}

		break;
	    }

	    //- register current contribution to a pool

	    case HECCER_MOP_FLUXPOOL:
	    {
		//- go to next operator

		struct MopsFluxPool *pmops = (struct MopsFluxPool *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsFluxPool * pmats = (struct MatsFluxPool *)pvMats;

		pvMats = (void *)&pmats[1];

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

    double *pdResults = &pheccer->vm.pdResults[0];

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

	    //- for a nernst operation with internal variable concentration

	    case HECCER_MOP_INTERNALNERNST:
	    {
		//- go to next operator

		struct MopsInternalNernst *pmops = (struct MopsInternalNernst *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsInternalNernst * pnernst = (struct MatsInternalNernst *)pvMats;

		pvMats = (void *)&((struct MatsInternalNernst *)pvMats)[1];

		//- fetch variables

		double dExternal = pmops->dExternal;

		double dConstant = pmops->dConstant;

		double dInternal = 0.0;

		if (pmops->pdInternal)
		{
		    dInternal = *pmops->pdInternal;
		}

		//- computer nernst potential

		//t produces invalid things if pdInternal is not set.

		double dPotential = log(dExternal / dInternal) * dConstant;

		//- store result

		pnernst->dPotential = dPotential;

		break;
	    }

	    //- for single channel initialization

	    case HECCER_MOP_INITIALIZECHANNEL:
	    {
		//- go to next operator

		struct MopsInitializeChannel *pmops = (struct MopsInitializeChannel *)piMop;

		piMop = (int *)&pmops[1];

		//- load channel variables

		dChannelConductance = pmops->dMaximalConductance;

		dReversalPotential = pmops->dReversalPotential;

		break;
	    }

	    //- for single channel initialization with variable reversal potential

	    case HECCER_MOP_INITIALIZECHANNELEK:
	    {
		//- go to next operator

		struct MopsInitializeChannelEk *pmops = (struct MopsInitializeChannelEk *)piMop;

		piMop = (int *)&pmops[1];

		//- load channel variables

		dChannelConductance = pmops->dMaximalConductance;

		dReversalPotential = pmops->pdReversalPotential[0];

		break;
	    }

	    //- to compute a channel's conductance

	    case HECCER_MOP_STORECHANNELCONDUCTANCE:
	    {
		//- go to next operator

		piMop = &piMop[1];

		//- store the current conductance

		struct MatsStoreChannelConductance * pmats = (struct MatsStoreChannelConductance *)pvMats;

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

		if (pdState)
		{
		    //- state is coming from a solved mechanism variable

		    dState = *pdState;
		}

		//- else is a membrane potential dependent gate

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

/* 		printf("forward %g, backward %g\n", dForward, dBackward); */

		//- compute gate activation state

/* 		dActivation = (dActivation * (2.0 - dBackward) + dForward) / dBackward; */

		dActivation = dForward / dBackward + dActivation * 2.0 / dBackward - dActivation;

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
		    //t HeccerError(number, message, varargs);

		    fprintf
			(stderr,
			 "Heccer the hecc : invalid gate power (%i)\n", iPower);

		    *(int *)0 = 0;
		}

		break;
	    }

	    //- register single channel contribution

	    case HECCER_MOP_REGISTERCHANNELCURRENT:
	    {
		//- go to next operator

		piMop = &piMop[1];

		//- compute single channel current

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

		//! so after the channel mat comes the flux mat.  This
		//! is a hack ... which could be solved, by having an
		//! intermediary that linearizes and specifies
		//! _all_ the equations (so including fluxes).

		//t In other words, the test 'if (pcac->iPool != -1)'
		//t should be removed and the removal should be
		//t counterbalanced by the neccessary specifications
		//t for a flux in the intermediary.  Then, these
		//t specifications are compiled to HECCER_MOP_FLUXPOOL
		//t byte code.

		//t needs a careful check again.

		double dExternal = 0.0;

		int i;

		for (i = 0 ; i < EXPONENTIALDECAY_CONTRIBUTORS ; i++)
		{
		    double *pdExternal = pmops->ppdExternal[i];

		    if (pdExternal)
		    {
			dExternal += pdExternal[0];
		    }
		}

		//- exponential decay with possibly external influx

/* 		dState = dSteadyState + ((dState - dSteadyState) * (2.0 - dTau) + (dExternal * dBeta)) / dTau; */

		dState = (dSteadyState * dTau * 2.0 + dState * 2.0 + dExternal * dBeta - dSteadyState * 2.0) / dTau - dState;

		//- save state

		pmats->dState = dState;

		break;
	    }

	    //- register current contribution to a pool

	    case HECCER_MOP_FLUXPOOL:
	    {
		//- go to next operator

		struct MopsFluxPool *pmops = (struct MopsFluxPool *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsFluxPool * pmats = (struct MatsFluxPool *)pvMats;

		pvMats = (void *)&pmats[1];

		//- register contribution

		pmats->dFlux = dSingleChannelCurrent;

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


