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

check_PROGRAMS = \
	doublep \
	c1c2p1 \
	c1c2p2 \
	fork3p \
	fork4p1 \
	fork4p2 \
	fork4p3 \
	singlep \
	tensizesp \
	triplep

noinst_HEADERS = \
	main.c

c1c2p1_DEPENDENCIES = ../../libheccer.a main.c

c1c2p1_LDADD = -L../.. -lheccer

c1c2p2_DEPENDENCIES = ../../libheccer.a main.c

c1c2p2_LDADD = -L../.. -lheccer

doublep_DEPENDENCIES = ../../libheccer.a main.c

doublep_LDADD = -L../.. -lheccer

fork3p_DEPENDENCIES = ../../libheccer.a main.c

fork3p_LDADD = -L../.. -lheccer

fork4p1_DEPENDENCIES = ../../libheccer.a main.c

fork4p1_LDADD = -L../.. -lheccer

fork4p2_DEPENDENCIES = ../../libheccer.a main.c

fork4p2_LDADD = -L../.. -lheccer

fork4p3_DEPENDENCIES = ../../libheccer.a main.c

fork4p3_LDADD = -L../.. -lheccer

singlep_DEPENDENCIES = ../../libheccer.a main.c

singlep_LDADD = -L../.. -lheccer

tensizesp_DEPENDENCIES = ../../libheccer.a main.c

tensizesp_LDADD = -L../.. -lheccer

triplep_DEPENDENCIES = ../../libheccer.a main.c

triplep_LDADD = -L../.. -lheccer

#t automake does not allow to pass in arguments for tests ?

#TESTS = $(srcdir)/tests/run

check_SCRIPTS = $(srcdir)/../run

TESTS = $(srcdir)/../run

