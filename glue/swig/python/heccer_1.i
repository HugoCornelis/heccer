/* -*- C -*- */

/* swig -perl5 -makedefault -module Heccer heccer.i */
/* gcc -c heccer_wrap.c `perl -MExtUtils::Embed -e ccopts`  */
/* gcc -shared heccer_wrap.o -L. -lheccer -o heccer.so */

%module heccer_base


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
#include "heccer/table.h"

//t so this should depend on the configuration
//t perhaps this can be done using regular #ifdef statements, not sure

#include "integrators/heccer/neurospaces/heccer.h"

%}

%inline %{



/// compartment array handling

struct Compartment *comp_array(int size)
{
    return (struct Compartment *)malloc(sizeof(struct Compartment) * size);
}
void comp_destroy(struct Compartment *a)
{
    free(a);
}
void comp_set(struct Compartment *a, int i, struct Compartment *val)
{
    a[i] = *val;
}
struct Compartment *comp_get(struct Compartment *a, int i)
{
    return &a[i];
}

/// table handling

struct HeccerTabulatedGate *htg_get(struct TabulatedGateTable *ptgt, int i)
{
    return &ptgt->phtg[i];
}

/* /// math component array handling */

/* struct MathComponent *math_component_array(int size) */
/* { */
/*     return (struct MathComponent *)malloc(sizeof(struct MathComponent) * size); */
/* } */
/* void math_component_destroy(struct MathComponent *a) */
/* { */
/*     free(a); */
/* } */
/* void math_component_set(struct MathComponent *a, int i, struct MathComponent *val) */
/* { */
/*     a[i] = *val; */
/* } */
/* struct MathComponent *math_component_get(struct MathComponent *a, int i) */
/* { */
/*     return NULL; */
/* } */
%}

%include "heccer/config.h"
%include "heccer/addressing.h"
%include "heccer/callout.h"
%include "heccer/compartment.h"
%include "heccer/des.h"
%include "heccer/intermediary.h"
%include "heccer/heccer.h"
%include "heccer/mathcomponent.h"
%include "heccer/mechanism.h"
%include "heccer/table.h"

%include "integrators/heccer/neurospaces/heccer.h"


