#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([ace-radius-linux], [0.9.1], [alexagr@users.sourceforge.net])
AM_INIT_AUTOMAKE([-Wall -Werror foreign]) 
AC_CONFIG_SRCDIR([ace-radius/Radius.h])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_RANLIB 

AC_LANG_CPLUSPLUS

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([sys/ioctl.h sys/filio.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_HEADER_TIME

# check endedness
AC_C_BIGENDIAN

AC_MSG_CHECKING([if struct in_addr is a union])

AC_TRY_COMPILE([#include <netinet/in.h>], struct in_addr i; i._S_un._S_addr;, \
              AC_DEFINE(IN_ADDR_DEEPSTRUCT, [1], [Define to 1 if struct in_addr is a union]) \
              AC_MSG_RESULT(yes) , \
              AC_TRY_COMPILE([#include <sys/types.h>
#include <netinet/in.h>], struct in_addr i; i.S_un.S_addr;, \
                             AC_DEFINE(IN_ADDR_DEEPSTRUCT, [1], [Define to 1 if struct in_addr is a union]) \
                             AC_MSG_RESULT(yes) , \
                             AC_MSG_RESULT(no);))

AC_MSG_CHECKING([if socklen_t type exists])
AC_TRY_COMPILE([#include <sys/types.h>],
               [#include <sys/socket.h>],
               [socklen_t foo; foo = 1235;],
               [
                   AC_DEFINE(HAVE_SOCKLEN_T, [1], [Define to 1 if socklen_t type exists])
                   AC_MSG_RESULT(yes)
               ],
               [AC_MSG_RESULT(no)])


# Checks for library functions.
AC_PROG_GCC_TRADITIONAL
AC_FUNC_MEMCMP
AC_FUNC_SELECT_ARGTYPES
AC_CHECK_FUNC(gethostbyname, , AC_CHECK_LIB(nsl, gethostbyname))
AC_CHECK_FUNC(setsockopt, , AC_CHECK_LIB(socket, setsockopt))
AC_CHECK_FUNC(inet_aton, , AC_CHECK_LIB(resolv, inet_aton))

AC_CONFIG_FILES([Makefile
                 ace-radius/Makefile
                 test/Makefile])
AC_OUTPUT
