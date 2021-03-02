system = Module("system"
io = Module("io"
math = Module("math"
cairo = Module("cairo"
Module("draw-sample")(system.arguments[0], @(context)
	image = cairo.ImageSurface.create_from_png((io.Path(system.script) / "../data/romedalen.png").__string(
	w = Float(image.get_width(
	h = Float(image.get_height(
	pattern = cairo.SurfacePattern(image
	pattern.set_extend(cairo.Extend.REPEAT
	context.translate(128.0, 128.0
	context.rotate(math.PI / 4.0
	context.scale(1.0 / math.sqrt(2.0), 1.0 / math.sqrt(2.0)
	context.translate(-128.0, -128.0
	matrix = cairo.Matrix(
	matrix.scale(w / 256.0 * 5.0, h / 256.0 * 5.0
	pattern.set_matrix(matrix
	context.set_source(pattern
	context.rectangle(0.0, 0.0, 256.0, 256.0
	context.fill(
	pattern.release(
	image.release(
