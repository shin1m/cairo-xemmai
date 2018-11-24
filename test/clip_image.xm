math = Module("math"
cairo = Module("cairo"
Module("draw-sample")(Module("system").script + ".png", @(context)
	context.arc(128.0, 128.0, 76.8, 0.0, 2.0 * math.PI
	context.clip(
	context.new_path(
	image = cairo.ImageSurface.create_from_png("data/romedalen.png"
	context.scale(256.0 / image.get_width(), 256.0 / image.get_height()
	context.set_source(image, 0.0, 0.0
	context.paint(
	image.release(
