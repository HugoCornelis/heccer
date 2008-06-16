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


//o
//o How do you define external callout functions ?
//o
//o step 1 : implement your function.
//o
//o the signature for the function is given by the typedef ExternalFunction.
//o Currently this is defined as a function that returns an integer (zero),
//o and has arguments that gives access to the intermediary, results computed
//o by Heccer, and results to be computed by the external function.  The exact
//o definition can be found below.
//o
//o Note: Heccer does not do any overwriting of the result data of the external
//o function.  So, if needed, the external function must reinitialize its result
//o data (to zero or another appropriate value), every time it is called.
//o
//o step 2 : define your model.
//o
//o The important fact is that you have to link you model with the
//o external function in the intermediary representation.  You use the struct
//o Callout to do so.  This struct contains a direct pointer to the external
//o function.
//o
//o other steps : compile and run your model.
//o
//o You compile and run your model as usual.  See the test scripts for examples
//o how to do that.
//o


#ifndef HECCER_CALLOUT_H
#define HECCER_CALLOUT_H


#include "heccer.h"
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

    //m external current, another example

    double dCurrent;
};


//f external function

struct Callout;

typedef 
int ExternalFunction
(struct Callout *pco, struct Heccer *pheccer, struct InternalResults *pir, struct ExternalResults *per);


//s call out intermediary

//! prefix all the intermediary struct's with something common, for
//! readability.

struct Callout
{
    //m administration overhead

    struct MathComponent mc;

    //m external alien data

    void *pvAlien;

    //m internal results

    struct InternalResults *pir;

    //m external results

    struct ExternalResults *per;

    //m external function

    ExternalFunction *pef;

    //! descriptive values can follow here

    //! and if convenient, internal and external results can follow thereafter
};


#endif


