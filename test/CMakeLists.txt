function(do_test name)
	add_test(NAME ${name} COMMAND xemmai --verbose "${CMAKE_CURRENT_SOURCE_DIR}/${name}.xm" "${CMAKE_CURRENT_BINARY_DIR}/${name}.png")
	set_property(TEST ${name} PROPERTY ENVIRONMENT "XEMMAI_MODULE_PATH=${PROJECT_BINARY_DIR}/src")
endfunction()
do_test(arc)
do_test(arc_negative)
do_test(clip)
do_test(clip_image)
do_test(curve_rectangle)
do_test(curve_to)
do_test(dash)
do_test(fill_and_stroke2)
do_test(fill_style)
do_test(gradient)
do_test(image)
do_test(imagepattern)
do_test(multi_segment_caps)
do_test(set_line_cap)
do_test(set_line_join)
do_test(text)
do_test(text_align_center)
do_test(text_extents)
do_test(tutorial0)
do_test(tutorial1)
do_test(jpeg)
do_test(gif)
