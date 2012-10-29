/* -*- C -*- */

/* swig -perl5 -makedefault -module Heccer heccer.i */
/* gcc -c heccer_wrap.c `perl -MExtUtils::Embed -e ccopts`  */
/* gcc -shared heccer_wrap.o -L. -lheccer -o heccer.so */



%{
#include "heccer/config.h"
#include "heccer/addressing.h"
#include "heccer/callout.h"
#include "heccer/compartment.h"
#include "heccer/des.h"
#include "heccer/intermediary.h"
#include "heccer/heccer.h"
#include "heccer/mathcomponent.h"
#include "heccer/mechanism.h"
#include "heccer/serialization.h"
#include "heccer/table.h"

#include "integrators/heccer/neurospaces/des2.h"
#include "integrators/heccer/neurospaces/heccer.h"

%}

%inline %{

//------------------------------------------ Prototypes -------------------------------

double HeccerAddressGetValue(struct simobj_Heccer *pheccer, int iSerial, char *pcParameter);
int AddressingNeurospaces2Heccer(int iNeuro);
int AddressingHeccer2Neurospaces(int iHeccer);
int SetDoubleValue(double *dAddress, double dValue);
//------------------------------------------ End Prototypes ---------------------------



int AddressingNeurospaces2Heccer(int iNeuro)
{

  return ADDRESSING_NEUROSPACES_2_HECCER(iNeuro);

}

int AddressingHeccer2Neurospaces(int iHeccer)
{

  return ADDRESSING_HECCER_2_NEUROSPACES(iHeccer);

}



int SetDoubleValue(double *dAddress, double dValue)
{

  if( !dAddress )
  {
    return 0;
  }

  (*dAddress) = dValue;

}

//------------------------------------------------------------------------------
/*
 * 
 */
double HeccerAddressGetValue(struct simobj_Heccer *pheccer, int iSerial, char *pcField)
{

  double *pdResult = NULL;

  if( !pheccer )
  {

    PyErr_SetString(PyExc_MemoryError,"A Heccer solver has not been allocated");

  }

  pdResult = HeccerAddressVariable(pheccer, iSerial, pcField);


  if( !pdResult )
  {

    PyErr_SetString(PyExc_LookupError,
		    "Heccer lookup failed, element or parameter does not exist");

  }

  return *pdResult;

}
//------------------------------------------------------------------------------



%}

