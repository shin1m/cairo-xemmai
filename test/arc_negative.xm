math = Module("math"
Module("draw-sample")(Module("system").arguments[0], @(context)
	xc = 128.0
	yc = 128.0
	radius = 100.0
	angle1 = 45.0 * math.PI / 180.0
	angle2 = 180.0 * math.PI / 180.0
	context.set_line_width(10.0
	context.arc_negative(xc, yc, radius, angle1, angle2
	context.stroke(
	context.set_source_rgba(1.0, 0.2, 0.2, 0.6
	context.set_line_width(6.0
	context.arc(xc, yc, 10.0, 0.0, 2.0 * math.PI
	context.fill(
	context.arc(xc, yc, radius, angle1, angle1
	context.line_to(xc, yc
	context.arc(xc, yc, radius, angle2, angle2
	context.line_to(xc, yc
	context.stroke(
