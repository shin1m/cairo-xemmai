#include "surface.h"

namespace xemmaix::cairo
{

cairo_status_t t_surface::f_write_stream(void* a_closure, const unsigned char* a_data, unsigned int a_length)
{
	auto& write = *static_cast<const t_pvalue**>(a_closure)[0];
	auto& buffer = *static_cast<const t_pvalue**>(a_closure)[1];
	auto& bytes = f_as<t_bytes&>(buffer);
	try {
		while (a_length > 0) {
			size_t m = std::min(bytes.f_size(), static_cast<size_t>(a_length));
			std::copy(a_data, a_data + m, &bytes[0]);
			write(buffer, 0, m);
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
	auto library = t_session::f_instance()->f_library();
	switch (cairo_surface_get_type(a_value)) {
	case CAIRO_SURFACE_TYPE_IMAGE:
		return &f_new<t_image_surface>(library, a_value)->f_as<t_surface>();
	default:
		return &f_new<t_surface>(library, a_value)->f_as<t_surface>();
	}
}

void t_surface::f_write_to_png_stream(const t_pvalue& a_write) const
{
	t_pvalue buffer = t_bytes::f_instantiate(1024);
	const t_pvalue* closure[] = {
		&a_write, &buffer
	};
	cairo_surface_write_to_png_stream(v_value, f_write_stream, closure);
}

void t_image_source::f_read_buffer()
{
	f_rewind();
	f_fill();
	if (v_head >= v_tail) f_throw(L"unexpected end of stream."sv);
}

void t_image_source::f_prefetch_buffer()
{
	auto& bytes = f_as<t_bytes&>(v_buffer);
	if (v_tail >= &bytes[bytes.f_size()]) f_throw(L"too match prefetching."sv);
	f_fill();
	if (v_head >= v_tail) f_throw(L"unexpected end of stream."sv);
}

size_t t_file_source::f_read(size_t a_offset)
{
	t_safe_region region;
	auto& bytes = f_as<t_bytes&>(v_buffer);
	size_t n = std::fread(&bytes[0] + a_offset, 1, bytes.f_size() - a_offset, *this);
	if (n <= 0 && std::ferror(*this)) f_throw(L"failed to read."sv);
	return n;
}

size_t t_stream_source::f_read(size_t a_offset)
{
	auto& bytes = f_as<t_bytes&>(v_buffer);
	auto p = v_read(v_buffer, a_offset, bytes.f_size() - a_offset);
	f_check<size_t>(p, L"result of read");
	return f_as<size_t>(p);
}

cairo_status_t t_image_surface::f_read_stream(void* a_closure, unsigned char* a_data, unsigned int a_length)
{
	auto& source = *static_cast<t_image_source*>(a_closure);
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

t_pvalue t_image_surface::f_create_from_png_source(t_image_source& a_source)
{
	return f_transfer(f_new<t_image_surface>(t_session::f_instance()->f_library(), cairo_image_surface_create_from_png_stream(f_read_stream, &a_source)));
}

t_pvalue t_image_surface::f_create_from_png_stream(const t_pvalue& a_read)
{
	t_stream_source source(a_read);
	return f_create_from_png_source(source);
}

t_pvalue t_image_surface::f_create_from_source(t_image_source& a_source)
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
	f_throw(L"unknown source."sv);
	return nullptr;
}

}

namespace xemmai
{

void t_type_of<xemmaix::cairo::t_surface>::f_define(t_library* a_library)
{
	using namespace xemmaix::cairo;
	t_define{a_library}
		(L"acquire"sv, t_member<void(t_surface::*)(), &t_surface::f_acquire>())
		(L"release"sv, t_member<void(t_surface::*)(), &t_surface::f_release>())
		(L"status"sv, t_member<cairo_status_t(t_surface::*)() const, &t_surface::f_status>())
		(L"finish"sv, t_member<void(t_surface::*)(), &t_surface::f_finish>())
		(L"flush"sv, t_member<void(t_surface::*)(), &t_surface::f_flush>())
		(L"get_font_options"sv, t_member<t_pvalue(t_surface::*)() const, &t_surface::f_get_font_options>())
		(L"get_content"sv, t_member<cairo_content_t(t_surface::*)() const, &t_surface::f_get_content>())
		(L"mark_dirty"sv, t_member<void(t_surface::*)(), &t_surface::f_mark_dirty>())
		(L"mark_dirty_rectangle"sv, t_member<void(t_surface::*)(int, int, int, int), &t_surface::f_mark_dirty>())
		(L"set_device_offset"sv, t_member<void(t_surface::*)(double, double), &t_surface::f_set_device_offset>())
		(L"get_device_offset"sv, t_member<t_pvalue(t_surface::*)() const, &t_surface::f_get_device_offset>())
		(L"set_fallback_resolution"sv, t_member<void(t_surface::*)(double, double), &t_surface::f_set_fallback_resolution>())
		(L"get_fallback_resolution"sv, t_member<t_pvalue(t_surface::*)() const, &t_surface::f_get_fallback_resolution>())
		(L"get_type"sv, t_member<cairo_surface_type_t(t_surface::*)() const, &t_surface::f_get_type>())
		(L"copy_page"sv, t_member<void(t_surface::*)(), &t_surface::f_copy_page>())
		(L"show_page"sv, t_member<void(t_surface::*)(), &t_surface::f_show_page>())
		(L"has_show_text_glyphs"sv, t_member<bool(t_surface::*)() const, &t_surface::f_has_show_text_glyphs>())
		(L"write_to_png"sv, t_member<void(t_surface::*)(std::wstring_view) const, &t_surface::f_write_to_png>())
		(L"write_to_png_stream"sv, t_member<void(t_surface::*)(const t_pvalue&) const, &t_surface::f_write_to_png_stream>())
	.f_derive<t_surface, t_object>();
}

t_pvalue t_type_of<xemmaix::cairo::t_surface>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_construct_with<t_pvalue(*)(t_type*, xemmaix::cairo::t_surface&, cairo_content_t, int, int), xemmaix::cairo::t_surface::f_construct>::t_bind<xemmaix::cairo::t_surface>::f_do(this, a_stack, a_n);
}

t_object* t_type_of<cairo_content_t>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"COLOR"sv, CAIRO_CONTENT_COLOR)
		(L"ALPHA"sv, CAIRO_CONTENT_ALPHA)
		(L"COLOR_ALPHA"sv, CAIRO_CONTENT_COLOR_ALPHA)
		;
	});
}

t_object* t_type_of<cairo_surface_type_t>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"IMAGE"sv, CAIRO_SURFACE_TYPE_IMAGE)
		(L"PDF"sv, CAIRO_SURFACE_TYPE_PDF)
		(L"PS"sv, CAIRO_SURFACE_TYPE_PS)
		(L"XLIB"sv, CAIRO_SURFACE_TYPE_XLIB)
		(L"XCB"sv, CAIRO_SURFACE_TYPE_XCB)
		(L"GLITZ"sv, CAIRO_SURFACE_TYPE_GLITZ)
		(L"QUARTZ"sv, CAIRO_SURFACE_TYPE_QUARTZ)
		(L"WIN32"sv, CAIRO_SURFACE_TYPE_WIN32)
		(L"BEOS"sv, CAIRO_SURFACE_TYPE_BEOS)
		(L"DIRECTFB"sv, CAIRO_SURFACE_TYPE_DIRECTFB)
		(L"SVG"sv, CAIRO_SURFACE_TYPE_SVG)
		(L"OS2"sv, CAIRO_SURFACE_TYPE_OS2)
		(L"WIN32_PRINTING"sv, CAIRO_SURFACE_TYPE_WIN32_PRINTING)
		(L"QUARTZ_IMAGE"sv, CAIRO_SURFACE_TYPE_QUARTZ_IMAGE)
		;
	});
}

void t_type_of<xemmaix::cairo::t_image_surface>::f_define(t_library* a_library)
{
	using namespace xemmaix::cairo;
	t_define{a_library}
		(L"get_data"sv, t_member<t_pvalue(t_image_surface::*)() const, &t_image_surface::f_get_data>())
		(L"get_format"sv, t_member<cairo_format_t(t_image_surface::*)() const, &t_image_surface::f_get_format>())
		(L"get_width"sv, t_member<int(t_image_surface::*)() const, &t_image_surface::f_get_width>())
		(L"get_height"sv, t_member<int(t_image_surface::*)() const, &t_image_surface::f_get_height>())
		(L"get_stride"sv, t_member<int(t_image_surface::*)() const, &t_image_surface::f_get_stride>())
		(L"create_from_png"sv, t_static<t_pvalue(*)(std::wstring_view), t_image_surface::f_create_from_png>())
		(L"create_from_png_stream"sv, t_static<t_pvalue(*)(const t_pvalue&), t_image_surface::f_create_from_png_stream>())
		(L"create_from_jpeg"sv, t_static<t_pvalue(*)(std::wstring_view), t_image_surface::f_create_from_jpeg>())
		(L"create_from_jpeg_stream"sv, t_static<t_pvalue(*)(const t_pvalue&), t_image_surface::f_create_from_jpeg_stream>())
		(L"create_from_gif"sv, t_static<t_pvalue(*)(std::wstring_view), t_image_surface::f_create_from_gif>())
		(L"create_from_gif_stream"sv, t_static<t_pvalue(*)(const t_pvalue&), t_image_surface::f_create_from_gif_stream>())
		(L"create_all_from_gif"sv, t_static<t_pvalue(*)(std::wstring_view), t_image_surface::f_create_all_from_gif>())
		(L"create_all_from_gif_stream"sv, t_static<t_pvalue(*)(const t_pvalue&), t_image_surface::f_create_all_from_gif_stream>())
		(L"create_from_file"sv, t_static<t_pvalue(*)(std::wstring_view), t_image_surface::f_create_from_file>())
		(L"create_from_stream"sv, t_static<t_pvalue(*)(const t_pvalue&), t_image_surface::f_create_from_stream>())
	.f_derive<t_image_surface, t_surface>();
	a_library->v_type_gif_surface.f_construct(a_library->f_type<t_image_surface>()->f_derive<t_type_of<t_image_surface>>(t_object::f_of(a_library), {{
		t_symbol::f_instantiate(L"left"sv),
		t_symbol::f_instantiate(L"top"sv),
		t_symbol::f_instantiate(L"disposal"sv),
		t_symbol::f_instantiate(L"user_input"sv),
		t_symbol::f_instantiate(L"delay"sv)
	}}));
	auto type = a_library->f_type<t_list>();
	a_library->v_type_gif_surfaces.f_construct((type->*type->v_derive)({{
		t_symbol::f_instantiate(L"width"sv),
		t_symbol::f_instantiate(L"height"sv),
		t_symbol::f_instantiate(L"background"sv),
		t_symbol::f_instantiate(L"aspect"sv)
	}}));
}

t_pvalue t_type_of<xemmaix::cairo::t_image_surface>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_overload<
		t_construct_with<t_pvalue(*)(t_type*, cairo_format_t, int, int), xemmaix::cairo::t_image_surface::f_construct>,
		t_construct_with<t_pvalue(*)(t_type*, const t_pvalue&, cairo_format_t, int, int, int), xemmaix::cairo::t_image_surface::f_construct>
	>::t_bind<xemmaix::cairo::t_image_surface>::f_do(this, a_stack, a_n);
}

t_object* t_type_of<cairo_format_t>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"ARGB32"sv, CAIRO_FORMAT_ARGB32)
		(L"RGB24"sv, CAIRO_FORMAT_RGB24)
		(L"A8"sv, CAIRO_FORMAT_A8)
		(L"A1"sv, CAIRO_FORMAT_A1)
		;
	});
}

}
