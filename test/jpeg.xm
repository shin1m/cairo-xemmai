system = Module("system"
io = Module("io"
cairo = Module("cairo"
cairo.main(@
	image = cairo.ImageSurface.create_from_jpeg((io.Path(system.script) / "../data/lena.jpg").__string(
	image.write_to_png(system.arguments[0]
