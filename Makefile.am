## top directory
ACLOCAL_AMFLAGS = -I m4

#Build in these directories:
SUBDIRS = $(GENERIC_LIBRARY_NAME) test 

#Distribute these directories:
DIST_SUBDIRS = $(GENERIC_LIBRARY_NAME) test doxydoc

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = metslib.pc

EXTRA_DIST = autogen.sh

ConfigHeader = metslib_config.hh
install-exec-local:
	echo "#ifndef HAVE_CONFIG_H" >bla
	echo "#define HAVE_CONFIG_H" >>bla
	echo "#endif" >> bla
	cat $(srcdir)/$(GENERIC_LIBRARY_NAME)/$(ConfigHeader) >> bla
	$(install_sh_DATA) bla $(DESTDIR)$(includedir)/$(GENERIC_LIBRARY_NAME)-$(GENERIC_API_VERSION)/$(GENERIC_LIBRARY_NAME)/$(ConfigHeader)
	rm -f bla

uninstall-local:
	rm -f $(DESTDIR)$(includedir)/$(GENERIC_LIBRARY_NAME)-$(GENERIC_API_VERSION)/$(GENERIC_LIBRARY_NAME)/$(ConfigHeader)

test: check

doxydoc:
	cd $(srcdir); doxygen doxydoc/doxygen.conf

targets:
	echo "METSlib makefile main targets"
	echo "  all       compile project"
	echo "  clean     remove objects and library files"
	echo "  dist      create tar.gz"
	echo "  test      compile and run test cases"
	echo "  doxydoc   run doxygen on project"

.PHONY: test doxydoc
