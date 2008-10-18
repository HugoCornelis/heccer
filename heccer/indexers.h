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


#ifndef HECCER_INDEXERS_H
#define HECCER_INDEXERS_H


#include <stdio.h>


struct Indexers;


#include "minimumdegree.h"


#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif


/// \struct all indexing structures

struct Indexers
{
    /// minimum degree

    struct MinimumDegree md;

    /// \todo need a couple of things for channel reordering

};



int
HeccerIndexersDump
(struct Indexers *pindexers, FILE *pfile, int iSelection);


#endif


