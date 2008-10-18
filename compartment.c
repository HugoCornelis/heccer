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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heccer/compartment.h"
#include "heccer/heccer.h"


/// 
/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Compile the intermediary of the compartments to byte code.
/// \details 
/// 

int HeccerCompartmentCompile(struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    //v time step

    double dt;

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

    //v make minimum degree indices accessible

    int *piChildren = pheccer->indexers.md.piChildren;

    int **ppiChildren = pheccer->indexers.md.ppiChildren;

    int *piForward = pheccer->indexers.md.piForward;

    int *piBackward = pheccer->indexers.md.piBackward;

    //- create storage for diagterms

    pheccer->vm.iDiagonals = pheccer->inter.iCompartments;

    double *pdDiagonals = (double *)calloc(pheccer->vm.iDiagonals, sizeof(double));

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

	    /// \todo check old hsolve code, this computation seems
	    /// \todo contradictory to me, mixes up child and parent
	    /// \todo properties. ...
	    /// \todo ... ok, done, perhaps this is a bug in hsolve ?
	    /// \todo have to check the computations carefully again.

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

#define SETCOP1(array,current,operator) ((array) ? (array)[(current)++] = (operator) : (current)++)

#define SETCOP2(array,current,operator,operand) ((array) ? ({(array)[(current)++] = (operator); (array)[(current)++] = (operand); }) : ({ (current) += 2; }))

#define SETAXRES(array,current,value) ((array) ? ((array)[(current)++] = (value)) : (current)++)

    //- first count, next compile the following block

    int iCountCompile;

    //- first counting by setting array to NULL

    int *piCops = NULL;

    double *pdAxres = NULL;

    for (iCountCompile = 0 ; iCountCompile < 2 ; iCountCompile++)
    {
	//- counters always start at zero

	int iCops = 0;

	int iAxres = 0;

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

		/// \todo easy consistency check

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
			SETCOP1(piCops, iCops, HECCER_COP_NEXT_ROW);

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

		/// \todo check old hsolve code, this computation seems
		/// \todo contradictory to me, mixes up child and parent
		/// \todo properties. ...
		/// \todo ... ok, done, perhaps this is a bug in hsolve ?
		/// \todo have to check the computations carefully again.

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

	    SETCOP1(piCops, iCops, HECCER_COP_FINISH_ROW);

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
		= (int *)calloc(iCops, sizeof(int));

	    piCops = pheccer->vm.piCops;

	    pheccer->vm.iCops = iCops;

	    pheccer->vm.pdAxres
		= (double *)calloc(iAxres, sizeof(double));

	    pdAxres = pheccer->vm.pdAxres;

	    pheccer->vm.iAxres = iAxres;
	}
    }

    pheccer->vm.iResults = 2 * pheccer->inter.iCompartments;

    pheccer->vm.pdResults = (double *)calloc(pheccer->vm.iResults, sizeof(double));

    pheccer->vm.iVms = pheccer->inter.iCompartments;

    pheccer->vm.pdVms = (double *)calloc(pheccer->vm.iVms, sizeof(double));

    pheccer->vm.iCompartments = pheccer->inter.iCompartments;

    /// \note the diagonal terms are also needed for solving the current
    /// \note equations, but I guess it is ok to deal with that in the
    /// \note mechanism compiler.  Check needed.

    //- return result

    return(iResult);
}


/// 
/// 
/// \arg pcomp a compartment.
/// \arg pfile stdio file.
/// \arg iSelection selection to dump.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Dump compartment parameters to the given stream.
/// \details 
/// 

int
HeccerCompartmentDump
(struct Compartment *pcomp, FILE *pfile, int iSelection)
{
    //- set default result

    int iResult = TRUE;

    //- administrative overhead

    /// \note this makes testing quite hard, needs careful thought

/*     if (iSelection & HECCER_DUMP_INTERMEDIARY_STRUCTURE) */
/*     { */
#ifdef lkjlkslkjasdf

HECCER_SOURCE_NEUROSPACES

    fprintf(pfile, "Compartment (mc.iSerial, mc.iType) : (%i, %i)\n", pcomp->mc.iSerial, pcomp->mc.iType);

#else

    fprintf(pfile, "Compartment (mc.iType) : (%i)\n", pcomp->mc.iType);

#endif
/*     } */

    //- index of parent compartment, -1 for none

    if (iSelection & HECCER_DUMP_INTERMEDIARY_STRUCTURE)
    {
	fprintf(pfile, "Compartment (iParent) : (%i)\n", pcomp->iParent);
    }

/*     /// number of mechanisms */

/*     if (iSelection & HECCER_DUMP_INTERMEDIARY_STRUCTURE) */
/*     { */
/* 	fprintf(pfile, "Compartment (iMechanisms) : (%i)\n", pcomp->iMechanisms); */
/*     } */

    /// descriptive values, alphabetical order

    if (iSelection & HECCER_DUMP_INTERMEDIARY_COMPARTMENTS_PARAMETERS)
    {
	fprintf(pfile, "Compartment (dCm) : (%g)\n", pcomp->dCm);

	fprintf(pfile, "Compartment (dEm) : (%g)\n", pcomp->dEm);

	fprintf(pfile, "Compartment (dInitVm) : (%g)\n", pcomp->dInitVm);

	fprintf(pfile, "Compartment (dInject) : (%g)\n", pcomp->dInject);

	fprintf(pfile, "Compartment (dRa) : (%g)\n", pcomp->dRa);

	fprintf(pfile, "Compartment (dRm) : (%g)\n", pcomp->dRm);
    }

    //- return result

    return(iResult);
}


/// 
/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Fill the compartment arrays with initial values.
/// \details 
/// 

int HeccerCompartmentInitiate(struct Heccer *pheccer)
{
    //- set default result

    int iResult = TRUE;

    //- loop over all compartments

    int i;

    for (i = 0 ; i < pheccer->inter.iCompartments ; i++)
    {
	//- get schedule number

	int iSchedule = pheccer->indexers.md.piForward[i];

	//- fill in initial membrane potential

	/// \note if I use initial vm of zero, I get NaN for vm ?

	pheccer->vm.pdVms[iSchedule] = pheccer->inter.pcomp[i].dInitVm;

	/// \todo fill in precomputed values for channels

    }    

    //- return result

    return(iResult);
}


/// 
/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Perform the compartment operators once.
/// \details 
/// 

int HeccerCompartmentSolveCN(struct Heccer *pheccer)
{
    int *piCops = &pheccer->vm.piCops[0];
    int iCop;

    double *pdAxres = &pheccer->vm.pdAxres[0];
    double *pdResults = &pheccer->vm.pdResults[0];
    double *pdResult = &pdResults[2];
    double *pdVms = &pheccer->vm.pdVms[pheccer->vm.iCompartments];
    double dDiagonal = pdResult[1];
    double dResult = pdResult[0];

    //- start forward elimination at row 1

    int iDone = FALSE;

    while (!iDone)
    {
	iCop = piCops[0];
	piCops++;

        if (iCop == HECCER_COP_FORWARD_ELIMINATION)
	{
	    /// \note pdResults[piCops[0] + 1] contains other diagonal term

            double d = pdAxres[0] / pdResults[piCops[0] + 1];
	    dDiagonal -= pdAxres[1] * d;
	    pdAxres += 2;
	    dResult -= pdResults[piCops[0]] * d;
	    piCops++;
        }
	else if (iCop == HECCER_COP_SET_DIAGONAL)
	{
	    //- store right side

	    pdResult[0] = dResult;

	    //- store left side

	    pdResult[1] = dDiagonal;

	    //- next row

	    pdResult += 2;
	    dResult = pdResult[0];
	    dDiagonal = pdResult[1];
        }
	else if (iCop == HECCER_COP_NEXT_ROW)
	{
	    //- store right side

	    pdResult[0] = dResult;

	    //- store left side

	    pdResult[1] = dDiagonal;

	    //- skip zero coefficients

	    pdResult += 2;

	    //- next row

	    pdResult += 2;
	    dResult = pdResult[0];
	    dDiagonal = pdResult[1];
	}
	else
	{
	    iDone = TRUE;
        }
    }

    //- last row done separately

    /// \todo should try to incorporate this in the next loop
    /// \todo I have the feeling the loop is coded in the wrong way.

/*     SOLVE_ROW(dResult, dResult / dDiagonal); */

    dResult = dResult / dDiagonal;

    //- explicit forwards step for last row

/*     COMPUTE_VM(pdVms, dResult); */

    pdVms--;
    pdVms[0] = dResult + dResult - pdVms[0];

/*     REGISTER_ROW_RIGHT(pdResult[0], dResult); */

    pdResult[0] = dResult;
    pdResult -= 2;

    //- start new right side

/*     INITIATE_ROW(dResult, pdResult[0]); */

    dResult = pdResult[0];

    //- backwards elimination

    iDone = FALSE;

    while (!iDone)
    {
	//- load the operation

        iCop = piCops[0];
	piCops++;

        if (iCop == HECCER_COP_BACKWARD_SUBSTITUTION)
	{
	    //- fill in the off diagonal contribution

/* 	    OFF_DIAGONAL_CONTRIBUTION(dResult, pdAxres[0], pdResults, piCops[0]); */

	    dResult -= pdAxres[0] * pdResults[piCops[0]];
	    pdAxres++;
	    piCops++;
        }
	else if (iCop == HECCER_COP_FINISH_ROW)
	{
	    //- solve the matrix row

	    /// \note pdResult[1] contains the diagonal

/* 	    SOLVE_ROW(dResult, dResult / pdResult[1]); */

            dResult = dResult / pdResult[1];

	    //- explicit forward step to get the membrane potential

/* 	    COMPUTE_VM(pdVms, dResult); */

	    pdVms--;
	    pdVms[0] = dResult + dResult - pdVms[0];

/* 	    REGISTER_ROW_RIGHT(pdResult[0], dResult); */

	    pdResult[0] = dResult;
            pdResult -= 2;

	    //- start new right side

/* 	    INITIATE_ROW(dResult, pdResult[0]); */

	    dResult = pdResult[0];
	}
	else
	{
	    iDone = TRUE;
	}
    }

    //- return success

    return(TRUE);
}


