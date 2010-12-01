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


#ifndef HECCER_COMPARTMENT_H
#define HECCER_COMPARTMENT_H


#include <stdio.h>

#include "heccer.h"
#include "mathcomponent.h"


/* \struct compartment */

struct Compartment
{
    /// administrative overhead

    struct MathComponent mc;

    /// index of parent compartment, -1 for none

    int iParent;

/*     /// first mechanism */

/*     struct MathComponent *pmcMechanisms; */

/*     /// number of mechanisms */

/*     int iMechanisms; */

    /// descriptive values, alphabetical order

    double dCm;
    double dEm;
    double dInitVm;
    double dInject;
    double dRa;
    double dRm;

#ifdef USE_ENABLE_LINEAR_MODE

    double dLength;

    double dDia;

#endif
};



int HeccerCompartmentCompile(struct simobj_Heccer *pheccer);

int
HeccerCompartmentDump
(struct Compartment *pcomp, FILE *pfile, int iSelection);

int HeccerCompartmentInitiate(struct simobj_Heccer *pheccer);

int HeccerCompartmentSolveCN(struct simobj_Heccer *pheccer);


#endif


