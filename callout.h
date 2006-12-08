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


#ifndef CALLOUT_H
#define CALLOUT_H


#include "mathcomponent.h"


//s internal results, computed by heccer byte code

struct InternalResults
{
    //m membrane potential for this compartment

    double dVm;

    //! other potentially interesting things may follow: total
    //! currents per channel, etc.
};


//s external results, computed by an external function

struct ExternalResults
{
    //m external conductance, this is just an example

    double dConductance;
};


//f external function

struct Callout;

typedef 
int ExternalFunction
(struct Callout *pco, struct InternalResults *pir, struct ExternalResults *per);


//s call out intermediary

//! prefix all the intermediary struct's with something common, for
//! readability.

struct Callout
{
    //m administration overhead

    struct MathComponent mc;

    //m internal results

    struct InternalResults *pir;

    //m external results

    struct ExternalResults *per;

    //m external function

    ExternalFunction *pef;

    //! descriptive values can follow here

    //! and if convenient, internal and external results can follow thereafter
};


//f prototypes

int HeccerMechanismCompile(struct Heccer *pheccer);

int HeccerMechanismSolveCN(struct Heccer *pheccer);

int HeccerMechanismSort(struct Heccer *pheccer);


#endif


