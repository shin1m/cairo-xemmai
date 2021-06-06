Module("draw-tutorial").do(Module("system").arguments[0], @(context)
	context.set_source_rgb(0.0, 0.0, 0.0
	context.move_to(0.0, 0.0
	context.line_to(1.0, 1.0
	context.move_to(1.0, 0.0
	context.line_to(0.0, 1.0
	context.set_line_width(0.2
	context.stroke(
	context.rectangle(0.0, 0.0, 0.5, 0.5
	context.set_source_rgba(1.0, 0.0, 0.0, 0.8
	context.fill(
	context.rectangle(0.0, 0.5, 0.5, 0.5
	context.set_source_rgba(0.0, 1.0, 0.0, 0.6
	context.fill(
	context.rectangle(0.5, 0.0, 0.5, 0.5
	context.set_source_rgba(0.0, 0.0, 1.0, 0.4
	context.fill(
