#ifndef CAIRO__XEMMAI__SURFACE_H
#define CAIRO__XEMMAI__SURFACE_H

#include "cairo.h"

namespace cairo
{

namespace xemmai
{

class t_surface : public t_proxy_of<t_surface, cairo_surface_t>
{
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

	t_surface(cairo_surface_t* a_value) : t_base(t_session::f_instance()->f_extension()->f_type<t_surface>(), a_value)
	{
	}

protected:
	t_surface(t_object* a_class, cairo_surface_t* a_value) : t_base(a_class, a_value)
	{
	}

public:
	using t_base::f_construct;
	static t_transfer f_construct(t_object* a_class, t_surface& a_other, cairo_content_t a_content, int a_width, int a_height)
	{
		return f_transfer(new t_surface(cairo_surface_create_similar(a_other, a_content, a_width, a_height)));
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
	void f_get_font_options(cairo_font_options_t* a_options) const
	{
		cairo_surface_get_font_options(v_value, a_options);
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
	t_transfer f_get_device_offset() const
	{
		double x;
		double y;
		cairo_surface_get_device_offset(v_value, &x, &y);
		return f_array(f_global()->f_as(x), f_global()->f_as(y));
	}
	void f_set_fallback_resolution(double a_x, double a_y)
	{
		cairo_surface_set_fallback_resolution(v_value, a_x, a_y);
	}
	t_transfer f_get_fallback_resolution() const
	{
		double x;
		double y;
		cairo_surface_get_fallback_resolution(v_value, &x, &y);
		return f_array(f_global()->f_as(x), f_global()->f_as(y));
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
		return cairo_surface_has_show_text_glyphs(v_value);
	}
	void f_write_to_png(const std::wstring& a_path) const
	{
		cairo_surface_write_to_png(v_value, f_convert(a_path).c_str());
	}
};

class t_image_surface : public t_surface
{
	friend class t_surface;

	t_scoped v_data;

	t_image_surface(cairo_surface_t* a_value) : t_surface(t_session::f_instance()->f_extension()->f_type<t_image_surface>(), a_value)
	{
	}
	t_image_surface(cairo_surface_t* a_value, const t_transfer& a_data) : t_surface(t_session::f_instance()->f_extension()->f_type<t_image_surface>(), a_value), v_data(a_data)
	{
	}
	virtual void f_destroy();

public:
	static t_transfer f_construct(t_object* a_class, cairo_format_t a_format, int a_width, int a_height)
	{
		return f_transfer(new t_image_surface(cairo_image_surface_create(a_format, a_width, a_height)));
	}
	static t_transfer f_construct(t_object* a_class, const t_transfer& a_data, cairo_format_t a_format, int a_width, int a_height, int a_stride)
	{
		f_check<t_bytes>(a_data, L"data");
		t_bytes& data = f_as<t_bytes&>(a_data);
		return f_transfer(new t_image_surface(cairo_image_surface_create_for_data(&data[0], a_format, a_width, a_height, a_stride), a_data));
	}
	static t_transfer f_construct(const std::wstring& a_path)
	{
		return f_transfer(new t_image_surface(cairo_image_surface_create_from_png(f_convert(a_path).c_str())));
	}

	t_object* f_get_data()
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

}

namespace xemmai
{

using cairo::xemmai::t_surface;
using cairo::xemmai::t_image_surface;

template<>
struct t_type_of<t_surface> : t_type
{
#include "cast.h"
	typedef cairo::xemmai::t_extension t_extension;

	static void f_define(t_extension* a_extension);

	t_type_of(const t_transfer& a_module, const t_transfer& a_super) : t_type(a_module, a_super)
	{
	}
	virtual t_type* f_derive(t_object* a_this);
	virtual void f_finalize(t_object* a_this);
	virtual void f_construct(t_object* a_class, size_t a_n, t_stack& a_stack);
	virtual void f_instantiate(t_object* a_class, size_t a_n, t_stack& a_stack);
};

template<>
struct t_type_of<cairo_content_t> : t_enum_of<cairo_content_t, cairo::xemmai::t_extension>
{
	static void f_define(t_extension* a_extension);

	t_type_of(const t_transfer& a_module, const t_transfer& a_super) : t_base(a_module, a_super)
	{
	}
};

template<>
struct t_type_of<cairo_surface_type_t> : t_enum_of<cairo_surface_type_t, cairo::xemmai::t_extension>
{
	static void f_define(t_extension* a_extension);

	t_type_of(const t_transfer& a_module, const t_transfer& a_super) : t_base(a_module, a_super)
	{
	}
};

template<>
struct t_type_of<t_image_surface> : t_type_of<t_surface>
{
	static void f_define(t_extension* a_extension);

	t_type_of(const t_transfer& a_module, const t_transfer& a_super) : t_type_of<t_surface>(a_module, a_super)
	{
	}
	virtual void f_construct(t_object* a_class, size_t a_n, t_stack& a_stack);
};

template<>
struct t_type_of<cairo_format_t> : t_enum_of<cairo_format_t, cairo::xemmai::t_extension>
{
	static void f_define(t_extension* a_extension);

	t_type_of(const t_transfer& a_module, const t_transfer& a_super) : t_base(a_module, a_super)
	{
	}
};

}

#endif
