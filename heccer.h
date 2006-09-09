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


struct Heccer;


#include "compartment.h"
#include "mechanism.h"
#include "minimumdegree.h"


#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif


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

    int iCompartments;

    struct Compartment *pcomp;

    //m mechanism index

    int iMechanisms;

    struct MechanismIndex *pim;

    //m mechanism data

    void * pvMechanism;
};


/* //s minimum degree indexing */

/* struct MinimumDegree */
/* { */
/*     //m structural analyzers */

/*     int *piParents; */

/*     int *piChildren; */

/*     int **ppiChildren; */

/*     //m unordered to flow */

/*     int *piForward; */

/*     //m flow to unordered */

/*     int *piBackward; */
/* }; */


//t need a couple of things for channel reordering


//s all indexing structures

struct Indexers
{
    //m minimum degree

    struct MinimumDegree md;

    //t need a couple of things for channel reordering

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

    //m indexing structures

    struct Indexers indexers;

    //m vm

    struct VM vm;

};


//f prototypes

int HeccerCompileP1(struct Heccer *pheccer);

int HeccerCompileP2(struct Heccer *pheccer);

int HeccerHecc(struct Heccer *pheccer);

int HeccerIntialize(struct Heccer *pheccer);

struct Heccer *HeccerNewP1(void);

struct Heccer *HeccerNewP2(struct Intermediary *pinter);


#endif


