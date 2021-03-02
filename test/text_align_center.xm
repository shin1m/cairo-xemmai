math = Module("math"
cairo = Module("cairo"
Module("draw-sample")(Module("system").arguments[0], @(context)
	utf8 = "cairo"
	context.select_font_face("Sans", cairo.FontSlant.NORMAL, cairo.FontWeight.NORMAL
	context.set_font_size(52.0
	extents = context.text_extents(utf8
	x = 128.0 - (extents[2] / 2.0 + extents[0])
	y = 128.0 - (extents[3] / 2.0 + extents[1])
	context.move_to(x, y
	context.show_text(utf8
	context.set_source_rgba(1.0, 0.2, 0.2, 0.6
	context.set_line_width(6.0
	context.arc(x, y, 10.0, 0.0, 2.0 * math.PI
	context.fill(
	context.move_to(128.0, 0.0
	context.rel_line_to(0.0, 256.0
	context.move_to(0.0, 128.0
	context.rel_line_to(256.0, 0.0
	context.stroke(
