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


#t the following rules are crap complete, would be good if a auto
#t expert takes a look at it.

dist-hook:
	cp $(srcdir)/heccer.i $(distdir)
	cp $(srcdir)/heccer_test.pm $(distdir)

swigdir = $(prefix)/glue/swig

#t use $(swigdir) here

perldir = $(prefix)/glue/swig/perl

swig_DATA = heccer.i

perl_DATA = heccer_test.pm Heccer.pm Heccer.so

BUILT_SOURCES = \
	Heccer.pm \
	heccer_wrap.c

Heccer.pm heccer_wrap.c: $(swig_DATA)
	swig -I$(srcdir)/../../.. -perl5 -makedefault -module Heccer -o heccer_wrap.c $(srcdir)/heccer.i

heccer_wrap.o: heccer_wrap.c
	gcc -I$(srcdir)/../../.. -c heccer_wrap.c `perl -MExtUtils::Embed -e ccopts`

Heccer.so: heccer_wrap.o
	gcc -shared heccer_wrap.o -L../../.. -lheccer -o Heccer.so

all: Heccer.so

CLEANFILES = \
	Heccer.pm \
	heccer_wrap.c \
	heccer_wrap.o \
	Heccer.so

TESTS = heccer_test.pm

test: check

## following http://www.geocities.com/foetsch/python/swig_linux.htm

#BUILT_SOURCES = $(srcdir)/heccer_wrap.c
#SWIG_SOURCES = heccer.i

## other sources
##
## http://sourceware.org/ml/automake/2001-03/msg00395.html
## http://autoconf-archive.cryp.to/macros-by-category.html
## http://sources.redhat.com/ml/automake/2005-02/msg00058.html
## https://www.desy.de/~salvaire/root_wrapper.html

