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


#ifndef HECCER_NEUROSPACES_DES_H
#define HECCER_NEUROSPACES_DES_H


#define PRE_PROTO_TRAVERSAL 1


#include <neurospaces/projectionquery.h>
#include <neurospaces/solverinfo.h>

#include "heccer/des.h"


int DESConnect(struct DES *pdes, struct SolverRegistry *psr, struct ProjectionQuery *ppq);


#endif


