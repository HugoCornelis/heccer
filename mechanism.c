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


#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heccer/addressing.h"
#include "heccer/config.h"
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

static double
HeccerGateInitActivation
(struct Heccer *pheccer, int iTable, double dInitVm, double dInitActivation);

static
int
HeccerMechanismReadDoubleFile
(struct Heccer *pheccer, char *pcFilename, double **ppdValues);


/// 
/// \arg pheccer a heccer.
/// \arg pcDescription description of these parameters.
/// \arg va_list -1 terminated list of boolean values.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Check parameters utility function.
///
/// \details
/// 
///	Just give a list of boolean expressions, telling if the
///	parameters comply or not, a description where they occur.
///	This function will call HeccerError() for any FALSE boolean in
///	the stdarg list.
/// 

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


/// 
/// 
/// \arg pgc a gate concept.
/// \arg dInitActivation negative initial activation code.
/// 
/// \return double
/// 
///	initial gate value.
/// 
/// \brief Recompute an initial gate code to an initial gate value.
///

static double
HeccerGateInitActivation
(struct Heccer *pheccer, int iTable, double dInitVm, double dInitActivation)
{
    //- set default result: failure

    double dResult = DBL_MAX;

    //- if code is -1

    if (dInitActivation == -1)
    {
	// \todo nicely copied from HeccerMechanismSolveCN(), needs a
	// macro?

	//- fetch tables

	/// \todo table rearrangements

	struct HeccerTabulatedGate *phtg = &pheccer->tgt.phtg[iTable];

	double *pdA = phtg->pdA;
	double *pdB = phtg->pdB;

	double dState;

	//- for a concentration dependent gate

	double *pdState = NULL;

	double dVm = dInitVm;

	if (pdState)
	{
	    //- state is coming from a solved mechanism variable

	    dState = *pdState;
	}

	//- else is a membrane potential dependent gate

	else
	{
	    //- state is membrane potential

	    /// \todo move this to load membrane potential
	    /// \todo need LOADVOLTAGETABLE or LOADVOLTAGEINDEX

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

	//- fetch A and B gate rates

	double dA = pdA[iIndex];
	double dB = pdB[iIndex];

	dResult = dA / dB;
    }

    //- return result

    return(dResult);
}


/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Compile the intermediary of the mechanisms to byte code.
/// 
/// \note 
/// 
///	Compartment leak is a current, so it is considered to be a
///	mechanism.
/// 

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
    double *pdMats = NULL;
    double **ppdCMatsIndex = NULL;
    void **ppvMopsIndex = NULL;
    double **ppdMatsIndex = NULL;
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
	    //- get intermediary number for the current compartment

	    int iIntermediary = pheccer->indexers.md.piBackward[iSchedule];

	    //- register: it is undefined if a voltage has been
	    //- loaded, used by SETMOP_COMPARTMENT and
	    //- SETMOP_LOADVOLTAGETABLE

	    int iLoadVoltageTable = -1;

	    //- fill in compartment operation

	    SETMOP_COMPARTMENT(ppvMopsIndex, &pheccer->inter.pcomp[iIntermediary].mc, iMopNumber, pvMops, iMops);

	    /// \note Em/Rm
	    /// \note injected current
	    /// \note dt/cm
	    /// \note diagonal
	    ///
	    /// \note injected current needs a separate entry for interfacing.

	    //- retreive compartment constants

	    double dCm = pheccer->inter.pcomp[iIntermediary].dCm;

	    double dEm = pheccer->inter.pcomp[iIntermediary].dEm;

	    double dInitVm = pheccer->inter.pcomp[iIntermediary].dInitVm;

	    /// \todo perhaps better to do current injection with a
	    /// \todo hardcoded injector callout ?

	    double dInject = pheccer->inter.pcomp[iIntermediary].dInject;

	    double dRm = pheccer->inter.pcomp[iIntermediary].dRm;

	    //- check parameters

	    char pcDescription[1000];

	    sprintf(pcDescription, "HeccerMechanismCompile(): compartment %i parameters (dCm == %f, dEm == %f, dInitVm == %f dRm == %f)", iIntermediary, dCm, dEm, dInitVm, dRm);

	    HeccerCheckParameters
		(
		    pheccer,
		    pcDescription,
		    (dCm != 0),
		    (dEm >= -1 && dEm <= 1),
		    (dInitVm > -0.1 && dInitVm < 0.5),
		    (dRm != 0),
		    -1
		    );

	    //- fill in compartment constants

	    /// \note note : pdDiagonals was computed with schedule numbers.

	    /// \todo these need an extra check, probably wrong.

	    /// \todo perhaps need to split SETMAT_COMPARTMENT in SETMAT_COMPARTMENT_START
	    /// \todo and SETMAT_COMPARTMENT_FINISH
	    /// \todo between those two, we compile in the mechanisms.

	    SETMAT_COMPARTMENT(ppdCMatsIndex, iSchedule, ppdMatsIndex, iMatNumber, pdMats, iMats, dEm / dRm, dInject, dt / dCm, pheccer->vm.pdDiagonals[iSchedule]);

	    //- lookup the start of the mechanisms for this compartment

	    int iStart = iIntermediary == 0 ? 0 : pheccer->inter.piC2m[iIntermediary - 1];

	    if (pheccer->inter.pmca && iStart > pheccer->inter.pmca->iMathComponents)
	    {
		HeccerError
		    (pheccer,
		     NULL,
		     "trying to fetch math component number %i, which is out of range",
		     iStart);

		return(FALSE);
	    }

	    struct MathComponent *pmc = HeccerIntermediaryLookup(pheccer, iStart);

	    //- loop over mechanisms for this compartment

	    int iMathComponent;

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

		    SETMAT_CALLOUT(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, pcall);

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
/* 			    (pcsm->parameters.dTau1 != pcsm->parameters.dTau2), */
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
			HeccerError
			    (pheccer,
			     NULL,
			     "found both a file specification and an array specification for event times of a springmass channel, "
			     "model container component number %i, can only deal with one at this time\n",
#ifdef HECCER_SOURCE_NEUROSPACES
			     pcsm->mc.iSerial,
#else
			     /// \todo bhlkjwe, should have a char * here

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
			    HeccerError
				(pheccer,
				 NULL,
				 "could not read file %s, specified for a springmass channel, "
				 "model container component number %i\n",
				 pcsm->pcEventTimes,
#ifdef HECCER_SOURCE_NEUROSPACES
				 pcsm->mc.iSerial,
#else
				 /// \todo bhlkjwe, should have a char * here

				 -1,
#endif
				 iStart);

			    //- return error

			    return(FALSE);
			}

			/// \note it would probably be a good idea to be able to go back to the original specification.

			//- mark end of array

			pcsm->pdEventTimes[iDoubles] = DBL_MAX;

			//- remove the reference to the file, for next loop over processing

			pcsm->pcEventTimes = NULL;
		    }

		    //- tabulate the channel

		    //- tabulate activation, Genesis X
		    //- create A table, alpha, create B table, alpha + beta

		    int iTabulated = HeccerTabulateAny(pheccer, pcsm, pcsm->mc.iPrototype, MATH_TYPE_ChannelSpringMass);

#ifdef HECCER_SOURCE_NEUROSPACES

		    //- convert serial to index in the connection matrix

		    int iDiscreteTarget = EventQueuerSerial2ConnectionIndex(pheccer->peq, ADDRESSING_HECCER_2_NEUROSPACES(pcsm->mc.iSerial));

#else

		    int iDiscreteTarget = -1;

#endif

		    SETMOP_SPRINGMASS(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcsm->pdEventTimes, iDiscreteTarget, pcsm->iTable, pheccer->dStep * pcsm->dFrequency);

		    double dNextEvent = -1.0;

		    SETMAT_SPRINGMASS(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, pcsm->dInitX, pcsm->dInitY, dNextEvent);

		    SETMOP_UPDATECOMPARTMENTCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    /// \todo would it be useful to retabulate here ?

		    //- register pool index

		    /// \todo for reasons of easy initialization, this should be a check for zero.
		    /// \todo this means that I have to offset all mechanisms with 1
		    /// \todo (mmm, the hines solver did the same, but for other reasons).

		    if (pcsm->iPool != -1)
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_FLUXPOOL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			/// \note initial flux is assumed to be zero, always

			SETMAT_FLUXPOOL(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, 0.0);

		    }

		    //- compute individual channel contributions

		    if ( (pheccer->ho.iOptions & HECCER_OPTION_ENABLE_INDIVIDUAL_CURRENTS) )
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_STORESINGLECHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMAT_STORESINGLECHANNELCURRENT(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, 0.0, 0.0);

		    }

		    //- compute aggregate current and conductance for this mathematical component type

		    if ((pheccer->ho.iOptions & HECCER_OPTION_ENABLE_AGGREGATORS)
			&& pcsm->mc.iModelSourceType != -1)
		    {
			int iAggregator = pcsm->mc.iModelSourceType;

			SETMOP_AGGREGATECURRENT(&pheccer->vm, iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, iAggregator);

		    }

		    //- register result from tabulation for outcome of this function

		    iResult = iResult && iTabulated;

		    if (!iResult)
		    {
			HeccerError
			    (pheccer,
			     NULL,
			     "Compilation of ChannelSpringMass failed");
		    }

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

		    SETMAT_INTERNALNERNST(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, pin->dInitPotential);

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
		    //- create A table, alpha, create B table, alpha + beta

		    int iTabulated
			= HeccerTabulateAny(pheccer, &pca->pgc.gc, pca->mc.iPrototype, MATH_TYPE_GateConcept);

		    SETMOP_LOADVOLTAGETABLE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pca->pgc.gc.iTable, pca->pgc.iPower,-1);

		    /// \note at the beginning of a simulation, you would expect this to be the steady state value

		    {
			double dInitActivation = pca->pgc.gc.dInitActivation;

			if (dInitActivation == -1)
			{
			    dInitActivation = HeccerGateInitActivation(pheccer, pca->pgc.gc.iTable, dInitVm, dInitActivation);
			}

			SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, dInitActivation);
		    }

		    SETMOP_UPDATECOMPARTMENTCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    /// \todo retabulate cannot be done yet, do not know yet how many tables

		    //- register pool index

		    /// \todo for reasons of easy initialization, this should be a check for zero.
		    /// \todo this means that I have to offset all mechanisms with 1
		    /// \todo (mmm, the hines solver did the same, but for other reasons).

		    if (pca->iPool != -1)
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_FLUXPOOL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			/// \note initial flux is assumed to be zero, always

			SETMAT_FLUXPOOL(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, 0.0);

		    }

		    //- compute individual channel contributions

		    if ( (pheccer->ho.iOptions & HECCER_OPTION_ENABLE_INDIVIDUAL_CURRENTS) )
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_STORESINGLECHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMAT_STORESINGLECHANNELCURRENT(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, 0.0, 0.0);

		    }

		    //- compute aggregate current and conductance for this mathematical component type

		    if ((pheccer->ho.iOptions & HECCER_OPTION_ENABLE_AGGREGATORS)
			&& pca->mc.iModelSourceType != -1)
		    {
			int iAggregator = pca->mc.iModelSourceType;

			SETMOP_AGGREGATECURRENT(&pheccer->vm, iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, iAggregator);

		    }

		    //- register result from tabulation for outcome of this function

		    iResult = iResult && iTabulated;

		    if (!iResult)
		    {
			HeccerError
			    (pheccer,
			     NULL,
			     "Compilation of ChannelAct failed");
		    }

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
		    //- create A table, alpha, create B table, alpha + beta

		    int iTabulatedActivation
			= HeccerTabulateAny(pheccer, &pcai->pgcActivation.gc, pcai->mc.iPrototype, MATH_TYPE_GateConcept);

		    SETMOP_LOADVOLTAGETABLE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcai->pgcActivation.gc.iTable, pcai->pgcActivation.iPower,-1);

		    /// \note at the beginning of a simulation, you would expect this to be the steady state value

		    {
			double dInitActivation = pcai->pgcActivation.gc.dInitActivation;

			if (dInitActivation == -1)
			{
			    dInitActivation = HeccerGateInitActivation(pheccer, pcai->pgcActivation.gc.iTable, dInitVm, dInitActivation);
			}

			SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, dInitActivation);
		    }

		    //- tabulate inactivation, Genesis Y
		    //- create A table, alpha, create B table, alpha + beta

		    int iTabulatedInactivation
			= HeccerTabulateAny(pheccer, &pcai->pgcInactivation.gc, pcai->mc.iPrototype, MATH_TYPE_GateConcept);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcai->pgcInactivation.gc.iTable, pcai->pgcInactivation.iPower,-1);

		    /// \note at the beginning of a simulation, you would expect this to be the steady state value

		    {
			double dInitActivation = pcai->pgcInactivation.gc.dInitActivation;

			if (dInitActivation == -1)
			{
			    dInitActivation = HeccerGateInitActivation(pheccer, pcai->pgcInactivation.gc.iTable, dInitVm, dInitActivation);
			}

			SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, dInitActivation);
		    }

		    SETMOP_UPDATECOMPARTMENTCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    /// \todo retabulate cannot be done yet, do not know yet how many tables

		    //- register pool index

		    /// \todo for reasons of easy initialization, this should be a check for zero.
		    /// \todo this means that I have to offset all mechanisms with 1
		    /// \todo (mmm, the hines solver did the same, but for other reasons).

		    if (pcai->iPool != -1)
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_FLUXPOOL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			/// \note initial flux is assumed to be zero, always

			SETMAT_FLUXPOOL(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, 0.0);

		    }

		    //- compute individual channel contributions

		    if ( (pheccer->ho.iOptions & HECCER_OPTION_ENABLE_INDIVIDUAL_CURRENTS) )
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_STORESINGLECHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMAT_STORESINGLECHANNELCURRENT(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, 0.0, 0.0);

		    }

		    //- compute aggregate current and conductance for this mathematical component type

		    if ((pheccer->ho.iOptions & HECCER_OPTION_ENABLE_AGGREGATORS)
			&& pcai->mc.iModelSourceType != -1)
		    {
			int iAggregator = pcai->mc.iModelSourceType;

			SETMOP_AGGREGATECURRENT(&pheccer->vm, iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, iAggregator);

		    }

		    //- register result from tabulation for outcome of this function

		    iResult = iResult && iTabulatedActivation && iTabulatedInactivation;

		    if (!iResult)
		    {
			HeccerError
			    (pheccer,
			     NULL,
			     "Compilation of ChannelActInact failed");
		    }

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
		    //- create A table, alpha, create B table, alpha + beta

		    int iTabulatedMembraneDependence
			= HeccerTabulateAny(pheccer, &pcac->pgc.gc, pcac->mc.iPrototype, MATH_TYPE_GateConcept);

		    SETMOP_LOADVOLTAGETABLE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcac->pgc.gc.iTable, pcac->pgc.iPower,-1);

		    /// \note at the beginning of a simulation, you would expect this to be the steady state value

		    {
			double dInitActivation = pcac->pgc.gc.dInitActivation;

			if (dInitActivation == -1)
			{
			    dInitActivation = HeccerGateInitActivation(pheccer, pcac->pgc.gc.iTable, dInitVm, dInitActivation);
			}

			SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, dInitActivation);
		    }

		    //- tabulate concentration dependence, Genesis Z
		    //- create A table, alpha, create B table, alpha + beta

		    int iTabulatedBasalActivator
			= HeccerTabulateAny(pheccer, &pcac->pac.ca, pcac->mc.iPrototype, MATH_TYPE_Concentration);

		    /// \note gate computations are just fetching things from tables, and
		    /// \note multiplying the conductances, so it is not relevant if these
		    /// \note computations are done for membrane potential dependent gates or
		    /// \note concentration dependent gates.

		    //- get math component number

		    int iMathComponentActivator = pcac->pac.ca.iActivator;

		    int iMatsActivator = -1;

		    if (iMathComponentActivator != -1)
		    {
			//- convert math component to mat number, convert mat number to mat addressable

			iMatsActivator = piMC2Mat ? piMC2Mat[iMathComponentActivator].iMat : -1;
		    }

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcac->pac.ca.iTable, pcac->pac.iPower, iMatsActivator);

		    /// \note at the beginning of a simulation, you would expect this to be the steady state value

		    {
			double dInitActivation = pcac->pac.ca.dInitActivation;

			if (dInitActivation == -1)
			{
/* 			    dInitActivation = HeccerGateInitActivation(pheccer, pcac->pac.ca.iTable, dInitVm, dInitActivation); */

/* 			    HeccerError */
/* 				(pheccer, */
/* 				 NULL, */
/* 				 "Compilation of MATH_TYPE_ChannelActConc failed, illegal initial gate state"); */

			    //- this is a G2 compatibility thing, does not make sense, but sometimes ...

			    dInitActivation = 0;
			}

			SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, dInitActivation);
		    }

		    SETMOP_UPDATECOMPARTMENTCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    /// \todo retabulate cannot be done yet, do not know yet how many tables

		    //- register pool index

		    /// \todo for reasons of easy initialization, this should be a check for zero.
		    /// \todo this means that I have to offset all mechanisms with 1
		    /// \todo (mmm, the hines solver did the same, but for other reasons).

		    if (pcac->iPool != -1)
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_FLUXPOOL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			/// \note initial flux is assumed to be zero, always

			SETMAT_FLUXPOOL(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, 0.0);

		    }

		    //- compute individual channel contributions

		    if ( (pheccer->ho.iOptions & HECCER_OPTION_ENABLE_INDIVIDUAL_CURRENTS) )
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_STORESINGLECHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMAT_STORESINGLECHANNELCURRENT(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, 0.0, 0.0);

		    }

		    //- compute aggregate current and conductance for this mathematical component type

		    if ((pheccer->ho.iOptions & HECCER_OPTION_ENABLE_AGGREGATORS)
			&& pcac->mc.iModelSourceType != -1)
		    {
			int iAggregator = pcac->mc.iModelSourceType;

			SETMOP_AGGREGATECURRENT(&pheccer->vm, iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, iAggregator);

		    }

		    //- register result from tabulation for outcome of this function

		    iResult = iResult && iTabulatedMembraneDependence && iTabulatedBasalActivator;

		    if (!iResult)
		    {
			HeccerError
			    (pheccer,
			     NULL,
			     "Compilation of ChannelActConc failed");
		    }

		    break;
		}

		//- for a channel with only an external dependence

		case MATH_TYPE_ChannelConc:
		{
		    //- get type specific data

		    struct ChannelConc *pcc = (struct ChannelConc *)pmc;

		    pmc = MathComponentNext(&pcc->mc);

		    //- check parameters

		    HeccerCheckParameters
			(
			    pheccer,
			    "MATH_TYPE_ChannelConc parameters",
			    -1
			    );

		    //- for a constant reversal potential

		    if (pcc->iReversalPotential == -1)
		    {
			SETMOP_INITIALIZECHANNEL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcc->dMaximalConductance, pcc->dReversalPotential);
		    }

		    //- else a solved reversal potential

		    else
		    {
			//- get math component number

			int iMathComponentReversalPotential = pcc->iReversalPotential;

			int iMatsReversalPotential = -1;

			if (iMathComponentReversalPotential != -1)
			{
			    //- convert math component to mat number, convert mat number to mat addressable

			    iMatsReversalPotential = piMC2Mat ? piMC2Mat[iMathComponentReversalPotential].iMat : -1;
			}

			SETMOP_INITIALIZECHANNELEK(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcc->dMaximalConductance, iMatsReversalPotential);
		    }

		    //- tabulate concentration dependence, Genesis Z
		    //- create A table, alpha, create B table, alpha + beta

		    int iTabulatedBasalActivator
			= HeccerTabulateAny(pheccer, &pcc->pac.ca, pcc->mc.iPrototype, MATH_TYPE_Concentration);

		    /// \note gate computations are just fetching things from tables, and
		    /// \note multiplying the conductances, so it is not relevant if these
		    /// \note computations are done for membrane potential dependent gates or
		    /// \note concentration dependent gates.

		    //- get math component number

		    int iMathComponentActivator = pcc->pac.ca.iActivator;

		    int iMatsActivator = -1;

		    if (iMathComponentActivator != -1)
		    {
			//- convert math component to mat number, convert mat number to mat addressable

			iMatsActivator = piMC2Mat ? piMC2Mat[iMathComponentActivator].iMat : -1;
		    }

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcc->pac.ca.iTable, pcc->pac.iPower, iMatsActivator);

		    /// \note at the beginning of a simulation, you would expect this to be the steady state value

		    {
			double dInitActivation = pcc->pac.ca.dInitActivation;

			if (dInitActivation == -1)
			{
/* 			    dInitActivation = HeccerGateInitActivation(pheccer, pcc->pac.ca.iTable, dInitVm, dInitActivation); */

/* 			    HeccerError */
/* 				(pheccer, */
/* 				 NULL, */
/* 				 "Compilation of MATH_TYPE_ChannelConc failed, illegal initial gate state"); */

			    //- this is a G2 compatibility thing, does not make sense, but sometimes ...

			    dInitActivation = 0;
			}

			SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, dInitActivation);
		    }

		    SETMOP_UPDATECOMPARTMENTCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    /// \todo retabulate cannot be done yet, do not know yet how many tables

		    //- register pool index

		    /// \todo for reasons of easy initialization, this should be a check for zero.
		    /// \todo this means that I have to offset all mechanisms with 1
		    /// \todo (mmm, the hines solver did the same, but for other reasons).

		    if (pcc->iPool != -1)
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_FLUXPOOL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			/// \note initial flux is assumed to be zero, always

			SETMAT_FLUXPOOL(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, 0.0);

		    }

		    //- compute individual channel contributions

		    if ( (pheccer->ho.iOptions & HECCER_OPTION_ENABLE_INDIVIDUAL_CURRENTS) )
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_STORESINGLECHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMAT_STORESINGLECHANNELCURRENT(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, 0.0, 0.0);

		    }

		    //- compute aggregate current and conductance for this mathematical component type

		    if ((pheccer->ho.iOptions & HECCER_OPTION_ENABLE_AGGREGATORS)
			&& pcc->mc.iModelSourceType != -1)
		    {
			int iAggregator = pcc->mc.iModelSourceType;

			SETMOP_AGGREGATECURRENT(&pheccer->vm, iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, iAggregator);

		    }

		    //- register result from tabulation for outcome of this function

		    iResult = iResult && iTabulatedBasalActivator;

		    if (!iResult)
		    {
			HeccerError
			    (pheccer,
			     NULL,
			     "Compilation of ChannelConc failed");
		    }

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

		    SETMAT_EXPONENTIALDECAY(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, pexdec->dInitValue);

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
			= HeccerTabulateAny(pheccer, pcsst, pcsst->mc.iPrototype, MATH_TYPE_ChannelSteadyStateSteppedTau);

		    SETMOP_LOADVOLTAGETABLE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcsst->iFirstTable, pcsst->iFirstPower, -1);

		    /// \note at the beginning of a simulation, you would expect this to be the steady state value

		    {
			double dInitActivation = pcsst->dFirstInitActivation;

			if (dInitActivation == -1)
			{
			    dInitActivation = HeccerGateInitActivation(pheccer, pcsst->iFirstTable, dInitVm, dInitActivation);

/* 			    HeccerError */
/* 				(pheccer, */
/* 				 NULL, */
/* 				 "Compilation of MATH_TYPE_ChannelSteadyStateSteppedTau failed, illegal initial gate state"); */
			}

			SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, dInitActivation);
		    }

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcsst->iSecondTable, pcsst->iSecondPower, -1);

		    {
			double dInitActivation = pcsst->dSecondInitActivation;

			if (dInitActivation == -1)
			{
			    dInitActivation = HeccerGateInitActivation(pheccer, pcsst->iSecondTable, dInitVm, dInitActivation);

/* 			    HeccerError */
/* 				(pheccer, */
/* 				 NULL, */
/* 				 "Compilation of MATH_TYPE_ChannelSteadyStateSteppedTau failed, illegal initial gate state"); */
			}

			SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, dInitActivation);
		    }

		    SETMOP_UPDATECOMPARTMENTCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    /// \todo retabulate cannot be done yet, do not know yet how many tables

		    //- register pool index

		    /// \todo for reasons of easy initialization, this should be a check for zero.
		    /// \todo this means that I have to offset all mechanisms with 1
		    /// \todo (mmm, the hines solver did the same, but for other reasons).

		    if (pcsst->iPool != -1)
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_FLUXPOOL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			/// \note initial flux is assumed to be zero, always

			SETMAT_FLUXPOOL(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, 0.0);

		    }

		    //- compute individual channel contributions

		    if ( (pheccer->ho.iOptions & HECCER_OPTION_ENABLE_INDIVIDUAL_CURRENTS) )
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_STORESINGLECHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMAT_STORESINGLECHANNELCURRENT(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, 0.0, 0.0);

		    }

		    //- compute aggregate current and conductance for this mathematical component type

		    if ((pheccer->ho.iOptions & HECCER_OPTION_ENABLE_AGGREGATORS)
			&& pcsst->mc.iModelSourceType != -1)
		    {
			int iAggregator = pcsst->mc.iModelSourceType;

			SETMOP_AGGREGATECURRENT(&pheccer->vm, iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, iAggregator);

		    }

		    //- register result from tabulation for outcome of this function

		    iResult = iResult && iTabulated;

		    if (!iResult)
		    {
			HeccerError
			    (pheccer,
			     NULL,
			     "Compilation of ChannelSteadyStateSteppedTau failed");
		    }

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
			= HeccerTabulateAny(pheccer, pcpsdt, pcpsdt->mc.iPrototype, MATH_TYPE_ChannelPersistentSteadyStateDualTau);

		    SETMOP_LOADVOLTAGETABLE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcpsdt->iFirstTable, pcpsdt->iFirstPower, -1);

		    /// \note at the beginning of a simulation, you would expect this to be the steady state value

		    {
			double dInitActivation = pcpsdt->dFirstInitActivation;

			if (dInitActivation == -1)
			{
			    dInitActivation = HeccerGateInitActivation(pheccer, pcpsdt->iFirstTable, dInitVm, dInitActivation);

/* 			    HeccerError */
/* 				(pheccer, */
/* 				 NULL, */
/* 				 "Compilation of MATH_TYPE_ChannelPersistentSteadyStateDualTau failed, illegal initial gate state"); */
			}

			SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, dInitActivation);
		    }

		    SETMOP_UPDATECOMPARTMENTCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_INITIALIZECHANNEL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcpsdt->dMaximalConductance, pcpsdt->dReversalPotential);

		    SETMOP_LOADVOLTAGETABLE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcpsdt->iSecondTable, pcpsdt->iSecondPower, -1);

		    {
			double dInitActivation = pcpsdt->dSecondInitActivation;

			if (dInitActivation == -1)
			{
			    dInitActivation = HeccerGateInitActivation(pheccer, pcpsdt->iSecondTable, dInitVm, dInitActivation);

/* 			    HeccerError */
/* 				(pheccer, */
/* 				 NULL, */
/* 				 "Compilation of MATH_TYPE_ChannelPersistentSteadyStateDualTau failed, illegal initial gate state"); */
			}

			SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, dInitActivation);
		    }

		    SETMOP_UPDATECOMPARTMENTCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    /// \todo retabulate cannot be done yet, do not know yet how many tables

		    //- register pool index

		    /// \todo for reasons of easy initialization, this should be a check for zero.
		    /// \todo this means that I have to offset all mechanisms with 1
		    /// \todo (mmm, the hines solver did the same, but for other reasons).

		    if (pcpsdt->iPool != -1)
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_FLUXPOOL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			/// \note initial flux is assumed to be zero, always

			SETMAT_FLUXPOOL(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, 0.0);

		    }

		    //- compute individual channel contributions

		    if ( (pheccer->ho.iOptions & HECCER_OPTION_ENABLE_INDIVIDUAL_CURRENTS) )
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_STORESINGLECHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMAT_STORESINGLECHANNELCURRENT(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, 0.0, 0.0);

		    }

		    //- compute aggregate current and conductance for this mathematical component type

		    if ((pheccer->ho.iOptions & HECCER_OPTION_ENABLE_AGGREGATORS)
			&& pcpsdt->mc.iModelSourceType != -1)
		    {
			int iAggregator = pcpsdt->mc.iModelSourceType;

			SETMOP_AGGREGATECURRENT(&pheccer->vm, iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, iAggregator);

		    }

		    //- register result from tabulation for outcome of this function

		    iResult = iResult && iTabulated;

		    if (!iResult)
		    {
			HeccerError
			    (pheccer,
			     NULL,
			     "Compilation of ChannelPersistentSteadyStateDualTau failed");
		    }

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
			= HeccerTabulateAny(pheccer, pcpst, pcpst->mc.iPrototype, MATH_TYPE_ChannelPersistentSteadyStateTau);

		    SETMOP_LOADVOLTAGETABLE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, pcpst->iTable, pcpst->iPower, -1);

		    /// \note at the beginning of a simulation, you would expect this to be the steady state value

		    {
			double dInitActivation = pcpst->dInitActivation;

			if (dInitActivation == -1)
			{
			    dInitActivation = HeccerGateInitActivation(pheccer, pcpst->iTable, dInitVm, dInitActivation);

/* 			    HeccerError */
/* 				(pheccer, */
/* 				 NULL, */
/* 				 "Compilation of MATH_TYPE_ChannelPersistentSteadyStateTau failed, illegal initial gate state"); */
			}

			SETMAT_POWEREDGATECONCEPT(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, dInitActivation);
		    }

		    SETMOP_UPDATECOMPARTMENTCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

		    /// \todo retabulate cannot be done yet, do not know yet how many tables

		    //- register pool index

		    /// \todo for reasons of easy initialization, this should be a check for zero.
		    /// \todo this means that I have to offset all mechanisms with 1
		    /// \todo (mmm, the hines solver did the same, but for other reasons).

		    if (pcpst->iPool != -1)
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_FLUXPOOL(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			/// \note initial flux is assumed to be zero, always

			SETMAT_FLUXPOOL(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, 0.0);

		    }

		    //- compute individual channel contributions

		    if ( (pheccer->ho.iOptions & HECCER_OPTION_ENABLE_INDIVIDUAL_CURRENTS) )
		    {
			SETMOP_REGISTERCHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMOP_STORESINGLECHANNELCURRENT(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops);

			SETMAT_STORESINGLECHANNELCURRENT(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, 0.0, 0.0);

		    }

		    //- compute aggregate current and conductance for this mathematical component type

		    if ((pheccer->ho.iOptions & HECCER_OPTION_ENABLE_AGGREGATORS)
			&& pcpst->mc.iModelSourceType != -1)
		    {
			int iAggregator = pcpst->mc.iModelSourceType;

			SETMOP_AGGREGATECURRENT(&pheccer->vm, iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, iAggregator);

		    }

		    //- register result from tabulation for outcome of this function

		    iResult = iResult && iTabulated;

		    if (!iResult)
		    {
			HeccerError
			    (pheccer,
			     NULL,
			     "Compilation of ChannelPersistentSteadyStateTau failed");
		    }

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

		    /// \note INT_MAX means the membrane potential is the source

		    /// \note for other things, fill in the matindex of the
		    /// \note source, the linker will link the mechanisms
		    /// \note together (untested).

		    int iSource = INT_MAX;

		    int iTable = psg->iTable;

		    if (iTable == INT_MAX)
		    {
			/// \todo from ssp viewpoint, the distributor_service is already setup, and knows that it connects to this spikegen

			/// \todo the distributor_service builds a table that converts model container serials to entries in the connection matrix

			/// \todo here we use that table, to convert the serial to the index in the connection matrix


#ifdef HECCER_SOURCE_NEUROSPACES
			int iSerial = psg->mc.iSerial;
#else
			int iSerial = INT_MAX;
#endif

			struct EventDistributor *ped = pheccer->ped;

			/// there are two cases: spiker1 and spiker4
			/// spiker1 does have an event distributor service / solver
			/// spiker4 connects the addressable directly to the output solver

			if (ped)
			{
			    /// \todo EventDistributor does not know about anything yet, this cannot work.

			    /// \todo we need to register (indirectly) the
			    /// \todo memory location of iTable, probably by
			    /// \todo storing the iMopNumber in an index intended
			    /// \todo for resolving connections after CompileP3.

			    iTable = EventDistributorSerial2Index(ped, ADDRESSING_HECCER_2_NEUROSPACES(iSerial));

			    /// \todo so hardcoded solution that makes the spiker1 test case work

				iTable = 0;
			}
		    }

		    SETMOP_EVENTGENERATE(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, iSource, psg->dThreshold, psg->dRefractory, iTable);

		    /// \todo we are not in the refractory period, check randomspike2 for initial refractory probability calculation.

		    double dRefractoryTime = -1.0;

		    double dSpike = 0.0;

		    SETMAT_EVENTGENERATE(iMathComponent, piMC2Mat, ppdMatsIndex, iMatNumber, pdMats, iMats, dRefractoryTime, dSpike);

		    //- if there is a reset value set

		    if (psg->dReset != DBL_MAX)
		    {
			//- generate op for resetting the membrane potential

			SETMOP_RESET(iMathComponent, piMC2Mop, ppvMopsIndex, iMopNumber, pvMops, iMops, psg->dReset);

		    }

		    break;
		}

		default:
		{
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

	/// \note so pheccer->inter.piC2m can be NULL if no compartments have been found.

	if (pheccer->inter.piC2m
	    && pheccer->inter.piC2m[iSchedule] != -1)
	{
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
	    pheccer->vm.iMathComponents = pheccer->inter.pmca ? pheccer->inter.pmca->iMathComponents : 0;

	    pheccer->vm.iMopNumber = iMopNumber;

	    pheccer->vm.ppdCMatsIndex = (double **)calloc(pheccer->inter.iCompartments + 1, sizeof(double *));

	    ppdCMatsIndex = pheccer->vm.ppdCMatsIndex;

	    pheccer->vm.ppvMopsIndex = (void **)calloc(iMopNumber + 1, sizeof(void *));

	    ppvMopsIndex = pheccer->vm.ppvMopsIndex;

	    pheccer->vm.iMatNumber = iMatNumber;

	    pheccer->vm.ppdMatsIndex = (double **)calloc(iMatNumber + 1, sizeof(double *));

	    ppdMatsIndex = pheccer->vm.ppdMatsIndex;

	    if (pheccer->inter.pmca)
	    {
		/// \note note that this one does not index compartments, only the mechanism math components.

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

	    pheccer->vm.pdMats = (double *)calloc(iMats, 1);

	    pdMats = pheccer->vm.pdMats;

	    pheccer->vm.iMats = iMats;
	}
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Convert mat indices to pointers.
///
/// \details HeccerMechanismIndex2Pointer() converts mat indices in
/// the mops to mat pointers.  HeccerMechanismPointer2Index() converts
/// mat pointers in the mops to mat indices.
/// 

int HeccerMechanismIndex2Pointer(struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    int *piMop = (int *)pheccer->vm.pvMops;

    double *pdMats = pheccer->vm.pdMats;

    //- loop over mechanism operators

    while (piMop[0] == HECCER_MOP_COMPARTMENT)
    {
	//- go to next operator

	piMop = &piMop[1];

#if (USE_ID_DISASSEM)

	//- go to next operator

	piMop = &piMop[1];

#endif

	//- get compartment mechanism data

	struct MatsCompartment *pmatsc
	    = (struct MatsCompartment *)pdMats;

	pdMats = (double *)&((struct MatsCompartment *)pdMats)[1];

	//- loop over mechanism operators

	while (piMop[0] > HECCER_MOP_COMPARTMENT_BARRIER)
	{
	    //- look at next mechanism

	    switch (piMop[0])
	    {
	    //- for aggregate current

	    case HECCER_MOP_AGGREGATECURRENT:
	    {
		//- go to next operator

		struct MopsAggregateCurrent *pmops = (struct MopsAggregateCurrent *)piMop;

		piMop = (int *)&pmops[1];

		break;
	    }

	    //- for a call out

	    case HECCER_MOP_CALLOUT:
	    {
		//- go to next operator

		piMop = &piMop[1];

		//- go to next type specific data

		struct MatsCallout * pcall = (struct MatsCallout *)pdMats;

		pdMats = (double *)&((struct MatsCallout *)pdMats)[1];

		break;
	    }

	    //- for a spring mass equation

	    case HECCER_MOP_SPRINGMASS:
	    {
		//- go to next operator

		struct MopsSpringMass *pmops = (struct MopsSpringMass *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsSpringMass *pmats = (struct MatsSpringMass *)pdMats;

		pdMats = (double *)&((struct MatsSpringMass *)pdMats)[1];

		/// \todo iDiscreteSource must be linked here ?

		break;
	    }

	    //- for a nernst operation with internal variable concentration

	    case HECCER_MOP_INTERNALNERNST:
	    {
		//- go to next operator

		struct MopsInternalNernst *pmops = (struct MopsInternalNernst *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsInternalNernst * pnernst = (struct MatsInternalNernst *)pdMats;

		pdMats = (double *)&((struct MatsInternalNernst *)pdMats)[1];

		//- get index of internal concentration

		int iInternal = pmops->uInternal.iMat;

		if (iInternal != -1)
		{
		    //- get solved dependency

		    double *pdConcentration = &pheccer->vm.pdMats[iInternal];

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

		    double *pdNernst = &pheccer->vm.pdMats[iReversalPotential];

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

		struct MatsStoreChannelConductance * pmats = (struct MatsStoreChannelConductance *)pdMats;

		//- go to next type specific data

		pdMats = (double *)&pmats[1];

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

		struct MatsSingleGateConcept * pmats = (struct MatsSingleGateConcept *)pdMats;

		pdMats = (double *)&pmats[1];

		//- get possibly solved dependence

		int iMatsActivator = pmops->uState.iMat;

		if (iMatsActivator != -1)
		{
		    //- get solved dependency

		    double *pdMatsActivator = &pheccer->vm.pdMats[iMatsActivator];

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

	    //- compute current for single channel

	    case HECCER_MOP_STORESINGLECHANNELCURRENT:
	    {
		//- go to next operator

		struct MopsStoreSingleChannelCurrent *pmops = (struct MopsStoreSingleChannelCurrent *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsStoreSingleChannelCurrent * pmats = (struct MatsStoreSingleChannelCurrent *)pdMats;

		pdMats = (double *)&pmats[1];

		break;
	    }

	    //- compute exponential decay, mostly an ion concentration

	    case HECCER_MOP_EXPONENTIALDECAY:
	    {
		//- go to next operator

		struct MopsExponentialDecay *pmops = (struct MopsExponentialDecay *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsExponentialDecay * pmats = (struct MatsExponentialDecay *)pdMats;

		pdMats = (double *)&pmats[1];

		//- get possibly solved external flux contributions

		int i;

		for (i = 0 ; i < EXPONENTIALDECAY_CONTRIBUTORS ; i++)
		{
		    int iExternal = pmops->puExternal[i].iMat;

		    if (iExternal != -1)
		    {
			//- get solved dependency

			double *pdFlux = &pheccer->vm.pdMats[iExternal];

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

		struct MatsFluxPool * pmats = (struct MatsFluxPool *)pdMats;

		pdMats = (double *)&pmats[1];

		break;
	    }

	    //- for an event generator

	    case HECCER_MOP_EVENTGENERATE:
	    {
		//- go to next operator

		struct MopsEventGenerate *pmops = (struct MopsEventGenerate *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsEventGenerate * pmats = (struct MatsEventGenerate *)pdMats;

		pdMats = (double *)&pmats[1];

		//- get source for comparison

/* 		int i; */

/* 		for (i = 0 ; i < EVENT_SOURCES ; i++) */
		{
		    int iSource = pmops->uSource.iMat;

		    //- if should be current membrane potential

		    if (iSource == INT_MAX)
		    {
			//- set pointer value to a sentinel value

			/// \note this will generate a warning on some architectures

			pmops->uSource.pdValue = (double *)-1;
		    }

		    //- if linked to a mechanism value

		    else if (iSource != -1)
		    {
			//- get solved dependency

			double *pdSource = &pheccer->vm.pdMats[iSource];

			//- store solved external flux contribution

			pmops->uSource.pdValue = pdSource;
		    }
		    else
		    {
			pmops->uSource.pdValue = NULL;
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

		break;
	    }

	    default:
	    {
		HeccerError
		    (pheccer,
		     NULL,
		     "unknown mechanism operation (%i)",
		     piMop[0]);

		/// \note the best we can do is advance the pointer with one

		piMop = &piMop[1];

		break;
	    }
	    }
	}
    }

    //- check sanity of operator array

    if (piMop[0] != HECCER_MOP_FINISH)
    {
	HeccerError
	    (pheccer,
	     NULL,
	     "piMop[0] is %i, should be %i",
	     piMop[0],
	     HECCER_MOP_FINISH);

	/// \todo depending on options, bail out

	/// \todo set status : illegal mop hecc.
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Link mechanism operations.
///
/// \details HeccerMechanismLink() converts indices in the mops to
/// pointers.  HeccerMechanismIndex() converts points in the mops to
/// indices.
/// 

int HeccerMechanismLink(struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    int *piMop = (int *)pheccer->vm.pvMops;

    void *pdMats = pheccer->vm.pdMats;

    //- loop over mechanism operators

    while (piMop[0] == HECCER_MOP_COMPARTMENT)
    {
	//- go to next operator

	piMop = &piMop[1];

#if (USE_ID_DISASSEM)

	//- go to next operator

	piMop = &piMop[1];

#endif

	//- get compartment mechanism data

	struct MatsCompartment *pmatsc
	    = (struct MatsCompartment *)pdMats;

	pdMats = (double *)&((struct MatsCompartment *)pdMats)[1];

	//- loop over mechanism operators

	while (piMop[0] > HECCER_MOP_COMPARTMENT_BARRIER)
	{
	    //- look at next mechanism

	    switch (piMop[0])
	    {
	    //- for aggregate current

	    case HECCER_MOP_AGGREGATECURRENT:
	    {
		//- go to next operator

		struct MopsAggregateCurrent *pmops = (struct MopsAggregateCurrent *)piMop;

		piMop = (int *)&pmops[1];

		break;
	    }

	    //- for a call out

	    case HECCER_MOP_CALLOUT:
	    {
		//- go to next operator

		piMop = &piMop[1];

		//- go to next type specific data

		struct MatsCallout * pcall = (struct MatsCallout *)pdMats;

		pdMats = (double *)&((struct MatsCallout *)pdMats)[1];

		break;
	    }

	    //- for a spring mass equation

	    case HECCER_MOP_SPRINGMASS:
	    {
		//- go to next operator

		struct MopsSpringMass *pmops = (struct MopsSpringMass *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsSpringMass *pmats = (struct MatsSpringMass *)pdMats;

		pdMats = (double *)&((struct MatsSpringMass *)pdMats)[1];

		/// \todo iDiscreteSource must be linked here ?

		break;
	    }

	    //- for a nernst operation with internal variable concentration

	    case HECCER_MOP_INTERNALNERNST:
	    {
		//- go to next operator

		struct MopsInternalNernst *pmops = (struct MopsInternalNernst *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsInternalNernst * pnernst = (struct MatsInternalNernst *)pdMats;

		pdMats = (double *)&((struct MatsInternalNernst *)pdMats)[1];

		//- get index of internal concentration

		int iInternal = pmops->uInternal.iMat;

		if (iInternal != -1)
		{
		    //- get solved dependency

		    double *pdConcentration = pheccer->vm.ppdMatsIndex[iInternal];

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

		    double *pdNernst = pheccer->vm.ppdMatsIndex[iReversalPotential];

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

		struct MatsStoreChannelConductance * pmats = (struct MatsStoreChannelConductance *)pdMats;

		//- go to next type specific data

		pdMats = (double *)&pmats[1];

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

		struct MatsSingleGateConcept * pmats = (struct MatsSingleGateConcept *)pdMats;

		pdMats = (double *)&pmats[1];

		//- get possibly solved dependence

		int iMatsActivator = pmops->uState.iMat;

		if (iMatsActivator != -1)
		{
		    //- get solved dependency

		    double *pdMatsActivator = pheccer->vm.ppdMatsIndex[iMatsActivator];

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

	    //- compute current for single channel

	    case HECCER_MOP_STORESINGLECHANNELCURRENT:
	    {
		//- go to next operator

		struct MopsStoreSingleChannelCurrent *pmops = (struct MopsStoreSingleChannelCurrent *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsStoreSingleChannelCurrent * pmats = (struct MatsStoreSingleChannelCurrent *)pdMats;

		pdMats = (double *)&pmats[1];

		break;
	    }

	    //- compute exponential decay, mostly an ion concentration

	    case HECCER_MOP_EXPONENTIALDECAY:
	    {
		//- go to next operator

		struct MopsExponentialDecay *pmops = (struct MopsExponentialDecay *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsExponentialDecay * pmats = (struct MatsExponentialDecay *)pdMats;

		pdMats = (double *)&pmats[1];

		//- get possibly solved external flux contributions

		int i;

		for (i = 0 ; i < EXPONENTIALDECAY_CONTRIBUTORS ; i++)
		{
		    int iExternal = pmops->puExternal[i].iMat;

		    if (iExternal != -1)
		    {
			int iOffset = 0;

			//- if individual channel currents are enabled

			if (pheccer->ho.iOptions & HECCER_OPTION_ENABLE_INDIVIDUAL_CURRENTS)
			{
			    //- there is a mat entry in between, subtract one from the index

			    iOffset = -1;
			}

			//- get solved dependency

			double *pdFlux = pheccer->vm.ppdMatsIndex[iExternal + iOffset];

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

		struct MatsFluxPool * pmats = (struct MatsFluxPool *)pdMats;

		pdMats = (double *)&pmats[1];

		break;
	    }

	    //- for an event generator

	    case HECCER_MOP_EVENTGENERATE:
	    {
		//- go to next operator

		struct MopsEventGenerate *pmops = (struct MopsEventGenerate *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsEventGenerate * pmats = (struct MatsEventGenerate *)pdMats;

		pdMats = (double *)&pmats[1];

		//- get source for comparison

/* 		int i; */

/* 		for (i = 0 ; i < EVENT_SOURCES ; i++) */
		{
		    int iSource = pmops->uSource.iMat;

		    //- if should be current membrane potential

		    if (iSource == INT_MAX)
		    {
			//- set pointer value to a sentinel value

			/// \note this will generate a warning on some architectures

			pmops->uSource.pdValue = (double *)-1;
		    }

		    //- if linked to a mechanism value

		    else if (iSource != -1)
		    {
			//- get solved dependency

			double *pdSource = pheccer->vm.ppdMatsIndex[iSource];

			//- store solved external flux contribution

			pmops->uSource.pdValue = pdSource;
		    }
		    else
		    {
			pmops->uSource.pdValue = NULL;
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

		break;
	    }

	    default:
	    {
		HeccerError
		    (pheccer,
		     NULL,
		     "unknown mechanism operation (%i)",
		     piMop[0]);

		/// \note the best we can do is advance the pointer with one

		piMop = &piMop[1];

		break;
	    }
	    }
	}
    }

    //- check sanity of operator array

    if (piMop[0] != HECCER_MOP_FINISH)
    {
	HeccerError
	    (pheccer,
	     NULL,
	     "piMop[0] is %i, should be %i",
	     piMop[0],
	     HECCER_MOP_FINISH);

	/// \todo depending on options, bail out

	/// \todo set status : illegal mop hecc.
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Link mechanism operations.
///
/// \details HeccerMechanismIndex2Pointer() converts mat indices in
/// the mops to mat pointers.  HeccerMechanismPointer2Index() converts
/// mat pointers in the mops to mat indices.
/// 

int HeccerMechanismPointer2Index(struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    int *piMop = (int *)pheccer->vm.pvMops;

    double *pdMats = pheccer->vm.pdMats;

    //- loop over mechanism operators

    while (piMop[0] == HECCER_MOP_COMPARTMENT)
    {
	//- go to next operator

	piMop = &piMop[1];

#if (USE_ID_DISASSEM)

	//- go to next operator

	piMop = &piMop[1];

#endif

	//- get compartment mechanism data

	struct MatsCompartment *pmatsc
	    = (struct MatsCompartment *)pdMats;

	pdMats = (double *)&((struct MatsCompartment *)pdMats)[1];

	//- loop over mechanism operators

	while (piMop[0] > HECCER_MOP_COMPARTMENT_BARRIER)
	{
	    //- look at next mechanism

	    switch (piMop[0])
	    {
	    //- for aggregate current

	    case HECCER_MOP_AGGREGATECURRENT:
	    {
		//- go to next operator

		struct MopsAggregateCurrent *pmops = (struct MopsAggregateCurrent *)piMop;

		piMop = (int *)&pmops[1];

		break;
	    }

	    //- for a call out

	    case HECCER_MOP_CALLOUT:
	    {
		//- go to next operator

		piMop = &piMop[1];

		//- go to next type specific data

		struct MatsCallout * pcall = (struct MatsCallout *)pdMats;

		pdMats = (double *)&((struct MatsCallout *)pdMats)[1];

		break;
	    }

	    //- for a spring mass equation

	    case HECCER_MOP_SPRINGMASS:
	    {
		//- go to next operator

		struct MopsSpringMass *pmops = (struct MopsSpringMass *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsSpringMass *pmats = (struct MatsSpringMass *)pdMats;

		pdMats = (double *)&((struct MatsSpringMass *)pdMats)[1];

		/// \todo pmops->pdEvents is pointer to event list,
		/// must be serialized.

		break;
	    }

	    //- for a nernst operation with internal variable concentration

	    case HECCER_MOP_INTERNALNERNST:
	    {
		//- go to next operator

		struct MopsInternalNernst *pmops = (struct MopsInternalNernst *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsInternalNernst * pnernst = (struct MatsInternalNernst *)pdMats;

		pdMats = (double *)&((struct MatsInternalNernst *)pdMats)[1];

		//- get index of internal concentration

		double *pdInternal = pmops->uInternal.pdValue;

		if (pdInternal)
		{
		    //- get solved dependency

		    int iConcentration = pdInternal - pheccer->vm.pdMats;

		    //- store solved internal concentration

		    pmops->uInternal.iMat = iConcentration;
		}
		else
		{
		    pmops->uInternal.iMat = -1;
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

		double *pdReversalPotential = pmops->uReversalPotential.pdValue;

		if (pdReversalPotential)
		{
		    //- get solved dependency

		    int iNernst = pdReversalPotential - pheccer->vm.pdMats;

		    //- store solved nernst potential

		    pmops->uReversalPotential.iMat = iNernst;
		}
		else
		{
		    pmops->uReversalPotential.iMat = -1;
		}

		break;
	    }

	    //- to compute a channel's conductance

	    case HECCER_MOP_STORECHANNELCONDUCTANCE:
	    {
		//- go to next operator

		piMop = &piMop[1];

		//- store the current conductance

		struct MatsStoreChannelConductance * pmats = (struct MatsStoreChannelConductance *)pdMats;

		//- go to next type specific data

		pdMats = (double *)&pmats[1];

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

		struct MatsSingleGateConcept * pmats = (struct MatsSingleGateConcept *)pdMats;

		pdMats = (double *)&pmats[1];

		//- get possibly solved dependence

		double *pdMatsActivator = pmops->uState.pdValue;

		if (pdMatsActivator)
		{
		    //- get solved dependency

		    int iMatsActivator = pdMatsActivator - pheccer->vm.pdMats;

		    //- store solved dependency

		    pmops->uState.iMat = iMatsActivator;
		}
		else
		{
		    pmops->uState.iMat = -1;
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

	    //- compute current for single channel

	    case HECCER_MOP_STORESINGLECHANNELCURRENT:
	    {
		//- go to next operator

		struct MopsStoreSingleChannelCurrent *pmops = (struct MopsStoreSingleChannelCurrent *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsStoreSingleChannelCurrent * pmats = (struct MatsStoreSingleChannelCurrent *)pdMats;

		pdMats = (double *)&pmats[1];

		break;
	    }

	    //- compute exponential decay, mostly an ion concentration

	    case HECCER_MOP_EXPONENTIALDECAY:
	    {
		//- go to next operator

		struct MopsExponentialDecay *pmops = (struct MopsExponentialDecay *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsExponentialDecay * pmats = (struct MatsExponentialDecay *)pdMats;

		pdMats = (double *)&pmats[1];

		//- get possibly solved external flux contributions

		int i;

		for (i = 0 ; i < EXPONENTIALDECAY_CONTRIBUTORS ; i++)
		{
		    double *pdExternal = pmops->puExternal[i].pdValue;

		    if (pdExternal)
		    {
			int iOffset = 0;

			//- if individual channel currents are enabled

			if (pheccer->ho.iOptions & HECCER_OPTION_ENABLE_INDIVIDUAL_CURRENTS)
			{
			    //- there is a mat entry in between, subtract one from the index

			    iOffset = -1;
			}

			//- get solved dependency

			int iFlux = pdExternal - pheccer->vm.pdMats;

			//- store solved external flux contribution

			pmops->puExternal[i].iMat = iFlux;
		    }
		    else
		    {
			pmops->puExternal[i].iMat = -1;
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

		struct MatsFluxPool * pmats = (struct MatsFluxPool *)pdMats;

		pdMats = (double *)&pmats[1];

		break;
	    }

	    //- for an event generator

	    case HECCER_MOP_EVENTGENERATE:
	    {
		//- go to next operator

		struct MopsEventGenerate *pmops = (struct MopsEventGenerate *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsEventGenerate * pmats = (struct MatsEventGenerate *)pdMats;

		pdMats = (double *)&pmats[1];

		//- get source for comparison

/* 		int i; */

/* 		for (i = 0 ; i < EVENT_SOURCES ; i++) */
		{
		    double *pdSource = pmops->uSource.pdValue;

		    //- if should be current membrane potential

		    /// \note this will generate a warning on some architectures

		    if (pdSource == (double *)-1)
		    {
			//- set pointer value to a sentinel value

			pmops->uSource.iMat = INT_MAX;
		    }

		    //- if linked to a mechanism value

		    else if (pdSource)
		    {
			//- get solved dependency

			int iSource = pdSource - pheccer->vm.pdMats;

			//- store solved external flux contribution

			pmops->uSource.iMat = iSource;
		    }
		    else
		    {
			pmops->uSource.iMat = -1;
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

		break;
	    }

	    default:
	    {
		HeccerError
		    (pheccer,
		     NULL,
		     "unknown mechanism operation (%i)",
		     piMop[0]);

		/// \note the best we can do is advance the pointer with one

		piMop = &piMop[1];

		break;
	    }
	    }
	}
    }

    //- check sanity of operator array

    if (piMop[0] != HECCER_MOP_FINISH)
    {
	HeccerError
	    (pheccer,
	     NULL,
	     "piMop[0] is %i, should be %i",
	     piMop[0],
	     HECCER_MOP_FINISH);

	/// \todo depending on options, bail out

	/// \todo set status : illegal mop hecc.
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pcFilename filename to read.
/// \arg ppdValues values that have been read, NULL for failure.
/// 
/// \return int
/// 
///	Number of doubles read, -1 for failure.
/// 
///	ppdValues..: values that have been read, NULL for failure.
/// 
/// \brief Read a file with doubles, -1 terminated.
/// 

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
	fclose(pfile);

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

	    /// \note hardcoded indentation, 4 spaces required

	    if ((pc[0] == ' '
		 && pc[1] == ' '
		 && pc[2] == ' '
		 && pc[3] == ' '
		 && pc[4] == '-'
		 && pc[5] == ' '
		 && pc[6] != ' ')
		||
		(pc[0] == ' '
		 && pc[1] == ' '
		 && pc[2] == '-'
		 && pc[3] == ' '
		 && pc[4] != ' '))
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

    //- close

    fclose(pfile);

    //- return result

    iResult = iDoubles;

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Perform the mechanisms operators once.
/// 

int HeccerMechanismSolveCN(struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    int *piMop = (int *)pheccer->vm.pvMops;

    //- get access to compartment variables and results

    double *pdVm = &pheccer->vm.pdVms[0];

    double *pdMats = pheccer->vm.pdMats;

    double *pdResults = &pheccer->vm.pdResults[0];

    //- loop over mechanism operators

    while (piMop[0] == HECCER_MOP_COMPARTMENT)
    {
	//- go to next operator

	piMop = &piMop[1];

#if (USE_ID_DISASSEM)

	//- go to next operator

	piMop = &piMop[1];

#endif

	//- get compartment mechanism data

	struct MatsCompartment *pmatsc
	    = (struct MatsCompartment *)pdMats;

	pdMats = (double *)&((struct MatsCompartment *)pdMats)[1];

	//- get membrane potential

	double dVm = pdVm[0];

	//- initialize current with leak and injected

	double dCompartmentCurrents = pmatsc->dLeak + pmatsc->dInjected;

	//- initial total conductance is zero

	double dConductances = 0;

	//- single channel contribution is zero

	double dChannelConductance = 0.0;

	double dReversalPotential = 0.0;

	//- pointers to tables for the currently used membrane potential

	double dIntervalStep = ((pheccer->ho.dIntervalEnd - pheccer->ho.dIntervalStart) / pheccer->ho.iIntervalEntries);

	double *pdRearranged = NULL;

	//- loop over mechanism operators

	while (piMop[0] > HECCER_MOP_COMPARTMENT_BARRIER)
	{
	    //v single channel current (if applicable)

	    double dSingleChannelCurrent;

	    //- look at next mechanism

	    switch (piMop[0])
	    {
	    //- for aggregate current

	    case HECCER_MOP_AGGREGATECURRENT:
	    {
		//- go to next operator

		struct MopsAggregateCurrent *pmops = (struct MopsAggregateCurrent *)piMop;

		piMop = (int *)&pmops[1];

		pheccer->vm.pdAggregators[pmops->iIndex] += dSingleChannelCurrent;

		break;
	    }

	    //- for a nernst operation with internal variable concentration

	    case HECCER_MOP_INTERNALNERNST:
	    {
		//- go to next operator

		struct MopsInternalNernst *pmops = (struct MopsInternalNernst *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsInternalNernst * pnernst = (struct MatsInternalNernst *)pdMats;

		pdMats = (double *)&((struct MatsInternalNernst *)pdMats)[1];

		//- fetch variables

		double dExternal = pmops->dExternal;

		double dConstant = pmops->dConstant;

		double dInternal = 0.0;

		if (pmops->uInternal.pdValue)
		{
		    dInternal = *pmops->uInternal.pdValue;
		}

		//- computer nernst potential

		/// \todo produces invalid things if pdInternal is not set.

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

		struct MatsStoreChannelConductance * pmats = (struct MatsStoreChannelConductance *)pdMats;

		pmats->dChannelConductance = dChannelConductance;

		//- go to next type specific data

		pdMats = (double *)&pmats[1];

		break;
	    }

	    //- for a new membrane potential

	    case HECCER_MOP_LOADVOLTAGETABLE:
	    {
		//- go to next operator

		struct MopsVoltageTableDependency *pmops = (struct MopsVoltageTableDependency *)piMop;

		piMop = (int *)&pmops[1];

		double dState = dVm;

		//- discretize and offset the state

		int iIndex = (dState - pheccer->ho.dIntervalStart) / dIntervalStep;

		if (iIndex < 0)
		{
		    iIndex = 0;
		}
		else if (iIndex >= pheccer->ho.iIntervalEntries)
		{
		    iIndex = pheccer->ho.iIntervalEntries - 1;
		}

		//- initialize pointers to tables for this membrane potential

		pdRearranged = &pheccer->tgt.pdRearranged[iIndex * pheccer->tgt.iTabulatedGateCount * 2];

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

		dCompartmentCurrents += dChannelConductance * dReversalPotential;

		break;
	    }

	    //- compute current for single channel

	    case HECCER_MOP_STORESINGLECHANNELCURRENT:
	    {
		//- go to next operator

		struct MopsStoreSingleChannelCurrent *pmops = (struct MopsStoreSingleChannelCurrent *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsStoreSingleChannelCurrent * pmats = (struct MatsStoreSingleChannelCurrent *)pdMats;

		pdMats = (double *)&pmats[1];

		//- store the current, use appropriate indexing

		pmats->dConductance = dChannelConductance;
		pmats->dCurrent = dSingleChannelCurrent;

		break;
	    }

	    //- compute exponential decay, mostly an ion concentration

	    case HECCER_MOP_EXPONENTIALDECAY:
	    {
		//- go to next operator

		struct MopsExponentialDecay *pmops = (struct MopsExponentialDecay *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsExponentialDecay * pmats = (struct MatsExponentialDecay *)pdMats;

		pdMats = (double *)&pmats[1];

		double dBeta = pmops->dBeta;

		double dSteadyState = pmops->dSteadyState;

		double dTau = pmops->dTau;

		double dState = pmats->dState;

		//- fetch external contribution

		/// \note so after the channel mat comes the flux mat.  This
		/// \note is a hack ... which could be solved, by having an
		/// \note intermediary that linearizes and specifies
		/// \note _all_ the equations (so including fluxes).

		/// \todo In other words, the test 'if (pcac->iPool != -1)'
		/// \todo should be removed and the removal should be
		/// \todo counterbalanced by the neccessary specifications
		/// \todo for a flux in the intermediary.  Then, these
		/// \todo specifications are compiled to HECCER_MOP_FLUXPOOL
		/// \todo byte code.

		/// \todo needs a careful check again.

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

		struct MatsFluxPool * pmats = (struct MatsFluxPool *)pdMats;

		pdMats = (double *)&pmats[1];

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

		struct MatsEventGenerate * pmats = (struct MatsEventGenerate *)pdMats;

		pdMats = (double *)&pmats[1];

		//- if spiking

		if (pmats->dRefractory == DBL_MAX)
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

			    pmats->dRefractory = DBL_MAX;

			    pmats->dSpike = 1.0;

			    if (pmops->iTable != INT_MAX)
			    {
				//- generate event for associated targets

				int iResult = HeccerEventGenerate(pheccer, pmops->iTable);

				if (!iResult)
				{
				    HeccerError
					(pheccer,
					 NULL,
					 "spike generation failed at time (%g)",
					 pheccer->dTime);
				}
			    }
			    else
			    {
				// \note the presence of spikegen does
				// not necessarily mean that it must
				// have post-synaptic targets.  In the
				// future, if there is no spike
				// distributor, spikegens should be
				// optimized away, and may be a
				// spikegen must always have
				// post-synaptic targets if it exists.

/* 				HeccerError */
/* 				    (pheccer, */
/* 				     NULL, */
/* 				     "spike generation without a spike target at time (%g)", */
/* 				     pheccer->dTime); */
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

		/// \todo what if the user mixes this with active currents ?
		/// \todo this is ok for simple integrate and fire,
		/// \todo but for more complicated models I am not sure.

		pdVm[0] = dVmNew;

		break;
	    }

	    //- for a call out

	    case HECCER_MOP_CALLOUT:
	    {
		//- go to next operator

		piMop = &piMop[1];

		//- go to next type specific data

		struct MatsCallout * pcall = (struct MatsCallout *)pdMats;

		pdMats = (double *)&((struct MatsCallout *)pdMats)[1];

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

		dCompartmentCurrents += per->dCurrent;

		/// \todo check signaling

		break;
	    }

	    //- for a conceptual gate (HH alike, with powers)

	    case HECCER_MOP_CONCEPTGATE:
	    {
		//- go to next operator

		struct MopsSingleGateConcept *pmops = (struct MopsSingleGateConcept *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsSingleGateConcept * pmats = (struct MatsSingleGateConcept *)pdMats;

		pdMats = (double *)&pmats[1];

		//- get type specific constants and variables

		int iPower = pmops->iPower;

		double *pdState = pmops->uState.pdValue;

		double dA;
		double dB;

		int iInstantaneous = (iPower < 0);

		//- for a concentration dependent gate

		if (pdState)
		{
		    //- state is coming from a solved mechanism variable

		    double dState = *pdState;

		    //- fetch tables

		    int iTable = pmops->iTableIndex;

		    struct HeccerTabulatedGate *phtg = &pheccer->tgt.phtg[iTable];

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

		    //- fetch A and B gate rates

		    dA = phtg->pdA[iIndex];
		    dB = phtg->pdB[iIndex];

		    //- for non-instantaneous gates

		    if (!iInstantaneous)
		    {
			//- CN logic has not been applied yet, apply it here

			/// \todo move to channel rearrangements

			dB = 1.0 + pheccer->dStep / 2.0 * dB;

			dA = pheccer->dStep * dA;
		    }
		}

		//- else is a membrane potential dependent gate

		else
		{
		    //- fetch A and B gate rates

		    int iTable = pmops->iTableIndex;

		    dA = pdRearranged[iTable * 2];
		    dB = pdRearranged[iTable * 2 + 1];
		}

		//- start computing the new state based on the previous state

		double dActivation = pmats->dActivation;

		//- for instantaneous gates

		if (iInstantaneous)
		{
		    //- compute activation directly

		    dActivation = dA / dB;

		    iPower = -iPower;
		}

		//- else

		else
		{
		    //- compute gate activation state for the CN rule

		    dActivation = dA / dB + dActivation * 2.0 / dB - dActivation;
		}

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
		    HeccerError
			(pheccer,
			 NULL,
			 "invalid gate power (%i)",
			 iPower);

		    *(int *)0 = 0;
		}

		break;
	    }

	    //- for a spring mass equation

	    case HECCER_MOP_SPRINGMASS:
	    {
		//- go to next operator

		struct MopsSpringMass *pmops = (struct MopsSpringMass *)piMop;

		piMop = (int *)&pmops[1];

		//- go to next type specific data

		struct MatsSpringMass *pmats = (struct MatsSpringMass *)pdMats;

		pdMats = (double *)&((struct MatsSpringMass *)pdMats)[1];

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

			/// \note weight not normalized to the time step

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

			/// \note fixed weight of 1, normalized to the time step

			pmats->dX += phtsm->dX1;

			//- go to the next event

			/// \todo should be a variable ?

			pmops->iEvent++;
		    }
		}

		//- if there is an incoming event from the event distributor

		if (pmats->dNextEvent != -1.0
		    && pmats->dNextEvent < pheccer->dTime

		    /// \note target index for this object

		    && pmops->iDiscreteTarget != -1)
		{
		    //- translate incoming events to their activation

		    double dActivation = HeccerEventReceive(pheccer, pmops->iDiscreteTarget);

		    if (dActivation != DBL_MAX)
		    {
			//- add the activation of (possibly multiple) events to the channel activation

			pmats->dX += dActivation * phtsm->dX1;
		    }
		    else
		    {
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

	    default:
	    {
		HeccerError
		    (pheccer,
		     NULL,
		     "unknown mechanism operation (%i)",
		     piMop[0]);

		/// \note the best we can do is advance the pointer with one

		piMop = &piMop[1];

		break;
	    }
	    }
	}

	//- for single compartment neurons

	if (pheccer->vm.iVms == 1)
	{
	    //- compute the membrane potential right here

	    /// \todo differentiation needed between CN and BE ?

	    double dResult = ((dVm + dCompartmentCurrents * pmatsc->dCapacity)
			      / (dConductances * pmatsc->dCapacity + pmatsc->dDiagonal));

	    pdVm[0] = dResult + dResult - pdVm[0];
	}

	//- for multiple compartment neurons

	else
	{
	    //- compute results for the morphology matrix

	    //- right side

	    pdResults[0] = dVm + dCompartmentCurrents * pmatsc->dCapacity;

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
	HeccerError
	    (pheccer,
	     NULL,
	     "piMop[0] is %i, should be %i",
	     piMop[0],
	     HECCER_MOP_FINISH);

	/// \todo depending on options, bail out

	/// \todo set status : illegal mop hecc.
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Sort mechanisms according to different characteristics.
///
/// \details
/// 
///	Mechanisms are sorted using a regular quicksort.  A full order
///	is enforced by looking at the serial identification number in
///	the intermediary (as last resort for unordered mechanisms).
/// 
/// \note 
/// 
///	Compartment leak is a current, so it is considered to be a
///	mechanism.
/// 

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
	    /// \todo build array with mechanism references into the intermediary

	    /// \todo because of the structure of the intermediary, we do
	    /// \todo not need this, do we ?
	}
    }

    /// \todo qsort mechanisms per compartment

    /// \todo sort on Erev, see adaptive time step paper and hsolve implementation.

    //- return result

    return(iResult);
}


