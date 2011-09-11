#include "pattern.h"

#include <cassert>

namespace cairo
{

namespace xemmai
{

t_pattern* t_pattern::f_wrap(cairo_pattern_t* a_value)
{
	if (!a_value) return 0;
	t_pattern* p = f_from(a_value);
	if (p) return p;
	switch (cairo_pattern_get_type(a_value)) {
	case CAIRO_PATTERN_TYPE_SOLID:
		return new t_solid_pattern(a_value);
	case CAIRO_PATTERN_TYPE_SURFACE:
		return new t_surface_pattern(a_value);
	case CAIRO_PATTERN_TYPE_LINEAR:
		return new t_linear_gradient(a_value);
	case CAIRO_PATTERN_TYPE_RADIAL:
		return new t_radial_gradient(a_value);
	default:
		t_throwable::f_throw(L"unknown pattern.");
	}
}

}

}

namespace xemmai
{

void t_type_of<t_pattern>::f_define(t_extension* a_extension)
{
	t_define<t_pattern, t_object>(a_extension, L"Pattern")
		(L"acquire", t_member<void (t_pattern::*)(), &t_pattern::f_acquire>())
		(L"release", t_member<void (t_pattern::*)(), &t_pattern::f_release>())
		(L"status", t_member<cairo_status_t (t_pattern::*)() const, &t_pattern::f_status>())
		(L"set_matrix", t_member<void (t_pattern::*)(const t_matrix&), &t_pattern::f_set_matrix>())
		(L"get_matrix", t_member<t_matrix (t_pattern::*)() const, &t_pattern::f_get_matrix>())
		(L"get_type", t_member<cairo_pattern_type_t (t_pattern::*)() const, &t_pattern::f_get_type>())
	;
}

t_type* t_type_of<t_pattern>::f_derive(t_object* a_this)
{
	return 0;
}

void t_type_of<t_pattern>::f_finalize(t_object* a_this)
{
	t_pattern* p = static_cast<t_pattern*>(a_this->f_pointer());
	assert(!*p);
	delete p;
}

t_transfer t_type_of<t_pattern>::f_construct(t_object* a_class, t_slot* a_stack, size_t a_n)
{
	t_throwable::f_throw(L"uninstantiatable.");
	return t_transfer();
}

void t_type_of<t_pattern>::f_instantiate(t_object* a_class, t_slot* a_stack, size_t a_n)
{
	a_stack[0].f_construct(f_construct(a_class, a_stack, a_n));
	for (size_t i = 1; i <= a_n; ++i) a_stack[i] = 0;
}

void t_type_of<t_solid_pattern>::f_define(t_extension* a_extension)
{
	t_define<t_solid_pattern, t_pattern>(a_extension, L"SolidPattern")
		(L"get_rgba", t_member<t_transfer (t_solid_pattern::*)() const, &t_solid_pattern::f_get_rgba>())
	;
}

t_transfer t_type_of<t_solid_pattern>::f_construct(t_object* a_class, t_slot* a_stack, size_t a_n)
{
	return
		t_overload<t_construct_with<t_transfer (*)(t_object*, double, double, double), t_solid_pattern::f_construct>,
		t_overload<t_construct_with<t_transfer (*)(t_object*, double, double, double, double), t_solid_pattern::f_construct>
	> >::t_bind<t_solid_pattern>::f_do(a_class, a_stack, a_n);
}

void t_type_of<t_surface_pattern>::f_define(t_extension* a_extension)
{
	t_define<t_surface_pattern, t_pattern>(a_extension, L"SurfacePattern")
		(L"get_surface", t_member<t_surface* (t_surface_pattern::*)() const, &t_surface_pattern::f_get_surface>())
		(L"set_extend", t_member<void (t_surface_pattern::*)(cairo_extend_t), &t_surface_pattern::f_set_extend>())
		(L"get_extend", t_member<cairo_extend_t (t_surface_pattern::*)() const, &t_surface_pattern::f_get_extend>())
		(L"set_filter", t_member<void (t_surface_pattern::*)(cairo_filter_t), &t_surface_pattern::f_set_filter>())
		(L"get_filter", t_member<cairo_filter_t (t_surface_pattern::*)() const, &t_surface_pattern::f_get_filter>())
	;
}

t_transfer t_type_of<t_surface_pattern>::f_construct(t_object* a_class, t_slot* a_stack, size_t a_n)
{
	return t_construct_with<t_transfer (*)(t_object*, t_surface&), t_surface_pattern::f_construct>::t_bind<t_surface_pattern>::f_do(a_class, a_stack, a_n);
}

void t_type_of<cairo_extend_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_extend_t, int>(a_extension, L"Extend")
		(L"NONE", CAIRO_EXTEND_NONE)
		(L"REPEAT", CAIRO_EXTEND_REPEAT)
		(L"REFLECT", CAIRO_EXTEND_REFLECT)
		(L"PAD", CAIRO_EXTEND_PAD)
	;
}

void t_type_of<cairo_filter_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_filter_t, int>(a_extension, L"Filter")
		(L"FAST", CAIRO_FILTER_FAST)
		(L"GOOD", CAIRO_FILTER_GOOD)
		(L"BEST", CAIRO_FILTER_BEST)
		(L"NEAREST", CAIRO_FILTER_NEAREST)
		(L"BILINEAR", CAIRO_FILTER_BILINEAR)
		(L"GAUSSIAN", CAIRO_FILTER_GAUSSIAN)
	;
}

void t_type_of<cairo_pattern_type_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_pattern_type_t, int>(a_extension, L"PatternType")
		(L"SOLID", CAIRO_PATTERN_TYPE_SOLID)
		(L"SURFACE", CAIRO_PATTERN_TYPE_SURFACE)
		(L"LINEAR", CAIRO_PATTERN_TYPE_LINEAR)
		(L"RADIAL", CAIRO_PATTERN_TYPE_RADIAL)
	;
}

void t_type_of<t_gradient>::f_define(t_extension* a_extension)
{
	t_define<t_gradient, t_pattern>(a_extension, L"Gradient")
		(L"add_color_stop_rgb", t_member<void (t_gradient::*)(double, double, double, double), &t_gradient::f_add_color_stop>())
		(L"add_color_stop_rgba", t_member<void (t_gradient::*)(double, double, double, double, double), &t_gradient::f_add_color_stop>())
		(L"get_color_stop_count", t_member<int (t_gradient::*)() const, &t_gradient::f_get_color_stop_count>())
		(L"get_color_stop_rgba", t_member<t_transfer (t_gradient::*)(int) const, &t_gradient::f_get_color_stop_rgba>())
	;
}

void t_type_of<t_linear_gradient>::f_define(t_extension* a_extension)
{
	t_define<t_linear_gradient, t_gradient>(a_extension, L"LinearGradient")
		(L"get_linear_points", t_member<t_transfer (t_linear_gradient::*)() const, &t_linear_gradient::f_get_linear_points>())
	;
}

t_transfer t_type_of<t_linear_gradient>::f_construct(t_object* a_class, t_slot* a_stack, size_t a_n)
{
	return t_construct_with<t_transfer (*)(t_object*, double, double, double, double), t_linear_gradient::f_construct>::t_bind<t_linear_gradient>::f_do(a_class, a_stack, a_n);
}

void t_type_of<t_radial_gradient>::f_define(t_extension* a_extension)
{
	t_define<t_radial_gradient, t_gradient>(a_extension, L"RadialGradient")
		(L"get_radial_circles", t_member<t_transfer (t_radial_gradient::*)() const, &t_radial_gradient::f_get_radial_circles>())
	;
}

t_transfer t_type_of<t_radial_gradient>::f_construct(t_object* a_class, t_slot* a_stack, size_t a_n)
{
	return t_construct_with<t_transfer (*)(t_object*, double, double, double, double, double, double), t_radial_gradient::f_construct>::t_bind<t_radial_gradient>::f_do(a_class, a_stack, a_n);
}

}
