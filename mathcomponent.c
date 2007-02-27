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
    MATH_TYPE_ChannelActConc,		((char *)&((struct ChannelActConc *)0)[2]) - ((char *)&((struct ChannelActConc *)0)[0]),
    MATH_TYPE_ChannelActInact,		((char *)&((struct ChannelActInact *)0)[2]) - ((char *)&((struct ChannelActInact *)0)[0]),
    MATH_TYPE_ExponentialDecay,		((char *)&((struct ExponentialDecay *)0)[2]) - ((char *)&((struct ExponentialDecay *)0)[0]),
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

int MathComponentArrayCallocData(struct MathComponentArray *pmca, int *iTypes)
{
    //- set default result : not ok

    int iResult = 0;

    //- compute size

    int iSize = 0;

    int i;

    for (i = 0 ; iTypes[i] > 0 ; i++)
    {
	//- lookup the type int the size table

	struct MathComponentInfo *pmci = MathComponentInfoLookup(iTypes[i]);

	if (!pmci)
	{
	    return(0);
	}

	//- increment size to allocate

	int iChars = pmci->iChars;

	iSize += iChars;
    }

    //- allocate memory

    pmca->pmc = (struct MathComponent *)calloc(iSize, sizeof(char));

    //- set cursor for filling the mathcomponent array

    pmca->iCursor = 0;

    pmca->pmcCursor = pmca->pmc;

    //- set the number of math components

    pmca->iMathComponents = i;

    //- clear out the index

    pmca->ppmcIndex = NULL;

    //- return result : ok

    return(1);
}


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

    //- determine size to copy

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


