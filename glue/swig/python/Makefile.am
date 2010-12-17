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

# Dist hook is commented out here because EXTRA_DIST does the
# work we need.
#dist-hook:

swigdir = $(prefix)/glue/swig

#t use $(swigdir) here

pythondir = $(prefix)/glue/swig/python

nobase_python_HEADERS = heccer/__init__.py

python_DATA =  SwiggableHeccer.py _SwiggableHeccer.$(PYTHONLIB_EXTENSION) tests/heccer_test.py

EXTRA_DIST = \
	$(srcdir)/heccer.i \
	$(srcdir)/tests/

BUILT_SOURCES = \
	SwiggableHeccer.py \
	swiggable_heccer_wrap.c

SwiggableHeccer.py swiggable_heccer_wrap.c: $(swig_DATA)
	$(SWIG) -I$(builddir)../../.. -I$(srcdir)/../../.. -python -makedefault -module SwiggableHeccer -o swiggable_heccer_wrap.c $(srcdir)/heccer.i 

swiggable_heccer_wrap.o: swiggable_heccer_wrap.c
	$(SWIGCOMPILECOMMAND_PYTHON)


_SwiggableHeccer.$(PYTHONLIB_EXTENSION): swiggable_heccer_wrap.o
	$(SWIGLINKCOMMAND_PYTHON)

all: _SwiggableHeccer.$(PYTHONLIB_EXTENSION)

CLEANFILES = \
	SwiggableHeccer.py \
	swiggable_heccer_wrap.c \
	swiggable_heccer_wrap.o \
	_SwiggableHeccer.$(PYTHONLIB_EXTENSION)


