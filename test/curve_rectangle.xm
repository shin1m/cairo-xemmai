math = Module("math"
Module("draw-sample")(Module("system").script + ".png", @(context)
	x0 = 25.6
	y0 = 25.6
	rect_width = 204.8
	rect_height = 204.8
	radius = 102.4
	x1 = x0 + rect_width
	y1 = y0 + rect_height
	if rect_width / 2.0 < radius
		if rect_height / 2.0 < radius
			context.move_to(x0, (y0 + y1) / 2.0
			context.curve_to(x0 ,y0, x0, y0, (x0 + x1) / 2.0, y0
			context.curve_to(x1, y0, x1, y0, x1, (y0 + y1) / 2.0
			context.curve_to(x1, y1, x1, y1, (x1 + x0) / 2.0, y1
			context.curve_to(x0, y1, x0, y1, x0, (y0 + y1) / 2.0
		else
			context.move_to(x0, y0 + radius
			context.curve_to(x0 ,y0, x0, y0, (x0 + x1) / 2.0, y0
			context.curve_to(x1, y0, x1, y0, x1, y0 + radius
			context.line_to(x1 , y1 - radius
			context.curve_to(x1, y1, x1, y1, (x1 + x0) / 2.0, y1
			context.curve_to(x0, y1, x0, y1, x0, y1 - radius
	else
		if rect_height / 2.0 < radius
			context.move_to(x0, (y0 + y1) / 2.0
			context.curve_to(x0 , y0, x0 , y0, x0 + radius, y0
			context.line_to(x1 - radius, y0
			context.curve_to(x1, y0, x1, y0, x1, (y0 + y1) / 2.0
			context.curve_to(x1, y1, x1, y1, x1 - radius, y1
			context.line_to(x0 + radius, y1
			context.curve_to(x0, y1, x0, y1, x0, (y0 + y1) / 2.0
		else
			context.move_to(x0, y0 + radius
			context.curve_to(x0 , y0, x0 , y0, x0 + radius, y0
			context.line_to(x1 - radius, y0
			context.curve_to(x1, y0, x1, y0, x1, y0 + radius
			context.line_to(x1 , y1 - radius
			context.curve_to(x1, y1, x1, y1, x1 - radius, y1
			context.line_to(x0 + radius, y1
			context.curve_to(x0, y1, x0, y1, x0, y1 - radius
	context.close_path(
	context.set_source_rgb(0.5, 0.5, 1.0
	context.fill_preserve(
	context.set_source_rgba(0.5, 0.0, 0.0, 0.5
	context.set_line_width(10.0
	context.stroke(
