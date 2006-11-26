##
## Heccer : a compartmental solver that implements efficient Crank-Nicolson
## integration for neuronal models.
##

##############################################################################
##'
##' Heccer : testbed C implementation
##'
##' Copyright (C) 2006 Hugo Cornelis
##'
##' functional ideas ..	Hugo Cornelis, hugo.cornelis@gmail.com
##'
##' coding ............	Hugo Cornelis, hugo.cornelis@gmail.com
##'
##############################################################################


SUBDIRS = 

Heccer.pm heccer_wrap.c:
	swig -I../../.. -perl5 -makedefault -module Heccer heccer.i

heccer_wrap.o:
	gcc -I../../.. -c heccer_wrap.c `perl -MExtUtils::Embed -e ccopts` 

Heccer.so:
	gcc -shared heccer_wrap.o -L../../.. -lheccer -o Heccer.so

all: Heccer.so

test: check

