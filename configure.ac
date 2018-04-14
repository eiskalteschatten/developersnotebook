AC_PREREQ([2.69])

AC_INIT([developersnotebooks], [0.1], [alex@alexseifert.com])
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_SRCDIR([src/main.cpp])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CXX

AX_BOOST_BASE([1.66],, AC_MSG_ERROR([Boost 1.66 or greater was not found on your system]))
AX_BOOST_SYSTEM
AX_BOOST_FILESYSTEM

PKG_CHECK_MODULES([DEPENDENCIES], [gtk+-3.0 >= 3.22.0 sqlite3 >= 3.17])

AC_CONFIG_FILES([Makefile src/Makefile])

AC_OUTPUT
