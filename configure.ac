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
AC_INIT(heccer, active-3, hugo\.cornelis\@gmail\.com)

AC_CONFIG_SRCDIR([compartment.c])
AC_CONFIG_HEADER([config.h])

dnl dnl all subdirs

dnl AC_CONFIG_SUBDIRS(tests/code glue)

# $Format: "AM_INIT_AUTOMAKE(${package}, ${label})"$
AM_INIT_AUTOMAKE(heccer, active-3)

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB

# Checks for libraries.

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
                 tests/code/Makefile])
AC_OUTPUT

dnl # Checks for library functions.

dnl AC_CONFIG_FILES([Makefile])
dnl AC_OUTPUT
