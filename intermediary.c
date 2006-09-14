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


#include "compartment.h"
#include "intermediary.h"


/// **************************************************************************
///
/// SHORT: HeccerIntermediaryDump()
///
/// ARGS.:
///
///	pinter.: heccer intermediary.
///	pfile..: stdio file.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Dump intermediary functions.
///
/// **************************************************************************

int HeccerIntermediaryDump(struct Intermediary *pinter, FILE *pfile)
{
    //- set default result : ok

    int iResult = TRUE;

    int iCompartments = pinter->iCompartments;

    //- number of compartments

    fprintf(pfile, "Intermediary (iCompartments) : (%i)\n", iCompartments);

    //- loop over compartment array

    //! should be using C++ iterators, should look into it

    struct Compartment *pcomp = pinter->pcomp;

    int i;

    for (i = 0 ; i < iCompartments ; i++)
    {
	//- dump compartment

	iResult = iResult && HeccerCompartmentDump(&pcomp[i], pfile);
    }

    //t mechanisms

    //- return result

    return(iResult);
}


