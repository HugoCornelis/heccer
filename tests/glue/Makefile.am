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
	$(srcdir)/swig/perl/active/singlea-naf \
	$(srcdir)/swig/perl/c1c2p1 \
	$(srcdir)/swig/perl/c1c2p2 \
	$(srcdir)/swig/perl/callout1 \
	$(srcdir)/swig/perl/doublep \
	$(srcdir)/swig/perl/fork3p \
	$(srcdir)/swig/perl/fork4p1 \
	$(srcdir)/swig/perl/fork4p2 \
	$(srcdir)/swig/perl/fork4p3 \
	$(srcdir)/swig/perl/main \
	$(srcdir)/swig/perl/pool1 \
	$(srcdir)/swig/perl/pool1-feedback1 \
	$(srcdir)/swig/perl/pool1-feedback2 \
	$(srcdir)/swig/perl/pool2 \
	$(srcdir)/swig/perl/singlep \
	$(srcdir)/swig/perl/table-ka \
	$(srcdir)/swig/perl/table-naf \
	$(srcdir)/swig/perl/tensizesp \
	$(srcdir)/swig/perl/triplep


##! automake does not copy the test scripts to the distdir ?  I am doing
##! something terribly wrong here, but works (for now).

dist-hook:
	$(top_srcdir)/install-sh -d $(distdir)/swig/perl/active
	cp $(srcdir)/swig/perl/active/singlea-naf $(distdir)/swig/perl/active
	cp $(srcdir)/swig/perl/c1c2p1 $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/c1c2p2 $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/callout1 $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/doublep $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/fork3p $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/fork4p1 $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/fork4p2 $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/fork4p3 $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/main $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/pool1 $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/pool1-feedback1 $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/pool1-feedback2 $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/pool2 $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/singlep $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/table-ka $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/table-naf $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/tensizesp $(distdir)/swig/perl
	cp $(srcdir)/swig/perl/triplep $(distdir)/swig/perl
