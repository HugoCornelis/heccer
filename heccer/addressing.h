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


#ifndef HECCER_ADDRESSING_H
#define HECCER_ADDRESSING_H


#include <stdio.h>

struct Heccer;


#ifdef HECCER_SOURCE_NEUROSPACES

//d number of function allowed per symbol as a shift operand

#define NEUROSPACES_2_HECCER_MAX_FUNCTIONS 2

#define ADDRESSING_NEUROSPACES_2_HECCER(iNeuro) ((iNeuro) << NEUROSPACES_2_HECCER_MAX_FUNCTIONS)

#define ADDRESSING_HECCER_2_NEUROSPACES(iHeccer) ((iHeccer) >> NEUROSPACES_2_HECCER_MAX_FUNCTIONS)

//t should add defines for assigning function IDs.
//t
//t note that this would be solved automatically if
//t neurospaces would do full traversals.


void *
HeccerAddressVariable
(struct Heccer *pheccer, int iSerial, char *pcType);
#endif

void *
HeccerAddressCompartmentVariable
(struct Heccer *pheccer, int iIntermediary, char *pcField);

void *
HeccerAddressMechanismVariable
(struct Heccer *pheccer, int iIndex, char *pcField);


#endif


