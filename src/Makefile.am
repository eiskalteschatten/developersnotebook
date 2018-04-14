AUTOMAKE_OPTIONS = subdir-objects

ACLOCAL_AMFLAGS = $(ACLOCAL_FLAGS)

bin_PROGRAMS = developersnotebook

developersnotebook_SOURCES = main.cpp
developersnotebook_CPPFLAGS = $(DEPENDENCIES_CPPFLAGS) $(BOOST_CPPFLAGS)
developersnotebook_LDFLAGS = $(DEPENDENCIES_LIBS) $(BOOST_FILESYSTEM_LDFLAGS)
developersnotebook_LDADD = $(BOOST_FILESYSTEM_LIBS)
