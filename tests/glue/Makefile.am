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


#t automake does not allow to pass in arguments for tests ?

#check_SCRIPTS = $(srcdir)/../run

#TESTS = $(srcdir)/../run

#test: check

noinst_SCRIPTS = \
	$(srcdir)/swig/perl/c1c2p1 \
	$(srcdir)/swig/perl/c1c2p2 \
	$(srcdir)/swig/perl/callout1 \
	$(srcdir)/swig/perl/doublep \
	$(srcdir)/swig/perl/fork3p \
	$(srcdir)/swig/perl/fork4p1 \
	$(srcdir)/swig/perl/fork4p2 \
	$(srcdir)/swig/perl/fork4p3 \
	$(srcdir)/swig/perl/singlep \
	$(srcdir)/swig/perl/tensizesp \
	$(srcdir)/swig/perl/triplep

##! automake does not copy the test scripts to the distdir ?  I am doing
##! something terribly wrong here, but works (for now).

dist-hook:
	$(top_srcdir)/install-sh -d $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/c1c2p1 $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/c1c2p2 $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/callout1 $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/doublep $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/fork3p $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/fork4p1 $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/fork4p2 $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/fork4p3 $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/singlep $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/tensizesp $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/triplep $(distdir)/swig/perl


#! these copy to the top srcdir, not top_builddir

#	$(top_srcdir)/install-sh -d $(top_builddir)/swig/perl
#	cp $(srcdir)/swig/perl/c1c2p1 $(top_builddir)/swig/perl
#	cp $(srcdir)/swig/perl/c1c2p2 $(top_builddir)/swig/perl
#	cp $(srcdir)/swig/perl/callout1 $(top_builddir)/swig/perl
#	cp $(srcdir)/swig/perl/doublep $(top_builddir)/swig/perl
#	cp $(srcdir)/swig/perl/fork3p $(top_builddir)/swig/perl
#	cp $(srcdir)/swig/perl/fork4p1 $(top_builddir)/swig/perl
#	cp $(srcdir)/swig/perl/fork4p2 $(top_builddir)/swig/perl
#	cp $(srcdir)/swig/perl/fork4p3 $(top_builddir)/swig/perl
#	cp $(srcdir)/swig/perl/singlep $(top_builddir)/swig/perl
#	cp $(srcdir)/swig/perl/tensizesp $(top_builddir)/swig/perl
#	cp $(srcdir)/swig/perl/triplep $(top_builddir)/swig/perl
