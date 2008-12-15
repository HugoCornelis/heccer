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


#define HECCER_SERIALIZATION_VERSION "HECCER 00000001"


struct Heccer *
HeccerDeserialize(FILE *pfile);

struct Heccer *
HeccerDeserializeFromFilename(char *pcFilename);

int
HeccerSerialize
(struct Heccer *pheccer, FILE *pfile);

int
HeccerSerializeToFilename
(struct Heccer *pheccer, char *pcFilename);


#endif


