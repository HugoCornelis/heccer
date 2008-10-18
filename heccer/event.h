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


#ifndef HECCER_EVENT_H
#define HECCER_EVENT_H


#ifndef HECCER_HECCER_H

#include "heccer/heccer.h"

#endif



int HeccerEventGenerate(struct Heccer *pheccer, int iTargets);

double HeccerEventReceive(struct Heccer *pheccer, int iTarget);

int HeccerEventSet(struct Heccer *pheccer, int iTarget, double dTime);


#endif


