## Source directory

h_sources = mets.h model.hh abstract-search.hh local-search.hh		\
	simulated-annealing.hh tabu-search.hh termination-criteria.hh	\
	observer.h config.h metslib_config.h
cc_sources = mets.cc model.cc local-search.cc tabu-search.cc	\
	simulated-annealing.cc termination-criteria.cc

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)-$(GENERIC_API_VERSION)/$(GENERIC_LIBRARY_NAME)
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)

lib_LTLIBRARIES= libmetslib.la
libmetslib_la_SOURCES= $(h_sources) $(cc_sources)
libmetslib_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)

