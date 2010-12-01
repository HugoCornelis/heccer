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


struct simobj_Heccer *
HeccerDeserialize(FILE *pfile);

int
HeccerDeserializeCompartmentState
(struct simobj_Heccer *pheccer, FILE *pfile);

int
HeccerDeserializeCompartmentStructure
(struct simobj_Heccer *pheccer, FILE *pfile);

struct simobj_Heccer *
HeccerDeserializeFromFilename(char *pcFilename);

int
HeccerDeserializeMechanismState
(struct simobj_Heccer *pheccer, FILE *pfile);

int
HeccerDeserializeMechanismStructure
(struct simobj_Heccer *pheccer, FILE *pfile);

int
HeccerSerializationClose(FILE *pfile);

FILE *
HeccerSerializationOpenRead(char *pcFilename);

FILE *
HeccerSerializationOpenWrite(char *pcFilename);

int
HeccerSerialize
(struct simobj_Heccer *pheccer, FILE *pfile);

int
HeccerSerializeCompartmentState
(struct simobj_Heccer *pheccer, FILE *pfile);

int
HeccerSerializeCompartmentStructure
(struct simobj_Heccer *pheccer, FILE *pfile);

int
HeccerSerializeMechanismState
(struct simobj_Heccer *pheccer, FILE *pfile);

int
HeccerSerializeMechanismStructure
(struct simobj_Heccer *pheccer, FILE *pfile);

int
HeccerSerializeToFilename
(struct simobj_Heccer *pheccer, char *pcFilename);


#endif


