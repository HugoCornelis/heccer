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

python_DATA = $(srcdir)/heccer.i SwiggableHeccer.py _SwiggableHeccer.so tests/heccer_test.py

BUILT_SOURCES = \
	SwiggableHeccer.py \
	swiggable_heccer_wrap.c

SwiggableHeccer.py swiggable_heccer_wrap.c: $(swig_DATA)
	swig -I$(builddir)../../.. -I$(srcdir)/../../.. -python -makedefault -module SwiggableHeccer -o swiggable_heccer_wrap.c $(srcdir)/heccer.i

swiggable_heccer_wrap.o: swiggable_heccer_wrap.c
	gcc -g -DPRE_PROTO_TRAVERSAL -I/usr/include/python2.4 -I/usr/local/neurospaces/instrumentor -I$(builddir)../../.. -I$(srcdir)/../../.. -I$(builddir)../../../hierarchy/output/symbols -I$(srcdir)/../../../hierarchy/output/symbols/ -c swiggable_heccer_wrap.c -fPIC -Xlinker -export-dynamic

#t this line needs -f PIC for some architectures, and -lncurses for some architectures

_SwiggableHeccer.so: swiggable_heccer_wrap.o
	gcc -g -shared swiggable_heccer_wrap.o -L../../.. -lheccer -L../../../integrators -lhneurospaces -L/usr/local/lib/model-container -lneurospacesread -L/usr/local/lib/neurospaces/algorithms/symbol -lsymbol_algorithms -lncurses -lreadline -lhistory -fPIC -o _SwiggableHeccer.so -Xlinker -export-dynamic

all: _SwiggableHeccer.so

CLEANFILES = \
	SwiggableHeccer.py \
	swiggable_heccer_wrap.c \
	swiggable_heccer_wrap.o \
	_SwiggableHeccer.so


