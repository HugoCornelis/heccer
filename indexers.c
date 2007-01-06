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


#include "heccer/indexers.h"


/// **************************************************************************
///
/// SHORT: HeccerIndexersDump()
///
/// ARGS.:
///
///	pindexers..: heccer indexers.
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
HeccerIndexersDump
(struct Indexers *pindexers, FILE *pfile, int iSelection)
{
    //- set default result : ok

    int iResult = TRUE;

    //- dump minimum degree structures

    iResult = iResult && HeccerMinimumDegreeDump(&pindexers->md, pfile, iSelection);

    //- return result

    return(iResult);
}


