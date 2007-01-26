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


#include <stdlib.h>

#include "heccer/compartment.h"
#include "heccer/intermediary.h"


/// **************************************************************************
///
/// SHORT: HeccerIntermediaryBuildIndex()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Index intermediary mechanism structures.
///
///	The index can afterwards be used for lookups, see
///	HeccerMechanismLookup().
///
/// **************************************************************************

int HeccerIntermediaryBuildIndex(struct Heccer *pheccer)
{
    //- set default result : success

    int iResult = TRUE;

    //- set default result : start of mechanisms

    struct MathComponent *pmc = (struct MathComponent *)pheccer->inter.pmc;

    //- allocate the index

    struct MathComponent **ppmcIndex
	= (struct MathComponent **)calloc(pheccer->inter.iMathComponents, sizeof(struct MathComponent *));

    if (!ppmcIndex)
    {
	return(FALSE);
    }

    pheccer->inter.ppmcIndex = ppmcIndex;

    //- loop over all mechanisms

    int i;

    for (i = 0 ; i < pheccer->inter.iMathComponents ; i++)
    {
	//- initialize the index

	ppmcIndex[i] = pmc;

	//- look at mechanism type

	int iType = pmc->iType;

	switch (iType)
	{
	    //- for a callout

	case MATH_TYPE_CallOut_conductance_current:
	{
	    //- get type specific data

	    struct Callout *pcall = (struct Callout *)pmc;

	    RETREIVE_MATH_COMPONENT(pmc,pcall,(struct Callout *));

	    break;
	}

	//- for an regular channel with activation and inactivation

	case MECHANISM_TYPE_ChannelActInact:
	{
	    //- get type specific data

	    struct ChannelActInact *pcai = (struct ChannelActInact *)pmc;

	    RETREIVE_MATH_COMPONENT(pmc,pcai,(struct ChannelActInact *));

	    break;
	}

	//- for a channel with a potential and a concentration dependence

	case MECHANISM_TYPE_ChannelActConc:
	{
	    //- get type specific data

	    struct ChannelActConc *pcac = (struct ChannelActConc *)pmc;

	    RETREIVE_MATH_COMPONENT(pmc,pcac,(struct ChannelActConc *));

	    break;
	}

	//- for an exponential decaying variable

	case MECHANISM_TYPE_ExponentialDecay:
	{
	    //- get type specific data

	    struct ExponentialDecay *pexdec = (struct ExponentialDecay *)pmc;

	    RETREIVE_MATH_COMPONENT(pmc,pexdec,(struct ExponentialDecay *));

	    break;
	}
	default:
	{
	    //t HeccerError(number, message, varargs);

	    fprintf
		(stderr,
		 "Heccer the hecc : unknown pmc->iType (%i)\n", iType);
	    break;
	}
	}
    }

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerIntermediaryDump()
///
/// ARGS.:
///
///	pinter.....: heccer intermediary.
///	pfile......: stdio file.
///	iSelection.: selection to dump.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Dump intermediary functions.
///
/// **************************************************************************

int
HeccerIntermediaryDump
(struct Intermediary *pinter, FILE *pfile, int iSelection)
{
    //- set default result : ok

    int iResult = TRUE;

    int iCompartments = pinter->iCompartments;

    //- number of compartments

    if (iSelection & HECCER_DUMP_INTERMEDIARY_SUMMARY)
    {
	fprintf(pfile, "Intermediary (iCompartments) : (%i)\n", iCompartments);
    }

    //- loop over compartment array

    struct Compartment *pcomp = pinter->pcomp;

    int i;

    for (i = 0 ; i < iCompartments ; i++)
    {
	//- dump compartment

	iResult = iResult && HeccerCompartmentDump(&pcomp[i], pfile, iSelection);
    }

    //t mechanisms

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerIntermediaryLookup()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	i.........: math component number to lookup.
///
/// RTN..: struct MathComponent *
///
///	math component structure, NULL for failure.
///
/// DESCR: Lookup the math component structure with the given number.
///
///	First call HeccerIntermediaryBuildIndex().
///
/// **************************************************************************

struct MathComponent *
HeccerIntermediaryLookup(struct Heccer *pheccer, int i)
{
    //- set default result : using the index

    struct MathComponent *pmcResult
	= pheccer->inter.ppmcIndex[i];

    //- return result

    return(pmcResult);
}


