#include "matrix.h"

namespace xemmai
{

void t_type_of<t_matrix>::f_define(t_extension* a_extension)
{
	t_define<t_matrix, t_object>(a_extension, L"Matrix")
		(L"translate", t_member<void (t_matrix::*)(double, double), &t_matrix::f_translate>())
		(L"scale", t_member<void (t_matrix::*)(double, double), &t_matrix::f_scale>())
		(L"rotate", t_member<void (t_matrix::*)(double), &t_matrix::f_rotate>())
		(L"invert", t_member<cairo_status_t (t_matrix::*)(), &t_matrix::f_invert>())
		(L"multiply", t_member<void (t_matrix::*)(const t_matrix&, const t_matrix&), &t_matrix::f_multiply>())
		(L"transform_distance", t_member<t_scoped (t_matrix::*)(double, double) const, &t_matrix::f_transform_distance>())
		(L"transform_point", t_member<t_scoped (t_matrix::*)(double, double) const, &t_matrix::f_transform_point>())
	;
}

t_type* t_type_of<t_matrix>::f_derive(t_object* a_this)
{
	return nullptr;
}

void t_type_of<t_matrix>::f_finalize(t_object* a_this)
{
	delete f_as<t_matrix*>(a_this);
}

t_scoped t_type_of<t_matrix>::f_construct(t_object* a_class, t_scoped* a_stack, size_t a_n)
{
	return t_overload<
		t_construct<double, double, double, double, double, double>,
		t_construct<>
	>::t_bind<t_matrix>::f_do(a_class, a_stack, a_n);
}

void t_type_of<t_matrix>::f_instantiate(t_object* a_class, t_scoped* a_stack, size_t a_n)
{
	a_stack[0].f_construct(f_construct(a_class, a_stack, a_n));
	for (size_t i = 1; i <= a_n; ++i) a_stack[i] = nullptr;
}

}
