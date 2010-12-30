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

python_DATA =  SwiggableHeccer.py _SwiggableHeccer.so

EXTRA_DIST = \
	$(srcdir)/heccer.i \
	$(srcdir)/heccer_1.i \
	$(srcdir)/tests/ \
	$(srcdir)/heccer/__cbi__.py \
	$(srcdir)/heccer/heccer.py \
	$(srcdir)/heccer/errors.py 

BUILT_SOURCES = \
	SwiggableHeccer.py \
	swiggable_heccer_wrap.c

SwiggableHeccer.py swiggable_heccer_wrap.c: $(swig_DATA)
	$(SWIG) -I$(builddir)../../.. -I$(srcdir)/../../.. -python -makedefault -module SwiggableHeccer -o swiggable_heccer_wrap.c $(srcdir)/heccer.i 

swiggable_heccer_wrap.o: swiggable_heccer_wrap.c
	$(SWIGCOMPILECOMMAND_PYTHON)


_SwiggableHeccer.$(PYTHONLIB_EXTENSION): swiggable_heccer_wrap.o
	$(SWIGLINKCOMMAND_PYTHON)



#---------------------------------------------------------
#-------- Rules for building the heccer swig binding -----

heccer_wrap.o: heccer_wrap.c
	gcc $(SWIGCOMPILELINKSFORPYTHON) -c $(srcdir)/heccer_wrap.c

heccer_wrap.c ./heccer/heccer_base.py: 
	$(SWIG) -I$(builddir)/../../.. -I$(srcdir)/../../.. -I$(top_builddir) -python -outdir $(srcdir)/heccer -o heccer_wrap.c $(srcdir)/heccer_1.i

_heccer_base.so: heccer_wrap.o
	$(HECCER_SWIGLINKCOMMAND_PYTHON)

#------------------ End rules for heccer swig ------------
#---------------------------------------------------------



all: _heccer_base.so _SwiggableHeccer.$(PYTHONLIB_EXTENSION)

CLEANFILES = \
	$(srcdir)/heccer_wrap.c \
	$(srcdir)/heccer_wrap.o \
	$(srcdir)/heccer/_heccer_base.so \
	$(srcdir)/heccer/heccer_base.py \
	$(srcdir)/SwiggableHeccer.py \
	$(srcdir)/swiggable_heccer_wrap.c \
	$(srcdir)/swiggable_heccer_wrap.o \
	$(srcdir)/_SwiggableHeccer.so


