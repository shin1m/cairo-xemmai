#ifndef XEMMAIX__CAIRO__MATRIX_H
#define XEMMAIX__CAIRO__MATRIX_H

#include "cairo.h"

namespace xemmaix
{

namespace cairo
{

struct t_matrix : cairo_matrix_t
{
	/*
	static t_matrix f_translate(double a_x, double a_y)
	{
		t_matrix matrix;
		cairo_matrix_init_translate(&matrix, a_x, a_y);
		return matrix;
	}
	static t_matrix f_scale(double a_x, double a_y)
	{
		t_matrix matrix;
		cairo_matrix_init_scale(&matrix, a_x, a_y);
		return matrix;
	}
	static t_matrix f_rotate(double a_radians)
	{
		t_matrix matrix;
		cairo_matrix_init_rotate(&matrix, a_radians);
		return matrix;
	}
	*/

	t_matrix(double a_xx, double a_yx, double a_xy, double a_yy, double a_x0, double a_y0)
	{
		cairo_matrix_init(this, a_xx, a_yx, a_xy, a_yy, a_x0, a_y0);
	}
	t_matrix()
	{
		cairo_matrix_init_identity(this);
	}
	t_matrix(const cairo_matrix_t& a_0)
	{
		*static_cast<cairo_matrix_t*>(this) = a_0;
	}
	void f_translate(double a_x, double a_y)
	{
		cairo_matrix_translate(this, a_x, a_y);
	}
	void f_scale(double a_x, double a_y)
	{
		cairo_matrix_scale(this, a_x, a_y);
	}
	void f_rotate(double a_radians)
	{
		cairo_matrix_rotate(this, a_radians);
	}
	cairo_status_t f_invert()
	{
		return cairo_matrix_invert(this);
	}
	void f_multiply(const t_matrix& a_0, const t_matrix& a_1)
	{
		cairo_matrix_multiply(this, &a_0, &a_1);
	}
	t_scoped f_transform_distance(double a_x, double a_y) const
	{
		cairo_matrix_transform_distance(this, &a_x, &a_y);
		return f_tuple(f_global()->f_as(a_x), f_global()->f_as(a_y));
	}
	t_scoped f_transform_point(double a_x, double a_y) const
	{
		cairo_matrix_transform_point(this, &a_x, &a_y);
		return f_tuple(f_global()->f_as(a_x), f_global()->f_as(a_y));
	}
};

}

}

namespace xemmai
{

template<>
struct t_type_of<xemmaix::cairo::t_matrix> : t_type
{
	typedef xemmaix::cairo::t_extension t_extension;

	template<typename T_extension, typename T>
	static t_scoped f_transfer(T_extension* a_extension, T a_value)
	{
		t_scoped object = t_object::f_allocate(a_extension->template f_type<typename t_fundamental<T>::t_type>());
		object.f_pointer__(new xemmaix::cairo::t_matrix(std::forward<T>(a_value)));
		return object;
	}
	static void f_define(t_extension* a_extension);

	using t_type::t_type;
	virtual t_type* f_derive(t_object* a_this);
	virtual void f_finalize(t_object* a_this);
	virtual t_scoped f_construct(t_object* a_class, t_stacked* a_stack, size_t a_n);
	virtual void f_instantiate(t_object* a_class, t_stacked* a_stack, size_t a_n);
};

}

#endif
