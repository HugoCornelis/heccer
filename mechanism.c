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


#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heccer/addressing.h"
#include "heccer/compartment.h"
#include "heccer/event.h"
#include "heccer/heccer.h"
#include "heccer/random.h"


static
int
HeccerCheckParameters
(struct Heccer *pheccer,
 char *pcDescription,
 ...);

static
int
HeccerMechanismReadDoubleFile
(struct Heccer *pheccer, char *pcFilename, double **ppdValues);


/// **************************************************************************
///
/// SHORT: HeccerCheckParameters()
///
/// ARGS.:
///
///	pheccer.......: a heccer.
///	pcDescription.: description of these parameters.
///	va_list.......: -1 terminated list of boolean values.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Check parameters utility function.
///
///	Just give a list of boolean expressions, telling if the
///	parameters comply or not, a description where they occur.
///	This function will call HeccerError() for any FALSE boolean in
///	the stdarg list.
///
/// **************************************************************************

static
int
HeccerCheckParameters
(struct Heccer *pheccer,
 char *pcDescription,
 ...)
{
    //- set default result: ok

    int iResult = 1;

    //v stdargs list

    va_list vaList;

    //- get start of stdargs

    va_start(vaList, pcDescription);

    //- loop over all arguments

    int iOk = va_arg(vaList, int);

    while (iOk != -1)
    {
	//- if current argument not ok

	if (!iOk)
	{
	    char pcMessage[1000];

	    sprintf(pcMessage, "%s invalid", pcDescription);

	    //t HeccerError(number, message, varargs);

	    HeccerError
		(pheccer,
		 NULL,
		 pcMessage);

	    //- break loop

	    break;
	}

	//- go to next argument

	iOk = va_arg(vaList, int);
    }

    //- end stdargs

    va_end(vaList);

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

    //- check parameters

    HeccerCheckParameters
	(
	    pheccer,
	    "HeccerMechanismCompile(): time step",
	    (dt > 0 && dt < 1),
	    -1
	    );

    //- first count, then index, next compile the following block

    int iMopNumber;
    int iMatNumber;

    int iCountIndexCompile;

    void *pvMops = NULL;
    void *pvMats = NULL;
    void **ppvCMatsIndex = NULL;
    void **ppvMopsIndex = NULL;
    void **ppvMatsIndex = NULL;
    int *piMC2Mop = NULL;
    uMC2Mat *piMC2Mat = NULL;

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

	    //- check parameters

	    char pcDescription[1000];

	    sprintf(pcDescription, "HeccerMechanismCompile(): compartment %i parameters (dCm == %f, dEm == %f, dRm == %f)", iIntermediary, dCm, dEm, dRm);

	    HeccerCheckParameters
		(
		    pheccer,
		    pcDescription,
		    (dCm != 0),
		    (dEm >= -1 && dEm <= 1),
		    (dRm != 0),
		    -1
		    );

	    //- fill in compartment constants

	    //! note : pdDiagonals was computed with schedule numbers.

	    //t these need an extra check, probably wrong.

	    //t perhaps need to split SETMAT_COMPARTMENT in SETMAT_COMPARTMENT_START
	    //t and SETMAT_COMPARTMENT_FINISH
	    //t between those two, we compile in the mechanisms.

	    SETMAT_COMPARTMENT(ppvCMatsIndex, iSchedule, ppvMatsIndex, iMatNumber, pvMats, iMats, dEm / dRm, dInject, dt / dCm, pheccer->vm.pdDiagonals[iSchedule]);

	    //- loop over mechanisms for this compartment

	    int iMathComponent;

	    int iStart = iIntermediary == 0 ? 0 : pheccer->inter.piC2m[iIntermediary - 1];

	    if (pheccer->inter.pmca && iStart > pheccer->inter.pmca->iMathComponents)
	    {
		//t HeccerError(number, message, varargs);

		HeccerError
		    (pheccer,
		     NULL,
		     "trying to fetch math component number %i, which is out of range",
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

		//- for a spring mass equation

		case MATH_TYPE_ChannelSpringMass:
		{
		    //- get type specific data

		    struct ChannelSpringMass * pcsm = (struct ChannelSpringMass *)pmc;

		    pmc = MathComponentNext(&pcsm->mc);

		    //- check parameters

		    HeccerCheckParameters
			(
			    pheccer,
			    "MATH_TYPE_ChannelSpringMass parameters",
			    (pcsm->dReversalPotential > -1 && pcsm->dReversalPotential < 1),
			    (pcsm->parameters.dTau1 != pcsm->parameters.dTau2),
			    -1
			    );

		    //- compute conductance normalizer

		    double dNormalizer;

		    if (pcsm->parameters.dTau1 == pcsm->parameters.dTau2)
		    {
			dNormalizer = pcsm->dMaximalConductance * M_E / pcsm->parameters.dTau1;
		    }
		    else 
		    {
			double dPeak
			    = (pcsm->parameters.dTau1
			       * pcsm->parameters.dTau2
			       * log(pcsm->parameters.dTau1 / pcsm->parameters.dTau2)
			       / (pcsm->parameters.dTau1 - pcsm->parameters.dTau2));

			dNormalizer
			    = (pcsm->dMaximalConductance
			       * (pcsm->parameters.dTau1 - pcsm->parameters.dTau2)
			       / (pcsm->parameters.dTau1
				  * pcsm->parameters.dTau2
				  * (exp(- dPeak / pcsm->parameters.dTau1)
				     - exp(- dPeak / pcsm->parameters.dTau2))));
		    }

		    //- for a constant reversal potential

		    if (pcsm->iReversalPotential == -1)
		    {
			SETMOP_INITIALIZECHANNEL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, dNormalizer, pcsm->dReversalPotential);
		    }

		    //- else a solved reversal potential

		    else
		    {
			//- get math component number

			int iMathComponentReversalPotential = pcsm->iReversalPotential;

			int iMatsReversalPotential = -1;

			if (iMathComponentReversalPotential != -1)
			{
			    //- convert math component to mat number, convert mat number to mat addressable

			    iMatsReversalPotential = piMC2Mat ? piMC2Mat[iMathComponentReversalPotential].iMat : -1;
			}

			SETMOP_INITIALIZECHANNELEK(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, dNormalizer, iMatsReversalPotential);
		    }

		    //- preprocess the event list if any

		    if (pcsm->pcEventTimes
			&& pcsm->pdEventTimes)
		    {
			//t HeccerError(number, message, varargs);

			HeccerError
			    (pheccer,
			     NULL,
			     "found a file specification as well as an array specification for event times of a springmass channel, "
			     "model container component number %i\n",
#ifdef HECCER_SOURCE_NEUROSPACES
			     pcsm->mc.iSerial,
#else
			     //t bhlkjwe, should have a char * here

			     -1,
#endif
			     iStart);

			//- return error

			return(FALSE);
		    }

		    if (pcsm->pcEventTimes)
		    {
			//- read in the file

			int iDoubles = HeccerMechanismReadDoubleFile(pheccer, pcsm->pcEventTimes, &pcsm->pdEventTimes);

			if (iDoubles == -1
			    || !pcsm->pdEventTimes)
			{
			    //t HeccerError(number, message, varargs);

			    HeccerError
				(pheccer,
				 NULL,
				 "could not read file %s, specified for a springmass channel, "
				 "model container component number %i\n",
				 pcsm->pcEventTimes,
#ifdef HECCER_SOURCE_NEUROSPACES
				 pcsm->mc.iSerial,
#else
				 //t bhlkjwe, should have a char * here

				 -1,
#endif
				 iStart);

			    //- return error

			    return(FALSE);
			}

			//! it would probably be a good idea to be able to go back to the original specification.

			//- mark end of array

			pcsm->pdEventTimes[iDoubles] = FLT_MAX;

			//- remove the reference to the file, for next loop over processing

			pcsm->pcEventTimes = NULL;
		    }

		    //- tabulate the channel

		    //- tabulate activation, Genesis X
		    //- create forward table, Genesis A, alpha, create backward table, Genesis B, alpha + beta

		    int iTabulated = HeccerTabulateAny(pheccer, pcsm, MATH_TYPE_ChannelSpringMass);

#ifdef HECCER_SOURCE_NEUROSPACES

		    //- convert serial to index in the connection matrix

		    int iDiscreteTarget = EventQueuerSerial2ConnectionIndex(pheccer->peq, ADDRESSING_HECCER_2_NEUROSPACES(pcsm->mc.iSerial));

#else

		    int iDiscreteTarget = -1;

#endif

		    SETMOP_SPRINGMASS(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcsm->pdEventTimes, iDiscreteTarget, pcsm->iTable, pheccer->dStep * pcsm->dFrequency);

		    double dNextEvent = -1.0;

		    SETMAT_SPRINGMASS(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, pcsm->dInitX, pcsm->dInitY, dNextEvent);

		    SETMOP_UPDATECOMPARTMENTCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    //t would it be useful to retabulate here ?

		    //- register pool index

		    //t for reasons of easy initialization, this should be a check for zero.
		    //t this means that I have to offset all mechanisms with 1
		    //t (mmm, the hines solver did the same, but for other reasons).

		    if (pcsm->iPool != -1)
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

		//- for a nernst operation with internal variable concentration

		case MATH_TYPE_InternalNernst:
		{
		    //- get type specific data

		    struct InternalNernst * pin = (struct InternalNernst *)pmc;

		    pmc = MathComponentNext(&pin->mc);

		    //- check parameters

		    HeccerCheckParameters
			(
			    pheccer,
			    "MATH_TYPE_InternalNernst parameters",
			    -1
			    );

		    //- get math component number

		    int iMathComponentActivator = pin->iInternal;

		    int iMatsActivator = -1;

		    if (iMathComponentActivator != -1)
		    {
			//- convert math component to mat number, convert mat number to mat addressable

			iMatsActivator = piMC2Mat ? piMC2Mat[iMathComponentActivator].iMat : -1;
		    }

		    SETMOP_INTERNALNERNST(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pin->dConstant, pin->dExternal, iMatsActivator);

		    SETMAT_INTERNALNERNST(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, pin->dInitPotential);

		    break;
		}

		//- for a channel with only activation

		case MATH_TYPE_ChannelAct:
		{
		    //- get type specific data

		    struct ChannelAct *pca = (struct ChannelAct *)pmc;

		    pmc = MathComponentNext(&pca->mc);

		    //- check parameters

		    HeccerCheckParameters
			(
			    pheccer,
			    "MATH_TYPE_ChannelAct parameters",
			    -1
			    );

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

			int iMatsReversalPotential = -1;

			if (iMathComponentReversalPotential != -1)
			{
			    //- convert math component to mat number, convert mat number to mat addressable

			    iMatsReversalPotential = piMC2Mat ? piMC2Mat[iMathComponentReversalPotential].iMat : -1;
			}

			SETMOP_INITIALIZECHANNELEK(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pca->dMaximalConductance, iMatsReversalPotential);
		    }

		    //- tabulate the channel

		    //- tabulate activation, Genesis X
		    //- create forward table, Genesis A, alpha, create backward table, Genesis B, alpha + beta

		    int iTabulated
			= HeccerTabulateAny(pheccer, &pca->pgc.gc, MATH_TYPE_GateConcept);

		    SETMOP_LOADVOLTAGETABLE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pca->pgc.gc.iTable, pca->pgc.iPower,-1);

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

		    //- check parameters

		    HeccerCheckParameters
			(
			    pheccer,
			    "MATH_TYPE_ChannelActInact parameters",
			    -1
			    );

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

			int iMatsReversalPotential = -1;

			if (iMathComponentReversalPotential != -1)
			{
			    //- convert math component to mat number, convert mat number to mat addressable

			    iMatsReversalPotential = piMC2Mat ? piMC2Mat[iMathComponentReversalPotential].iMat : -1;
			}

			SETMOP_INITIALIZECHANNELEK(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcai->dMaximalConductance, iMatsReversalPotential);
		    }

		    //- tabulate the channel

		    //- tabulate activation, Genesis X
		    //- create forward table, Genesis A, alpha, create backward table, Genesis B, alpha + beta

		    int iTabulatedActivation
			= HeccerTabulateAny(pheccer, &pcai->pgcActivation.gc, MATH_TYPE_GateConcept);

		    SETMOP_LOADVOLTAGETABLE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcai->pgcActivation.gc.iTable, pcai->pgcActivation.iPower,-1);

		    //! at the beginning of a simulation, you would expect this to be the steady state value

		    SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, pcai->pgcActivation.gc.dInitActivation);

		    //- tabulate inactivation, Genesis Y
		    //- create forward table, Genesis A, alpha, create backward table, Genesis B, alpha + beta

		    int iTabulatedInactivation
			= HeccerTabulateAny(pheccer, &pcai->pgcInactivation.gc, MATH_TYPE_GateConcept);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcai->pgcInactivation.gc.iTable, pcai->pgcInactivation.iPower,-1);

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

		    //- check parameters

		    HeccerCheckParameters
			(
			    pheccer,
			    "MATH_TYPE_ChannelActConc parameters",
			    -1
			    );

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

			int iMatsReversalPotential = -1;

			if (iMathComponentReversalPotential != -1)
			{
			    //- convert math component to mat number, convert mat number to mat addressable

			    iMatsReversalPotential = piMC2Mat ? piMC2Mat[iMathComponentReversalPotential].iMat : -1;
			}

			SETMOP_INITIALIZECHANNELEK(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcac->dMaximalConductance, iMatsReversalPotential);
		    }

		    //- tabulate the membrane dependence

		    //- tabulate membrane dependence, Genesis X
		    //- create forward table, Genesis A, alpha, create backward table, Genesis B, alpha + beta

		    int iTabulatedMembraneDependence
			= HeccerTabulateAny(pheccer, &pcac->pgc.gc, MATH_TYPE_GateConcept);

		    SETMOP_LOADVOLTAGETABLE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcac->pgc.gc.iTable, pcac->pgc.iPower,-1);

		    //! at the beginning of a simulation, you would expect this to be the steady state value

		    SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, pcac->pgc.gc.dInitActivation);

		    //- tabulate concentration dependence, Genesis Z
		    //- create forward table, Genesis A, alpha, create backward table, Genesis B, alpha + beta

		    int iTabulatedBasalActivator
			= HeccerTabulateAny(pheccer, &pcac->pac.ac, MATH_TYPE_BasalActivator);

		    //! gate computations are just fetching things from tables, and
		    //! multiplying the conductances, so it is not relevant if these
		    //! computations are done for membrane potential dependent gates or
		    //! concentration dependent gates.

		    //- get math component number

		    int iMathComponentActivator = pcac->pac.ac.iActivator;

		    int iMatsActivator = -1;

		    if (iMathComponentActivator != -1)
		    {
			//- convert math component to mat number, convert mat number to mat addressable

			iMatsActivator = piMC2Mat ? piMC2Mat[iMathComponentActivator].iMat : -1;
		    }

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcac->pac.ac.iTable, pcac->pac.iPower, iMatsActivator);

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

		    //- check parameters

		    HeccerCheckParameters
			(
			    pheccer,
			    "MATH_TYPE_ExponentialDecay parameters",
			    -1
			    );

		    int piExternal[EXPONENTIALDECAY_CONTRIBUTORS];

		    int i;

		    for (i = 0 ; i < EXPONENTIALDECAY_CONTRIBUTORS ; i++)
		    {
			//- get math component number

			int iContributor = pexdec->piExternal[i];

			int iMatsExternal = -1;

			if (iContributor != -1)
			{
			    //- convert math component to mat number, convert mat number to mat addressable

			    iMatsExternal = piMC2Mat ? piMC2Mat[iContributor].iMat : -1;

			    piExternal[i] = iMatsExternal;
			}
			else
			{
			    piExternal[i] = -1;
			}
		    }

		    SETMOP_EXPONENTIALDECAY(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pheccer->dStep * pexdec->dBeta, pexdec->dSteadyState, 1 + pheccer->dStep / (2 * pexdec->dTau), piExternal);

		    SETMAT_EXPONENTIALDECAY(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, pexdec->dInitValue);

		    break;
		}

		//- for a channel specified as steady state and a stepped tau

		case MATH_TYPE_ChannelSteadyStateSteppedTau:
		{
		    //- get type specific data

		    struct ChannelSteadyStateSteppedTau *pcsst = (struct ChannelSteadyStateSteppedTau *)pmc;

		    pmc = MathComponentNext(&pcsst->mc);

		    //- check parameters

		    HeccerCheckParameters
			(
			    pheccer,
			    "MATH_TYPE_ChannelSteadyStateSteppedTau parameters",
			    -1
			    );

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

			int iMatsReversalPotential = -1;

			if (iMathComponentReversalPotential != -1)
			{
			    //- convert math component to mat number, convert mat number to mat addressable

			    iMatsReversalPotential = piMC2Mat ? piMC2Mat[iMathComponentReversalPotential].iMat : -1;
			}

			SETMOP_INITIALIZECHANNELEK(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcsst->dMaximalConductance, iMatsReversalPotential);
		    }

		    //- tabulate the channel

		    int iTabulated
			= HeccerTabulateAny(pheccer, pcsst, MATH_TYPE_ChannelSteadyStateSteppedTau);

		    SETMOP_LOADVOLTAGETABLE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcsst->iFirstTable, pcsst->iFirstPower, -1);

		    //! at the beginning of a simulation, you would expect this to be the steady state value

		    SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, pcsst->dFirstInitActivation);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcsst->iSecondTable, pcsst->iSecondPower, -1);

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

		    //- check parameters

		    HeccerCheckParameters
			(
			    pheccer,
			    "MATH_TYPE_ChannelPersistentSteadyStateDualTau parameters",
			    -1
			    );

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

			int iMatsReversalPotential = -1;

			if (iMathComponentReversalPotential != -1)
			{
			    //- convert math component to mat number, convert mat number to mat addressable

			    iMatsReversalPotential = piMC2Mat ? piMC2Mat[iMathComponentReversalPotential].iMat : -1;
			}

			SETMOP_INITIALIZECHANNELEK(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcpsdt->dMaximalConductance, iMatsReversalPotential);
		    }

		    //- tabulate the channel

		    int iTabulated
			= HeccerTabulateAny(pheccer, pcpsdt, MATH_TYPE_ChannelPersistentSteadyStateDualTau);

		    SETMOP_LOADVOLTAGETABLE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcpsdt->iFirstTable, pcpsdt->iFirstPower, -1);

		    //! at the beginning of a simulation, you would expect this to be the steady state value

		    SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, pcpsdt->dFirstInitActivation);

		    SETMOP_UPDATECOMPARTMENTCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_INITIALIZECHANNEL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcpsdt->dMaximalConductance, pcpsdt->dReversalPotential);

		    SETMOP_LOADVOLTAGETABLE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcpsdt->iSecondTable, pcpsdt->iSecondPower, -1);

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

		    //- check parameters

		    HeccerCheckParameters
			(
			    pheccer,
			    "MATH_TYPE_ChannelPersistentSteadyStateTau parameters",
			    -1
			    );

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

			int iMatsReversalPotential = -1;

			if (iMathComponentReversalPotential != -1)
			{
			    //- convert math component to mat number, convert mat number to mat addressable

			    iMatsReversalPotential = piMC2Mat ? piMC2Mat[iMathComponentReversalPotential].iMat : -1;
			}

			SETMOP_INITIALIZECHANNELEK(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcpst->dMaximalConductance, iMatsReversalPotential);
		    }

		    //- tabulate the channel

		    int iTabulated
			= HeccerTabulateAny(pheccer, pcpst, MATH_TYPE_ChannelPersistentSteadyStateTau);

		    SETMOP_LOADVOLTAGETABLE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcpst->iTable, pcpst->iPower, -1);

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

		case MATH_TYPE_SpikeGenerator:
		{
		    //- get type specific data

		    struct SpikeGenerator *psg = (struct SpikeGenerator *)pmc;

		    pmc = MathComponentNext(&psg->mc);

		    //- check parameters

		    HeccerCheckParameters
			(
			    pheccer,
			    "MATH_TYPE_SpikeGenerator parameters",
			    -1
			    );

		    //- set operators and operands

		    //! INT_MAX means the membrane potential is the source

		    //! for other things, fill in the matindex of the
		    //! source, the linker will link the mechanisms
		    //! together (untested).

		    int iSource = INT_MAX;

		    int iTable = psg->iTable;

		    if (iTable == INT_MAX)
		    {
			//t from ssp viewpoint, the distributor_service is already setup, and knows that it connects to this spikegen

			//t the distributor_service builds a table that converts model container serials to entries in the connection matrix

			//t here we use that table, to convert the serial to the index in the connection matrix


#ifdef HECCER_SOURCE_NEUROSPACES
			int iSerial = psg->mc.iSerial;
#else
			int iSerial = INT_MAX;
#endif

			struct EventDistributor *ped = pheccer->ped;

			//t EventDistributor does not know about anything yet, this cannot work.

			iTable = EventDistributorSerial2Index(ped, ADDRESSING_HECCER_2_NEUROSPACES(iSerial));

			//t so hardcoded solution that makes the spiker1 test case work

			iTable = 0;
		    }

		    SETMOP_EVENTGENERATE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, iSource, psg->dThreshold, psg->dRefractory, iTable);

		    //t we are not in the refractory period, check randomspike2 for initial refractory probability calculation.

		    double dRefractoryTime = -1.0;

		    double dSpike = 0.0;

		    SETMAT_EVENTGENERATE(iMathComponent, piMC2Mat, ppvMatsIndex, iMatNumber, pvMats, iMats, dRefractoryTime, dSpike);

		    //- if there is a reset value set

		    if (psg->dReset != FLT_MAX)
		    {
			//- generate op for resetting the membrane potential

			SETMOP_RESET(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, psg->dReset);

		    }

		    break;
		}

		default:
		{
		    //t HeccerError(number, message, varargs);

		    HeccerError
			(pheccer,
			 NULL,
			 "unknown pmc->iType (%i)",
			 iType);

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

	    HeccerError
		(pheccer,
		 NULL,
		 "mechanisms found after last compartment's mechanism");

	    return(FALSE);
	}

	//- finish all operations

	SETMOP_FINISH(ppvMopsIndex, iMopNumber, pvMops, iMops);

	//- if we were counting during the previous loop

	if (iCountIndexCompile == 0)
	{
	    pheccer->vm.iMopNumber = iMopNumber;

	    pheccer->vm.ppvCMatsIndex = (void **)calloc(pheccer->inter.iCompartments + 1, sizeof(void *));

	    ppvCMatsIndex = pheccer->vm.ppvCMatsIndex;

	    pheccer->vm.ppvMopsIndex = (void **)calloc(iMopNumber + 1, sizeof(void *));

	    ppvMopsIndex = pheccer->vm.ppvMopsIndex;

	    pheccer->vm.iMatNumber = iMatNumber;

	    pheccer->vm.ppvMatsIndex = (void **)calloc(iMatNumber + 1, sizeof(void *));

	    ppvMatsIndex = pheccer->vm.ppvMatsIndex;

	    if (pheccer->inter.pmca)
	    {
		//! note that this one does not index compartments, only the mechanism math components.

		pheccer->vm.piMC2Mat = (uMC2Mat *)calloc(pheccer->inter.pmca->iMathComponents + 1, sizeof(uMC2Mat));

		piMC2Mat = pheccer->vm.piMC2Mat;

		pheccer->vm.piMC2Mop = (int *)calloc(pheccer->inter.pmca->iMathComponents + 1, sizeof(int));

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

	    //- for a spring mass equation

	    case HECCER_MOP_SPRINGMASS:
	    {
		//- go to next operator

		struct MopsSpringMass *pmops = (struct MopsSpringMass *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsSpringMass *pmats = (struct MatsSpringMass *)pvMats;

		pvMats = (void *)&((struct MatsSpringMass *)pvMats)[1];

		//t iDiscreteSource must be linked here ?

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

		int iInternal = pmops->uInternal.iMat;

		if (iInternal != -1)
		{
		    //- get solved dependency

		    double *pdConcentration = (double *)pheccer->vm.ppvMatsIndex[iInternal];

		    //- store solved internal concentration

		    pmops->uInternal.pdValue = pdConcentration;
		}
		else
		{
		    pmops->uInternal.pdValue = NULL;
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

	    case HECCER_MOP_INITIALIZECHANNELEREV:
	    {
		//- go to next operator

		struct MopsInitializeChannelErev *pmops = (struct MopsInitializeChannelErev *)piMop;

		piMop = (int *)&pmops[1];

		//- get index of reversal potential

		int iReversalPotential = pmops->uReversalPotential.iMat;

		if (iReversalPotential != -1)
		{
		    //- get solved dependency

		    double *pdNernst = (double *)pheccer->vm.ppvMatsIndex[iReversalPotential];

		    //- store solved nernst potential

		    pmops->uReversalPotential.pdValue = pdNernst;
		}
		else
		{
		    pmops->uReversalPotential.pdValue = NULL;
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

		struct MopsVoltageTableDependency *pmops = (struct MopsVoltageTableDependency *)piMop;

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

		int iMatsActivator = pmops->uState.iMat;

		if (iMatsActivator != -1)
		{
		    //- get solved dependency

		    double *pdMatsActivator = (double *)pheccer->vm.ppvMatsIndex[iMatsActivator];

		    //- store solved dependency

		    pmops->uState.pdValue = pdMatsActivator;
		}
		else
		{
		    pmops->uState.pdValue = NULL;
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
		    int iExternal = pmops->puExternal[i].iMat;

		    if (iExternal != -1)
		    {
			//- get solved dependency

			double *pdFlux = (double *)pheccer->vm.ppvMatsIndex[iExternal];

			//- store solved external flux contribution

			pmops->puExternal[i].pdValue = pdFlux;
		    }
		    else
		    {
			pmops->puExternal[i].pdValue = NULL;
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

	    //- for an event generator

	    case HECCER_MOP_EVENTGENERATE:
	    {
		//- go to next operator

		struct MopsEventGenerate *pmops = (struct MopsEventGenerate *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsEventGenerate * pmats = (struct MatsEventGenerate *)pvMats;

		pvMats = (void *)&pmats[1];

		//- get source for comparison

/* 		int i; */

/* 		for (i = 0 ; i < EVENT_SOURCES ; i++) */
/* 		{ */
		    int iSource = pmops->uSource.iMat;

		    //- if should be current membrane potential

		    if (iSource == INT_MAX)
		    {
			//- set pointer value to a sentinel value

			//! this will generate a warning on some architectures

			pmops->uSource.pdValue = (double *)-1;
		    }

		    //- if linked to a mechanism value

		    else if (iSource != -1)
		    {
			//- get solved dependency

			double *pdSource = (double *)pheccer->vm.ppvMatsIndex[iSource];

			//- store solved external flux contribution

			pmops->uSource.pdValue = pdSource;
		    }
		    else
		    {
			pmops->uSource.pdValue = NULL;
		    }
/* 		} */

		break;
	    }

	    //- for a reset operation

	    case HECCER_MOP_RESET:
	    {
		//- go to next operator

		struct MopsReset *pmops = (struct MopsReset *)piMop;

		piMop = (int *)&pmops[1];

		break;
	    }

	    default:
	    {
		//t HeccerError(number, message, varargs);

		HeccerError
		    (pheccer,
		     NULL,
		     "unknown mechanism operation (%i)",
		     piMop[0]);

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

	HeccerError
	    (pheccer,
	     NULL,
	     "piMop[0] is %i, should be %i",
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
/// SHORT: HeccerMechanismReadDoubleFile()
///
/// ARGS.:
///
///	pheccer....: a heccer.
///	pcFilename.: filename to read.
///	ppdValues..: values that have been read, NULL for failure.
///
/// RTN..: int
///
///	Number of doubles read, -1 for failure.
///
///	ppdValues..: values that have been read, NULL for failure.
///
/// DESCR: Read a file with doubles, -1 terminated.
///
/// **************************************************************************

static
int
HeccerMechanismReadDoubleFile
(struct Heccer *pheccer, char *pcFilename, double **ppdValues)
{
    //- set default result: failure

    int iResult = -1;

    //- open file

    FILE *pfile = fopen(pcFilename, "r");

    if (!pfile)
    {
	return(iResult);
    }

    //- allocate result

    int iAllocated = 100;

    double *pdValues = (double *)calloc(iAllocated, sizeof(double));

    if (!pdValues)
    {
	return(iResult);
    }

    //- go through the file

    int iEOF = 0;

    int iDoubles = 0;

    while (!iEOF)
    {
#define ELEMENT_NAME_SIZE 100

	//- read a record

	char pc[ELEMENT_NAME_SIZE * 10];

	if (fgets(pc, ELEMENT_NAME_SIZE * 10, pfile))
	{
	    //- if not an element of a yaml array

	    //! hardcoded indentation, 4 spaces required

	    if (pc[0] == ' '
		&& pc[1] == ' '
		&& pc[2] == ' '
		&& pc[3] == ' '
		&& pc[4] == '-'
		&& pc[5] == ' ')
	    {
		int iScanned = sscanf(pc, " - %lf\n", &pdValues[iDoubles]);

		//- if number of scanned values is ok

		if (iScanned == 1)
		{
		    //- next record

		    iDoubles++;

		    //- check for reallocation need

		    if (iDoubles >= 100)
		    {
			iAllocated += 100;

			pdValues = (double *)realloc(pdValues, iAllocated * sizeof(double));

			if (!pdValues)
			{
			    break;
			}
		    }
		}
		else
		{
		    HeccerError
			(pheccer,
			 NULL,
			 "parse failure for HeccerMechanismReadDoubleFile(), record %i, scanned %i items (instead of 1)\n",
			 iDoubles,
			 iScanned); 

		    break;
		}
	    }
	}

	//- or

	else
	{
	    //- end of file

	    iEOF = 1;
	}
    }

    //- set result

    if (ppdValues)
    {
	*ppdValues = pdValues;
    }

    //- return result

    iResult = iDoubles;

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

	    //- for a spring mass equation

	    case HECCER_MOP_SPRINGMASS:
	    {
		//- go to next operator

		struct MopsSpringMass *pmops = (struct MopsSpringMass *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsSpringMass *pmats = (struct MatsSpringMass *)pvMats;

		pvMats = (void *)&((struct MatsSpringMass *)pvMats)[1];

		//- get pointer to table

		int iTable = pmops->iTable;

		struct HeccerTabulatedSpringMass *phtsm = &pheccer->tsmt.phtsm[iTable];

		//- if the firing frequence has been set

		if (pmops->dFrequency > 0)
		{
		    //- generate random number

		    int iRandom = RANDOM;

		    //- check generated number with firing frequency

		    if (iRandom < RAND_MAX * pmops->dFrequency)
		    {
			//- add one to the activation, and apply decay

			//! weight not normalized to the time step

			pmats->dX += phtsm->dX1;

/* 			fprintf(stdout, "Firing %i, %g\n", (int)(pheccer->dTime / pheccer->dStep), pheccer->dTime); */

		    }
		}

		//- if there is an event time table

		if (pmops->pdEvents)
		{
		    //- while the next event fires

		    while (pmops->pdEvents[pmops->iEvent] < pheccer->dTime)
		    {
			//- add one to the activation, and apply decay

			//! fixed weight of 1, normalized to the time step

			pmats->dX += phtsm->dX1;

			//- go to the next event

			//t should be a variable ?

			pmops->iEvent++;
		    }
		}

		//- if there is an incoming event from the event distributor

		if (pmats->dNextEvent != -1.0
		    && pmats->dNextEvent < pheccer->dTime

		    //! target index for this object

		    && pmops->iDiscreteTarget != -1)
		{
		    //- translate incoming events to their activation

		    double dActivation = HeccerEventReceive(pheccer, pmops->iDiscreteTarget);

		    if (dActivation != FLT_MAX)
		    {
			//- add the activation of (possibly multiple) events to the channel activation

			pmats->dX += dActivation * phtsm->dX1;
		    }
		    else
		    {
			//t HeccerError(number, message, varargs);

			HeccerError
			    (pheccer,
			     NULL,
			     "event reception failed for (%i) at time %g\n",
			     pmops->iDiscreteTarget,
			     pheccer->dTime); 

			return(0);
		    }

		    //- reset the incoming event time

		    pmats->dNextEvent = -1.0;
		}

		//- compute channel activation

		pmats->dX = pmats->dX * phtsm->dX2;

		pmats->dY = pmats->dX * phtsm->dY1 + pmats->dY * phtsm->dY2;

		//- compute channel conductance

		dChannelConductance *= pmats->dY;

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

		if (pmops->uInternal.pdValue)
		{
		    dInternal = *pmops->uInternal.pdValue;
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

	    case HECCER_MOP_INITIALIZECHANNELEREV:
	    {
		//- go to next operator

		struct MopsInitializeChannelErev *pmops = (struct MopsInitializeChannelErev *)piMop;

		piMop = (int *)&pmops[1];

		//- load channel variables

		dChannelConductance = pmops->dMaximalConductance;

		dReversalPotential = *pmops->uReversalPotential.pdValue;

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

		struct MopsVoltageTableDependency *pmops = (struct MopsVoltageTableDependency *)piMop;

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

		double *pdState = pmops->uState.pdValue;

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

		    HeccerError
			(pheccer,
			 NULL,
			 "invalid gate power (%i)",
			 iPower);

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
		    double *pdExternal = pmops->puExternal[i].pdValue;

		    if (pdExternal)
		    {
			dExternal += *pdExternal;
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

	    //- for an event generator

	    case HECCER_MOP_EVENTGENERATE:
	    {
		//- go to next operator

		struct MopsEventGenerate *pmops = (struct MopsEventGenerate *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsEventGenerate * pmats = (struct MatsEventGenerate *)pvMats;

		pvMats = (void *)&pmats[1];

		//- if spiking

		if (pmats->dRefractory == FLT_MAX)
		{
		    //- initialize refractory period

		    pmats->dRefractory = pmops->dRefractoryReset - pheccer->dStep;

		    //- set not spiking

		    pmats->dSpike = 0.0;
		}

		//- if in refractory period

		else if (pmats->dRefractory > 0.0)
		{
		    //- maintain refractory period since last event

		    pmats->dRefractory -= pheccer->dStep;
		}

		//- if not in refractory period

		else
		{
		    //- get source value

		    double *pdSource = pmops->uSource.pdValue;

		    if (pdSource)
		    {
			double dSource;

			//- if using membrane potential

			if (pdSource == (double *)-1)
			{
			    dSource = dVm;
			}

			//- if using a solved mechanism value

			else
			{
			    dSource = *pdSource;
			}

			//- if source greater than threshold

			if (dSource > pmops->dThreshold)
			{
			    //- register spiking

			    pmats->dRefractory = FLT_MAX;

			    pmats->dSpike = 1.0;

			    //- generate event for associated targets

			    int iResult = HeccerEventGenerate(pheccer, pmops->iTable);

			    if (!iResult)
			    {
				//t HeccerError(number, message, varargs);

				HeccerError
				    (pheccer,
				     NULL,
				     "spike generation failed at time (%g)",
				     pheccer->dTime);
			    }
			}
		    }
		}

		break;
	    }

	    //- for a reset operation

	    case HECCER_MOP_RESET:
	    {
		//- go to next operator

		struct MopsReset *pmops = (struct MopsReset *)piMop;

		piMop = (int *)&pmops[1];

		//- get reset value

		double dVmNew = pmops->dReset;

		//- set the membrane potential

		//t what if the user mixes this with active currents ?
		//t this is ok for simple integrate and fire,
		//t but for more complicated models I am not sure.

		pdVm[0] = dVmNew;

		break;
	    }

	    default:
	    {
		//t HeccerError(number, message, varargs);

		HeccerError
		    (pheccer,
		     NULL,
		     "unknown mechanism operation (%i)",
		     piMop[0]);

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

	HeccerError
	    (pheccer,
	     NULL,
	     "piMop[0] is %i, should be %i",
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

    //t sort on Erev, see adaptive time step paper and hsolve implementation.

    //- return result

    return(iResult);
}


