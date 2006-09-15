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
	doublep \
	singlep \
	triplep

doublep_DEPENDENCIES = ../../libheccer.a main.c

doublep_LDADD = -L../.. -lheccer

singlep_DEPENDENCIES = ../../libheccer.a main.c

singlep_LDADD = -L../.. -lheccer

triplep_DEPENDENCIES = ../../libheccer.a main.c

triplep_LDADD = -L../.. -lheccer

