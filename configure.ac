#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([xhidecursor], [0.1.1])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([xhidecursor.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
PKG_CHECK_MODULES(XHIDECURSOR, x11 xfixes xi)

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for library functions.
AC_CHECK_FUNCS([memset select])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
