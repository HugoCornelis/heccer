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

#include "compartment.h"
#include "heccer.h"


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

    //- loop over all mechanisms

    int i;

    for (i = 0 ; i < pheccer->inter.iMechanisms ; i++)
    {
	//t add to operators for this mechanism, depending on previous
	//t mechanism, same for operands.
    }

    //- for backward euler integration

    if (pheccer->iOptions & HECCER_OPTION_BACKWARD_EULER)
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

	//- loop over all compartments

	for (i = 0 ; i < pheccer->inter.iCompartments ; i++)
	{
	    //- fill in compartment operation

#define	SETMOP_COMPARTMENT(piMops,iMops,operator) ((piMops) ? ((piMops)[(iMops)++] = (operator)) : (iMops)++)

	    SETMOP_COMPARTMENT((int *)pvMops, iMops, HECCER_MOP_COMPARTMENT);

	    //- get intermediary number for the current compartment

	    int iIntermediary = pheccer->indexers.md.piBackward[i];

	    //- retreive are constants

	    double dCm = pheccer->inter.pcomp[iIntermediary].dCm;

	    double dEm = pheccer->inter.pcomp[iIntermediary].dEm;

	    double dInject = pheccer->inter.pcomp[iIntermediary].dInject;

	    double dRm = pheccer->inter.pcomp[iIntermediary].dRm;

	    //- fill in compartment constants

	    //t these need an extra check, probably wrong.

	    //t perhaps need to split SETMAT_COMPARTMENT in SETMAT_COMPARTMENT_START
	    //t and SETMAT_COMPARTMENT_FINISH
	    //t between those two, we compile in the mechanisms.

/* #define	SETMAT_COMPARTMENT(pdMats,iMats,dLR,dI,dCR,dDL) ((pdMats) ? ({(pdMats)[(iMats)++] = dLR ; (pdMats)[(iMats)++] = dI ; (pdMats)[(iMats)++] = dCR ; (pdMats)[(iMats)++] = dDL ; }) : ((iMats) += 4)) */

/* 	    SETMAT_COMPARTMENT((double *)pvMats, iMats, dEm / dRm, dInject, dt / dCm, pheccer->vm.pdDiagonals[iIntermediary]); */

	    struct MatsCompartment *pmatsc = (struct MatsCompartment *)pvMats;

	    if (pmatsc)
	    {
		pmatsc->dLeak = dEm / dRm;
		pmatsc->dInjected = dInject;
		pmatsc->dCapacity = dt / dCm;

		//! note : pdDiagonals was computed with schedule numbers.
		//! perhaps it is better to change that for consistency
		//! reasons overhere, and to avoid confusion.

		pmatsc->dDiagonal = pheccer->vm.pdDiagonals[i];

		pvMats = (void *)&((struct MatsCompartment *)pvMats)[1];
	    }
	    else
	    {
		//! align to 8

		iMats += (((sizeof(struct MatsCompartment) - 1) >> 3) + 1) << 3;
	    }

	    //- loop over mechanisms for this compartment

	    int iMechanism;

	    struct MathComponent *pmc = (struct MathComponent *)pheccer->inter.pvMechanism;

	    for (iMechanism = 0 ; iMechanism < pheccer->inter.iMechanisms ; iMechanism++)
	    {
		//- look at mechanism type

		int iType = pmc->iType;

		switch (iType)
		{
		case MATH_TYPE_CallOut_conductance_current:
		{
#define	SETMOP_CALLOUT(piMops,iMops,operator) ((piMops) ? ((piMops)[(iMops)++] = (operator)) : (iMops)++)

		    SETMOP_CALLOUT((int *)pvMops, iMops, HECCER_MOP_CALLOUT);

		    //- get type specific data

		    struct MatsCallout *pcall = (struct MatsCallout *)pvMats;

		    if (pcall)
		    {
			//- fill in the pointer to the intermediary

			pcall->pco = (struct Callout *)pmc;

			//- go to next type specific data

#ifndef HECCER_SIZED_MATH_STRUCTURES

			pmc = (struct MathComponent *)&((struct Callout *)pmc)[1];

#endif

			pvMats = (void *)&((struct MatsCallout *)pvMats)[1];
		    }
		    else
		    {
			//! align to 8

			iMats += (((sizeof(struct MatsCallout) - 1) >> 3) + 1) << 3;
		    }
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

#ifdef HECCER_SIZED_MATH_STRUCTURES

		//- go to next mechanism data

		pmc = (struct MathComponent *)&(((char *)pmc)[pmc->iSize]);

#endif
	    }
	}

	//- finish all operations

#define	SETMOP_FINISH(piMops,iMops) ((piMops) ? ((piMops)[(iMops)++] = (HECCER_MOP_FINISH)) : (iMops)++)

	SETMOP_FINISH((int *)pvMops, iMops);

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

    //t build array with mechanism references into the intermediary

    //t qsort mechanisms

    //- return result

    return(iResult);
}


