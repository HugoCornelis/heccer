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


#ifndef COMPARTMENT_H
#define COMPARTMENT_H


#include "mathcomponent.h"


/*s compartment */

struct Compartment
{
    //m administrative overhead

    struct MathComponent mc;

    /*m index of parent compartment, -1 for none */

    int iParent;

    //m first mechanism

    struct MathComponent *pmcMechanisms;

    //m number of mechanisms

    int iMechanisms;

    //m descriptive values, alphabetical order

    double dCm;
    double dEm;
    double dIm;
    double dInitVm;
    double dInject;		
    double dRa;
    double dRm;
};


#endif


