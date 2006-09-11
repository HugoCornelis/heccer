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


#include <stdlib.h>

#include "heccer.h"
#include "minimumdegree.h"


//f static prototypes

static
int
HeccerMDFlowEnumerator
(struct Heccer *pheccer, int iCurrent, int iTarget);

static int HeccerMDFindFlow(struct Heccer *pheccer, int iCompartments);

static int HeccerMDInitialize(struct Heccer *pheccer, int iCompartments);

static int HeccerMDStructuralyze(struct Heccer *pheccer, int iCompartments);


/// **************************************************************************
///
/// SHORT: HeccerMDFindFlow()
///
/// ARGS.:
///
///	heccer........: a heccer.
///	iCompartments.: number of compartments.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Find natural flow in the morphology.
///
/// NOTE.:
///
///	This is assumed to follow reverse current flow for a passive
///	morphology, hence the name of the function.
///
/// **************************************************************************

/// worker : recursively schedule all compartments

static
int
HeccerMDFlowEnumerator
(struct Heccer *pheccer, int iCurrent, int iTarget)
{
    //- register schedule number for current compartment

    pheccer->indexers.md.piForward[iCurrent] = iTarget;

    //- register reverse schedule number

    pheccer->indexers.md.piBackward[iTarget] = iCurrent;

    //- decrement schedule number

    iTarget -= 1;

    //- loop over children for current compartment

    int i;

    for (i = 0 ; i < pheccer->indexers.md.piChildren[iCurrent]; i++)
    {
	//- get current child index

	int iIndex = pheccer->indexers.md.ppiChildren[iCurrent][i];

	//- if child has itself no children

	if (pheccer->indexers.md.piChildren[iIndex] == 0)
	{
	    //- register schedule number for this child

	    pheccer->indexers.md.piForward[iIndex] = iTarget;

	    //- register reverse schedule number

	    pheccer->indexers.md.piBackward[iTarget] = iIndex;

	    //- decrement schedule number

	    return(iTarget - 1);
	}

	//- else child has children

	else
	{
	    //- if logical branch scheduling

	    if (pheccer->iOptions & HECCER_OPTION_LOGICAL_BRANCH_SCHEDULING)
	    {
		//- find reverse flow starting at this child

		return(HeccerMDFlowEnumerator(pheccer, iIndex, iTarget));
	    }
	}
    }

    //- if leave to root scheduling

    if (!(pheccer->iOptions & HECCER_OPTION_LOGICAL_BRANCH_SCHEDULING))
    {
	//- loop over children for current compartment

	for (i = 0 ; i < pheccer->indexers.md.piChildren[iCurrent]; i++)
	{
	    //- get current child index

	    int iIndex = pheccer->indexers.md.ppiChildren[iCurrent][i];

	    //- find reverse flow starting at this child

	    return(HeccerMDFlowEnumerator(pheccer, iIndex, iTarget));
	}
    }

    //- no compartments : must return zero (recursively)

    //! check should be made by the driver of this routine

    return(iTarget);
}


/// driver : initialize and drive the enumerator

static int HeccerMDFindFlow(struct Heccer *pheccer, int iCompartments)
{
    //- set default result : ok

    int iResult = TRUE;

    struct MinimumDegree *pmd = &pheccer->indexers.md;

    //- allocate unordered to flow

    int *piForward = (int *)calloc(iCompartments, sizeof(int));

    //- allocate flow to unordered

    int *piBackward = (int *)calloc(iCompartments, sizeof(int));

    //- loop over compartments

    int i;

    int iStart;

    for (i = 0; i < iCompartments; i++)
    {
	//- if compartment has no parent

	if (pheccer->inter.pcomp[i].iParent == -1)
	{
	    //- this is a candidate to start the reverse flow

	    //! usually it will be the soma, but ok if it is a dendritic tip

	    iStart = i;
	}
    }

    //- schedule this compartment to be the last one solved

    int iTarget = iCompartments - 1;

    //- find reverse flow using the candidate as starting point

    int iEnd = HeccerMDFlowEnumerator(pheccer, iStart, iTarget);

    //- check if we ended with something reasonable (can only be 0, afaict)

    if (iEnd != 0)
    {
	//! segv

	*(int *)0 = 0;
    }

    //- set pointers

    pmd->piForward = piForward;

    pmd->piBackward = piBackward;

    //- return result

    return(piForward && piBackward);
}


/// **************************************************************************
///
/// SHORT: HeccerMDInitialize()
///
/// ARGS.:
///
///	heccer........: a heccer.
///	iCompartments.: number of compartments.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Initialize minimum degree indexing arrays.
///
/// **************************************************************************

static int HeccerMDInitialize(struct Heccer *pheccer, int iCompartments)
{
    //- set default result : ok

    int iResult = TRUE;

    struct MinimumDegree *pmd = &pheccer->indexers.md;

    //- allocate structural analyzers

/*     int *piParents = (int *)calloc(iCompartments, sizeof(int)); */

    int *piChildren = (int *)calloc(iCompartments, sizeof(int));

    int **ppiChildren = (int **)calloc(iCompartments, sizeof(int));

    //- allocate unordered to minimum

    int *piForward = (int *)calloc(iCompartments, sizeof(int));

    //- allocate minimum to unordered

    int *piBackward = (int *)calloc(iCompartments, sizeof(int));

    //- set pointers

/*     pmd->piParents = piParents; */

    pmd->piChildren = piChildren;

    pmd->ppiChildren = ppiChildren;

    pmd->piForward = piForward;

    pmd->piBackward = piBackward;

    //- return result

    return(/* piParents &&  */piChildren && ppiChildren && piForward && piBackward);
}


/// **************************************************************************
///
/// SHORT: HeccerMDStructuralyze()
///
/// ARGS.:
///
///	heccer........: a heccer.
///	iCompartments.: number of compartments.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Build structural indices.
///
/// **************************************************************************

static int HeccerMDStructuralyze(struct Heccer *pheccer, int iCompartments)
{
    //- set default result : ok

    int iResult = TRUE;

    struct MinimumDegree *pmd = &pheccer->indexers.md;

    //- allocate structural analyzers

/*     int *piParents = (int *)calloc(iCompartments, sizeof(int)); */

    int *piChildren = (int *)calloc(iCompartments, sizeof(int));

    int **ppiChildren = (int **)calloc(iCompartments, sizeof(int));

    //- analyze

    //- loop over all compartments

    int i;

    for (i = 0; i < iCompartments; i++)
    {
	//- set current compartment

	struct Compartment *pcomp = &pheccer->inter.pcomp[i];

/* 	//- set default : current compartment has no parent */

/* 	piParents[i] = -1; */

	//- if compartment has parent

	if (pcomp->iParent != -1)
	{
/* 	    //- register parent compartment index */

/* 	    piParents[i] = pcomp->iParent; */

	    //- increment number of children for the parent compartment

	    piChildren[pcomp->iParent] += 1;
	}
    }

    //- build indices for children

    //- i loop over all compartments

    for (i = 0; i < iCompartments; i++)
    {
	//- clear number of children for this compartment

	int iChildren = 0;

	//- if compartment has no children

	if (piChildren[i] == 0)
	{
	    //- it's a terminal branch

	    ppiChildren[i] = NULL;
	}

	//- else

	else
	{
	    //- allocate for number of children

	    ppiChildren[i] = (int *)calloc(piChildren[i], sizeof(int));

	    //- j loop over all compartments

	    int j;

	    for (j = 0; j < iCompartments; j++)
	    {
		//- if parent of j compartment is i compartment

		if (pheccer->inter.pcomp[j].iParent == i)
		{
		    //- remember j as a children of i

		    ppiChildren[i][iChildren] = j;

		    //- increment number of children

		    iChildren++;
		}
	    }
	}
    }
	
    //- set pointers

/*     pmd->piParents = piParents; */

    pmd->piChildren = piChildren;

    pmd->ppiChildren = ppiChildren;

    //- return result

    return(/* piParents &&  */piChildren && ppiChildren);
}


/// **************************************************************************
///
/// SHORT: HeccerMinimumDegree()
///
/// ARGS.:
///
///	heccer...: a heccer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Minimum degree enumeration for compartment matrix.
///
///	A small variant of hines, 1986.  Recursive function, typically
///	called with something like minimum_degree(heccer, -1, 0),
///	where the -1 is the soma.
///
/// NOTE.:
///
///	This is a very specific implementation of more general minimum
///	degree algorithms, and is therefore suboptimal.
///
/// **************************************************************************

int HeccerMinimumDegree (struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    if (pheccer->inter.iCompartments == 0
	|| pheccer->inter.iCompartments == 1)
    {
	return(TRUE);
    }

/*     //- initialize minimum degree indexing arrays */

/*     iResult = iResult && HeccerMDInitialize(pheccer, pheccer->inter.iCompartments); */

    //- build structural indices

    iResult = iResult && HeccerMDStructuralyze(pheccer, pheccer->inter.iCompartments);

    //- do minimum degree

    //! this is assumed to follow reverse current flow for a passive
    //! morphology, hence the name of the function.

    iResult = iResult && HeccerMDFindFlow(pheccer, pheccer->inter.iCompartments);

/*     //- sort children according to flow */

/*     iResult = iResult && HeccerMDSortChildren(pheccer, pheccer->inter.iCompartments); */

    //- return result

    return(iResult);
}


