cairo = Module("cairo"
cairo.main(@
	images = cairo.ImageSurface.create_all_from_gif("data/foo.gif"
	images[0].write_to_png(Module("system").script + ".png"
