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


//s heccer main structure

struct Intermediary
{
    //m compartment array

    int iCompartments;

    struct Compartment *pcomp;

    //m number of mechanisms

    int iMechanisms;

    //m mechanism data

    void * pvMechanism;

    //m compartment 2 first mechanism number

    int *piC2m;
};


//f prototypes

int
HeccerIntermediaryDump
(struct Intermediary *pinter, FILE *pfile, int iSelection);


#endif


