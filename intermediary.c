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


#include "heccer/compartment.h"
#include "heccer/intermediary.h"


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


