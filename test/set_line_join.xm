math = Module("math"
cairo = Module("cairo"
Module("draw-sample").do(Module("system").arguments[0], @(context)
	context.set_line_width(40.96
	context.move_to(76.8, 84.48
	context.rel_line_to(51.2, -51.2
	context.rel_line_to(51.2, 51.2
	context.set_line_join(cairo.LineJoin.MITER
	context.stroke(
	context.move_to(76.8, 161.28
	context.rel_line_to(51.2, -51.2
	context.rel_line_to(51.2, 51.2
	context.set_line_join(cairo.LineJoin.BEVEL
	context.stroke(
	context.move_to(76.8, 238.08
	context.rel_line_to(51.2, -51.2
	context.rel_line_to(51.2, 51.2
	context.set_line_join(cairo.LineJoin.ROUND
	context.stroke(
