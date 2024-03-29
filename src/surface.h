#ifndef XEMMAIX__CAIRO__SURFACE_H
#define XEMMAIX__CAIRO__SURFACE_H

#include "font_options.h"

#include <xemmai/io/file.h>

namespace xemmaix::cairo
{

class t_surface : public t_proxy_of<t_surface, cairo_surface_t>
{
	friend class t_type_of<t_object>;
	friend class t_proxy_of<t_surface, cairo_surface_t>;

	static cairo_status_t f_set_user_data(cairo_surface_t* a_value, const cairo_user_data_key_t* a_key, void* a_user, cairo_destroy_func_t a_destroy)
	{
		return cairo_surface_set_user_data(a_value, a_key, a_user, a_destroy);
	}
	static void* f_get_user_data(cairo_surface_t* a_value, const cairo_user_data_key_t* a_key)
	{
		return cairo_surface_get_user_data(a_value, a_key);
	}
	static cairo_surface_t* f_reference(cairo_surface_t* a_value)
	{
		return cairo_surface_reference(a_value);
	}
	static void f_unreference(cairo_surface_t* a_value)
	{
		cairo_surface_destroy(a_value);
	}
	static cairo_status_t f_write_stream(void* a_closure, const unsigned char* a_data, unsigned int a_length);

protected:
	using t_base::t_base;

public:
	using t_base::f_construct;
	static t_pvalue f_construct(t_type* a_class, t_surface& a_other, cairo_content_t a_content, int a_width, int a_height)
	{
		return f_transfer(a_class->f_new<t_surface>(cairo_surface_create_similar(a_other, a_content, a_width, a_height)));
	}
	static t_surface* f_wrap(cairo_surface_t* a_value);

	void f_acquire()
	{
		t_base::f_acquire();
	}
	void f_release()
	{
		t_base::f_release();
	}
	cairo_status_t f_status() const
	{
		return cairo_surface_status(v_value);
	}
	void f_finish()
	{
		cairo_surface_finish(v_value);
	}
	void f_flush()
	{
		cairo_surface_flush(v_value);
	}
	t_pvalue f_get_font_options() const
	{
		auto options = t_type_of<t_font_options>::f_construct();
		cairo_surface_get_font_options(v_value, t_font_options::f_to(f_as<t_font_options*>(options)));
		return options;
	}
	cairo_content_t f_get_content() const
	{
		return cairo_surface_get_content(v_value);
	}
	void f_mark_dirty()
	{
		cairo_surface_mark_dirty(v_value);
	}
	void f_mark_dirty(int a_x, int a_y, int a_width, int a_height)
	{
		cairo_surface_mark_dirty_rectangle(v_value, a_x, a_y, a_width, a_height);
	}
	void f_set_device_offset(double a_x, double a_y)
	{
		cairo_surface_set_device_offset(v_value, a_x, a_y);
	}
	t_pvalue f_get_device_offset() const
	{
		double x;
		double y;
		cairo_surface_get_device_offset(v_value, &x, &y);
		return f_tuple(x, y);
	}
	void f_set_fallback_resolution(double a_x, double a_y)
	{
		cairo_surface_set_fallback_resolution(v_value, a_x, a_y);
	}
	t_pvalue f_get_fallback_resolution() const
	{
		double x;
		double y;
		cairo_surface_get_fallback_resolution(v_value, &x, &y);
		return f_tuple(x, y);
	}
	cairo_surface_type_t f_get_type() const
	{
		return cairo_surface_get_type(v_value);
	}
	void f_copy_page()
	{
		cairo_surface_copy_page(v_value);
	}
	void f_show_page()
	{
		cairo_surface_show_page(v_value);
	}
	bool f_has_show_text_glyphs() const
	{
		return cairo_surface_has_show_text_glyphs(v_value) != 0;
	}
	void f_write_to_png(std::wstring_view a_path) const
	{
		cairo_surface_write_to_png(v_value, f_convert(a_path).c_str());
	}
	void f_write_to_png_stream(const t_pvalue& a_write) const;
};

class t_image_source
{
protected:
	t_object* v_buffer;
	unsigned char* v_head;
	unsigned char* v_tail;

	virtual size_t f_read(size_t a_offset) = 0;
	void f_read_buffer();
	void f_prefetch_buffer();

public:
	t_image_source() : v_buffer(t_bytes::f_instantiate(1024))
	{
		f_rewind();
		v_tail = v_head;
	}
	unsigned char* f_head()
	{
		return v_head;
	}
	unsigned char* f_tail()
	{
		return v_tail;
	}
	void f_rewind()
	{
		v_head = &f_as<t_bytes&>(v_buffer)[0];
	}
	void f_fill()
	{
		v_tail = v_head + f_read(v_head - &f_as<t_bytes&>(v_buffer)[0]);
	}
	unsigned char f_read_byte()
	{
		if (v_head >= v_tail) f_read_buffer();
		return *v_head++;
	}
	unsigned char f_prefetch_byte()
	{
		if (v_head >= v_tail) f_prefetch_buffer();
		return *v_head++;
	}
	size_t f_read_bytes(unsigned char* a_bytes, size_t a_size)
	{
		if (v_head >= v_tail) {
			f_rewind();
			f_fill();
		}
		size_t n = std::min(static_cast<size_t>(v_tail - v_head), a_size);
		std::copy(v_head, v_head + n, a_bytes);
		v_head += n;
		return n;
	}
};

class t_file_source : public t_image_source
{
	std::FILE* v_file;

protected:
	virtual size_t f_read(size_t a_offset);

public:
	t_file_source(std::wstring_view a_path) : v_file(std::fopen(portable::f_convert(a_path).c_str(), "rb"))
	{
		if (!v_file) portable::f_throw_system_error();
	}
	~t_file_source()
	{
		std::fclose(v_file);
	}
	operator std::FILE*() const
	{
		return v_file;
	}
};

class t_stream_source : public t_image_source
{
	t_pvalue v_read;

protected:
	virtual size_t f_read(size_t a_offset);

public:
	t_stream_source(const t_pvalue& a_read) : v_read(a_read)
	{
	}
};

class t_image_surface : public t_surface
{
	friend class t_surface;
	friend class t_type_of<t_object>;

	static cairo_status_t f_read_stream(void* a_closure, unsigned char* a_data, unsigned int a_length);

	t_rvalue v_data;

	using t_surface::t_surface;
	t_image_surface(cairo_surface_t* a_value, const t_pvalue& a_data) : t_surface(a_value), v_data(a_data)
	{
	}
	virtual void f_destroy();

public:
	static t_pvalue f_construct(t_type* a_class, cairo_format_t a_format, int a_width, int a_height)
	{
		int stride = cairo_format_stride_for_width(a_format, a_width);
		if (a_width < 0 || a_height < 0 || stride < 0) f_throw(L"invalid arguments."sv);
		auto data = t_bytes::f_instantiate(stride * a_height);
		auto& bytes = f_as<t_bytes&>(data);
		return f_transfer(a_class->f_new<t_image_surface>(cairo_image_surface_create_for_data(&bytes[0], a_format, a_width, a_height, stride), data));
	}
	static t_pvalue f_construct(t_type* a_class, const t_pvalue& a_data, cairo_format_t a_format, int a_width, int a_height, int a_stride)
	{
		f_check<t_bytes>(a_data, L"data");
		auto& bytes = f_as<t_bytes&>(a_data);
		if (a_width < 0 || a_height < 0 || a_stride < 0 || static_cast<int>(bytes.f_size()) < a_stride * a_height) f_throw(L"invalid arguments."sv);
		return f_transfer(a_class->f_new<t_image_surface>(cairo_image_surface_create_for_data(&bytes[0], a_format, a_width, a_height, a_stride), a_data));
	}
	static t_pvalue f_create_from_png_source(t_image_source& a_source);
	static t_pvalue f_create_from_png(std::wstring_view a_path)
	{
		return f_transfer(f_new<t_image_surface>(t_session::f_instance()->f_library(), cairo_image_surface_create_from_png(f_convert(a_path).c_str())));
	}
	static t_pvalue f_create_from_png_stream(const t_pvalue& a_read);
	static t_pvalue f_create_from_jpeg_source(t_image_source& a_source);
	static t_pvalue f_create_from_jpeg(std::wstring_view a_path);
	static t_pvalue f_create_from_jpeg_stream(const t_pvalue& a_read);
	static t_pvalue f_create_from_gif_source(t_image_source& a_source);
	static t_pvalue f_create_from_gif(std::wstring_view a_path);
	static t_pvalue f_create_from_gif_stream(const t_pvalue& a_read);
	static t_pvalue f_create_all_from_gif(std::wstring_view a_path);
	static t_pvalue f_create_all_from_gif_stream(const t_pvalue& a_read);
	static t_pvalue f_create_from_source(t_image_source& a_source);
	static t_pvalue f_create_from_file(std::wstring_view a_path)
	{
		t_file_source source(a_path);
		return f_create_from_source(source);
	}
	static t_pvalue f_create_from_stream(const t_pvalue& a_read)
	{
		t_stream_source source(a_read);
		return f_create_from_source(source);
	}

	t_pvalue f_get_data() const
	{
		return v_data;
	}
	cairo_format_t f_get_format() const
	{
		return cairo_image_surface_get_format(v_value);
	}
	int f_get_width() const
	{
		return cairo_image_surface_get_width(v_value);
	}
	int f_get_height() const
	{
		return cairo_image_surface_get_height(v_value);
	}
	int f_get_stride() const
	{
		return cairo_image_surface_get_stride(v_value);
	}
};

}

namespace xemmai
{

template<>
struct t_type_of<xemmaix::cairo::t_surface> : xemmaix::cairo::t_holds<xemmaix::cairo::t_surface>
{
	static void f_define(t_library* a_library);

	using t_base::t_base;
	t_pvalue f_do_construct(t_pvalue* a_stack, size_t a_n);
};

template<>
struct t_type_of<cairo_content_t> : t_enum_of<cairo_content_t, xemmaix::cairo::t_library>
{
	static t_object* f_define(t_library* a_library);

	using t_base::t_base;
};

template<>
struct t_type_of<cairo_surface_type_t> : t_enum_of<cairo_surface_type_t, xemmaix::cairo::t_library>
{
	static t_object* f_define(t_library* a_library);

	using t_base::t_base;
};

template<>
struct t_type_of<xemmaix::cairo::t_image_surface> : t_bears<xemmaix::cairo::t_image_surface, t_type_of<xemmaix::cairo::t_surface>>
{
	static void f_define(t_library* a_library);

	using t_base::t_base;
	t_pvalue f_do_construct(t_pvalue* a_stack, size_t a_n);
};

template<>
struct t_type_of<cairo_format_t> : t_enum_of<cairo_format_t, xemmaix::cairo::t_library>
{
	static t_object* f_define(t_library* a_library);

	using t_base::t_base;
};

}

#endif
