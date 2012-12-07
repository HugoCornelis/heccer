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

PyObject * PyDesConnectToModelContainer(struct simobj_DES *pdes, struct Neurospaces *pneuro);

//------------------------------------------ End Prototypes ---------------------------


//------------------------------------------------------------------------------

PyObject * PyDesConnectToModelContainer(struct simobj_DES *pdes, struct Neurospaces *pneuro)
{

  struct SolverRegistry *psr = NULL;
  struct ProjectionQuery *ppq = NULL;
  char pcErrorMsg[2048];
  int iResult = 0;

  if( !pneuro || !pneuro->psr )
  {

    snprintf(pcErrorMsg, 2048, "DES Connect Error: No solver registry has been allocated");
    PyErr_SetString(PyExc_Exception, pcErrorMsg);
    return NULL;
  }


  if( !pneuro->ppq )
  {
    //- Not sure if this would be a case i can skip or not.
    snprintf(pcErrorMsg, 2048, "DES Connect Error: No Projection Queries");
    PyErr_SetString(PyExc_MemoryError, pcErrorMsg);
    return NULL;
    
  }

  psr = pneuro->psr;

  ppq = pneuro->ppq;

  iResult = DESConnect(pdes, psr, ppq);


  if( iResult == 0 )
  {

    snprintf(pcErrorMsg, 2048, "DES Connect Error: Can't connect solver registry to model container");
    PyErr_SetString(PyExc_MemoryError, pcErrorMsg);
    return NULL;

  }


  Py_RETURN_NONE;

}

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------



%}

