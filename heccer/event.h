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


#ifndef HECCER_EVENT_H
#define HECCER_EVENT_H


#include "heccer/heccer.h"


//f prototypes

int HeccerEventGenerate(struct Heccer *pheccer, int iTargets);

double HeccerEventReceive(struct Heccer *pheccer, int iTarget);

int HeccerEventSet(struct Heccer *pheccer, int iTarget, double dTime);


#endif


