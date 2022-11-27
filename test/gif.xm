system = Module("system"
os = Module("os"
cairo = Module("cairo"
cairo.main(@
	images = cairo.ImageSurface.create_all_from_gif((os.Path(system.script) / "../data/foo.gif").__string(
	images[0].write_to_png(system.arguments[0]
