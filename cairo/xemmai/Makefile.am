xemmaidir = $(XEMMAI_MODULE_PATH)

xemmai_LTLIBRARIES = cairo.la
AM_CPPFLAGS = $(CAIRO_CFLAGS)
AM_LDFLAGS = -module
AM_CXXFLAGS =
if DEBUG
AM_CXXFLAGS += -g
else
AM_CPPFLAGS += -DNDEBUG
AM_CXXFLAGS += -O3
endif
if PROFILE
AM_CXXFLAGS += -pg
AM_LDFLAGS += -pg
endif
cairo_la_LIBADD = $(CAIRO_LIBS)
cairo_la_SOURCES = \
	matrix.h \
	matrix.cc \
	cast.h \
	surface.h \
	surface.cc \
	pattern.h \
	pattern.cc \
	context.h \
	context.cc \
	cairo.h \
	cairo.cc
