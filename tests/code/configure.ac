dnl
dnl Heccer : a compartmental solver that implements efficient Crank-Nicolson
dnl integration for neuronal models.
dnl

dnl //////////////////////////////////////////////////////////////////////////
dnl 
dnl Heccer : testbed C implementation
dnl 
dnl Copyright (C) 2006 Hugo Cornelis
dnl 
dnl functional ideas ..	Hugo Cornelis, hugo.cornelis@gmail.com
dnl 
dnl coding ............	Hugo Cornelis, hugo.cornelis@gmail.com
dnl 
dnl //////////////////////////////////////////////////////////////////////////

# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)

# $Format: "AC_INIT(${package}, ${label}, ${email})"$
AC_INIT(heccer, passive-21, hugo\.cornelis\@gmail\.com)

AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADER([config.h])

# $Format: "AM_INIT_AUTOMAKE(${package}, ${label})"$
AM_INIT_AUTOMAKE(heccer, passive-21)

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB

# Checks for libraries.
AC_CHECK_LIB([heccer], [main])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT


