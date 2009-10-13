## top directory
ACLOCAL_AMFLAGS = -I m4

#Build in these directories:
SUBDIRS = $(GENERIC_LIBRARY_NAME) test 

#Distribute these directories:
DIST_SUBDIRS = $(GENERIC_LIBRARY_NAME) test doxydoc

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = metslib.pc

EXTRA_DIST = autogen.sh metslib.sln metslib.vcproj 

ConfigHeader = metslib_config.h

install-exec-local:
	echo "#ifndef HAVE_CONFIG_H" >bla
	echo "#define HAVE_CONFIG_H" >>bla
	echo "#endif" >> bla
	cat $(srcdir)/$(GENERIC_LIBRARY_NAME)/$(ConfigHeader) >> bla
	$(install_sh_DATA) bla $(DESTDIR)$(includedir)/$(GENERIC_LIBRARY_NAME)-$(GENERIC_API_VERSION)/$(GENERIC_LIBRARY_NAME)/$(ConfigHeader)
	rm -f bla

uninstall-local:
	rm -f $(DESTDIR)$(includedir)/$(GENERIC_LIBRARY_NAME)-$(GENERIC_API_VERSION)/$(GENERIC_LIBRARY_NAME)/$(ConfigHeader)
