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


# glue can only be built if the tests work, explains the order.

SUBDIRS = . tests/code glue

AM_CFLAGS=-gdwarf-2 -g3 -Wmissing-prototypes -Wmissing-declarations

CFLAGS = -O0

noinst_LIBRARIES = libheccer.a

libheccer_a_SOURCES = \
	addressing.c \
	compartment.c \
	heccer.c \
	indexers.c \
	intermediary.c \
	mechanism.c \
	minimumdegree.c \
	vm.c

noinst_HEADERS = \
	addressing.h \
	callout.h \
	compartment.h \
	heccer.h \
	minimumdegree.h \
	indexers.h \
	intermediary.h \
	mathcomponent.h \
	mechanism.h \
	vm.h

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
	cp -R $(srcdir)/tests/library $(distdir)/tests/library
	cp -R $(srcdir)/tests/code/tests.config $(distdir)/tests/code/tests.config
	cp -R $(srcdir)/tests.config $(distdir)
	cp -R $(srcdir)/perl $(distdir)

#	cp -R $(srcdir)/hierarchy $(distdir)
#	cp -R $(srcdir)/library $(distdir)

#! this one breaks the distcheck, because automake makes dist dirs read-only
#	cd $(distdir)/tests && ./tests_2_html

test: check

