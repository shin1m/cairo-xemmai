xemmaiincludedir = $(XEMMAI_INCLUDE_PATH)/xemmaix/cairo

xemmaiinclude_HEADERS = \
	matrix.h \
	font_options.h \
	surface.h \
	pattern.h \
	font_face.h \
	scaled_font.h \
	context.h \
	cairo.h

xemmaimoduledir = $(XEMMAI_MODULE_PATH)

xemmaimodule_LTLIBRARIES = cairo.la
AM_CPPFLAGS = $(CAIRO_CFLAGS) $(XEMMAI_CFLAGS)
AM_CXXFLAGS =
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
	matrix.cc \
	font_options.cc \
	surface.cc \
	jpeg.cc \
	gif.cc \
	pattern.cc \
	font_face.cc \
	scaled_font.cc \
	context.cc \
	cairo.cc
