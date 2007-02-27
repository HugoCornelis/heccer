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
AC_INIT(heccer, integration-3, hugo\.cornelis\@gmail\.com)

AC_CONFIG_SRCDIR([compartment.c])
AC_CONFIG_HEADER([heccer/config.h])

dnl dnl all subdirs

dnl AC_CONFIG_SUBDIRS(tests/code glue)

# $Format: "AM_INIT_AUTOMAKE(${package}, ${label})"$
AM_INIT_AUTOMAKE(heccer, integration-3)

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB

# Checks for libraries.
AC_ARG_ENABLE(neurospaces, AS_HELP_STRING([--without-neurospaces   don't use neurospaces as modeling component]) )

if test x"$with_neurospaces" == "xno" ; then

    echo "NOT using Neurospaces as modeling component"

else

    echo "Using Neurospaces as modeling component"

    AC_DEFINE(HECCER_SOURCE_NEUROSPACES, 1, [use neurospaces as modeling component])

fi


# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([float.h limits.h locale.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

# Checks for library functions.
AC_CHECK_FUNCS([localeconv strchr])

AC_CONFIG_FILES([Makefile
                 glue/Makefile
                 glue/swig/perl/Makefile
                 integrators/Makefile
                 tests/Makefile
                 tests/code/Makefile
		 tests/glue/Makefile])
AC_OUTPUT

