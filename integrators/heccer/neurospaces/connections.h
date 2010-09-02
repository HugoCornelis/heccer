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


#ifndef HECCER_NEUROSPACES_CONNECTIONS_H
#define HECCER_NEUROSPACES_CONNECTIONS_H


#include <neurospaces/config.h>
#include <neurospaces/projectionquery.h>


int DESConstruct(struct SolverRegistry *psr, struct ProjectionQuery *ppq);


#endif


