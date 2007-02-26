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


struct sizes
{
    int iType;

    int iChars;
};


struct sizes ssMathComponentSizes[] =
{
    MATH_TYPE_ChannelActConc,		((char *)&((struct ChannelActConc *)0)[1]) - ((char *)&((struct ChannelActConc *)0)[0]),
    MATH_TYPE_ChannelActInact,		((char *)&((struct ChannelActInact *)0)[1]) - ((char *)&((struct ChannelActInact *)0)[0]),
    MATH_TYPE_ExponentialDecay,		((char *)&((struct ExponentialDecay *)0)[1]) - ((char *)&((struct ExponentialDecay *)0)[0]),
    -1,	-1,
};


static int lookup(int iType)
{
    int iResult = 0;

    int j;

    for (j = 0 ; ssMathComponentSizes[j].iType > 0 ; j++)
    {
	if (ssMathComponentSizes[j].iType == iType)
	{
	    iResult = ssMathComponentSizes[j].iChars;

	    break;
	}
    }

    return iResult;
}


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

	int iChars = lookup(iTypes[i]);

	if (iChars <= 0)
	{
	    return(0);
	}

	//- increment size to allocate

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

    int iChars = lookup(iType);

    if (iChars <= 0)
    {
	return(0);
    }

    //- copy the math component to the current cursor position

    memcpy(pmca->pmcCursor, pmc, iChars);

    //- advance the cursor

    pmca->iCursor++;

    pmca->pmcCursor = (struct MathComponent *)&((char *)pmca->pmcCursor)[iChars];

    //- return result

    return(1);
}


