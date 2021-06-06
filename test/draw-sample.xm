math = Module("math"
cairo = Module("cairo"
min = @(x, y) x < y ? x : y
round = @(x) math.floor(x + 0.5
$do = @(path, draw) cairo.main(@
	image = cairo.ImageSurface(cairo.Format.ARGB32, 320, 240
	context = cairo.Context(image
	try
		width0 = height0 = 256.0
		margin = 8.0
		width1 = image.get_width() - margin * 2.0
		height1 = image.get_height() - margin * 2.0
		scale = min(width1 / width0, height1 / height0
		context.rectangle(0.0, 0.0, image.get_width(), image.get_height()
		context.set_source_rgb(1.0, 1.0, 1.0
		context.fill(
		sw = round(width0 * scale
		sh = round(height0 * scale
		context.translate(round(margin + (width1 - sw) * 0.5), round(margin + (height1 - sh) * 0.5)
		context.rectangle(-0.5, -0.5, sw + 1.0, sh + 1.0
		context.set_source_rgb(0.95, 0.95, 0.95
		context.fill_preserve(
		context.set_source_rgb(0.6, 0.6, 0.6
		context.set_line_width(1.0
		context.stroke_preserve(
		context.clip(
		context.new_path(
		context.set_source_rgb(0.0, 0.0, 0.0
		context.scale(scale, scale
		draw(context
	finally
		context.release(
	image.write_to_png(path
