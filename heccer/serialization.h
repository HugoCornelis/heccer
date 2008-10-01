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


#ifndef HECCER_SERIALIZATION_H
#define HECCER_SERIALIZATION_H


#include "heccer/heccer.h"


#define HECCER_SERIALIZATION_VERSION "HECCER C"


struct Heccer *
HeccerDeserialize(FILE *pfile);

int
HeccerSerialize
(struct Heccer *pheccer, FILE *pfile);



#endif


