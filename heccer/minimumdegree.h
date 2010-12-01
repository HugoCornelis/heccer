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


#ifndef HECCER_MINIMUM_DEGREE_H
#define HECCER_MINIMUM_DEGREE_H


#include <stdio.h>


struct simobj_Heccer;
struct MinimumDegree;


/// \struct minimum degree indexing

struct MinimumDegree
{
    /// copy of ...

    int iEntries;

    /// structural analyzers

    int *piChildren;

    int **ppiChildren;

    /// unordered to flow

    int *piForward;

    /// flow to unordered

    int *piBackward;
};



int HeccerMinimumDegree(struct simobj_Heccer *pheccer);

int
HeccerMinimumDegreeDump
(struct MinimumDegree *pmd, FILE *pfile, int iSelection);


#endif


