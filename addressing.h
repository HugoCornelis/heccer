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


#ifndef COMPARTMENT_H
#define COMPARTMENT_H


#include <stdio.h>

struct Heccer;


//f prototypes

void *
AddressCompartmentVariable
(struct Heccer *pheccer, int iIntermediary, char *pcField);

void *
AddressMechanismVariable
(struct Heccer *pheccer, int iIndex, char *pcField);


#endif


