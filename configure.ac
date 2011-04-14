dnl --------------------------------
dnl Initialization macros.
dnl --------------------------------

AC_INIT([metslib], [0.5.2], [mirko.maischberger@gmail.com])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([config])

dnl -----------------------------------------------
dnl Package name and version number (user defined)
dnl -----------------------------------------------

GENERIC_LIBRARY_NAME=metslib

#release versioning
GENERIC_MAJOR_VERSION=0
GENERIC_MINOR_VERSION=5
GENERIC_MICRO_VERSION=2

#API version (often = GENERIC_MAJOR_VERSION.GENERIC_MINOR_VERSION)
GENERIC_API_VERSION=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION
AC_SUBST(GENERIC_API_VERSION)

# shared library versioning
# =========================
#
# libtool library versions are described by three integers:
# current
#    The most recent interface number that this library implements.
# revision
#    The implementation number of the current interface.
# age
#    The difference between the newest and oldest interfaces that this
#    library implements. In other words, the library implements all
#    the interface numbers in the range from number current - age to
#    current.
#
# If two libraries have identical current and age numbers, then the
# dynamic linker chooses the library with the greater revision number.
#
GENERIC_LIBRARY_VERSION=5:2:0
#                       | | |
#                +------+ | +---+
#                |        |     |
#             current:revision:age
#                |        |     |
#                |        |     +- increment if interfaces have been added
#                |        |        set to zero if interfaces have been removed
#                                  or changed
#                |        +- increment if source code has changed
#                |           set to zero if current is incremented
#                +- increment if interfaces have been added, removed or changed


dnl --------------------------------
dnl Package name and version number
dnl --------------------------------

AC_SUBST(GENERIC_LIBRARY_VERSION)

PACKAGE=$GENERIC_LIBRARY_NAME
AC_SUBST(GENERIC_LIBRARY_NAME)

GENERIC_VERSION=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION.$GENERIC_MICRO_VERSION
GENERIC_RELEASE=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION
AC_SUBST(GENERIC_RELEASE)
AC_SUBST(GENERIC_VERSION)

VERSION=$GENERIC_VERSION

AM_INIT_AUTOMAKE($PACKAGE, $VERSION, [mirko.maischberger@gmail.com])

AC_CONFIG_HEADERS([config.h])
AX_PREFIX_CONFIG_H([metslib/metslib_ah.hh])

dnl -----------------------------------------------
dnl Checks for programs.
dnl -----------------------------------------------

PKG_PROG_PKG_CONFIG([0.9])
AC_PROG_CXX
# AM_PROG_LIBTOOL
AM_SANITY_CHECK

AC_LANG_CPLUSPLUS


dnl ---------------------------------------------
dnl Check for TR1 headers
dnl ---------------------------------------------

AC_CHECK_HEADERS([tr1/unordered_map unordered_map],
                 [],
                 [])

if test $ac_cv_header_tr1_unordered_map = no; then
   if test $ac_cv_header_unordered_map = no; then
      AC_MSG_FAILURE([Unable to find <tr1/unordered_map> nor <unordered_map>, please use a recent C++ compiler supporting TR1 extension.])
    fi
fi

AC_TRY_COMPILE([#include <unordered_map>],
               [namespace std::tr1::unordered_map;],
	       [AC_DEFINE(TR1_MIXED_NAMESPACE, [], [Description])],
               [])
dnl ---------------------------------------------
dnl Add option to turn off optimizations
dnl ---------------------------------------------

release_version=yes
AC_ARG_ENABLE(debug, [  --enable-debug        Turn off optimizations.  ], \
 if test "$enableval" = "yes"; then \
        echo "disabling optimizations." 
	release_version=no
fi;)	

if test $release_version = no; then 
  CFLAGS=`echo $CFLAGS | sed s/-O2//`
  CXXFLAGS=`echo $CXXFLAGS | sed s/-O2//`
  CPPFLAGS=`echo $CPPFLAGS | sed s/-O2//`
fi

dnl ---------------------------------------------
dnl g++ specific options
dnl ---------------------------------------------

if test $CXX = g++; then
  CXXFLAGS="$CXXFLAGS -Wall -Weffc++"
  if test $release_version = yes; then
    CXXFLAGS="$CXXFLAGS -O3"
  fi
fi

dnl -----------------------------------------------
dnl Generates Makefile's, configuration files and scripts
dnl -----------------------------------------------

SHAVE_INIT
AC_CONFIG_FILES([shave shave-libtool])
AC_OUTPUT(Makefile \
          metslib.pc \
          metslib/Makefile \
          doxydoc/Makefile \
	  test/Makefile \
)
