TEST_EXTENSIONS = .xm
AM_TESTS_ENVIRONMENT = export XEMMAI_MODULE_PATH=$(top_builddir)/src/.libs:$(XEMMAI_MODULE_PATH);
XM_LOG_COMPILER = $(XEMMAI_BIN_PATH)
AM_XM_LOG_FLAGS = --verbose
scripts = \
	arc.xm \
	arc_negative.xm \
	clip.xm \
	clip_image.xm \
	curve_rectangle.xm \
	curve_to.xm \
	dash.xm \
	fill_and_stroke2.xm \
	fill_style.xm \
	gradient.xm \
	image.xm \
	imagepattern.xm \
	multi_segment_caps.xm \
	set_line_cap.xm \
	set_line_join.xm \
	text.xm \
	text_align_center.xm \
	text_extents.xm \
	tutorial0.xm \
	tutorial1.xm \
	jpeg.xm \
	gif.xm
EXTRA_DIST = draw-sample.xm draw-tutorial.xm $(scripts)
CLEANFILES = *.png

TESTS = $(scripts)
