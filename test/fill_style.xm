math = Module("math"
cairo = Module("cairo"
Module("draw-sample").do(Module("system").arguments[0], @(context)
	context.set_line_width(6.0
	context.rectangle(12.0, 12.0, 232.0, 70.0
	context.new_sub_path(
	context.arc(64.0, 64.0, 40.0, 0.0, 2.0 * math.PI
	context.new_sub_path(
	context.arc_negative(192.0, 64.0, 40.0, 0.0, -2.0 * math.PI
	context.set_fill_rule(cairo.FillRule.EVEN_ODD
	context.set_source_rgb(0.0, 0.7, 0.0
	context.fill_preserve(
	context.set_source_rgb(0.0, 0.0, 0.0
	context.stroke(
	context.translate(0.0, 128.0
	context.rectangle(12.0, 12.0, 232.0, 70.0
	context.new_sub_path(
	context.arc(64.0, 64.0, 40.0, 0.0, 2.0 * math.PI
	context.new_sub_path(
	context.arc_negative(192.0, 64.0, 40.0, 0.0, -2.0 * math.PI
	context.set_fill_rule(cairo.FillRule.WINDING
	context.set_source_rgb(0.0, 0.0, 0.9
	context.fill_preserve(
	context.set_source_rgb(0.0, 0.0, 0.0
	context.stroke(
