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


#include <stdlib.h>

#include "heccer/heccer.h"
#include "heccer/minimumdegree.h"



static
int
HeccerMDFlowEnumerator
(struct Heccer *pheccer, int iCurrent, int iTarget);

static
int
HeccerMDFlowEnumeratorB
(struct Heccer *pheccer, int iCurrent, int iTarget);

static
int
HeccerMDFlowEnumeratorL
(struct Heccer *pheccer, int iCurrent, int iTarget);

static int HeccerMDFindFlow(struct Heccer *pheccer, int iCompartments);


/// 
/// \arg pheccer a heccer.
/// \arg iCompartments number of compartments.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Find natural flow in the morphology.
/// 
/// \note 
/// 
///	This is assumed to follow reverse current flow for a passive
///	morphology, hence the name of the function.
/// 

/// driver : select and drive the enumerator
/// 
///	A small variant of hines, 1986.  Recursive function, typically
///	driven with something like HeccerMDFlowEnumerator(p, a, b),
///	where the a is the soma index and b is the number of
///	compartments.
/// 
/// \note 
/// 
///	This is a very specific implementation of more general minimum
///	degree algorithms, and is therefore suboptimal, afatiac.
/// 

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

    //- if branches first scheduling

    /// \todo note : leaves first does not work yet, do not use.

    if (1 || pheccer->ho.iOptions & HECCER_OPTION_BRANCHES_FIRST_SCHEDULING)
    {
	//- do a simple depth-first ordering

	return(HeccerMDFlowEnumeratorB(pheccer, iCurrent, iTarget));
    }

    //- else leaves first scheduling

    else
    {
	//- loop over children for current compartment

	int i;

	for (i = 0 ; i < pheccer->indexers.md.piChildren[iCurrent]; i++)
	{
	    //- get current child index

	    int iIndex = pheccer->indexers.md.ppiChildren[iCurrent][i];

	    //- only if this child has no children

	    if (pheccer->indexers.md.piChildren[iIndex] == 0)
	    {
		//- register schedule number for current compartment

		pheccer->indexers.md.piForward[iIndex] = iTarget;

		//- register reverse schedule number

		pheccer->indexers.md.piBackward[iTarget] = iIndex;

		//- decrement schedule number

		iTarget -= 1;
	    }
	}

	//- loop over children for current compartment

	for (i = 0 ; i < pheccer->indexers.md.piChildren[iCurrent]; i++)
	{
	    //- get current child index

	    int iIndex = pheccer->indexers.md.ppiChildren[iCurrent][i];

	    //- find reverse flow starting at this child

	    /// \note depth-first is the essence of branches first.

	    /// \note depth-first has two flavours : pre-order, post-order,
	    /// \note they are equivalent for this purpose, ie. for a heccer.

	    iTarget = HeccerMDFlowEnumeratorL(pheccer, iIndex, iTarget);
	}
    }

    //- no compartments : should return zero (recursively)

    /// \note check should be made by the driver of this routine

    return(iTarget);
}


/// worker : recursively schedule all compartments, branches first

static
int
HeccerMDFlowEnumeratorB
(struct Heccer *pheccer, int iCurrent, int iTarget)
{
    //- loop over children for current compartment

    int i;

    for (i = 0 ; i < pheccer->indexers.md.piChildren[iCurrent]; i++)
    {
	//- get current child index

	int iIndex = pheccer->indexers.md.ppiChildren[iCurrent][i];

	//- find reverse flow starting at this child

	/// \note depth-first is the essence of branches first.

	/// \note depth-first has two flavours : pre-order, post-order,
	/// \note they are equivalent for this purpose, ie. for a heccer.

	iTarget = HeccerMDFlowEnumerator(pheccer, iIndex, iTarget);
    }

    //- no compartments : should return zero (recursively)

    /// \note check should be made by the driver of this routine

    return(iTarget);
}


/// worker : recursively schedule all compartments, leaves first

static
int
HeccerMDFlowEnumeratorL
(struct Heccer *pheccer, int iCurrent, int iTarget)
{
    //- loop over children for current compartment

    int i;

    for (i = 0 ; i < pheccer->indexers.md.piChildren[iCurrent]; i++)
    {
	//- get current child index

	int iIndex = pheccer->indexers.md.ppiChildren[iCurrent][i];

	//- only if this child has no children

	if (pheccer->indexers.md.piChildren[iIndex] == 0)
	{
	    //- register schedule number for current compartment

	    pheccer->indexers.md.piForward[iIndex] = iTarget;

	    //- register reverse schedule number

	    pheccer->indexers.md.piBackward[iTarget] = iIndex;

	    //- decrement schedule number

	    iTarget -= 1;
	}
    }

    //- loop over children for current compartment

    for (i = 0 ; i < pheccer->indexers.md.piChildren[iCurrent]; i++)
    {
	//- get current child index

	int iIndex = pheccer->indexers.md.ppiChildren[iCurrent][i];

	//- find reverse flow starting at this child

	iTarget = HeccerMDFlowEnumerator(pheccer, iIndex, iTarget);
    }

    //- no compartments : should return zero (recursively)

    /// \note check should be made by the driver of this routine

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

    //- set pointers

    pmd->piForward = piForward;

    pmd->piBackward = piBackward;

    //- loop over compartments

    int i;

    int iStart;

    for (i = 0; i < iCompartments; i++)
    {
	//- if compartment has no parent

	if (pheccer->inter.pcomp[i].iParent == -1)
	{
	    //- this is a candidate to start the reverse flow

	    /// \note usually it will be the soma, but ok if it is a dendritic tip

	    iStart = i;
	}
    }

    //- schedule this compartment to be the last one solved

    int iTarget = iCompartments - 1;

    //- find reverse flow using the candidate as starting point

    int iEnd = HeccerMDFlowEnumerator(pheccer, iStart, iTarget);

    //- check if we ended with something reasonable (can only be -1, afaict)

    if (iEnd != -1)
    {
	/// \todo this can happen if the intermediary structure is wrong,
	/// \todo e.g. out of bound parent index or cycles

	/// \todo also happens for multiple segments without a parent

	/// \todo add something like HeccerError(number, message, varargs);

	/// \note segv

	*(int *)0 = 0;
    }

    //- set number of entries

    pmd->iEntries = iCompartments;

    //- return result

    return(piForward && piBackward);
}


/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Minimum degree enumeration for compartment matrix.
/// 

int HeccerMinimumDegree(struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    if (pheccer->inter.iCompartments == 0)
    {
	return(TRUE);
    }

    //- build structural indices

    iResult = iResult && HeccerMDStructuralyze(pheccer, pheccer->inter.iCompartments);

    //- do minimum degree

    /// \note this is assumed to follow reverse current flow for a passive
    /// \note morphology, hence the name of the function.

    iResult = iResult && HeccerMDFindFlow(pheccer, pheccer->inter.iCompartments);

/*     //- sort children according to flow */

/*     iResult = iResult && HeccerMDSortChildren(pheccer, pheccer->inter.iCompartments); */

    //- return result

    return(iResult);
}


/// 
/// \arg pmd minimum degree index.
/// \arg pfile stdio file.
/// \arg iSelection selection to dump.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Perform the compartment operators once.
/// 

int
HeccerMinimumDegreeDump
(struct MinimumDegree *pmd, FILE *pfile, int iSelection)
{
    //- set default result

    int iResult = TRUE;

    //- index of parent compartment, -1 for none

    if (iSelection & HECCER_DUMP_INDEXERS_SUMMARY)
    {
	fprintf(pfile, "MinimumDegree (iEntries) : (%i)\n", pmd->iEntries);
    }

    //- structural analyzers

    if (iSelection & HECCER_DUMP_INDEXERS_STRUCTURE)
    {
	int i;

	for (i = 0 ; i < pmd->iEntries ; i++)
	{
	    fprintf(pfile, "MinimumDegree (piChildren[%i]) : (%i)\n", i, pmd->piChildren[i]);

	    int j;

	    for (j = 0 ; j < pmd->piChildren[i] ; j++)
	    {
		fprintf(pfile, "MinimumDegree (piChildren[%i][%i]) : (%i)\n", i, j, pmd->ppiChildren[i][j]);
	    }
	}
    }

    //- unordered to flow

    if (iSelection & HECCER_DUMP_INDEXERS_STRUCTURE)
    {
	int i;

	for (i = 0 ; i < pmd->iEntries ; i++)
	{
	    fprintf(pfile, "MinimumDegree (piForward[%i]) : (%i)\n", i, pmd->piForward[i]);
	}
    }

    //- flow to unordered

    if (iSelection & HECCER_DUMP_INDEXERS_STRUCTURE)
    {
	int i;

	for (i = 0 ; i < pmd->iEntries ; i++)
	{
	    fprintf(pfile, "MinimumDegree (piBackward[%i]) : (%i)\n", i, pmd->piBackward[i]);
	}
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg iCompartments number of compartments.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Build structural indices.
/// 

int HeccerStructuralyze(struct Heccer *pheccer, int iCompartments)
{
    //- set default result : ok

    int iResult = TRUE;

    struct MinimumDegree *pmd = &pheccer->indexers.md;

    //- allocate structural analyzers

/*     int *piParents = (int *)calloc(iCompartments, sizeof(int)); */

    int *piChildren = (int *)calloc(iCompartments, sizeof(int));

    int **ppiChildren = (int **)calloc(iCompartments, sizeof(int *));

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
	    if (pcomp->iParent == i
		|| pcomp->iParent >= iCompartments)
	    {
		/// \todo HeccerError(number, message, varargs);

		HeccerError
		    (pheccer,
		     NULL,
		     "the compartment array does not describe a valid tree structure"
		     " at compartment (%i)\n",
		     i);
	    }

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


