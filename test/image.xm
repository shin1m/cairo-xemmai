system = Module("system"
io = Module("io"
math = Module("math"
cairo = Module("cairo"
Module("draw-sample").do(system.arguments[0], @(context)
	file = io.File((io.Path(system.script) / "../data/romedalen.png").__string(), "rb"
	try
		image = cairo.ImageSurface.create_from_png_stream(file.read
	finally
		file.close(
	w = Float(image.get_width(
	h = Float(image.get_height(
	context.translate(128.0, 128.0
	context.rotate(45.0 * math.PI / 180.0
	context.scale(256.0 / w, 256.0 / h
	context.translate(-0.5 * w, -0.5 * h
	context.set_source(image, 0.0, 0.0
	context.paint(
	image.release(
