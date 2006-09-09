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

noinst_LIBRARIES = libheccer.a

libheccer_a_SOURCES = \
	compartment.h \
	heccer.c \
	intermediary.c \
	mathcomponent.h \
	minimumdegree.c

noinst_HEADERS = \
	compartment.h \
	heccer.h \
	mathcomponent.h \
	mechanism.h

#TESTS = tests/run

#test: check

