#include "matrix.h"

namespace xemmai
{

void t_type_of<xemmaix::cairo::t_matrix>::f_define(t_extension* a_extension)
{
	using namespace xemmaix::cairo;
	t_define<t_matrix, t_object>(a_extension, L"Matrix")
		(L"translate", t_member<void(t_matrix::*)(double, double), &t_matrix::f_translate>())
		(L"scale", t_member<void(t_matrix::*)(double, double), &t_matrix::f_scale>())
		(L"rotate", t_member<void(t_matrix::*)(double), &t_matrix::f_rotate>())
		(L"invert", t_member<cairo_status_t(t_matrix::*)(), &t_matrix::f_invert>())
		(L"multiply", t_member<void(t_matrix::*)(const t_matrix&, const t_matrix&), &t_matrix::f_multiply>())
		(L"transform_distance", t_member<t_scoped(t_matrix::*)(double, double) const, &t_matrix::f_transform_distance>())
		(L"transform_point", t_member<t_scoped(t_matrix::*)(double, double) const, &t_matrix::f_transform_point>())
	;
}

t_scoped t_type_of<xemmaix::cairo::t_matrix>::f_do_construct(t_stacked* a_stack, size_t a_n)
{
	return t_overload<
		t_construct<double, double, double, double, double, double>,
		t_construct<>
	>::t_bind<xemmaix::cairo::t_matrix>::f_do(this, a_stack, a_n);
}

}
