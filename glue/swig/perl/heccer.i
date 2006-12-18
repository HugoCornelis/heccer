/* File : example.i */
/* -*- C-mode -*- */

/* swig -perl5 -makedefault -module Heccer heccer.i */
/* gcc -c heccer_wrap.c `perl -MExtUtils::Embed -e ccopts`  */
/* gcc -shared heccer_wrap.o -L. -lheccer -o heccer.so */

%module Heccer
%{
#include "heccer/compartment.h"
#include "heccer/intermediary.h"
#include "heccer/heccer.h"
#include "heccer/mathcomponent.h"
%}

%include "heccer/compartment.h"
%include "heccer/intermediary.h"
%include "heccer/heccer.h"
%include "heccer/mathcomponent.h"
