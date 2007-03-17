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


#t note the use of builddir without '/' suffixed.

AM_CFLAGS=-gdwarf-2 -g3 -Wmissing-prototypes -Wmissing-declarations -ffloat-store -I$(srcdir)/.. -I$(builddir)../.. -include heccer/config.h -DPRE_PROTO_TRAVERSAL -D__NO_MATH_INLINES

# ease debugging

CFLAGS=-O0

check_PROGRAMS = \
	c1c2p1 \
	c1c2p2 \
	callout1 \
	calloutInjector \
	doublep \
	fork3p \
	fork4p1 \
	fork4p2 \
	fork4p3 \
	pool1-feedback1 \
	pool1-feedback2 \
	pool1 \
	pool2 \
	singlea-naf \
	singlep \
	table-cap \
	table-cat \
	table-k2 \
	table-ka \
	table-kc \
	table-kdr \
	table-kh \
	table-km \
	table-naf \
	tensizesp \
	triplep \
	version

noinst_HEADERS = \
	main.c

c1c2p1_DEPENDENCIES = ../../libheccer.a main.c
c1c2p1_LDADD = -L../.. -lheccer -lm
c1c2p2_DEPENDENCIES = ../../libheccer.a main.c
c1c2p2_LDADD = -L../.. -lheccer -lm
callout1_DEPENDENCIES = ../../libheccer.a main.c
callout1_LDADD = -L../.. -lheccer -lm
calloutInjector_DEPENDENCIES = ../../libheccer.a main.c
calloutInjector_LDADD = -L../.. -lheccer -lm
doublep_DEPENDENCIES = ../../libheccer.a main.c
doublep_LDADD = -L../.. -lheccer -lm
fork3p_DEPENDENCIES = ../../libheccer.a main.c
fork3p_LDADD = -L../.. -lheccer -lm
fork4p1_DEPENDENCIES = ../../libheccer.a main.c
fork4p1_LDADD = -L../.. -lheccer -lm
fork4p2_DEPENDENCIES = ../../libheccer.a main.c
fork4p2_LDADD = -L../.. -lheccer -lm
fork4p3_DEPENDENCIES = ../../libheccer.a main.c
fork4p3_LDADD = -L../.. -lheccer -lm
pool1_DEPENDENCIES = ../../libheccer.a main.c
pool1_LDADD = -L../.. -lheccer -lm
pool1_feedback1_DEPENDENCIES = ../../libheccer.a main.c
pool1_feedback1_LDADD = -L../.. -lheccer -lm
pool1_feedback2_DEPENDENCIES = ../../libheccer.a main.c
pool1_feedback2_LDADD = -L../.. -lheccer -lm
pool2_DEPENDENCIES = ../../libheccer.a main.c
pool2_LDADD = -L../.. -lheccer -lm
singlea_naf_DEPENDENCIES = ../../libheccer.a main.c
singlea_naf_LDADD = -L../.. -lheccer -lm
singlep_DEPENDENCIES = ../../libheccer.a main.c
singlep_LDADD = -L../.. -lheccer -lm
table_cap_DEPENDENCIES = ../../libheccer.a main.c
table_cap_LDADD = -L../.. -lheccer -lm
table_cat_DEPENDENCIES = ../../libheccer.a main.c
table_cat_LDADD = -L../.. -lheccer -lm
table_k2_DEPENDENCIES = ../../libheccer.a main.c
table_k2_LDADD = -L../.. -lheccer -lm
table_ka_DEPENDENCIES = ../../libheccer.a main.c
table_ka_LDADD = -L../.. -lheccer -lm
table_kc_DEPENDENCIES = ../../libheccer.a main.c
table_kc_LDADD = -L../.. -lheccer -lm
table_kdr_DEPENDENCIES = ../../libheccer.a main.c
table_kdr_LDADD = -L../.. -lheccer -lm
table_kh_DEPENDENCIES = ../../libheccer.a main.c
table_kh_LDADD = -L../.. -lheccer -lm
table_km_DEPENDENCIES = ../../libheccer.a main.c
table_km_LDADD = -L../.. -lheccer -lm
table_naf_DEPENDENCIES = ../../libheccer.a main.c
table_naf_LDADD = -L../.. -lheccer -lm
tensizesp_DEPENDENCIES = ../../libheccer.a main.c
tensizesp_LDADD = -L../.. -lheccer -lm
triplep_DEPENDENCIES = ../../libheccer.a main.c
triplep_LDADD = -L../.. -lheccer -lm
version_DEPENDENCIES = ../../libheccer.a
version_LDADD = -L../.. -lheccer -lm

#t automake does not allow to pass in arguments for tests ?

#check_SCRIPTS = $(srcdir)/../run

#TESTS = $(srcdir)/../run

#test: check

