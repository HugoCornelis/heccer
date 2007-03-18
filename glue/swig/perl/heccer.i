/* -*- C -*- */

/* swig -perl5 -makedefault -module Heccer heccer.i */
/* gcc -c heccer_wrap.c `perl -MExtUtils::Embed -e ccopts`  */
/* gcc -shared heccer_wrap.o -L. -lheccer -o heccer.so */

%module SwiggableHeccer

/* %typemap(in) struct Neurospaces * { */

/*     //- cast to _p_Neurospaces */

/*     if (SvOK($input)) */
/*     { */
/* 	$1 = SvRV($input); */
/*     } */
/* } */

/* %typemap(out) struct Neurospaces * { */

/*     //- cast to _p_Neurospaces */

/*     $1 = $input; */
/* } */

/* %typemap(ruby,in) (int size, int *ary) { */
/*    int i; */
/*    if (!rb_obj_is_kind_of($input,rb_cArray)) */
/*      rb_raise(rb_eArgError, "Expected Array of Integers"); */
/*    $1 = RARRAY($input)->len; */
/*    $2 = malloc($1*sizeof(int)); */
/*    for (i=0; i<$1; ++i) */
/*      ($2)[i] = NUM2INT(RARRAY($input)->ptr[i]); */
/* } */
/* %typemap(freearg) (int size, int *ary) { */
/*     if ($2) free($2); */
/* } */

/* %typemap(memberin) int [ANY] */
/* { */
/*     int i; */
/*     for (i = 0 ; i < $1_dim0 ; i++) */
/*     { */
/* 	$1[i] = $input[i]; */
/*     } */
/* } */

%{
#include "heccer/config.h"
#include "heccer/addressing.h"
#include "heccer/callout.h"
#include "heccer/compartment.h"
#include "heccer/intermediary.h"
#include "heccer/heccer.h"
#include "heccer/mathcomponent.h"
#include "heccer/mechanism.h"
#include "heccer/output.h"

//t so this should depend on the configuration

#include "integrators/heccer/neurospaces/heccer.h"

/* #include "/usr/local/include/neurospaces/neurospaces.h" */

%}

%inline %{

/* void piC2m_set(struct Intermediary *pim, int *piC2m) */
/* { */
/*     pim->piC2m = piC2m; */
/* } */

/// integer array handling

//t use array generics, see carray.i

int *int_array(int size)
{
    return (int *) malloc(sizeof(int) * size);
}
void int_destroy(int *a)
{
    free(a);
}
void int_set(int *a, int i, int val)
{
    a[i] = val;
}
int int_get(int *a, int i)
{
    return a[i];
}

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
%include "heccer/intermediary.h"
%include "heccer/heccer.h"
%include "heccer/mathcomponent.h"
%include "heccer/mechanism.h"
%include "heccer/output.h"

//t so this should depend on the configuration

%include "integrators/heccer/neurospaces/heccer.h"

/* %include "/usr/local/include/neurospaces/neurospaces.h" */


