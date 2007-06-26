dnl
dnl Heccer : a compartmental solver that implements efficient Crank-Nicolson
dnl integration for neuronal models.
dnl

dnl //////////////////////////////////////////////////////////////////////////
dnl 
dnl Heccer : testbed C implementation
dnl 
dnl Copyright (C) 2006-2007 Hugo Cornelis
dnl 
dnl functional ideas ..	Hugo Cornelis, hugo.cornelis@gmail.com
dnl 
dnl coding ............	Hugo Cornelis, hugo.cornelis@gmail.com
dnl 
dnl //////////////////////////////////////////////////////////////////////////

# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)

# $Format: "AC_INIT(${package}, ${label}, ${email})"$
AC_INIT(heccer, i64-5, hugo.cornelis@gmail.com)

AC_CONFIG_SRCDIR([compartment.c])
AC_CONFIG_HEADER([heccer/config.h])

dnl dnl all subdirs

dnl AC_CONFIG_SUBDIRS(tests/code glue)

# $Format: "AM_INIT_AUTOMAKE(${package}, ${label})"$
AM_INIT_AUTOMAKE(heccer, i64-5)

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB

# Checks for options

AC_ARG_ENABLE(random, AS_HELP_STRING([--with-random   use the builtin random number generator (recommended not to use the builtin)]) )
if test x"$with_random" == "xyes" ; then

    echo "USING THE BUILTIN RANDOM NUMBER GENERATOR (recommended not to use the builtin)"

    AC_DEFINE(RANDOM, (RAND_MAX * ran1(0)), [use the numerical recipes ran1() random number generator (not recommended)])

else

    echo "not using the builtin random number generator (recommended not to use the builtin)"

    AC_DEFINE(RANDOM, random(), [use the 4.3BSD random() random number generator])

fi

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

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([float.h limits.h locale.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

# Checks for library functions.
AC_CHECK_FUNCS([localeconv strchr])

# determine the test library to install

TEST_SPECIFICATION_FILES=`find tests/specifications -name "*.t" -printf "%p " && find tests/specifications/strings -name "*.txt" -printf "%p "`
AC_SUBST(TEST_SPECIFICATION_FILES)


AC_CONFIG_FILES([Makefile
                 glue/Makefile
                 glue/swig/perl/Makefile
                 integrators/Makefile
                 tests/Makefile
                 tests/code/Makefile
		 tests/glue/Makefile])
AC_OUTPUT

