#ifndef CAIRO__XEMMAI__PATTERN_H
#define CAIRO__XEMMAI__PATTERN_H

#include "matrix.h"
#include "surface.h"

namespace cairo
{

namespace xemmai
{

class t_pattern : public t_proxy_of<t_pattern, cairo_pattern_t>
{
	friend class t_proxy_of<t_pattern, cairo_pattern_t>;

	static cairo_status_t f_set_user_data(cairo_pattern_t* a_value, const cairo_user_data_key_t* a_key, void* a_user, cairo_destroy_func_t a_destroy)
	{
		return cairo_pattern_set_user_data(a_value, a_key, a_user, a_destroy);
	}
	static void* f_get_user_data(cairo_pattern_t* a_value, const cairo_user_data_key_t* a_key)
	{
		return cairo_pattern_get_user_data(a_value, a_key);
	}
	static cairo_pattern_t* f_reference(cairo_pattern_t* a_value)
	{
		return cairo_pattern_reference(a_value);
	}
	static void f_unreference(cairo_pattern_t* a_value)
	{
		cairo_pattern_destroy(a_value);
	}

protected:
	t_pattern(t_object* a_class, cairo_pattern_t* a_value) : t_base(a_class, a_value)
	{
	}

public:
	static t_pattern* f_wrap(cairo_pattern_t* a_value);

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
		return cairo_pattern_status(v_value);
	}
	void f_set_matrix(const t_matrix& a_matrix)
	{
		cairo_pattern_set_matrix(v_value, &a_matrix);
	}
	t_matrix f_get_matrix() const
	{
		cairo_matrix_t matrix;
		cairo_pattern_get_matrix(v_value, &matrix);
		return matrix;
	}
	cairo_pattern_type_t f_get_type() const
	{
		return cairo_pattern_get_type(v_value);
	}
};

class t_solid_pattern : public t_pattern
{
	friend class t_pattern;

	t_solid_pattern(cairo_pattern_t* a_value) : t_pattern(t_session::f_instance()->f_extension()->f_type<t_solid_pattern>(), a_value)
	{
	}

public:
	static t_transfer f_construct(t_object* a_class, double a_red, double a_green, double a_blue)
	{
		return f_transfer(new t_solid_pattern(cairo_pattern_create_rgb(a_red, a_green, a_blue)));
	}
	static t_transfer f_construct(t_object* a_class, double a_red, double a_green, double a_blue, double a_alpha)
	{
		return f_transfer(new t_solid_pattern(cairo_pattern_create_rgba(a_red, a_green, a_blue, a_alpha)));
	}

	t_transfer f_get_rgba() const
	{
		double red;
		double green;
		double blue;
		double alpha;
		cairo_pattern_get_rgba(v_value, &red, &green, &blue, &alpha);
		return f_tuple(f_global()->f_as(red), f_global()->f_as(green), f_global()->f_as(blue), f_global()->f_as(alpha));
	}
};

class t_surface_pattern : public t_pattern
{
	friend class t_pattern;

	t_surface_pattern(cairo_pattern_t* a_value) : t_pattern(t_session::f_instance()->f_extension()->f_type<t_surface_pattern>(), a_value)
	{
	}

public:
	static t_transfer f_construct(t_object* a_class, t_surface& a_surface)
	{
		return f_transfer(new t_surface_pattern(cairo_pattern_create_for_surface(a_surface)));
	}

	t_surface* f_get_surface() const
	{
		cairo_surface_t* surface;
		cairo_pattern_get_surface(v_value, &surface);
		return t_surface::f_wrap(surface);
	}
	void f_set_extend(cairo_extend_t a_extend)
	{
		cairo_pattern_set_extend(v_value, a_extend);
	}
	cairo_extend_t f_get_extend() const
	{
		return cairo_pattern_get_extend(v_value);
	}
	void f_set_filter(cairo_filter_t a_filter)
	{
		cairo_pattern_set_filter(v_value, a_filter);
	}
	cairo_filter_t f_get_filter() const
	{
		return cairo_pattern_get_filter(v_value);
	}
};

class t_gradient : public t_pattern
{
protected:
	t_gradient(t_object* a_class, cairo_pattern_t* a_value) : t_pattern(a_class, a_value)
	{
	}

public:
	void f_add_color_stop(double a_offset, double a_red, double a_green, double a_blue)
	{
		cairo_pattern_add_color_stop_rgb(v_value, a_offset, a_red, a_green, a_blue);
	}
	void f_add_color_stop(double a_offset, double a_red, double a_green, double a_blue, double a_alpha)
	{
		cairo_pattern_add_color_stop_rgba(v_value, a_offset, a_red, a_green, a_blue, a_alpha);
	}
	int f_get_color_stop_count() const
	{
		int count;
		cairo_pattern_get_color_stop_count(v_value, &count);
		return count;
	}
	t_transfer f_get_color_stop_rgba(int a_index) const
	{
		double offset;
		double red;
		double green;
		double blue;
		double alpha;
		cairo_pattern_get_color_stop_rgba(v_value, a_index, &offset, &red, &green, &blue, &alpha);
		return f_tuple(f_global()->f_as(offset), f_global()->f_as(red), f_global()->f_as(green), f_global()->f_as(blue), f_global()->f_as(alpha));
	}
};

class t_linear_gradient : public t_gradient
{
	friend class t_pattern;

	t_linear_gradient(cairo_pattern_t* a_value) : t_gradient(t_session::f_instance()->f_extension()->f_type<t_linear_gradient>(), a_value)
	{
	}

public:
	static t_transfer f_construct(t_object* a_class, double a_x0, double a_y0, double a_x1, double a_y1)
	{
		return f_transfer(new t_linear_gradient(cairo_pattern_create_linear(a_x0, a_y0, a_x1, a_y1)));
	}

	t_transfer f_get_linear_points() const
	{
		double x0;
		double y0;
		double x1;
		double y1;
		cairo_pattern_get_linear_points(v_value, &x0, &y0, &x1, &y1);
		return f_tuple(f_global()->f_as(x0), f_global()->f_as(y0), f_global()->f_as(x1), f_global()->f_as(y1));
	}
};

class t_radial_gradient : public t_gradient
{
	friend class t_pattern;

	t_radial_gradient(cairo_pattern_t* a_value) : t_gradient(t_session::f_instance()->f_extension()->f_type<t_radial_gradient>(), a_value)
	{
	}

public:
	static t_transfer f_construct(t_object* a_class, double a_x0, double a_y0, double a_r0, double a_x1, double a_y1, double a_r1)
	{
		return f_transfer(new t_radial_gradient(cairo_pattern_create_radial(a_x0, a_y0, a_r0, a_x1, a_y1, a_r1)));
	}

	t_transfer f_get_radial_circles() const
	{
		double x0;
		double y0;
		double r0;
		double x1;
		double y1;
		double r1;
		cairo_pattern_get_radial_circles(v_value, &x0, &y0, &r0, &x1, &y1, &r1);
		return f_tuple(f_global()->f_as(x0), f_global()->f_as(y0), f_global()->f_as(r0), f_global()->f_as(x1), f_global()->f_as(y1), f_global()->f_as(r1));
	}
};

}

}

namespace xemmai
{

using cairo::xemmai::t_pattern;
using cairo::xemmai::t_solid_pattern;
using cairo::xemmai::t_surface_pattern;
using cairo::xemmai::t_gradient;
using cairo::xemmai::t_linear_gradient;
using cairo::xemmai::t_radial_gradient;

template<>
struct t_type_of<t_pattern> : t_type
{
#include "cast.h"
	typedef cairo::xemmai::t_extension t_extension;

	static void f_define(t_extension* a_extension);

	t_type_of(const t_transfer& a_module, const t_transfer& a_super) : t_type(a_module, a_super)
	{
	}
	virtual t_type* f_derive(t_object* a_this);
	virtual void f_finalize(t_object* a_this);
	virtual t_transfer f_construct(t_object* a_class, t_slot* a_stack, size_t a_n);
	virtual void f_instantiate(t_object* a_class, t_slot* a_stack, size_t a_n);
};

template<>
struct t_type_of<t_solid_pattern> : t_type_of<t_pattern>
{
	static void f_define(t_extension* a_extension);

	t_type_of(const t_transfer& a_module, const t_transfer& a_super) : t_type_of<t_pattern>(a_module, a_super)
	{
	}
	virtual t_transfer f_construct(t_object* a_class, t_slot* a_stack, size_t a_n);
};

template<>
struct t_type_of<t_surface_pattern> : t_type_of<t_pattern>
{
	static void f_define(t_extension* a_extension);

	t_type_of(const t_transfer& a_module, const t_transfer& a_super) : t_type_of<t_pattern>(a_module, a_super)
	{
	}
	virtual t_transfer f_construct(t_object* a_class, t_slot* a_stack, size_t a_n);
};

template<>
struct t_type_of<cairo_extend_t> : t_enum_of<cairo_extend_t, cairo::xemmai::t_extension>
{
	static void f_define(t_extension* a_extension);

	t_type_of(const t_transfer& a_module, const t_transfer& a_super) : t_base(a_module, a_super)
	{
	}
};

template<>
struct t_type_of<cairo_filter_t> : t_enum_of<cairo_filter_t, cairo::xemmai::t_extension>
{
	static void f_define(t_extension* a_extension);

	t_type_of(const t_transfer& a_module, const t_transfer& a_super) : t_base(a_module, a_super)
	{
	}
};

template<>
struct t_type_of<cairo_pattern_type_t> : t_enum_of<cairo_pattern_type_t, cairo::xemmai::t_extension>
{
	static void f_define(t_extension* a_extension);

	t_type_of(const t_transfer& a_module, const t_transfer& a_super) : t_base(a_module, a_super)
	{
	}
};

template<>
struct t_type_of<t_gradient> : t_type_of<t_pattern>
{
	static void f_define(t_extension* a_extension);

	t_type_of(const t_transfer& a_module, const t_transfer& a_super) : t_type_of<t_pattern>(a_module, a_super)
	{
	}
};

template<>
struct t_type_of<t_linear_gradient> : t_type_of<t_gradient>
{
	static void f_define(t_extension* a_extension);

	t_type_of(const t_transfer& a_module, const t_transfer& a_super) : t_type_of<t_gradient>(a_module, a_super)
	{
	}
	virtual t_transfer f_construct(t_object* a_class, t_slot* a_stack, size_t a_n);
};

template<>
struct t_type_of<t_radial_gradient> : t_type_of<t_gradient>
{
	static void f_define(t_extension* a_extension);

	t_type_of(const t_transfer& a_module, const t_transfer& a_super) : t_type_of<t_gradient>(a_module, a_super)
	{
	}
	virtual t_transfer f_construct(t_object* a_class, t_slot* a_stack, size_t a_n);
};

}

#endif
