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


#include "indexers.h"


/// **************************************************************************
///
/// SHORT: HeccerIndexersDump()
///
/// ARGS.:
///
///	pindexers.: heccer indexers.
///	pfile.....: stdio file.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Dump intermediary functions.
///
/// **************************************************************************

int HeccerIndexersDump(struct Indexers *pindexers, FILE *pfile)
{
    //- set default result : ok

    int iResult = TRUE;

    //- dump minimum degree structures

    iResult = iResult && HeccerMinimumDegreeDump(&pindexers->md, pfile);

    //- return result

    return(iResult);
}


