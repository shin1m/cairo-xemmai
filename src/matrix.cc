#include "matrix.h"

namespace xemmai
{

void t_type_of<xemmaix::cairo::t_matrix>::f_define(t_library* a_library)
{
	using namespace xemmaix::cairo;
	t_define{a_library}
	(L"translate"sv, t_member<void(t_matrix::*)(double, double), &t_matrix::f_translate>())
	(L"scale"sv, t_member<void(t_matrix::*)(double, double), &t_matrix::f_scale>())
	(L"rotate"sv, t_member<void(t_matrix::*)(double), &t_matrix::f_rotate>())
	(L"invert"sv, t_member<cairo_status_t(t_matrix::*)(), &t_matrix::f_invert>())
	(L"multiply"sv, t_member<void(t_matrix::*)(const t_matrix&, const t_matrix&), &t_matrix::f_multiply>())
	(L"transform_distance"sv, t_member<t_pvalue(t_matrix::*)(double, double) const, &t_matrix::f_transform_distance>())
	(L"transform_point"sv, t_member<t_pvalue(t_matrix::*)(double, double) const, &t_matrix::f_transform_point>())
	.f_derive<t_matrix, t_object>();
}

t_pvalue t_type_of<xemmaix::cairo::t_matrix>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_overload<
		t_construct<double, double, double, double, double, double>,
		t_construct<>
	>::t_bind<xemmaix::cairo::t_matrix>::f_do(this, a_stack, a_n);
}

}
