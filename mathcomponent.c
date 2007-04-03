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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heccer/mathcomponent.h"
#include "heccer/mechanism.h"


static struct MathComponentInfo pmci[] =
{
    MATH_TYPE_ChannelAct,		((char *)&((struct ChannelAct *)0)[1]) - ((char *)&((struct ChannelAct *)0)[0]),
    MATH_TYPE_ChannelActConc,		((char *)&((struct ChannelActConc *)0)[1]) - ((char *)&((struct ChannelActConc *)0)[0]),
    MATH_TYPE_ChannelActInact,		((char *)&((struct ChannelActInact *)0)[1]) - ((char *)&((struct ChannelActInact *)0)[0]),
    MATH_TYPE_ChannelPersistentSteadyStateDualTau,	((char *)&((struct ChannelPersistentSteadyStateDualTau *)0)[1]) - ((char *)&((struct ChannelPersistentSteadyStateDualTau *)0)[0]),
    MATH_TYPE_ChannelPersistentSteadyStateTau,	((char *)&((struct ChannelPersistentSteadyStateTau *)0)[1]) - ((char *)&((struct ChannelPersistentSteadyStateTau *)0)[0]),
    MATH_TYPE_ChannelSpringMass,	((char *)&((struct ChannelSpringMass *)0)[1]) - ((char *)&((struct ChannelSpringMass *)0)[0]),
    MATH_TYPE_ChannelSteadyStateSteppedTau,	((char *)&((struct ChannelSteadyStateSteppedTau *)0)[1]) - ((char *)&((struct ChannelSteadyStateSteppedTau *)0)[0]),
    MATH_TYPE_ExponentialDecay,		((char *)&((struct ExponentialDecay *)0)[1]) - ((char *)&((struct ExponentialDecay *)0)[0]),
    MATH_TYPE_InternalNernst,		((char *)&((struct InternalNernst *)0)[1]) - ((char *)&((struct InternalNernst *)0)[0]),
    -1,	-1,
};


/// **************************************************************************
///
/// SHORT: MathComponentArrayCallocData()
///
/// ARGS.:
///
///	pmca...: math component array.
///	iTypes.: set of math component types to allocate for.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Allocate the math component data for the given set of types.
///
///	As a side effect, sets the number of expected math components
///	to the number of types, and the cursor to zero.  After this,
///	fill the array by calling for each math component
///	MathComponentArraySetAdvance().
///
/// **************************************************************************

int MathComponentArrayCallocData(struct MathComponentArray *pmca, int *piTypes)
{
    //- set default result : not ok

    int iResult = 0;

    //- compute size

    int iSize = 0;

    int i;

    for (i = 0 ; piTypes[i] > 0 ; i++)
    {
	//- lookup the type int the size table

	struct MathComponentInfo *pmci = MathComponentInfoLookup(piTypes[i]);

	if (!pmci)
	{
	    return(0);
	}

	//- increment size to allocate

	int iChars = pmci->iChars;

	iSize += iChars;
    }

    //- if we need to allocate something

    if (iSize)
    {
	//- allocate memory

	pmca->pmc = (struct MathComponent *)calloc(iSize, sizeof(char));

	//- set cursor for filling the mathcomponent array

	pmca->iCursor = 0;

	pmca->pmcCursor = pmca->pmc;

	//- set the number of math components

	pmca->iMathComponents = i;

	//- clear out the index

	pmca->ppmcIndex = NULL;
    }

    //- return result : ok

    return(1);
}


#ifdef HECCER_SOURCE_NEUROSPACES

/// **************************************************************************
///
/// SHORT: MathComponentArrayLookupSerial()
///
/// ARGS.:
///
///	pmca....: math component array.
///	iSerial.: serial to search.
///
/// RTN..: int
///
///	index of matching math component, -1 for not found.
///
/// DESCR: Look up a math component by serial.
///
/// **************************************************************************

int
MathComponentArrayLookupSerial
(struct MathComponentArray *pmca, int iSerial)
{
    //- set default result : not found

    int iResult = -1;

    //- loop over all mathcomponents

    struct MathComponent * pmc = pmca->pmc;

    int iMathComponent;

    for (iMathComponent = 0 ; iMathComponent < pmca->iMathComponents ; iMathComponent++)
    {
	//- if serials match

	if (pmc->iSerial == iSerial)
	{
	    //- set result : current index

	    iResult = iMathComponent;

	    //- break searching loop

	    break;
	}

	//- advance to the next math component

	pmc = MathComponentNext(pmc);
    }

    //- return result

    return(iResult);
}

#endif


/// **************************************************************************
///
/// SHORT: MathComponentArraySetAdvance()
///
/// ARGS.:
///
///	pmca...: math component array.
///	pmc....: math component to add.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Add math component at current cursor position, advance.
///
/// NOTE.:
///
///	There is no protection for overflows by checking the cursor
///	with the number of math components.
///
/// **************************************************************************

int
MathComponentArraySetAdvance
(struct MathComponentArray *pmca, struct MathComponent *pmc)
{
    //- set default result : failure

    int iResult = 0;

    //- determine size to copy

    int iType = pmc->iType;

    struct MathComponentInfo *pmci = MathComponentInfoLookup(iType);

    if (!pmci)
    {
	return(0);
    }

    int iChars = pmci->iChars;

    //- copy the math component to the current cursor position

    memcpy(pmca->pmcCursor, pmc, iChars);

    //- advance the cursor

    pmca->iCursor++;

    pmca->pmcCursor = (struct MathComponent *)&((char *)pmca->pmcCursor)[iChars];

    //- return result

    return(1);
}


/// **************************************************************************
///
/// SHORT: MathComponentCopyNext()
///
/// ARGS.:
///
///	pmcTarget.: math component target.
///	pmcSource.: math component source.
///
/// RTN..: struct MathComponent *
///
///	Next math component in the array, NULL for failure.
///
/// DESCR: Copy a math component, advance to the next math component.
///
///	The original content of pmcTarget is completely ignored and
///	overwritten.
///
/// TODO:
///
///	This need an additional helper function that takes an ///
///	non-linear array of math components and linearizes them in
///	memory.
///
/// **************************************************************************

struct MathComponent *
MathComponentCopyNext
(struct MathComponent *pmcTarget, struct MathComponent *pmcSource)
{
    //- set default result : failure

    struct MathComponent *pmcResult = NULL;

    //- determine size to copy

    int iType = pmcSource->iType;

    struct MathComponentInfo *pmci = MathComponentInfoLookup(iType);

    if (!pmci)
    {
	return(NULL);
    }

    int iChars = pmci->iChars;

    //- copy the math component to the current cursor position

    memcpy(pmcTarget, pmcSource, iChars);

    //- set result

    pmcResult = MathComponentNext(pmcTarget);

    //- return result

    return(pmcResult);
}


/// **************************************************************************
///
/// SHORT: MathComponentInfoLookup()
///
/// ARGS.:
///
///	iType.: math component type.
///
/// RTN..: struct MathComponentInfo *
///
///	Math component info, respecting compilation options.
///
/// DESCR: Lookup math component type, respecting compilation options.
///
/// NOTE.:
///
///	This function is for the purpose of constructing
///	intermediaries from C level.  The info returned depends on
///	compilation options.  See the test code for an example of its
///	use.
///
/// **************************************************************************

struct MathComponentInfo * MathComponentInfoLookup(int iType)
{
    //- set default result : failure

    struct MathComponentInfo *pmciResult = NULL;

    //- loop & search

    int j;

    for (j = 0 ; pmci[j].iType > 0 ; j++)
    {
	//- if found, set result

	if (pmci[j].iType == iType)
	{
	    pmciResult = &pmci[j];

	    break;
	}
    }

    //- return result

    return pmciResult;
}


/// **************************************************************************
///
/// SHORT: MathComponentNext()
///
/// ARGS.:
///
///	pmc....: math component in the array.
///
/// RTN..: struct MathComponent *
///
///	Next math component, NULL for failure.
///
/// DESCR: Access a math component, and lookup the next component.
///
/// NOTE.:
///
///	There is no protection for overflows by checking the cursor
///	with the number of math components.
///
/// **************************************************************************

struct MathComponent * MathComponentNext(struct MathComponent *pmc)
{
    //- set default result : next math component

    //- determine size

    int iType = pmc->iType;

    struct MathComponentInfo *pmci = MathComponentInfoLookup(iType);

    if (!pmci)
    {
	return(0);
    }

    int iChars = pmci->iChars;

    struct MathComponent *pmcResult
	= (struct MathComponent *)&((char *)pmc)[iChars];

    //- return result

    return(pmcResult);
}


