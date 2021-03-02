math = Module("math"
cairo = Module("cairo"
Module("draw-sample")(Module("system").arguments[0], @(context)
	context.set_line_width(30.0
	context.set_line_cap(cairo.LineCap.BUTT
	context.move_to(64.0, 50.0
	context.line_to(64.0, 200.0
	context.stroke(
	context.set_line_cap(cairo.LineCap.ROUND
	context.move_to(128.0, 50.0
	context.line_to(128.0, 200.0
	context.stroke(
	context.set_line_cap(cairo.LineCap.SQUARE
	context.move_to(192.0, 50.0
	context.line_to(192.0, 200.0
	context.stroke(
	context.set_source_rgb(1.0, 0.2, 0.2
	context.set_line_width(2.56
	context.move_to(64.0, 50.0
	context.line_to(64.0, 200.0
	context.move_to(128.0, 50.0
	context.line_to(128.0, 200.0
	context.move_to(192.0, 50.0
	context.line_to(192.0, 200.0
	context.stroke(
