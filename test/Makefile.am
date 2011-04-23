check_PROGRAMS = tabu_list_test permutation_problem_test termination_test

#AM_LDFLAGS = -L$(top_builddir)/metslib/.libs/  -lmetslib
#AM_LIBS =
AM_CPPFLAGS = -I$(top_builddir) -I$(top_srcdir) -DMETSLIB_TESTING

tabu_list_test_SOURCES = tabu_list_test.cc 

permutation_problem_test_SOURCES = permutation_problem_test.cc

termination_test_SOURCES = termination_test.cc

TESTS = tabu_list_test permutation_problem_test termination_test
