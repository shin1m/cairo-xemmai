math = Module("math"
cairo = Module("cairo"
Module("draw-sample")(Module("system").script + ".png", @(context)
	context.select_font_face("Sans", cairo.FontSlant.NORMAL, cairo.FontWeight.BOLD
	context.set_font_size(90.0
	context.move_to(10.0, 135.0
	context.show_text("Hello"
	context.move_to(70.0, 165.0
	context.text_path("void"
	context.set_source_rgb(0.5, 0.5, 1.0
	context.fill_preserve(
	context.set_source_rgb(0.0, 0.0, 0.0
	context.set_line_width(2.56
	context.stroke(
	context.set_source_rgba(1.0, 0.2, 0.2, 0.6
	context.arc(10.0, 135.0, 5.12, 0.0, 2.0 * math.PI
	context.close_path(
	context.arc(70.0, 165.0, 5.12, 0.0, 2.0 * math.PI
	context.fill(
