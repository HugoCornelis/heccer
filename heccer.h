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


#include <stdio.h>


struct Heccer;


#include "intermediary.h"
#include "indexers.h"
#include "vm.h"


#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif


//s heccer main structure

struct Heccer
{
    //m status : reflects phases of compilation.

    int iStatus;

    //m options and operation mode.

    int iOptions;

    //m current time

    double dTime;

    //m time step

    double dStep;

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


//d logical branch grouping for solution matrix :
//d schedules first a leave and all attached compartments until a
//d branch point.  When disabled, all the leaves are scheduled first,
//d next the compartments attached to the leaves, etc.

#define HECCER_OPTION_BRANCHES_FIRST_SCHEDULING		1

//d use backward euler, default is crank-nicolson

#define HECCER_OPTION_BACKWARD_EULER			2


//f prototypes

int HeccerCompileP1(struct Heccer *pheccer);

int HeccerCompileP2(struct Heccer *pheccer);

int HeccerCompileP3(struct Heccer *pheccer);

int HeccerDump(struct Heccer *pheccer, FILE *pfile);

int HeccerHecc(struct Heccer *pheccer);

int HeccerInitiate(struct Heccer *pheccer);

struct Heccer *HeccerNewP1(int iOptions, double dStep);

struct Heccer *HeccerNewP2(struct Intermediary *pinter);


#endif

