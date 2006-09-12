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
/// SHORT: HeccerCompileCompartments()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Compile the intermediary of the compartments to byte code.
///
/// **************************************************************************

int HeccerCompartmentCompile(struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = FALSE;

    //v time step

    double dt;

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

    //v make minimum degree indices accessible

    int *piChildren = pheccer->indexers.md.piChildren;

    int **ppiChildren = pheccer->indexers.md.ppiChildren;

    int *piForward = pheccer->indexers.md.piForward;

    int *piBackward = pheccer->indexers.md.piBackward;

    //- create storage for diagterms

    double *pdDiagonals
	= (double *)calloc(pheccer->inter.iCompartments, sizeof(double));

    pheccer->vm.pdDiagonals = pdDiagonals;

    //- loop over all compartments (in flow order)

    int i;

    for (i = 0 ; i < pheccer->inter.iCompartments ; i++)
    {
	//- get intermediary number for the current compartment

	int iIntermediary = piBackward[i];

	//- get compartment parameters

	double dCm = pheccer->inter.pcomp[iIntermediary].dCm;

	double dRm = pheccer->inter.pcomp[iIntermediary].dRm;

	//- compute diagonal term : time constant

	pdDiagonals[i] = 1.0 + dt / (dCm * dRm);

#ifdef DEBUG_OPERATIONS_DIAGONALS

	fprintf(stdout, "pdDiagonals[%i] : %e\t= 1.0 + %e / (%e * %e)\n", i, pdDiagonals[i], dt, dCm, dRm);

#endif

	//- get compartment's parent number

	int iParent = pheccer->inter.pcomp[iIntermediary].iParent;

	//- get number of children of current compartment

	int iChildren = piChildren[iIntermediary];

	//- loop over all children

	int iChild;

	for (iChild = 0 ; iChild < iChildren ; iChild++)
	{
	    //- get index number for child of current compartment

	    int iModelNumber = ppiChildren[iIntermediary][iChild];

	    //- compute reverse contribution (genesis raxial)

	    //t check old hsolve code, this computation seems
	    //t contradictory to me, mixes up child and parent
	    //t properties. ...
	    //t ... ok, done, perhaps this is a bug in hsolve ?
	    //t have to check the computations carefully again.

	    double dReverse = -dt / (pheccer->inter.pcomp[iIntermediary].dCm * pheccer->inter.pcomp[iModelNumber].dRa);

	    pdDiagonals[i] -= dReverse;

#ifdef DEBUG_OPERATIONS_DIAGONALS

	    fprintf(stdout, "pdDiagonals[%i] : %e (- %e)\n", i, pdDiagonals[i], dReverse);

#endif

	    //- compute verse contribution, comes from child (genesis axial)

	    double dVerse = -dt / (pheccer->inter.pcomp[iModelNumber].dCm * pheccer->inter.pcomp[iModelNumber].dRa);

	    //- convert child compartment number to schedule number

	    int iScheduleNumber = piForward[iModelNumber];

	    pdDiagonals[iScheduleNumber] -= dVerse;

#ifdef DEBUG_OPERATIONS_DIAGONALS

	    fprintf(stdout,"pdDiagonals[%i] : %e (- %e)\n", iScheduleNumber, pdDiagonals[i], dVerse);

#endif
	}
    }

#define SETCOP1(array,current,operator) array ? array[current++] = operator : current++

#define SETCOP2(array,current,operator,operand) array ? ({array[current++] = operator; array[current++] = operand; }) : ({ current += 2; })

#define SETAXRES(array,current,value) array ? (array[current++] = value) : current++;

    //- first count, next compile the following block

    int iCountCompile;

    //- first counting by setting array to nil

    int *piCops = NULL;

    int iCops = 0;

    double *pdAxres = NULL;

    int iAxres = 0;

    for (iCountCompile = 0 ; iCountCompile < 2 ; iCountCompile++)
    {
	//v for leaves in the mid of the array, immediate skip to diagonal

	int iSkipped = 0;

	//- loop over all compartments : start forward elimination

	int i;

	for (i = 0 ; i < pheccer->inter.iCompartments ; i++)
	{
	    //- get intermediary number for the current compartment

	    int iIntermediary = piBackward[i];

	    //- get compartment capacity

	    double dCm = pheccer->inter.pcomp[iIntermediary].dCm;

	    //- get compartment's parent number

	    int iParent = pheccer->inter.pcomp[iIntermediary].iParent;

	    //- get number of children of current compartment

	    int iChildren = piChildren[iIntermediary];

	    //- if skipped previous compartment

	    if (iSkipped)
	    {
		//- can only occur once in a row, so next sets diagonal

		//t easy consistency check

		iSkipped = 0;
	    }

	    //- previous compartment has set diagonal

	    else
	    {
		//- if current compartment has children

		if (iChildren)
		{
		    //- skip first two compartments, other always set the diagonal

		    if (i > 1)
		    {
			SETCOP1(piCops, iCops, HECCER_COP_SET_DIAGONAL);
		    }
		}

		//- if no children for the current compartment

		else
		{
		    //- starting from the second compartment

		    if (i > 1)
		    {
			SETCOP1(piCops, iCops, HECCER_COP_SKIP_DIAGONAL);

			//- remember skipped to the diagonal for the next compartment

			iSkipped = 1;
		    }
		}
	    }

	    //- loop over all children

	    int j;

	    for (j = 0; j < iChildren; j++)
	    {
		//- get index number for child of current compartment

		int iModelNumber = ppiChildren[iIntermediary][j];

		//- convert to schedule number

		int iScheduleNumber = piForward[iModelNumber];

		SETCOP2(piCops, iCops, HECCER_COP_FORWARD_ELIMINATION, 2 * iScheduleNumber);

		//- compute reverse contribution (genesis raxial)

		//t check old hsolve code, this computation seems
		//t contradictory to me, mixes up child and parent
		//t properties. ...
		//t ... ok, done, perhaps this is a bug in hsolve ?
		//t have to check the computations carefully again.

		double dReverse = -dt / (pheccer->inter.pcomp[iIntermediary].dCm * pheccer->inter.pcomp[iModelNumber].dRa);

		SETAXRES(pdAxres, iAxres, dReverse);

		//- compute verse contribution, comes from child (genesis axial)

		double dVerse = -dt / (pheccer->inter.pcomp[iModelNumber].dCm * pheccer->inter.pcomp[iModelNumber].dRa);

		SETAXRES(pdAxres, iAxres, dVerse);
	    }
	}

	//- finishing forward elimination

	SETCOP1(piCops, iCops, HECCER_COP_FINISH);

	//- start backward substitution

	for (i = pheccer->inter.iCompartments - 2 ; i >= 0 ; i--)
	{
	    //- get intermediary number for the current compartment

	    int iIntermediary = piBackward[i];

	    //- get compartment capacity

	    double dCm = pheccer->inter.pcomp[iIntermediary].dCm;

	    //- get compartment's parent number

	    int iParent = pheccer->inter.pcomp[iIntermediary].iParent;

	    //- get number of children of current compartment

	    int iChildren = piChildren[iIntermediary];

	    //- convert to schedule number

	    int iScheduleNumber = piForward[iParent];

	    SETCOP2(piCops, iCops, HECCER_COP_BACKWARD_SUBSTITUTION, 2 * iScheduleNumber);

	    SETCOP1(piCops, iCops, HECCER_COP_CALC_RESULTS);

	    //- set axial resistance value for child

	    double dRa = pheccer->inter.pcomp[iIntermediary].dRa;

	    SETAXRES(pdAxres, iAxres, -dt / (dCm * dRa));
	}

	//- finish backward substitution

	SETCOP1(piCops, iCops, HECCER_COP_FINISH);

	//- if we were counting during the previous loop

	if (!pheccer->vm.piCops)
	{
	    //- prepare for compilation : allocate ->piCops and ->pdAxres, set counters

	    pheccer->vm.piCops
		= (int *)calloc(pheccer->vm.iCops, sizeof(int));

	    piCops = pheccer->vm.piCops;

	    pheccer->vm.iCops = iCops;

	    pheccer->vm.pdAxres
		= (double *)calloc(pheccer->vm.iAxres, sizeof(double));

	    pdAxres = pheccer->vm.pdAxres;

	    pheccer->vm.iAxres = iAxres;
	}
    }

    pheccer->vm.pdResults = (double *)calloc(2 * pheccer->inter.iCompartments, sizeof(double));

    pheccer->vm.pdVm = (double *)calloc(pheccer->inter.iCompartments, sizeof(double));

    //! the diagonal terms are also needed for solving the current
    //! equations, but I guess it is ok to deal with that in the
    //! mechanism compiler.  Check needed.

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerCompartmentDump()
///
/// ARGS.:
///
///	pcomp...: a compartment.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Perform the compartment operators once.
///
/// **************************************************************************

int HeccerCompartmentDump(struct Compartment *pcomp, FILE *pfile)
{
    //- set default result

    int iResult = TRUE;

    //- administrative overhead

    fprintf(pfile, "Compartment (mc.iSerial, mc.iType) : (%i, %i)\n", pcomp->mc.iSerial, pcomp->mc.iType);

    //- index of parent compartment, -1 for none

    fprintf(pfile, "Compartment (iParent) : (%i)\n", pcomp->iParent);

    //m number of mechanisms

    fprintf(pfile, "Compartment (iMechanisms) : (%i)\n", pcomp->iMechanisms);

    //m descriptive values, alphabetical order

    fprintf(pfile, "Compartment (dCm) : (%f)\n", pcomp->dCm);

    fprintf(pfile, "Compartment (dEm) : (%f)\n", pcomp->dEm);

    fprintf(pfile, "Compartment (dInitVm) : (%f)\n", pcomp->dInitVm);

    fprintf(pfile, "Compartment (dInject) : (%f)\n", pcomp->dInject);

    fprintf(pfile, "Compartment (dRa) : (%f)\n", pcomp->dRa);

    fprintf(pfile, "Compartment (dRm) : (%f)\n", pcomp->dRm);

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerCompartmentSolveCN()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Perform the compartment operators once.
///
/// **************************************************************************

int HeccerCompartmentSolveCN(struct Heccer *pheccer)
{
    int *piCops=pheccer->vm.piCops;
    int iCop;

    double *pdAxres = pheccer->vm.pdAxres;
    double *pdResult;
    double *pdResults = pheccer->vm.pdResults;
    double *pdVm = &pheccer->vm.pdVm[pheccer->inter.iCompartments - 1];
    double dDiagonal;
    double dResult;

    iCop = *piCops++;

    //- for one compartment

    if (iCop == HECCER_COP_FINISH)
    {
	//- compute result

        dResult = pdResults[0] / pdResults[1];
        pdVm[0] = dResult + dResult - pdVm[0];

	//- return success

        return(TRUE);
    }
    else
    {
        //- start forward elimination at row 1

        pdResult = &pdResults[2];
        dResult = pdResult[0];
        dDiagonal = pdResult[1];
    }

    while (1)
    {
        if (iCop == HECCER_COP_FORWARD_ELIMINATION)
	{
            double d = *pdAxres++ / pdResults[piCops[1]];
	    dDiagonal -= *pdAxres++ * d;
	    dResult -= pdResults[piCops[0]] * d;
	    piCops++;
        }
	else if (iCop == HECCER_COP_SET_DIAGONAL)
	{
	    *pdResult ++= dResult;
	    *pdResult ++= dDiagonal;
	    dResult = *pdResult;
	    dDiagonal = pdResult[1];
        }
	else if (iCop == HECCER_COP_SKIP_DIAGONAL)
	{
	    pdResult[0] = dResult;
	    pdResult++;
	    pdResult[0] = dDiagonal;
	    pdResult += 3;
	    dResult = pdResult[0];
	    dDiagonal = pdResult[1];
	}
	else
	{
            break;
        }

        iCop = piCops[0];
	piCops++;
    }

    /* store result last row */

    dResult = dResult / dDiagonal;

    pdVm[0] = dResult + dResult - pdVm[0];

    pdResult[0] = dResult;

    pdResult -= 2;

    dResult = pdResult[0];

    //- backwards elimination

    while (1)
    {
        iCop = piCops[0];
	piCops++;

        if (iCop == HECCER_COP_BACKWARD_SUBSTITUTION)
	{
	    dResult -= *pdAxres++ * pdResults[piCops[0]];
	    piCops++;
        }
	else if (iCop == HECCER_COP_CALC_RESULTS)
	{
	    pdVm--;

            dResult = dResult / pdResult[1];
	    pdVm[0] = dResult + dResult - pdVm[0];

	    pdResult[0] = dResult;
            pdResult -= 2;

	    dResult = pdResult[0];
	}
	else
	{
            break;
	}
    }

    //- return success

    return(TRUE);
}


