AUTOMAKE_OPTIONS = subdir-objects
EXTRA_DIST = bootstrap

ACLOCAL_AMFLAGS = $(ACLOCAL_FLAGS)

bin_PROGRAMS = developersnotebook

developersnotebook_SOURCES = main.cpp
developersnotebook_CPPFLAGS = $(DEPENDENCIES_CPPFLAGS) $(BOOST_CPPFLAGS)
developersnotebook_LDFLAGS = $(BOOST_FILESYSTEM_LDFLAGS)
developersnotebook_LDADD = $(DEPENDENCIES_LIBS) $(BOOST_FILESYSTEM_LIBS)
