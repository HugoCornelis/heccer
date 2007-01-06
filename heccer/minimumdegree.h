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


#ifndef HECCER_MINIMUM_DEGREE_H
#define HECCER_MINIMUM_DEGREE_H


#include <stdio.h>


struct Heccer;
struct MinimumDegree;


//s minimum degree indexing

struct MinimumDegree
{
    //m copy of ...

    int iEntries;

    //m structural analyzers

    int *piChildren;

    int **ppiChildren;

    //m unordered to flow

    int *piForward;

    //m flow to unordered

    int *piBackward;
};


//f prototypes

int HeccerMinimumDegree(struct Heccer *pheccer);

int
HeccerMinimumDegreeDump
(struct MinimumDegree *pmd, FILE *pfile, int iSelection);


#endif


