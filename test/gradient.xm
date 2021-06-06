math = Module("math"
cairo = Module("cairo"
Module("draw-sample").do(Module("system").arguments[0], @(context)
	pattern = cairo.LinearGradient(0.0, 0.0, 0.0, 256.0
	pattern.add_color_stop_rgba(1.0, 0.0, 0.0, 0.0, 1.0
	pattern.add_color_stop_rgba(0.0, 1.0, 1.0, 1.0, 1.0
	context.rectangle(0.0, 0.0, 256.0, 256.0
	context.set_source(pattern
	context.fill(
	pattern.release(
	pattern = cairo.RadialGradient(115.2, 102.4, 25.6, 102.4, 102.4, 128.0
	pattern.add_color_stop_rgba(0.0, 1.0, 1.0, 1.0, 1.0
	pattern.add_color_stop_rgba(1.0, 0.0, 0.0, 0.0, 1.0
	context.set_source(pattern
	context.arc(128.0, 128.0, 76.8, 0.0, 2.0 * math.PI
	context.fill(
	pattern.release(
