cairo = Module("cairo"
range = @(i, j, callable) for ; i < j; i = i + 1
	callable(i
Module("draw-tutorial")(Module("system").script + ".png", @(context)
	radial = cairo.RadialGradient(0.25, 0.25, 0.1, 0.5, 0.5, 0.5
	radial.add_color_stop_rgb(0.0, 1.0, 0.8, 0.8
	radial.add_color_stop_rgb(1.0, 0.9, 0.0, 0.0
	range(1, 10, @(i)
		range(1, 10, @(j)
			context.rectangle(Float(i) / 10.0 - 0.04, Float(j) / 10.0 - 0.04, 0.08, 0.08
	context.set_source(radial
	context.fill(
	radial.release(
	linear = cairo.LinearGradient(0.25, 0.35, 0.75, 0.65
	linear.add_color_stop_rgba(0.0, 1.0, 1.0, 1.0, 0.0
	linear.add_color_stop_rgba(0.25, 0.0, 1.0, 0.0, 0.5
	linear.add_color_stop_rgba(0.5, 1.0, 1.0, 1.0, 0.0
	linear.add_color_stop_rgba(0.75, 0.0, 0.0, 1.0, 0.5
	linear.add_color_stop_rgba(1.0, 1.0, 1.0, 1.0, 0.0
	context.rectangle(0.0, 0.0, 1.0, 1.0
	context.set_source(linear
	context.fill(
	linear.release(
