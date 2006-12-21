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


#ifndef HECCER_COMPARTMENT_H
#define HECCER_COMPARTMENT_H


#include <stdio.h>

#include "heccer.h"
#include "mathcomponent.h"


/*s compartment */

struct Compartment
{
    //m administrative overhead

    struct MathComponent mc;

    //m index of parent compartment, -1 for none

    int iParent;

    //m first mechanism

    struct MathComponent *pmcMechanisms;

    //m number of mechanisms

    int iMechanisms;

    //m descriptive values, alphabetical order

    double dCm;
    double dEm;
    double dInitVm;
    double dInject;
    double dRa;
    double dRm;
};


//f prototypes

int HeccerCompartmentCompile(struct Heccer *pheccer);

int
HeccerCompartmentDump
(struct Compartment *pcomp, FILE *pfile, int iSelection);

int HeccerCompartmentInitiate(struct Heccer *pheccer);

int HeccerCompartmentSolveCN(struct Heccer *pheccer);


#endif


