math = Module("math"
Module("draw-sample").do(Module("system").arguments[0], @(context)
	dashes = [50.0, 10.0, 10.0, 10.0
	offset = -50.0
	context.set_dash(dashes, offset
	context.set_line_width(10.0
	context.move_to(128.0, 25.6
	context.line_to(230.4, 230.4
	context.rel_line_to(-102.4, 0.0
	context.curve_to(51.2, 230.4, 51.2, 128.0, 128.0, 128.0
	context.stroke(
