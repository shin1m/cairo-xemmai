math = Module("math"
Module("draw-sample")(Module("system").script + ".png", @(context)
	x = 25.6
	y = 128.0
	x1 = 102.4
	y1 = 230.4
	x2 = 153.6
	y2 = 25.6
	x3 = 230.4
	y3 = 128.0
	context.move_to(x, y
	context.curve_to(x1, y1, x2, y2, x3, y3
	context.set_line_width(10.0
	context.stroke(
	context.set_source_rgba(1.0 ,0.2 ,0.2 ,0.6
	context.set_line_width(6.0
	context.move_to(x, y
	context.line_to(x1, y1
	context.move_to(x2, y2
	context.line_to(x3, y3
	context.stroke(
