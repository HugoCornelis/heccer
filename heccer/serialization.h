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

int
HeccerDeserializeCompartmentState
(struct Heccer *pheccer, FILE *pfile);

int
HeccerDeserializeCompartmentStructure
(struct Heccer *pheccer, FILE *pfile);

int
HeccerDeserializeMechanismState
(struct Heccer *pheccer, FILE *pfile);

int
HeccerDeserializeMechanismStructure
(struct Heccer *pheccer, FILE *pfile);

struct Heccer *
HeccerDeserializeFromFilename(char *pcFilename);

int
HeccerSerialize
(struct Heccer *pheccer, FILE *pfile);

int
HeccerSerializeCompartmentState
(struct Heccer *pheccer, FILE *pfile);

int
HeccerSerializeCompartmentStructure
(struct Heccer *pheccer, FILE *pfile);

int
HeccerSerializeMechanismState
(struct Heccer *pheccer, FILE *pfile);

int
HeccerSerializeMechanismStructure
(struct Heccer *pheccer, FILE *pfile);

int
HeccerSerializeToFilename
(struct Heccer *pheccer, char *pcFilename);


#endif


