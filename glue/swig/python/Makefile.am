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

# The nmc module is installed under the g3 module from the developer
# package. Since it comes first in the user workflow, it should 
# be installed first.
pythondir = $(prefix)/glue/swig/python/g3

nobase_python_HEADERS = \
	heccer/__init__.py \
	heccer/__cbi__.py \
	heccer/errors.py

nobase_python_DATA = \
	heccer/_heccer_base.so \
	heccer/heccer_base.py

EXTRA_DIST = \
	$(srcdir)/heccer.i 

BUILT_SOURCES = \
	heccer/heccer_base.py \
	heccer_wrap.c


#---------------------------------------------------------
#-------- Rules for building the heccer swig binding -----

heccer_wrap.o: heccer_wrap.c
	gcc $(SWIGCOMPILELINKSFORPYTHON) -c $(srcdir)/heccer_wrap.c

heccer_wrap.c ./heccer/heccer_base.py: 
	$(SWIG) -I$(builddir)/../../.. -I$(srcdir)/../../.. -I$(top_builddir) -python -outdir $(srcdir)/heccer -o heccer_wrap.c $(srcdir)/heccer.i

_heccer_base.so: heccer_wrap.o
	$(HECCER_SWIGLINKCOMMAND_PYTHON)

#------------------ End rules for heccer swig ------------
#---------------------------------------------------------



all: _heccer_base.so 



clean-local:
	$(RM) -rf $(srcdir)/docs/html
	echo "Removing all compiled byte code files"
	$(RM) `find . -name "*.pyc"`
	$(RM) -rf $(srcdir)/build
	$(RM) -rf $(srcdir)/dist/

CLEANFILES = \
	$(srcdir)/heccer_wrap.c \
	$(srcdir)/heccer_wrap.o \
	$(srcdir)/heccer/_heccer_base.so \
	$(srcdir)/heccer/heccer_base.py 


