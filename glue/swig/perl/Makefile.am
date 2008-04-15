##
## Heccer : a compartmental solver that implements efficient Crank-Nicolson
## integration for neuronal models.
##

##############################################################################
##'
##' Heccer : testbed C implementation
##'
##' Copyright (C) 2006-2007 Hugo Cornelis
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

perl_HEADERS = Heccer.pm

perl_DATA = heccer_test.pm SwiggableHeccer.pm SwiggableHeccer.so

BUILT_SOURCES = \
	SwiggableHeccer.pm \
	swiggable_heccer_wrap.c

#t the configuration should say if this depends on neurospaces or not

SwiggableHeccer.pm swiggable_heccer_wrap.c: $(swig_DATA)
	swig -I/usr/local/neurospaces/instrumentor -I$(srcdir)/../../.. -I$(top_builddir) -perl5 -makedefault -module SwiggableHeccer -o swiggable_heccer_wrap.c $(srcdir)/heccer.i

#t the configuration should say if this depends on neurospaces or not

swiggable_heccer_wrap.o: swiggable_heccer_wrap.c
	gcc -I/usr/local/neurospaces/instrumentor -I$(srcdir)/../../.. -I$(top_builddir) -ffloat-store -I../../.. -include heccer/config.h -g -O0 -c swiggable_heccer_wrap.c -fPIC `perl -MExtUtils::Embed -e ccopts`

SwiggableHeccer.so: swiggable_heccer_wrap.o
	gcc -shared swiggable_heccer_wrap.o -L../../.. -lheccer -L../../../integrators -lhneurospaces -L/usr/local/lib/model-container -lneurospacesread -L/usr/local/lib/neurospaces/algorithms/symbol -lsymbol_algorithms -lreadline -lhistory -fPIC -o SwiggableHeccer.so

all: SwiggableHeccer.so

CLEANFILES = \
	SwiggableHeccer.pm \
	swiggable_heccer_wrap.c \
	swiggable_heccer_wrap.o \
	SwiggableHeccer.so

TESTS = heccer_test.pm

test: check

## following http://www.geocities.com/foetsch/python/swig_linux.htm

#BUILT_SOURCES = $(srcdir)/swiggable_heccer_wrap.c
#SWIG_SOURCES = heccer.i

## other sources
##
## http://sourceware.org/ml/automake/2001-03/msg00395.html
## http://autoconf-archive.cryp.to/macros-by-category.html
## http://sources.redhat.com/ml/automake/2005-02/msg00058.html
## https://www.desy.de/~salvaire/root_wrapper.html

