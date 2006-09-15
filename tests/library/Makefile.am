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


AM_CFLAGS=-gdwarf-2 -g3 -Wmissing-prototypes -Wmissing-declarations

CFLAGS = -O0

bin_PROGRAMS = \
	double \
	single \
	triple

double_DEPENDENCIES = ../../libheccer.a

double_LDADD = -L../.. -lheccer

single_DEPENDENCIES = ../../libheccer.a

single_LDADD = -L../.. -lheccer

triple_DEPENDENCIES = ../../libheccer.a

triple_LDADD = -L../.. -lheccer

