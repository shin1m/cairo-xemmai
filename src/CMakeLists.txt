add_library(cairo MODULE
	matrix.cc
	font_options.cc
	surface.cc
	jpeg.cc
	gif.cc
	pattern.cc
	font_face.cc
	scaled_font.cc
	context.cc
	cairo.cc
	)
target_compile_options(cairo PRIVATE ${CAIRO_CFLAGS})
target_link_libraries(cairo xemmai -l${CAIRO_LIBRARIES} JPEG::JPEG)
set_property(TARGET cairo PROPERTY PREFIX "")
install(FILES
	matrix.h
	font_options.h
	surface.h
	pattern.h
	font_face.h
	scaled_font.h
	context.h
	cairo.h
	DESTINATION include/xemmai-${xemmai_VERSION_MAJOR}/xemmaix/cairo
	)
