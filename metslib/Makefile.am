## Source directory

h_sources = mets.h observer.h
cc_sources = mets.cc tabu-search.cc simulated-annealing.cc \
	local-search.cc

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)-$(GENERIC_API_VERSION)/$(GENERIC_LIBRARY_NAME)
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)

lib_LTLIBRARIES= libmetslib.la
libmetslib_la_SOURCES= $(h_sources) $(cc_sources)
libmetslib_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)
