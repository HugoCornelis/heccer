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

#t note the use of builddir without '/' suffixed.

#t the neurospaces prefix should be used for this

AM_CFLAGS=-g3 -fPIC -Wmissing-prototypes -Wmissing-declarations -ffloat-store -I/usr/local/neurospaces/instrumentor -I$(srcdir)/.. -I$(builddir).. -include heccer/config.h -DPRE_PROTO_TRAVERSAL -D__NO_MATH_INLINES

CFLAGS = -O0

pkglib_LIBRARIES = libhneurospaces.a

libhneurospaces_a_SOURCES = \
	heccer/neurospaces/heccer.c \
	heccer/neurospaces/mechanisms.c \
	heccer/neurospaces/segments.c

nobase_include_HEADERS = \
	heccer/neurospaces/heccer.h \
	heccer/neurospaces/mechanisms.h \
	heccer/neurospaces/segments.h

