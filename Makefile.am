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


SUBDIRS = \
	. \
	@HECCER_INTEGRATORS@ \
	glue \
	tests

AM_CFLAGS=-g3 -fPIC -include heccer/config.h -Wmissing-prototypes -Wmissing-declarations -ffloat-store -D__NO_MATH_INLINES

CFLAGS = -O0

lib_LIBRARIES = libheccer.a

libheccer_a_SOURCES = \
	addressing.c \
	compartment.c \
	heccer.c \
	indexers.c \
	intermediary.c \
	mathcomponent.c \
	mechanism.c \
	minimumdegree.c \
	output.c \
	random.c \
	table.c \
	vm.c

nobase_include_HEADERS = \
	heccer/addressing.h \
	heccer/callout.h \
	heccer/compartment.h \
	heccer/config.h \
	heccer/heccer.h \
	heccer/minimumdegree.h \
	heccer/indexers.h \
	heccer/intermediary.h \
	heccer/mathcomponent.h \
	heccer/mechanism.h \
	heccer/output.h \
	heccer/random.h \
	heccer/service.h \
	heccer/table.h \
	heccer/vm.h

heccertestdir=$(prefix)/heccer
nobase_dist_heccertest_DATA=@TEST_SPECIFICATION_FILES@

# the tests are copied overhere.
# the perl library is copied overhere.
#
# The variable EXTRA_DIST could also be used here.

dist-hook:
	find $(distdir) -name _Inline -exec chmod u+w -R \{\} \;
	$(RM) -fr `find $(distdir) -name _Inline`
	cp $(srcdir)/license.txt $(distdir)
	cp -R $(srcdir)/docs $(distdir)
	$(srcdir)/install-sh -d $(distdir)/tests
	$(srcdir)/install-sh -d $(distdir)/tests/html
#	$(srcdir)/install-sh -d $(distdir)/tests/html/algorithms
#	$(srcdir)/install-sh -d $(distdir)/tests/html/code
#	$(srcdir)/install-sh -d $(distdir)/tests/html/specifications
#	$(srcdir)/install-sh -d $(distdir)/tests/html/specifications/algorithms
#	$(srcdir)/install-sh -d $(distdir)/tests/html/specifications/code
	cp -dp $(srcdir)/tests/{run,run.ptkdb,command_extractor,command_extractor.ptkdb,tests_2_html,tests_2_html.ptkdb,tests.config} $(distdir)/tests
	cp -a $(srcdir)/tests.config $(distdir)
	cp -a $(srcdir)/tests/code/tests.config $(distdir)/tests/code/tests.config
	cp -a $(srcdir)/perl $(distdir)
#	cp -a $(srcdir)/hierarchy $(distdir)
#	rm -fr $(distdir)/hierarchy/output
	( cd $(distdir)/tests && chmod -R u+w . && ./tests_2_html )

#! this one breaks the distcheck, because automake makes dist dirs read-only
#	cd $(distdir)/tests && ./tests_2_html

test: check

html-upload-prepare:
	rm -fr html/htdocs/neurospaces_project/heccer/
	mkdir --parents html/htdocs/neurospaces_project/heccer
	mkdir --parents html/htdocs/neurospaces_project/heccer/html_source
	tar cfh - tests/html | ( cd html/htdocs/neurospaces_project/heccer && tar vxf - )
# remove swig generated large files.
	rm -fr ~/HTML/local_home/local_home/hugo/neurospaces_project/heccer/source/c/snapshots/0/glue
	( cd ~/HTML/local_home/local_home/hugo && tar cfh - Xrefs/heccer heccer neurospaces_project/heccer ) | ( cd html/htdocs/neurospaces_project/heccer/html_source && tar vxf - )

html-upload: html-upload-prepare
	scp -pr html/htdocs/* hcornelis@shell.sourceforge.net:/home/groups/n/ne/neurospaces/htdocs/

