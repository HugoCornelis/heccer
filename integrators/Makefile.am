##
## Heccer : a compartmental solver that implements efficient Crank-Nicolson
## integration for neuronal models.
##

##############################################################################
##'
##' Heccer : testbed C implementation
##'
##' Copyright (C) 2006-2007 Hugo Cornelis
##'
##' functional ideas ..	Hugo Cornelis, hugo.cornelis@gmail.com
##'
##' coding ............	Hugo Cornelis, hugo.cornelis@gmail.com
##'
##############################################################################


SUBDIRS = 

AM_CFLAGS=-gdwarf-2 -g3 -Wmissing-prototypes -Wmissing-declarations -ffloat-store -D__NO_MATH_INLINES -DPRE_PROTO_TRAVERSAL

CFLAGS = -O0

pkglib_LIBRARIES = libneurospaces.a

libneurospaces_a_SOURCES = \
	heccer/neurospaces/heccer.c \
	heccer/neurospaces/segments.c

nobase_include_HEADERS = \
	heccer/neurospaces/heccer.h \
	heccer/neurospaces/segments.h

