system = Module("system"
os = Module("os"
cairo = Module("cairo"
cairo.main(@
	image = cairo.ImageSurface.create_from_jpeg((os.Path(system.script) / "../data/lena.jpg").__string(
	image.write_to_png(system.arguments[0]
