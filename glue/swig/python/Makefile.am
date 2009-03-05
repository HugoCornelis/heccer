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
	cp $(srcdir)/heccer.i $(distdir)
	$(INSTALL) -d $(distdir)/tests
	cp $(srcdir)/tests/*.py $(distdir)/tests

swigdir = $(prefix)/glue/swig

#t use $(swigdir) here

pythondir = $(prefix)/glue/swig/python

nobase_python_HEADERS = Heccer/__init__.py

python_DATA = $(srcdir)/heccer.i SwiggableHeccer.py _SwiggableHeccer.$(PERLLIB_EXTENSION) tests/heccer_test.py

BUILT_SOURCES = \
	SwiggableHeccer.py \
	swiggable_heccer_wrap.c

SwiggableHeccer.py swiggable_heccer_wrap.c: $(swig_DATA)
	swig -I$(builddir)../../.. -I$(srcdir)/../../.. -python -makedefault -module SwiggableHeccer -o swiggable_heccer_wrap.c $(srcdir)/heccer.i 

swiggable_heccer_wrap.o: swiggable_heccer_wrap.c
	gcc $(SWIGCOMPILELINKSFORPYTHON) -c swiggable_heccer_wrap.c -fPIC


_SwiggableHeccer.$(PERLLIB_EXTENSION): swiggable_heccer_wrap.o
	gcc $(SWIGLDLINKSFORPYTHON) -o _SwiggableHeccer.$(PERLLIB_EXTENSION)


all: _SwiggableHeccer.$(PERLLIB_EXTENSION)

CLEANFILES = \
	SwiggableHeccer.py \
	swiggable_heccer_wrap.c \
	swiggable_heccer_wrap.o \
	_SwiggableHeccer.$(PERLLIB_EXTENSION)


