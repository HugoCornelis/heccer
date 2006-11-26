/* File : example.i */
/* -*- C-mode -*- */

/* swig -perl5 -makedefault -module Heccer heccer.i */
/* gcc -c heccer_wrap.c `perl -MExtUtils::Embed -e ccopts`  */
/* gcc -shared heccer_wrap.o -L. -lheccer -o heccer.so */

%module Heccer
%{
#include "compartment.h"
#include "intermediary.h"
#include "heccer.h"
#include "mathcomponent.h"
%}

%include "compartment.h"
%include "intermediary.h"
%include "heccer.h"
%include "mathcomponent.h"
