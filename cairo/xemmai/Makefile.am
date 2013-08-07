xemmaidir = $(XEMMAI_MODULE_PATH)

xemmai_LTLIBRARIES = cairo.la
AM_CPPFLAGS = $(CAIRO_CFLAGS) $(XEMMAI_CFLAGS)
AM_CXXFLAGS = -std=c++11
AM_LDFLAGS = -module -avoid-version -ljpeg
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
cairo_la_LIBADD = $(CAIRO_LIBS) $(XEMMAI_LIBS)
cairo_la_SOURCES = \
	matrix.h \
	matrix.cc \
	font_options.h \
	font_options.cc \
	cast.h \
	surface.h \
	surface.cc \
	jpeg.cc \
	gif.cc \
	pattern.h \
	pattern.cc \
	font_face.h \
	font_face.cc \
	scaled_font.h \
	scaled_font.cc \
	context.h \
	context.cc \
	cairo.h \
	cairo.cc
