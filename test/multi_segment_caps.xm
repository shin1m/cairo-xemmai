math = Module("math"
cairo = Module("cairo"
Module("draw-sample")(Module("system").script + ".png", @(context)
	context.move_to(50.0, 75.0
	context.line_to(200.0, 75.0
	context.move_to(50.0, 125.0
	context.line_to(200.0, 125.0
	context.move_to(50.0, 175.0
	context.line_to(200.0, 175.0
	context.set_line_width(30.0
	context.set_line_cap(cairo.LineCap.ROUND
	context.stroke(
