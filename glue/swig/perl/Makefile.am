##
## Heccer : a compartmental solver that implements efficient Crank-Nicolson
## integration for neuronal models.
##

##############################################################################
##'
##' Heccer : testbed C implementation
##'
##' Copyright (C) 2006-2008 Hugo Cornelis
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

swigdir = $(prefix)/glue/swig

perldir = @PMDIR@

EXTRA_DIST = \
	heccer.i \
	$(srcdir)/heccer_test.pm

perl_HEADERS = Heccer.pm

perl_DATA = SwiggableHeccer.pm SwiggableHeccer.$(PERLLIB_EXTENSION)

BUILT_SOURCES = \
	SwiggableHeccer.pm \
	swiggable_heccer_wrap.c

#t the configuration should say if this depends on neurospaces or not

SwiggableHeccer.pm swiggable_heccer_wrap.c: $(swig_DATA)
	$(SWIG) -I/usr/local/neurospaces/instrumentor -I$(srcdir)/../../.. -I$(top_builddir) -perl5 -makedefault -module SwiggableHeccer -o swiggable_heccer_wrap.c $(srcdir)/heccer.i

#t the configuration should say if this depends on neurospaces or not

swiggable_heccer_wrap.o: swiggable_heccer_wrap.c
	$(SWIGCOMPILECOMMAND_PERL)


SwiggableHeccer.$(PERLLIB_EXTENSION): swiggable_heccer_wrap.o
	$(SWIGLINKCOMMAND_PERL)





all: SwiggableHeccer.$(PERLLIB_EXTENSION)

CLEANFILES = \
	SwiggableHeccer.pm \
	swiggable_heccer_wrap.c \
	swiggable_heccer_wrap.o \
	SwiggableHeccer.$(PERLLIB_EXTENSION)

TESTS = heccer_test.pm

# test: check

## following http://www.geocities.com/foetsch/python/swig_linux.htm

#BUILT_SOURCES = $(srcdir)/swiggable_heccer_wrap.c
#SWIG_SOURCES = heccer.i

## other sources
##
## http://sourceware.org/ml/automake/2001-03/msg00395.html
## http://autoconf-archive.cryp.to/macros-by-category.html
## http://sources.redhat.com/ml/automake/2005-02/msg00058.html
## https://www.desy.de/~salvaire/root_wrapper.html

