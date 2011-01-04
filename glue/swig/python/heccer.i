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

 // info on the carray library here http://www.swig.org/Doc1.3/Library.html#Library_carrays
%include "carrays.i"
%array_functions(double, DoubleArray)


%array_functions(int, IntArray)


%array_functions(struct Compartment, CompartmentArray)

