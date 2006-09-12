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


//s all indexing structures

struct Indexers
{
    //m minimum degree

    struct MinimumDegree md;

    //t need a couple of things for channel reordering

};


//f prototypes

int HeccerIndexersDump(struct Indexers *pindexers, FILE *pfile);


#endif


