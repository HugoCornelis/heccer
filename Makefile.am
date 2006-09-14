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


SUBDIRS = . tests/library

AM_CFLAGS=-gdwarf-2 -g3 -Wmissing-prototypes -Wmissing-declarations

CFLAGS = -O0

noinst_LIBRARIES = libheccer.a

libheccer_a_SOURCES = \
	compartment.c \
	heccer.c \
	indexers.c \
	intermediary.c \
	mechanism.c \
	minimumdegree.c \
	vm.c

noinst_HEADERS = \
	compartment.h \
	heccer.h \
	indexers.h \
	intermediary.h \
	mathcomponent.h \
	mechanism.h \
	vm.h

#TESTS = tests/run

#test: check

