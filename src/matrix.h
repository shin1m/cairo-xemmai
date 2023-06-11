#ifndef XEMMAIX__CAIRO__MATRIX_H
#define XEMMAIX__CAIRO__MATRIX_H

#include "cairo.h"

namespace xemmaix::cairo
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
	t_pvalue f_transform_distance(double a_x, double a_y) const
	{
		cairo_matrix_transform_distance(this, &a_x, &a_y);
		return f_tuple(a_x, a_y);
	}
	t_pvalue f_transform_point(double a_x, double a_y) const
	{
		cairo_matrix_transform_point(this, &a_x, &a_y);
		return f_tuple(a_x, a_y);
	}
};

}

namespace xemmai
{

template<>
struct t_type_of<xemmaix::cairo::t_matrix> : xemmaix::cairo::t_instantiatable<t_holds<xemmaix::cairo::t_matrix>>
{
	using t_library = xemmaix::cairo::t_library;

	static t_pvalue f_transfer(auto* a_library, auto&& a_value)
	{
		return xemmai::f_new<typename t_fundamental<decltype(a_value)>::t_type>(a_library, std::forward<decltype(a_value)>(a_value));
	}
	static void f_define(t_library* a_library);

	using t_base::t_base;
	t_pvalue f_do_construct(t_pvalue* a_stack, size_t a_n);
};

}

#endif
