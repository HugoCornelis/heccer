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


#ifndef HECCER_H
#define HECCER_H


#include "compartment.h"
#include "mechanism.h"


//s mechanism index

struct MechanismIndex
{
    //m pointer to mechanism data

    void * pvMechanism;
};


//s heccer main structure

struct Intermediary
{
    //m compartment array

    struct Compartment *pcomp;

    //m mechanism index

    struct MechanismIndex *pim;

    //m mechanism data

    void * pvMechanism;
};


//s vm related (name subject to change)

struct VM
{
    //m compartment operations

    //t data type unspecified

    void *pvCops;

    //m compartment data

    //t data type unspecified

    void *pvCats;

    //m mechanism operations

    //t data type unspecified

    void *pvMops;

    //m mechanism data

    //t data type unspecified

    void *pvMats;

};


//s heccer main structure

struct Heccer
{
    //m identification service : translates serials to math components

    void * pvService;

    //m intermediary

    struct Intermediary inter;

    //m vm

    struct VM vm;

};


#endif


