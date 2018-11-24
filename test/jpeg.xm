cairo = Module("cairo"
cairo.main(@
	image = cairo.ImageSurface.create_from_jpeg("data/lena.jpg"
	image.write_to_png(Module("system").script + ".png"
