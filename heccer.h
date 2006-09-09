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
    //m status : reflects phases of compilation.

    int iStatus;

    //m identification service : translates serials to math components

    void * pvService;

    //m intermediary

    struct Intermediary inter;

    //m indexing structures

    struct Indexers indexers;

    //m vm

    struct VM vm;

};


//d brandnew allocated, nothing done

#define HECCER_STATUS_PHASE_0		0

//d brandnew allocated, correctly initialized

#define HECCER_STATUS_PHASE_1		10

//d brandnew allocated, intermediary has been built

#define HECCER_STATUS_PHASE_2		20

//d brandnew allocated, byte has been compiled

#define HECCER_STATUS_PHASE_3		30

//d brandnew allocated, initial values have been put in place

#define HECCER_STATUS_PHASE_4		40

//d brandnew allocated, heccs have been done, further status unknown

#define HECCER_STATUS_PHASE_5		50


//f prototypes

int HeccerCompileP1(struct Heccer *pheccer);

int HeccerCompileP2(struct Heccer *pheccer);

int HeccerHecc(struct Heccer *pheccer);

int HeccerIntialize(struct Heccer *pheccer);

struct Heccer *HeccerNewP1(void);

struct Heccer *HeccerNewP2(struct Intermediary *pinter);


#endif


