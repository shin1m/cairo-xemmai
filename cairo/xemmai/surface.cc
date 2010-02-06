#include "surface.h"

#include <cassert>

namespace cairo
{

namespace xemmai
{

cairo_status_t t_surface::f_write_stream(void* a_closure, const unsigned char* a_data, unsigned int a_length)
{
	t_object* write = static_cast<t_object**>(a_closure)[0];
	t_object* buffer = static_cast<t_object**>(a_closure)[1];
	t_bytes& bytes = f_as<t_bytes&>(buffer);
	t_scoped zero = f_global()->f_as(0);
	try {
		while (a_length > 0) {
			size_t m = std::min(bytes.f_size(), a_length);
			std::copy(a_data, a_data + m, &bytes[0]);
			write->f_call(buffer, zero, f_global()->f_as(m));
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
	if (!a_value) return 0;
	t_surface* p = f_from(a_value);
	if (p) return p;
	switch (cairo_surface_get_type(a_value)) {
	case CAIRO_SURFACE_TYPE_IMAGE:
		return new t_image_surface(a_value);
	default:
		return new t_surface(a_value);
	}
}

void t_surface::f_write_to_png_stream(t_object* a_write) const
{
	t_scoped buffer = t_bytes::f_instantiate(1024);
	t_object* closure[] = {
		a_write, buffer
	};
	cairo_surface_write_to_png_stream(v_value, f_write_stream, closure);
}

cairo_status_t t_image_surface::f_read_stream(void* a_closure, unsigned char* a_data, unsigned int a_length)
{
	t_object* read = static_cast<t_object**>(a_closure)[0];
	t_object* buffer = static_cast<t_object**>(a_closure)[1];
	t_bytes& bytes = f_as<t_bytes&>(buffer);
	t_scoped zero = f_global()->f_as(0);
	try {
		while (a_length > 0) {
			size_t m = std::min(bytes.f_size(), a_length);
			t_transfer p = read->f_call(buffer, zero, f_global()->f_as(m));
			f_check<size_t>(p, L"result of read");
			size_t n = f_as<size_t>(p);
			if (n <= 0 || n > m) return CAIRO_STATUS_READ_ERROR;
			a_data = std::copy(&bytes[0], &bytes[n], a_data);
			a_length -= n;
		}
		return CAIRO_STATUS_SUCCESS;
	} catch (...) {
		return CAIRO_STATUS_READ_ERROR;
	}
}

void t_image_surface::f_destroy()
{
	v_data = 0;
	t_surface::f_destroy();
}

t_transfer t_image_surface::f_create_from_png_stream(t_object* a_read)
{
	t_scoped buffer = t_bytes::f_instantiate(1024);
	t_object* closure[] = {
		a_read, buffer
	};
	return f_transfer(new t_image_surface(cairo_image_surface_create_from_png_stream(f_read_stream, closure)));
}

}

}

namespace xemmai
{

void t_type_of<t_surface>::f_define(t_extension* a_extension)
{
	t_define<t_surface, t_object>(a_extension, L"Surface")
		(L"acquire", t_member<void (t_surface::*)(), &t_surface::f_acquire>())
		(L"release", t_member<void (t_surface::*)(), &t_surface::f_release>())
		(L"status", t_member<cairo_status_t (t_surface::*)() const, &t_surface::f_status>())
		(L"finish", t_member<void (t_surface::*)(), &t_surface::f_finish>())
		(L"flush", t_member<void (t_surface::*)(), &t_surface::f_flush>())
		(L"get_font_options", t_member<t_transfer (t_surface::*)() const, &t_surface::f_get_font_options>())
		(L"get_content", t_member<cairo_content_t (t_surface::*)() const, &t_surface::f_get_content>())
		(L"mark_dirty", t_member<void (t_surface::*)(), &t_surface::f_mark_dirty>())
		(L"mark_dirty_rectangle", t_member<void (t_surface::*)(int, int, int, int), &t_surface::f_mark_dirty>())
		(L"set_device_offset", t_member<void (t_surface::*)(double, double), &t_surface::f_set_device_offset>())
		(L"get_device_offset", t_member<t_transfer (t_surface::*)() const, &t_surface::f_get_device_offset>())
		(L"set_fallback_resolution", t_member<void (t_surface::*)(double, double), &t_surface::f_set_fallback_resolution>())
		(L"get_fallback_resolution", t_member<t_transfer (t_surface::*)() const, &t_surface::f_get_fallback_resolution>())
		(L"get_type", t_member<cairo_surface_type_t (t_surface::*)() const, &t_surface::f_get_type>())
		(L"copy_page", t_member<void (t_surface::*)(), &t_surface::f_copy_page>())
		(L"show_page", t_member<void (t_surface::*)(), &t_surface::f_show_page>())
		(L"has_show_text_glyphs", t_member<bool (t_surface::*)() const, &t_surface::f_has_show_text_glyphs>())
		(L"write_to_png", t_member<void (t_surface::*)(const std::wstring&) const, &t_surface::f_write_to_png>())
		(L"write_to_png_stream", t_member<void (t_surface::*)(t_object*) const, &t_surface::f_write_to_png_stream>())
	;
}

t_type* t_type_of<t_surface>::f_derive(t_object* a_this)
{
	return 0;
}

void t_type_of<t_surface>::f_finalize(t_object* a_this)
{
	t_surface* p = static_cast<t_surface*>(a_this->v_pointer);
	assert(!*p);
	delete p;
}

void t_type_of<t_surface>::f_construct(t_object* a_class, size_t a_n, t_stack& a_stack)
{
	t_construct_with<t_transfer (*)(t_object*, t_surface&, cairo_content_t, int, int), t_surface::f_construct>::f_call(a_class, a_n, a_stack);
}

void t_type_of<t_surface>::f_instantiate(t_object* a_class, size_t a_n, t_stack& a_stack)
{
	f_construct(a_class, a_n, a_stack);
}

void t_type_of<cairo_content_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_content_t, int>(a_extension, L"Content")
		(L"COLOR", CAIRO_CONTENT_COLOR)
		(L"ALPHA", CAIRO_CONTENT_ALPHA)
		(L"COLOR_ALPHA", CAIRO_CONTENT_COLOR_ALPHA)
	;
}

void t_type_of<cairo_surface_type_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_surface_type_t, int>(a_extension, L"SurfaceType")
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

void t_type_of<t_image_surface>::f_define(t_extension* a_extension)
{
	t_define<t_image_surface, t_surface>(a_extension, L"ImageSurface")
		(L"get_data", t_member<t_object* (t_image_surface::*)(), &t_image_surface::f_get_data>())
		(L"get_format", t_member<cairo_format_t (t_image_surface::*)() const, &t_image_surface::f_get_format>())
		(L"get_width", t_member<int (t_image_surface::*)() const, &t_image_surface::f_get_width>())
		(L"get_height", t_member<int (t_image_surface::*)() const, &t_image_surface::f_get_height>())
		(L"get_stride", t_member<int (t_image_surface::*)() const, &t_image_surface::f_get_stride>())
		(L"create_from_png", t_static<t_transfer (*)(const std::wstring&), t_image_surface::f_create_from_png>())
		(L"create_from_png_stream", t_static<t_transfer (*)(t_object*), t_image_surface::f_create_from_png_stream>())
	;
}

void t_type_of<t_image_surface>::f_construct(t_object* a_class, size_t a_n, t_stack& a_stack)
{
	t_overload<t_construct_with<t_transfer (*)(t_object*, cairo_format_t, int, int), t_image_surface::f_construct>,
	t_overload<t_construct_with<t_transfer (*)(t_object*, const t_transfer&, cairo_format_t, int, int, int), t_image_surface::f_construct>
	> >::f_call(a_class, a_n, a_stack);
}

void t_type_of<cairo_format_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_format_t, int>(a_extension, L"Format")
		(L"ARGB32", CAIRO_FORMAT_ARGB32)
		(L"RGB24", CAIRO_FORMAT_RGB24)
		(L"A8", CAIRO_FORMAT_A8)
		(L"A1", CAIRO_FORMAT_A1)
	;
}

}
