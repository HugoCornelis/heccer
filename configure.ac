dnl
dnl Heccer : a compartmental solver that implements efficient Crank-Nicolson
dnl integration for neuronal models.
dnl

dnl //////////////////////////////////////////////////////////////////////////
dnl 
dnl Heccer : testbed C implementation
dnl 
dnl Copyright (C) 2006-2008 Hugo Cornelis
dnl 
dnl functional ideas ..	Hugo Cornelis, hugo.cornelis@gmail.com
dnl 
dnl coding ............	Hugo Cornelis, hugo.cornelis@gmail.com
dnl 
dnl //////////////////////////////////////////////////////////////////////////

# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)

# $Format: "AC_INIT(${package}, ${label}, ${email})"$
AC_INIT(heccer, python-5, hugo.cornelis@gmail.com)

dnl Obtain operating system information.
AC_CANONICAL_TARGET

AC_CONFIG_SRCDIR([compartment.c])
AC_CONFIG_HEADER([heccer/config.h])

dnl dnl all subdirs

dnl AC_CONFIG_SUBDIRS(tests/code glue)

# $Format: "AM_INIT_AUTOMAKE(${package}, ${label})"$
AM_INIT_AUTOMAKE(heccer, python-5)


# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB

AC_PATH_PROGS(DOXYGEN,doxygen)

dnl Check for Python and it's headers
AM_PATH_PYTHON(,[],[
   echo "Python is not installed."
   exit -1
])


case $PYTHON_PREFIX in
  *)   
    PYTHON_PREFIX=`echo $PYTHON | sed -e "s,[[^/]]*$,,;s,/$,,;s,^$,.,"`
    PYTHON_PREFIX=`echo $PYTHON_PREFIX | sed -e "s,[[^/]]*$,,;s,/$,,;s,^$,.,"`
    PYTHONHOME=$PYTHON_PREFIX
    AC_SUBST(PYTHON_PREFIX)
    AC_SUBST(PYTHONHOME)

    AC_MSG_CHECKING([Python header location])
    PYTHON_HEADERS='$(PYTHON_PREFIX)/include/python$(PYTHON_VERSION)'
    AC_SUBST(PYTHON_HEADERS)
    AC_MSG_RESULT([$PYTHON_PREFIX/include/python$PYTHON_VERSION])

    PYTHON_EXE='$(PYTHON_PREFIX)/bin/python'
    AC_SUBST(PYTHON_EXE)
  ;;
esac

# Checks for options

AC_ARG_ENABLE(random, AS_HELP_STRING([--with-random   use the builtin random number generator (recommended not to use the builtin)]) )
if test x"$with_random" == "xyes" ; then

    echo "USING THE BUILTIN RANDOM NUMBER GENERATOR (recommended not to use the builtin)"

    AC_DEFINE(RANDOM, (RAND_MAX * ran1(0)), [use the numerical recipes ran1() random number generator (not recommended)])

else

    echo "not using the builtin random number generator (recommended not to use the builtin)"

    AC_DEFINE(RANDOM, random(), [use the 4.3BSD random() random number generator])

fi

AC_ARG_ENABLE(sglib, AS_HELP_STRING([--with-sglib   use the sglib based event queue]) )
if test x"$with_sglib" == "xyes" ; then

    echo "using the sglib based event queue"

    AC_DEFINE(USE_SGLIB, 1, [use the sglib based event queue])

else

    echo "not using the sglib based event queue"

    AC_DEFINE(USE_SGLIB, 0, [use the builtin event queue])

fi

# integrators: integrate with model-container of neurospaces ?

AC_ARG_ENABLE(neurospaces, AS_HELP_STRING([--without-neurospaces   don't use neurospaces as modeling component]) )

HECCER_INTEGRATORS=

if test x"$with_neurospaces" == "xno" ; then

    echo "NOT using Neurospaces as modeling component"

else

    echo "Using Neurospaces as modeling component"

    AC_DEFINE(HECCER_SOURCE_NEUROSPACES, 1, [use neurospaces as modeling component])

    HECCER_INTEGRATORS="integrators"
fi

AC_SUBST(HECCER_INTEGRATORS)

# enable source typing to compute aggregate currents ?

AC_ARG_ENABLE(source-typing, AS_HELP_STRING([--without-source-typing   don't use model source typing for calculation of aggregate currents]) )

if test x"$with_source_typing" == "xno" ; then

    echo "NOT using source typing"

else

    echo "Using source typing"

    AC_DEFINE(HECCER_SOURCE_TYPING, 1, [use model source typing])
fi

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([float.h limits.h locale.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

# Checks for library functions.
AC_CHECK_FUNCS([localeconv strchr])


dnl This does macro substitutions for certain opertaing systems and 
dnl architectures 
AC_MSG_CHECKING([OS specifics...])
AC_MSG_RESULT([Host is running $host_os.])
dnl {{{
case "$host_os" in
  darwin*)
    #
    # These are settings specific to MAC OS X.
    #
    dnl {{{{
    AC_MSG_CHECKING([Using libtool for MAC OS X.])
    AR=libtool
    ARFLAGS='-static -c -o'
    AC_SUBST(AR)
    AC_SUBST(ARFLAGS)
    AC_MSG_RESULT([$AR $ARFLAGS])

    PERLLIB_EXTENSION='dylib'
    AC_SUBST(PERLLIB_EXTENSION)

    SWIGCOMPILELINKSFORPERL='-I/usr/local/neurospaces/instrumentor \
	-I$(srcdir)/../../.. \
	-I$(top_builddir) \
	-ffloat-store \
	-I../../.. \
	-include heccer/config.h \
	-g \
	-O0 \
	-dynamic \
	-fPIC \
	`perl -MExtUtils::Embed -e ccopts | perl -pe 's/\-arch\s\S+\s//g'`'
    AC_SUBST(SWIGCOMPILELINKSFORPERL)

    SWIGCOMPILECOMMAND_PERL='gcc \
        $(SWIGCOMPILELINKSFORPERL) \
        -c swiggable_heccer_wrap.c'
    AC_SUBST(SWIGCOMPILECOMMAND_PERL)

 

    SWIGLDLINKSFORPERL='-L../../.. \
	-lheccer -L../../../integrators \
	-lhneurospaces \
	-L/usr/local/lib/model-container \
	-lneurospacesread \
	-L/usr/local/lib/neurospaces/algorithms/symbol \
	-lsymbol_algorithms \
	-lncurses -lreadline \
	-bundle \
	-undefined suppress \
	-flat_namespace'
    AC_SUBST(SWIGLDLINKSFORPERL)

    SWIGLINKCOMMAND_PERL='ld \
	$(SWIGLDLINKSFORPERL) \
	-o SwiggableHeccer.$(PERLLIB_EXTENSION) \
	swiggable_heccer_wrap.o'
    AC_SUBST(SWIGLINKCOMMAND_PERL)




    PYTHONLIB_EXTENSION='dylib'
    AC_SUBST(PYHONLIB_EXTENSION)

    SWIGCOMPILELINKSFORPYTHON='-I$(PYTHON_HEADERS) \
	-I/usr/local/neurospaces/instrumentor \
	-I.../../.. \
	-I./../../.. \
	-I.../../../hierarchy/output/symbols \
	-I./../../../hierarchy/output/symbols/'
    AC_SUBST(SWIGCOMPILELINKSFORPYTHON)

    SWIGCOMPILECOMMAND_PYTHON='gcc \
        $(SWIGCOMPILELINKSFORPYTHON) \
        -c swiggable_heccer_wrap.c'
    AC_SUBST(SWIGCOMPILECOMMAND_PYTHON)

    SWIGLDLINKSFORPYTHON='-L$(PYTHON_HEADERS) \
        -framework Python \
        -flat_namespace \
        -undefined suppress \
	-bundle \
	-bundle_loader $(PYTHON_EXE)'
    AC_SUBST(SWIGLDLINKSFORPYTHON)

    SWIGLINKCOMMAND_PYTHON='ld \
	$(SWIGLDLINKSFORPYTHON) \
	-o _SwiggableHeccer.$(PERLLIB_EXTENSION) \
	swiggable_heccer_wrap.o'
    AC_SUBST(SWIGLINKCOMMAND_PYTHON)

    AC_MSG_RESULT([done.])
    dnl }}} end MAC OS X settings
    ;;




  *)
  
    dnl {{{
    AR='ar'
    ARFLAGS='cru'
    AC_SUBST(AR)
    AC_SUBST(ARFLAGS)
    AC_MSG_CHECKING([ranlib invocation ])
    AC_MSG_RESULT([$AR $ARFLAGS])

    PERLLIB_EXTENSION='so'
    AC_SUBST(PERLLIB_EXTENSION)


    SWIGCOMPILELINKSFORPERL='-I/usr/local/neurospaces/instrumentor -I$(srcdir)/../../.. -I$(top_builddir) -ffloat-store -I../../.. -include heccer/config.h -g -O0 -fPIC `perl -MExtUtils::Embed -e ccopts`'
    AC_SUBST(SWIGCOMPILELINKSFORPERL)

    SWIGCOMPILECOMMAND_PERL='gcc $(SWIGCOMPILELINKSFORPERL) -c swiggable_heccer_wrap.c'
    AC_SUBST(SWIGCOMPILECOMMAND_PERL)


    SWIGLDLINKSFORPERL='-g -shared swiggable_heccer_wrap.o -L../../.. -lheccer -L../../../integrators -lhneurospaces -L/usr/local/lib/model-container -lneurospacesread -L/usr/local/lib/neurospaces/algorithms/symbol -lsymbol_algorithms -lncurses -lreadline -lhistory -fPIC'
    AC_SUBST(SWIGLDLINKSFORPERL)

    SWIGLINKCOMMAND_PERL='gcc $(SWIGLDLINKSFORPERL) -o SwiggableHeccer.$(PERLLIB_EXTENSION)'
    AC_SUBST(SWIGLINKCOMMAND_PERL)


    PYTHONLIB_EXTENSION='so'
    AC_SUBST(PYTHONLIB_EXTENSION)

    SWIGCOMPILELINKSFORPYTHON='-g -DPRE_PROTO_TRAVERSAL -I$(PYTHON_HEADERS) -I/usr/local/neurospaces/instrumentor -I$(builddir)../../.. -I$(srcdir)/../../.. -I$(builddir)../../../hierarchy/output/symbols -I$(srcdir)/../../../hierarchy/output/symbols/ -fPIC -Xlinker -export-dynamic'
    AC_SUBST(SWIGCOMPILELINKSFORPYTHON)

   SWIGCOMPILECOMMAND_PYTHON='gcc $(SWIGCOMPILELINKSFORPYTHON) -c swiggable_heccer_wrap.c'
   AC_SUBST(SWIGCOMPILECOMMAND_PYTHON)

    SWIGLDLINKSFORPYTHON='-g -shared swiggable_heccer_wrap.o -L../../.. -lheccer -L../../../integrators -lhneurospaces -L/usr/local/lib/model-container -lneurospacesread -L/usr/local/lib/neurospaces/algorithms/symbol -lsymbol_algorithms -lncurses -lreadline -lhistory -fPIC -Xlinker -export-dynamic'
    AC_SUBST(SWIGLDLINKSFORPYTHON)

    SWIGLINKCOMMAND_PYTHON='gcc $(SWIGLDLINKSFORPYTHON) -o _SwiggableHeccer.$(PYTHONLIB_EXTENSION)'
    AC_SUBST(SWIGLINKCOMMAND_PYTHON)
    dnl }}} End of General Settings

  ;;
esac
dnl }}}



# determine the test library to install

TEST_SPECIFICATION_FILES=`/bin/echo -n "tests/introduction.html " && find tests/specifications -name "*.t" | perl -pe 's/\n/ /g' && find tests/specifications/strings -name "*.txt" | perl -pe 's/\n/ /g' && find tests/data -name "*.yml" | perl -pe 's/\n/ /g'`
AC_SUBST(TEST_SPECIFICATION_FILES)


AC_CONFIG_FILES([Makefile
                 glue/Makefile
                 glue/swig/perl/Makefile
                 glue/swig/python/Makefile
                 integrators/Makefile
                 tests/Makefile
                 tests/code/Makefile
                 tests/genesis/Makefile
		 tests/glue/Makefile])
AC_OUTPUT

