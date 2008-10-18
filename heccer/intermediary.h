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


#ifndef HECCER_INTERMEDIARY_H
#define HECCER_INTERMEDIARY_H


#include <stdio.h>


struct Intermediary;
struct MechanismIndex;


#include "compartment.h"
#include "mechanism.h"


#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif


/// \struct heccer main structure

struct Intermediary
{
    /// compartment array

    int iCompartments;

    struct Compartment *pcomp;

    /// all other mathematical components

    struct MathComponentArray *pmca;

    /// compartment 2 first mechanism number

    int *piC2m;

#ifdef HECCER_SOURCE_NEUROSPACES

    /// identification of the originator, mostly a cell or cell
    /// population, but perhaps just a segment vector

    /// start range

    int iSerialStart;

    /// end range

    int iSerialEnd;

#endif

};



int HeccerIntermediaryBuildIndex(struct Heccer *pheccer);

int
HeccerIntermediaryDump
(struct Intermediary *pinter, FILE *pfile, int iSelection);

struct MathComponent *
HeccerIntermediaryLookup(struct Heccer *pheccer, int i);


#endif


