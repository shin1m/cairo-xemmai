system = Module("system"
io = Module("io"
cairo = Module("cairo"
cairo.main(@
	images = cairo.ImageSurface.create_all_from_gif((io.Path(system.script) / "../data/foo.gif").__string(
	images[0].write_to_png(system.arguments[0]
