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


AM_CFLAGS=-g3 -fPIC -Wmissing-prototypes -Wmissing-declarations -ffloat-store -I$(srcdir)/.. -I$(top_srcdir) -include heccer/config.h -DPRE_PROTO_TRAVERSAL -D__NO_MATH_INLINES

# ease debugging

CFLAGS=-O0

check_PROGRAMS = \
	addressing-aggregator1 \
	addressing-current \
	addressing-purk-test-segment \
	addressing-synchan \
	aggregator-kc \
	aggregator-kc-feedback \
	c1c2p1 \
	c1c2p2 \
	callout1 \
	calloutInjector \
	channel1-nernst1 \
	channel2-nernst1 \
	channel2-nernst2 \
	check-compartment \
	doublea-aggregator \
	doublep \
	fork3p \
	fork4p1 \
	fork4p2 \
	fork4p3 \
	hh1 \
	perfectclamp-passive1 \
	perfectclamp-passive10 \
	perfectclamp-passive10-2 \
	pool1 \
	pool1-contributors2 \
	pool1-feedback1 \
	pool1-feedback2 \
	pool1-nernst \
	pool2 \
	pulsegen-extgate \
	pulsegen-exttrig \
	pulsegen-freerun \
	serialization-c1c2p1 \
	serialization-c1c2p2 \
	serialization-channel2-nernst2 \
	serialization-doublep \
	serialization-fork3p \
	serialization-fork4p1 \
	serialization-fork4p2 \
	serialization-fork4p3 \
	serialization-pool1-feedback2 \
	serialization-pool2 \
	serialization-singlea-naf \
	serialization-singlep \
	serialization-tensizesp \
	serialization-triplep \
	singlea-naf \
	singlea-naf-current \
	singlea-naf2-aggregator \
	singlep \
	spiker1 \
	spiker2 \
	spiker3 \
	springmass1 \
	springmass2 \
	springmass3 \
	springmass4 \
	table-cap \
	table-cat \
	table-dual-kdr \
	table-dual-km \
	table-k2 \
	table-ka \
	table-kc \
	table-kdr \
	table-kdr2 \
	table-kh \
	table-km \
	table-naf \
	table-nap \
	tensizesp \
	triplep \
	vclamp-passive \
	vclamp-sodium \
	version

noinst_HEADERS = \
	main-serializer.c \
	main-serializer.h \
	main.c \
	main.h

addressing_aggregator1_DEPENDENCIES = ../../libheccer.a main.c
addressing_aggregator1_LDADD = -L../.. -lheccer -lm
addressing_current_DEPENDENCIES = ../../libheccer.a main.c
addressing_current_LDADD = -L../.. -lheccer -lexperiment -lm
addressing_purk_test_segment_DEPENDENCIES = ../../libheccer.a main.c
addressing_purk_test_segment_LDADD = -L../.. -lheccer -lm
addressing_synchan_DEPENDENCIES = ../../libheccer.a main.c
addressing_synchan_LDADD = -L../.. -lheccer -lexperiment -lm
aggregator_kc_DEPENDENCIES = ../../libheccer.a main.c
aggregator_kc_LDADD = -L../.. -lheccer -lm
aggregator_kc_feedback_DEPENDENCIES = ../../libheccer.a main.c
aggregator_kc_feedback_LDADD = -L../.. -lheccer -lm
c1c2p1_DEPENDENCIES = ../../libheccer.a main.c
c1c2p1_LDADD = -L../.. -lheccer -lm
c1c2p2_DEPENDENCIES = ../../libheccer.a main.c
c1c2p2_LDADD = -L../.. -lheccer -lm
callout1_DEPENDENCIES = ../../libheccer.a main.c
callout1_LDADD = -L../.. -lheccer -lm
calloutInjector_DEPENDENCIES = ../../libheccer.a main.c
calloutInjector_LDADD = -L../.. -lheccer -lm
channel1_nernst1_DEPENDENCIES = ../../libheccer.a main.c
channel1_nernst1_LDADD = -L../.. -lheccer -lm
channel2_nernst1_DEPENDENCIES = ../../libheccer.a main.c
channel2_nernst1_LDADD = -L../.. -lheccer -lm
channel2_nernst2_DEPENDENCIES = ../../libheccer.a main.c
channel2_nernst2_LDADD = -L../.. -lheccer -lm
check_compartment_DEPENDENCIES = ../../libheccer.a main.c
check_compartment_LDADD = -L../.. -lheccer -lm
doublea_aggregator_DEPENDENCIES = ../../libheccer.a main.c
doublea_aggregator_LDADD = -L../.. -lheccer -lm
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
hh1_DEPENDENCIES = ../../libheccer.a main.c
hh1_LDADD = -L../.. -lheccer -lexperiment -lm
perfectclamp_passive1_DEPENDENCIES = ../../libheccer.a main.c
perfectclamp_passive1_LDADD = -L../.. -lheccer -lexperiment -lm
perfectclamp_passive10_2_DEPENDENCIES = ../../libheccer.a main.c
perfectclamp_passive10_2_LDADD = -L../.. -lheccer -lexperiment -lm
perfectclamp_passive10_DEPENDENCIES = ../../libheccer.a main.c
perfectclamp_passive10_LDADD = -L../.. -lheccer -lexperiment -lm
pool1_DEPENDENCIES = ../../libheccer.a main.c
pool1_LDADD = -L../.. -lheccer -lm
pool1_contributors2_DEPENDENCIES = ../../libheccer.a main.c
pool1_contributors2_LDADD = -L../.. -lheccer -lm
pool1_feedback1_DEPENDENCIES = ../../libheccer.a main.c
pool1_feedback1_LDADD = -L../.. -lheccer -lm
pool1_feedback2_DEPENDENCIES = ../../libheccer.a main.c
pool1_feedback2_LDADD = -L../.. -lheccer -lm
pool1_nernst_DEPENDENCIES = ../../libheccer.a main.c
pool1_nernst_LDADD = -L../.. -lheccer -lm
pool2_DEPENDENCIES = ../../libheccer.a main.c
pool2_LDADD = -L../.. -lheccer -lm
pulsegen_freerun_DEPENDENCIES = ../../libheccer.a main.c
pulsegen_freerun_LDADD = -L../.. -lheccer -lexperiment -lm
pulsegen_exttrig_DEPENDENCIES = ../../libheccer.a main.c
pulsegen_exttrig_LDADD = -L../.. -lheccer -lexperiment -lm
pulsegen_extgate_DEPENDENCIES = ../../libheccer.a main.c
pulsegen_extgate_LDADD = -L../.. -lheccer -lexperiment -lm
serialization_c1c2p1_DEPENDENCIES = ../../libheccer.a main.c main-serializer.c
serialization_c1c2p1_LDADD = -L../.. -lheccer -lm
serialization_c1c2p2_DEPENDENCIES = ../../libheccer.a main.c main-serializer.c
serialization_c1c2p2_LDADD = -L../.. -lheccer -lm
serialization_channel2_nernst2_DEPENDENCIES = ../../libheccer.a main.c main-serializer.c
serialization_channel2_nernst2_LDADD = -L../.. -lheccer -lm
serialization_doublep_DEPENDENCIES = ../../libheccer.a main.c main-serializer.c
serialization_doublep_LDADD = -L../.. -lheccer -lm
serialization_fork3p_DEPENDENCIES = ../../libheccer.a main.c main-serializer.c
serialization_fork3p_LDADD = -L../.. -lheccer -lm
serialization_fork4p1_DEPENDENCIES = ../../libheccer.a main.c main-serializer.c
serialization_fork4p1_LDADD = -L../.. -lheccer -lm
serialization_fork4p2_DEPENDENCIES = ../../libheccer.a main.c main-serializer.c
serialization_fork4p2_LDADD = -L../.. -lheccer -lm
serialization_fork4p3_DEPENDENCIES = ../../libheccer.a main.c main-serializer.c
serialization_fork4p3_LDADD = -L../.. -lheccer -lm
serialization_pool1_feedback2_DEPENDENCIES = ../../libheccer.a main.c main-serializer.c
serialization_pool1_feedback2_LDADD = -L../.. -lheccer -lm
serialization_pool2_DEPENDENCIES = ../../libheccer.a main.c main-serializer.c
serialization_pool2_LDADD = -L../.. -lheccer -lm
serialization_singlea_naf_DEPENDENCIES = ../../libheccer.a main.c main-serializer.c
serialization_singlea_naf_LDADD = -L../.. -lheccer -lm
serialization_singlep_DEPENDENCIES = ../../libheccer.a main.c main-serializer.c
serialization_singlep_LDADD = -L../.. -lheccer -lm
serialization_tensizesp_DEPENDENCIES = ../../libheccer.a main.c main-serializer.c
serialization_tensizesp_LDADD = -L../.. -lheccer -lm
serialization_triplep_DEPENDENCIES = ../../libheccer.a main.c main-serializer.c
serialization_triplep_LDADD = -L../.. -lheccer -lm
singlea_naf2_aggregator_DEPENDENCIES = ../../libheccer.a main.c
singlea_naf2_aggregator_LDADD = -L../.. -lheccer -lm
singlea_naf_DEPENDENCIES = ../../libheccer.a main.c
singlea_naf_LDADD = -L../.. -lheccer -lm
singlea_naf_current_DEPENDENCIES = ../../libheccer.a main.c
singlea_naf_current_LDADD = -L../.. -lheccer -lm
singlep_DEPENDENCIES = ../../libheccer.a main.c
singlep_LDADD = -L../.. -lheccer -lm
spiker1_DEPENDENCIES = ../../libheccer.a main.c
spiker1_LDADD = -L../.. -lheccer -lexperiment -lm
spiker2_DEPENDENCIES = ../../libheccer.a main.c
spiker2_LDADD = -L../.. -lheccer -lexperiment -lm
spiker3_DEPENDENCIES = ../../libheccer.a main.c
spiker3_LDADD = -L../.. -lheccer -lexperiment -lm
springmass1_DEPENDENCIES = ../../libheccer.a main.c
springmass1_LDADD = -L../.. -lheccer -lexperiment -lm
springmass2_DEPENDENCIES = ../../libheccer.a main.c
springmass2_LDADD = -L../.. -lheccer -lexperiment -lm
springmass3_DEPENDENCIES = ../../libheccer.a main.c
springmass3_LDADD = -L../.. -lheccer -lexperiment -lm
springmass4_DEPENDENCIES = ../../libheccer.a main.c
springmass4_LDADD = -L../.. -lheccer -lexperiment -lm
table_cap_DEPENDENCIES = ../../libheccer.a main.c
table_cap_LDADD = -L../.. -lheccer -lm
table_cat_DEPENDENCIES = ../../libheccer.a main.c
table_cat_LDADD = -L../.. -lheccer -lm
table_dual_kdr_DEPENDENCIES = ../../libheccer.a main.c
table_dual_kdr_LDADD = -L../.. -lheccer -lm
table_dual_km_DEPENDENCIES = ../../libheccer.a main.c
table_dual_km_LDADD = -L../.. -lheccer -lm
table_k2_DEPENDENCIES = ../../libheccer.a main.c
table_k2_LDADD = -L../.. -lheccer -lm
table_ka_DEPENDENCIES = ../../libheccer.a main.c
table_ka_LDADD = -L../.. -lheccer -lm
table_kc_DEPENDENCIES = ../../libheccer.a main.c
table_kc_LDADD = -L../.. -lheccer -lm
table_kdr_DEPENDENCIES = ../../libheccer.a main.c
table_kdr_LDADD = -L../.. -lheccer -lm
table_kdr2_DEPENDENCIES = ../../libheccer.a main.c
table_kdr2_LDADD = -L../.. -lheccer -lm
table_kh_DEPENDENCIES = ../../libheccer.a main.c
table_kh_LDADD = -L../.. -lheccer -lm
table_km_DEPENDENCIES = ../../libheccer.a main.c
table_km_LDADD = -L../.. -lheccer -lm
table_naf_DEPENDENCIES = ../../libheccer.a main.c
table_naf_LDADD = -L../.. -lheccer -lm
table_nap_DEPENDENCIES = ../../libheccer.a main.c
table_nap_LDADD = -L../.. -lheccer -lm
tensizesp_DEPENDENCIES = ../../libheccer.a main.c
tensizesp_LDADD = -L../.. -lheccer -lm
triplep_DEPENDENCIES = ../../libheccer.a main.c
triplep_LDADD = -L../.. -lheccer -lm
vclamp_passive_DEPENDENCIES = ../../libheccer.a
vclamp_passive_LDADD = -L../.. -lheccer -lexperiment -lm
vclamp_sodium_DEPENDENCIES = ../../libheccer.a
vclamp_sodium_LDADD = -L../.. -lheccer -lexperiment -lm
version_DEPENDENCIES = ../../libheccer.a
version_LDADD = -L../.. -lheccer -lm

#t automake does not allow to pass in arguments for tests ?

#check_SCRIPTS = $(srcdir)/../neurospaces_harness

#TESTS = $(srcdir)/../neurospaces_harness

#test: check

