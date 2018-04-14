AUTOMAKE_OPTIONS = subdir-objects

ACLOCAL_AMFLAGS = $(ACLOCAL_FLAGS)

bin_PROGRAMS = developersnotebook

developersnotebook_SOURCES = main.cpp
developersnotebook_CPPFLAGS = $(DEPENDENCIES_CFLAGS) $(BOOST_CPPFLAGS)
developersnotebook_LDFLAGS = $(DEPENDENCIES_LIBS)
developersnotebook_LDADD = $(BOOST_SYSTEM_LIB) $(BOOST_FILESYSTEM_LIB)
