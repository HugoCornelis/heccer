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


#ifndef HECCER_ADDRESSING_H
#define HECCER_ADDRESSING_H


#include <stdio.h>

struct simobj_Heccer;


#ifdef HECCER_SOURCE_NEUROSPACES

/// \def number of function allowed per symbol as a shift operand

#define NEUROSPACES_2_HECCER_MAX_FUNCTIONS 2

#define ADDRESSING_NEUROSPACES_2_HECCER(iNeuro) ((iNeuro) << NEUROSPACES_2_HECCER_MAX_FUNCTIONS)

#define ADDRESSING_HECCER_2_NEUROSPACES(iHeccer) ((iHeccer) >> NEUROSPACES_2_HECCER_MAX_FUNCTIONS)

/// \todo should add defines for assigning function IDs.
/// \todo note that this would be solved automatically if the
/// \todo neurospaces model_container would do full traversals.


double *
HeccerAddressAggregator
(struct simobj_Heccer *pheccer, int iSerial, char *pcType);

char *
HeccerAddressableSet
(struct simobj_Heccer *pheccer, int iSerial, char *pcType, double dValue);

double *
HeccerAddressCompartmentVariable
(struct simobj_Heccer *pheccer, int iIntermediary, char *pcField);

double *
HeccerAddressMechanismVariable
(struct simobj_Heccer *pheccer, int iIndex, char *pcField);

int
HeccerAddressTableIndex
(struct simobj_Heccer *pheccer, int iSerial, char *pcField);

double *
HeccerAddressVariable
(struct simobj_Heccer *pheccer, int iSerial, char *pcType);

#else

double *
HeccerAddressVariable
(struct simobj_Heccer *pheccer, int iSerial, char *pcType);

#endif


#endif


