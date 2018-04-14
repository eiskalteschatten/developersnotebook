ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPTIONS = foreign
EXTRA_DIST = bootstrap

ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

AM_CXXFLAGS = -std=c++11

bin_PROGRAMS = developersnotebook

developersnotebook_SOURCES = src/main.cpp
developersnotebook_CPPFLAGS = $(DEPENDENCIES_CPPFLAGS) $(BOOST_CPPFLAGS)
developersnotebook_LDFLAGS = $(BOOST_FILESYSTEM_LDFLAGS)
developersnotebook_LDADD = $(DEPENDENCIES_LIBS) $(BOOST_FILESYSTEM_LIBS)
