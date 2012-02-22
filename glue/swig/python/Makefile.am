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

#nobase_dist_python_DATA = \
#	heccer/__cbi__.py \
#	heccer/__init__.py \
#	heccer/errors.py 

EXTRA_DIST = \
	heccer.i \
	heccer/__cbi__.py \
	heccer/__init__.py \
	heccer/errors.py \
	clean.py \
	setup.py \
	uninstall.py 

setup: setup.py
	$(PYTHON) setup.py build
	$(PYTHON) setup.py build_py

install-exec-hook:
	$(PYTHON) setup.py install

uninstall-hook:
	$(PYTHON) uninstall.py

all: setup

clean-local:
	$(RM) `find . -name "*.pyc"`
	$(PYTHON) clean.py

CLEANFILES = \
	$(srcdir)/heccer_wrap.c \
	$(srcdir)/heccer_wrap.o \
	$(srcdir)/_heccer_base.so \
	$(srcdir)/heccer_base.py \
	$(srcdir)/heccer_wrap.c \
	$(srcdir)/heccer_wrap.o \
	$(srcdir)/heccer/_heccer_base.so \
	$(srcdir)/heccer/heccer_base.py 




# SUBDIRS = 

# pythondir = $(prefix)/glue/swig/python/

# nobase_python_HEADERS = \
# 	neurospaces/heccer/__init__.py \
# 	neurospaces/heccer/__cbi__.py \
# 	neurospaces/heccer/errors.py

# nobase_python_DATA = \
# 	neurospaces/heccer/_heccer_base.so \
# 	neurospaces/heccer/heccer_base.py

# EXTRA_DIST = \
# 	$(srcdir)/heccer.i 

# BUILT_SOURCES = \
# 	neurospaces/heccer/heccer_base.py \
# 	heccer_wrap.c


# #---------------------------------------------------------
# #-------- Rules for building the heccer swig binding -----

# heccer_wrap.o: heccer_wrap.c
# 	gcc $(SWIGCOMPILELINKSFORPYTHON) -c $(srcdir)/heccer_wrap.c

# heccer_wrap.c ./neurospaces/heccer/heccer_base.py: 
# 	$(SWIG) -I$(builddir)/../../.. -I$(srcdir)/../../.. -I$(top_builddir) -python -outdir $(srcdir)/neurospaces/heccer -o heccer_wrap.c $(srcdir)/heccer.i

# _heccer_base.so: heccer_wrap.o
# 	$(HECCER_SWIGLINKCOMMAND_PYTHON)

# #------------------ End rules for heccer swig ------------
# #---------------------------------------------------------



# all: _heccer_base.so 
