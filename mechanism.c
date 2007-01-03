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

    //v time step

    double dt;

    //- initialize number of operators and operands

    int iMops = pheccer->inter.iCompartments * sizeof(int);

    //! Em/Rm
    //! injected current
    //! dt/cm
    //! diagonal
    //!
    //! injected current needs a separate entry for interfacing.

    int iMats = pheccer->inter.iCompartments * 4 * sizeof(double);

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

	//- loop over all compartments via their schedule number

	int iSchedule;

	for (iSchedule = 0 ; iSchedule < pheccer->inter.iCompartments ; iSchedule++)
	{
	    //- fill in compartment operation

	    SETMOP_COMPARTMENT(pvMops, iMops);

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

	    //t these need an extra check, probably wrong.

	    //t perhaps need to split SETMAT_COMPARTMENT in SETMAT_COMPARTMENT_START
	    //t and SETMAT_COMPARTMENT_FINISH
	    //t between those two, we compile in the mechanisms.

	    SETMAT_COMPARTMENT(pvMats, iMats, dEm / dRm, dInject, dt / dCm, pheccer->vm.pdDiagonals[iSchedule]);

	    //- loop over mechanisms for this compartment

	    struct MathComponent *pmc = (struct MathComponent *)pheccer->inter.pvMechanism;

	    int iMechanism;

	    int iStart = iIntermediary == 0 ? 0 : pheccer->inter.piC2m[iIntermediary - 1];

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

		    SETMOP_CALLOUT(pvMops, iMops);

		    SETMAT_CALLOUT(pvMats, iMats, (struct Callout *)pmc);

		    break;
		}

		//- for an regular channel with activation and inactivation

		case MECHANISM_TYPE_ChannelActInact:
		{
		    //- get type specific data

		    struct ChannelActInact *pcai = (struct ChannelActInact *)pmc;

		    SETMOP_INITIALIZECHANNEL(pvMops, iMops, pcai->dMaximalConductance, pcai->dReversalPotential);

		    //- tabulate the channel

		    //- tabulate activation, Genesis X
		    //- create forward table, Genesis A, alpha, create backward table, Genesis B, alpha + beta

		    int iTabulatedActivation
			= HeccerDiscretizeGateConcept(pheccer, &pcai->pgcActivation.gc);

		    SETMOP_LOADVOLTAGETABLE(pvMops, iMops);

		    SETMOP_POWEREDGATECONCEPT(pvMops, iMops, pcai->pgcActivation.gc.iTable, pcai->pgcActivation.iPower);

		    SETMAT_POWEREDGATECONCEPT(pvMats, iMats, 0);

		    //- tabulate inactivation, Genesis Y
		    //- create forward table, Genesis A, alpha, create backward table, Genesis B, alpha + beta

		    int iTabulatedInactivation
			= HeccerDiscretizeGateConcept(pheccer, &pcai->pgcInactivation.gc);

		    SETMOP_POWEREDGATECONCEPT(pvMops, iMops, pcai->pgcInactivation.gc.iTable, pcai->pgcInactivation.iPower);

		    SETMAT_POWEREDGATECONCEPT(pvMats, iMats, 0);

		    SETMOP_UPDATECOMPARTMENTCURRENT(pvMops, iMops);

		    //t retabulate cannot be done yet, do not know yet how many tables

		    //- register result from tabulation for outcome of this function

		    iResult = iResult && iTabulatedActivation && iTabulatedInactivation;

		    break;
		}
		default:
		{
		    //t HeccerError(number, message, varargs);

		    fprintf
			(stderr,
			 "Heccer the hecc : unknown pvMat->iType (%i)\n", iType);
		    break;
		}
		}

/* #ifdef HECCER_SIZED_MATH_STRUCTURES */

/* 		//- go to next mechanism data */

/* 		pmc = (struct MathComponent *)&(((char *)pmc)[pmc->iSize]); */

/* #endif */
	    }
	}

	//- sanity : is next compartment's mechanism invalid ?

	if (pheccer->inter.piC2m[iSchedule] != -1)
	{
	    fprintf
		(stderr,
		 "Heccer the hecc : mechanisms found after last compartment's mechanism\n");
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
	}
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

	    //- for a new membrane potential

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

		double dActivation = pmats->dActivation;

		//- fetch tables

		//t table rearrangements

		struct HeccerTabulatedGate *phtg = &pheccer->tgt.phtg[iTable];

		double *pdForward = phtg->pdForward;
		double *pdBackward = phtg->pdBackward;

		//- discretize and offset membrane potential

		//t move this to load membrane potential
		//t need LOADVOLTAGETABLE or LOADVOLTAGEINDEX

		int iVm = (dVm - phtg->hi.dStart) / phtg->hi.dStep;

		if (iVm < 0)
		{
		    iVm = 0;
		}
		else if (iVm >= phtg->iEntries)
		{
		    iVm = phtg->iEntries - 1;
		}

		//- fetch forward and backward gate rates

		double dForward = pdForward[iVm];
		double dBackward = pdBackward[iVm];

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

		//- add to current

		break;
	    }

	    //- add channel contributions to compartmental currents

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


