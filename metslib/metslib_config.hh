#ifndef METSLIB_CONFIG_HH_
#define METSLIB_CONFIG_HH_
#ifdef HAVE_CONFIG_H
#  ifndef METSLIB_TESTING
#    include "metslib_ah.hh"
#else
#    include "metslib-config.h"
#  endif
#else
#  if defined (WIN32)
#    define METSLIB_HAVE_UNORDERED_MAP 1
#    define METSLIB_TR1_MIXED_NAMESPACE 1
#  elif defined (__GXX_EXPERIMENTAL_CXX0X__)
#    define METSLIB_HAVE_UNORDERED_MAP 1
#  else
#    define METSLIB_HAVE_TR1_UNORDERED_MAP 1
#  endif
#endif
#endif
