#include "surface.h"

namespace xemmaix::cairo
{

cairo_status_t t_surface::f_write_stream(void* a_closure, const unsigned char* a_data, unsigned int a_length)
{
	const t_value& write = *static_cast<const t_value**>(a_closure)[0];
	const t_value& buffer = *static_cast<const t_value**>(a_closure)[1];
	t_bytes& bytes = f_as<t_bytes&>(buffer);
	t_scoped zero = f_global()->f_as(0);
	try {
		while (a_length > 0) {
			size_t m = std::min(bytes.f_size(), static_cast<size_t>(a_length));
			std::copy(a_data, a_data + m, &bytes[0]);
			write(buffer, zero, f_global()->f_as(m));
			a_data += m;
			a_length -= m;
		}
		return CAIRO_STATUS_SUCCESS;
	} catch (...) {
		return CAIRO_STATUS_WRITE_ERROR;
	}
}

t_surface* t_surface::f_wrap(cairo_surface_t* a_value)
{
	if (!a_value) return nullptr;
	t_surface* p = f_from(a_value);
	if (p) return p;
	switch (cairo_surface_get_type(a_value)) {
	case CAIRO_SURFACE_TYPE_IMAGE:
		return new t_image_surface(a_value);
	default:
		return new t_surface(a_value);
	}
}

void t_surface::f_write_to_png_stream(const t_value& a_write) const
{
	t_scoped buffer = t_bytes::f_instantiate(1024);
	const t_value* closure[] = {
		&a_write, &buffer
	};
	cairo_surface_write_to_png_stream(v_value, f_write_stream, closure);
}

void t_image_source::f_read_buffer()
{
	f_rewind();
	f_fill();
	if (v_head >= v_tail) f_throw(L"unexpected end of stream.");
}

void t_image_source::f_prefetch_buffer()
{
	t_bytes& bytes = f_as<t_bytes&>(v_buffer);
	if (v_tail >= &bytes[bytes.f_size()]) f_throw(L"too match prefetching.");
	f_fill();
	if (v_head >= v_tail) f_throw(L"unexpected end of stream.");
}

size_t t_file_source::f_read(size_t a_offset)
{
	t_safe_region region;
	t_bytes& bytes = f_as<t_bytes&>(v_buffer);
	return io::t_file::f_read(bytes, a_offset, bytes.f_size() - a_offset);
}

size_t t_stream_source::f_read(size_t a_offset)
{
	t_bytes& bytes = f_as<t_bytes&>(v_buffer);
	t_scoped p = v_read(v_buffer, f_global()->f_as(a_offset), f_global()->f_as(bytes.f_size() - a_offset));
	f_check<size_t>(p, L"result of read");
	return f_as<size_t>(p);
}

cairo_status_t t_image_surface::f_read_stream(void* a_closure, unsigned char* a_data, unsigned int a_length)
{
	t_image_source& source = *static_cast<t_image_source*>(a_closure);
	try {
		while (a_length > 0) {
			size_t n = source.f_read_bytes(a_data, a_length);
			if (n < 0) return CAIRO_STATUS_READ_ERROR;
			a_data += n;
			a_length -= n;
		}
		return CAIRO_STATUS_SUCCESS;
	} catch (...) {
		return CAIRO_STATUS_READ_ERROR;
	}
}

void t_image_surface::f_destroy()
{
	v_data = nullptr;
	t_surface::f_destroy();
}

t_scoped t_image_surface::f_create_from_png_source(t_image_source& a_source)
{
	return f_transfer(new t_image_surface(cairo_image_surface_create_from_png_stream(f_read_stream, &a_source)));
}

t_scoped t_image_surface::f_create_from_png_stream(const t_value& a_read)
{
	t_stream_source source(a_read);
	return f_create_from_png_source(source);
}

t_scoped t_image_surface::f_create_from_source(t_image_source& a_source)
{
	switch (a_source.f_prefetch_byte()) {
	case 'G':
		if (a_source.f_prefetch_byte() == 'I')
		if (a_source.f_prefetch_byte() == 'F')
		if (a_source.f_prefetch_byte() == '8')
			switch (a_source.f_prefetch_byte()) {
			case '7':
			case '9':
				if (a_source.f_prefetch_byte() == 'a') {
					a_source.f_rewind();
					return f_create_from_gif_source(a_source);
				}
				break;
			}
		break;
	case 0x89:
		if (a_source.f_prefetch_byte() == 'P')
		if (a_source.f_prefetch_byte() == 'N')
		if (a_source.f_prefetch_byte() == 'G')
		if (a_source.f_prefetch_byte() == '\r')
		if (a_source.f_prefetch_byte() == '\n')
		if (a_source.f_prefetch_byte() == 0x1a)
		if (a_source.f_prefetch_byte() == '\n') {
			a_source.f_rewind();
			return f_create_from_png_source(a_source);
		}
		break;
	case 0xff:
		if (a_source.f_prefetch_byte() == 0xd8) {
			a_source.f_rewind();
			return f_create_from_jpeg_source(a_source);
		}
		break;
	}
	f_throw(L"unknown source.");
	return nullptr;
}

}

namespace xemmai
{

void t_type_of<xemmaix::cairo::t_surface>::f_define(t_extension* a_extension)
{
	using namespace xemmaix::cairo;
	t_define<t_surface, t_object>(a_extension, L"Surface")
		(L"acquire", t_member<void(t_surface::*)(), &t_surface::f_acquire>())
		(L"release", t_member<void(t_surface::*)(), &t_surface::f_release>())
		(L"status", t_member<cairo_status_t(t_surface::*)() const, &t_surface::f_status>())
		(L"finish", t_member<void(t_surface::*)(), &t_surface::f_finish>())
		(L"flush", t_member<void(t_surface::*)(), &t_surface::f_flush>())
		(L"get_font_options", t_member<t_scoped(t_surface::*)() const, &t_surface::f_get_font_options>())
		(L"get_content", t_member<cairo_content_t(t_surface::*)() const, &t_surface::f_get_content>())
		(L"mark_dirty", t_member<void(t_surface::*)(), &t_surface::f_mark_dirty>())
		(L"mark_dirty_rectangle", t_member<void(t_surface::*)(int, int, int, int), &t_surface::f_mark_dirty>())
		(L"set_device_offset", t_member<void(t_surface::*)(double, double), &t_surface::f_set_device_offset>())
		(L"get_device_offset", t_member<t_scoped(t_surface::*)() const, &t_surface::f_get_device_offset>())
		(L"set_fallback_resolution", t_member<void(t_surface::*)(double, double), &t_surface::f_set_fallback_resolution>())
		(L"get_fallback_resolution", t_member<t_scoped(t_surface::*)() const, &t_surface::f_get_fallback_resolution>())
		(L"get_type", t_member<cairo_surface_type_t(t_surface::*)() const, &t_surface::f_get_type>())
		(L"copy_page", t_member<void(t_surface::*)(), &t_surface::f_copy_page>())
		(L"show_page", t_member<void(t_surface::*)(), &t_surface::f_show_page>())
		(L"has_show_text_glyphs", t_member<bool(t_surface::*)() const, &t_surface::f_has_show_text_glyphs>())
		(L"write_to_png", t_member<void(t_surface::*)(const std::wstring&) const, &t_surface::f_write_to_png>())
		(L"write_to_png_stream", t_member<void(t_surface::*)(const t_value&) const, &t_surface::f_write_to_png_stream>())
	;
}

t_scoped t_type_of<xemmaix::cairo::t_surface>::f_do_construct(t_stacked* a_stack, size_t a_n)
{
	return t_construct_with<t_scoped(*)(t_type*, xemmaix::cairo::t_surface&, cairo_content_t, int, int), xemmaix::cairo::t_surface::f_construct>::t_bind<xemmaix::cairo::t_surface>::f_do(this, a_stack, a_n);
}

void t_type_of<cairo_content_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_content_t, intptr_t>(a_extension, L"Content")
		(L"COLOR", CAIRO_CONTENT_COLOR)
		(L"ALPHA", CAIRO_CONTENT_ALPHA)
		(L"COLOR_ALPHA", CAIRO_CONTENT_COLOR_ALPHA)
	;
}

void t_type_of<cairo_surface_type_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_surface_type_t, intptr_t>(a_extension, L"SurfaceType")
		(L"IMAGE", CAIRO_SURFACE_TYPE_IMAGE)
		(L"PDF", CAIRO_SURFACE_TYPE_PDF)
		(L"PS", CAIRO_SURFACE_TYPE_PS)
		(L"XLIB", CAIRO_SURFACE_TYPE_XLIB)
		(L"XCB", CAIRO_SURFACE_TYPE_XCB)
		(L"GLITZ", CAIRO_SURFACE_TYPE_GLITZ)
		(L"QUARTZ", CAIRO_SURFACE_TYPE_QUARTZ)
		(L"WIN32", CAIRO_SURFACE_TYPE_WIN32)
		(L"BEOS", CAIRO_SURFACE_TYPE_BEOS)
		(L"DIRECTFB", CAIRO_SURFACE_TYPE_DIRECTFB)
		(L"SVG", CAIRO_SURFACE_TYPE_SVG)
		(L"OS2", CAIRO_SURFACE_TYPE_OS2)
		(L"WIN32_PRINTING", CAIRO_SURFACE_TYPE_WIN32_PRINTING)
		(L"QUARTZ_IMAGE", CAIRO_SURFACE_TYPE_QUARTZ_IMAGE)
	;
}

void t_type_of<xemmaix::cairo::t_image_surface>::f_define(t_extension* a_extension)
{
	using namespace xemmaix::cairo;
	t_define<t_image_surface, t_surface>(a_extension, L"ImageSurface")
		(L"get_data", t_member<t_scoped(t_image_surface::*)() const, &t_image_surface::f_get_data>())
		(L"get_format", t_member<cairo_format_t(t_image_surface::*)() const, &t_image_surface::f_get_format>())
		(L"get_width", t_member<int(t_image_surface::*)() const, &t_image_surface::f_get_width>())
		(L"get_height", t_member<int(t_image_surface::*)() const, &t_image_surface::f_get_height>())
		(L"get_stride", t_member<int(t_image_surface::*)() const, &t_image_surface::f_get_stride>())
		(L"create_from_png", t_static<t_scoped(*)(const std::wstring&), t_image_surface::f_create_from_png>())
		(L"create_from_png_stream", t_static<t_scoped(*)(const t_value&), t_image_surface::f_create_from_png_stream>())
		(L"create_from_jpeg", t_static<t_scoped(*)(const std::wstring&), t_image_surface::f_create_from_jpeg>())
		(L"create_from_jpeg_stream", t_static<t_scoped(*)(const t_value&), t_image_surface::f_create_from_jpeg_stream>())
		(L"create_from_gif", t_static<t_scoped(*)(const std::wstring&), t_image_surface::f_create_from_gif>())
		(L"create_from_gif_stream", t_static<t_scoped(*)(const t_value&), t_image_surface::f_create_from_gif_stream>())
		(L"create_all_from_gif", t_static<t_scoped(*)(const std::wstring&), t_image_surface::f_create_all_from_gif>())
		(L"create_all_from_gif_stream", t_static<t_scoped(*)(const t_value&), t_image_surface::f_create_all_from_gif_stream>())
		(L"create_from_file", t_static<t_scoped(*)(const std::wstring&), t_image_surface::f_create_from_file>())
		(L"create_from_stream", t_static<t_scoped(*)(const t_value&), t_image_surface::f_create_from_stream>())
	;
}

t_scoped t_type_of<xemmaix::cairo::t_image_surface>::f_do_construct(t_stacked* a_stack, size_t a_n)
{
	return t_overload<
		t_construct_with<t_scoped(*)(t_type*, cairo_format_t, int, int), xemmaix::cairo::t_image_surface::f_construct>,
		t_construct_with<t_scoped(*)(t_type*, t_scoped&&, cairo_format_t, int, int, int), xemmaix::cairo::t_image_surface::f_construct>
	>::t_bind<xemmaix::cairo::t_image_surface>::f_do(this, a_stack, a_n);
}

void t_type_of<cairo_format_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_format_t, intptr_t>(a_extension, L"Format")
		(L"ARGB32", CAIRO_FORMAT_ARGB32)
		(L"RGB24", CAIRO_FORMAT_RGB24)
		(L"A8", CAIRO_FORMAT_A8)
		(L"A1", CAIRO_FORMAT_A1)
	;
}

}
