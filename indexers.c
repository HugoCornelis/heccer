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


#include "heccer/indexers.h"


/// 
/// 
/// \arg pindexers heccer indexers.
/// \arg pfile stdio file.
/// \arg iSelection selection to dump.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Dump intermediary functions.
/// \details 
/// 

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


