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


SUBDIRS = . integrators glue tests

AM_CFLAGS=-gdwarf-2 -g3 -Wmissing-prototypes -Wmissing-declarations -ffloat-store -D__NO_MATH_INLINES

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
	table.c \
	vm.c

nobase_include_HEADERS = \
	heccer/addressing.h \
	heccer/callout.h \
	heccer/compartment.h \
	heccer/heccer.h \
	heccer/minimumdegree.h \
	heccer/indexers.h \
	heccer/intermediary.h \
	heccer/mathcomponent.h \
	heccer/mechanism.h \
	heccer/service.h \
	heccer/table.h \
	heccer/vm.h

# the tests are copied overhere.
# the perl library is copied overhere.
#
# The variable EXTRA_DIST could also be used here.

dist-hook:
	find $(distdir) -name _Inline -exec chmod u+w -R \{\} \;
	$(RM) -fr `find $(distdir) -name _Inline`
	cp $(srcdir)/license.txt $(distdir)
	cp -R $(srcdir)/docs $(distdir)
	test -d $(distdir)/tests || mkdir $(distdir)/tests
	test -d $(distdir)/tests/library || mkdir $(distdir)/tests/library
	cp -R $(srcdir)/tests/run $(distdir)/tests/run
	cp -R $(srcdir)/tests/tests_2_html $(distdir)/tests/tests_2_html
	cp -R $(srcdir)/tests/library $(distdir)/tests
	cp -R $(srcdir)/tests/code/tests.config $(distdir)/tests/code/tests.config
	cp -R $(srcdir)/tests/tests.config $(distdir)/tests/tests.config
	cp -R $(srcdir)/tests.config $(distdir)
	cp -R $(srcdir)/perl $(distdir)

#	cp -R $(srcdir)/hierarchy $(distdir)
#	cp -R $(srcdir)/library $(distdir)

#! this one breaks the distcheck, because automake makes dist dirs read-only
#	cd $(distdir)/tests && ./tests_2_html

test: check

html-upload-prepare:
	rm -fr html/htdocs/neurospaces_project/heccer/
	mkdir --parents html/htdocs/neurospaces_project/heccer
	mkdir --parents html/htdocs/neurospaces_project/heccer/html_source
	tar cfh - tests/html | ( cd html/htdocs/neurospaces_project/heccer && tar vxf - )
	( cd ~/HTML/local_home/local_home/hugo && tar cfh - Xrefs/heccer heccer neurospaces_project/heccer ) | ( cd html/htdocs/neurospaces_project/heccer/html_source && tar vxf - )

html-upload: html-upload-prepare
	scp -pr html/htdocs/* hcornelis@shell.sourceforge.net:/home/groups/n/ne/neurospaces/htdocs/

