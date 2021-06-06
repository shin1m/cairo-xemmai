cairo = Module("cairo"
$do = @(path, draw) cairo.main(@
	image = cairo.ImageSurface(cairo.Format.ARGB32, 320, 240
	context = cairo.Context(image
	try
		context.scale(image.get_width(), image.get_height()
		context.rectangle(0.0, 0.0, 1.0, 1.0
		context.set_source_rgb(1.0, 1.0, 1.0
		context.fill(
		draw(context
	finally
		context.release(
	image.write_to_png(path
