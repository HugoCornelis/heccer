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

    //! always one needed to finish

    iMops = 1;

    void *pvMats = NULL;

    iMats = 0;

    for (iCountCompile = 0 ; iCountCompile < 2 ; iCountCompile++)
    {
	//- loop over all compartments

	iMops = 0;

	iMats = 0;

	for (i = 0 ; i < pheccer->inter.iCompartments ; i++)
	{
	    //- fill in compartment operation

#define HECCER_MOP_COMPARTMENT 1

#define	SETMOP_COMPARTMENT(piMops,iMops,operator) ((piMops) ? ((piMops)[(iMops)++] = (operator)) : (iMops)++)

	    SETMOP_COMPARTMENT((int *)pvMops, iMops, HECCER_MOP_COMPARTMENT);

	    //- get intermediary number for the current compartment

	    int iIntermediary = pheccer->indexers.md.piBackward[i];

	    //- retreive are constants

	    double dCm = pheccer->inter.pcomp[iIntermediary].dCm;

	    double dEm = pheccer->inter.pcomp[iIntermediary].dEm;

	    double dInject = pheccer->inter.pcomp[iIntermediary].dInject;

	    double dRm = pheccer->inter.pcomp[iIntermediary].dRm;

	    //- fill in constants

	    //t these need an extra check, probably wrong.

	    //t need to split SETMAT_COMPARTMENT in SETMAT_COMPARTMENT_START and SETMAT_COMPARTMENT_FINISH
	    //t between those two, we compile in the mechanisms.

#define	SETMAT_COMPARTMENT(pdMats,iMats,dLR,dI,dCR,dDL) ((pdMats) ? ({(pdMats)[(iMats)++] = dLR ; (pdMats)[(iMats)++] = dI ; (pdMats)[(iMats)++] = dCR ; (pdMats)[(iMats)++] = dDL ; }) : ((iMats) += 4))

	    SETMAT_COMPARTMENT((double *)pvMats, iMats, dEm / dRm, dInject, dt / dCm, pheccer->vm.pdDiagonals[iIntermediary]);
	}

	//- if we were counting during the previous loop

	if (!pheccer->vm.pvMops)
	{
	    //- prepare for compilation : allocate ->pvMops and ->pvMats, set counters

	    pheccer->vm.pvMops = (void *)calloc(pheccer->vm.iMops, 1);

	    pvMops = pheccer->vm.pvMops;

	    pheccer->vm.iMops = iMops;

	    pheccer->vm.pvMats = (void *)calloc(pheccer->vm.iMats, 1);

	    pvMats = pheccer->vm.pvMats;

	    pheccer->vm.iMats = iMats;
	}
    }

    //- finish all operations

#define HECCER_MOP_FINISH 2

#define	SETMOP_FINISH(piMops,iMops) ((piMops) ? ((piMops)[(iMops)++] = (HECCER_MOP_FINISH)) : (iMops)++)

    SETMOP_FINISH((int *)pvMops, iMops);

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

    double *pdMats = (double *)pvMats;

    double *pdResults = &pheccer->vm.pdResults[0];

    //- loop over mechanism operators

    while (piMop[0] == HECCER_MOP_COMPARTMENT)
    {
	//- go to next operator

	piMop = &piMop[1];

	//- get membrane potential

	double dVm = pdVm[0];

	//t mechanisms could go here (preferred cause it groups the
	//t mechanism data for the leak).

	//- initialize current with leak and injected

	double dCurrent = pdMats[0] + pdMats[1];

	pvMats = (void *)&pdMats[2];

	//- initial total conductance is zero

	double dConductances = 0;

	//t mechanisms could go here

	//- compute results for the morphology matrix

	if (pheccer->vm.iVms == 1)
	{
	    //t the hines solver made a difference here between single
	    //t compartment neurons and multi compartment neurons.  For
	    //t efficiency reasons, this makes good sense.  Should do the
	    //t same here, yet differentiation needed between CN and BE ?

	    double dResult = (dVm + dConductances * pdMats[0]) / (dConductances * pdMats[0] + pdMats[1]);

	    pdVm[0] = dResult + dResult - pdVm[0];
	}
	else
	{
	    pdResults[0] = dVm + dConductances * pdMats[0];

	    pdResults++;

	    pdResults[0] = dConductances * pdMats[0] + pdMats[1];

	    pdResults++;
	}

	//- go to next compartment

	pvMats = (void *)&pdMats[2];

	pdVm++;
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


