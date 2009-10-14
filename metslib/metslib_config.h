#ifndef METSLIB_CONFIG_H
#define METSLIB_CONFIG_H
#ifdef HAVE_CONFIG_H
#  include "config.h"
#  undef PACKAGE
#  undef PACKAGE_BUGREPORT
#  undef PACKAGE_NAME
#  undef PACKAGE_STRING
#  undef PACKAGE_TARNAME
#  undef PACKAGE_VERSION
#  undef VERSION
#else
#  if defined (WIN32)
#    define HAVE_UNORDERED_MAP 1
#    define TR1_MIXED_NAMESPACE 1
#  elif defined (__GXX_EXPERIMENTAL_CXX0X__)
#    define HAVE_UNORDERED_MAP 1
#  else
#    define HAVE_TR1_UNORDERED_MAP 1
#  endif
#endif
#endif
