#include "pattern.h"

namespace xemmaix::cairo
{

t_pattern* t_pattern::f_wrap(cairo_pattern_t* a_value)
{
	if (!a_value) return nullptr;
	t_pattern* p = f_from(a_value);
	if (p) return p;
	auto extension = t_session::f_instance()->f_extension();
	switch (cairo_pattern_get_type(a_value)) {
	case CAIRO_PATTERN_TYPE_SOLID:
		return &f_new<t_solid_pattern>(extension, false, a_value)->f_as<t_pattern>();
	case CAIRO_PATTERN_TYPE_SURFACE:
		return &f_new<t_surface_pattern>(extension, false, a_value)->f_as<t_pattern>();
	case CAIRO_PATTERN_TYPE_LINEAR:
		return &f_new<t_linear_gradient>(extension, false, a_value)->f_as<t_pattern>();
	case CAIRO_PATTERN_TYPE_RADIAL:
		return &f_new<t_radial_gradient>(extension, false, a_value)->f_as<t_pattern>();
	default:
		f_throw(L"unknown pattern."sv);
	}
}

}

namespace xemmai
{

void t_type_of<xemmaix::cairo::t_pattern>::f_define(t_extension* a_extension)
{
	using namespace xemmaix::cairo;
	t_define<t_pattern, t_object>(a_extension, L"Pattern"sv)
		(L"acquire"sv, t_member<void(t_pattern::*)(), &t_pattern::f_acquire>())
		(L"release"sv, t_member<void(t_pattern::*)(), &t_pattern::f_release>())
		(L"status"sv, t_member<cairo_status_t(t_pattern::*)() const, &t_pattern::f_status>())
		(L"set_matrix"sv, t_member<void(t_pattern::*)(const t_matrix&), &t_pattern::f_set_matrix>())
		(L"get_matrix"sv, t_member<t_matrix(t_pattern::*)() const, &t_pattern::f_get_matrix>())
		(L"get_type"sv, t_member<cairo_pattern_type_t(t_pattern::*)() const, &t_pattern::f_get_type>())
	;
}

t_scoped t_type_of<xemmaix::cairo::t_pattern>::f_do_construct(t_stacked* a_stack, size_t a_n)
{
	f_throw(L"uninstantiatable."sv);
}

void t_type_of<xemmaix::cairo::t_solid_pattern>::f_define(t_extension* a_extension)
{
	using namespace xemmaix::cairo;
	t_define<t_solid_pattern, t_pattern>(a_extension, L"SolidPattern"sv)
		(L"get_rgba"sv, t_member<t_scoped(t_solid_pattern::*)() const, &t_solid_pattern::f_get_rgba>())
	;
}

t_scoped t_type_of<xemmaix::cairo::t_solid_pattern>::f_do_construct(t_stacked* a_stack, size_t a_n)
{
	return t_overload<
		t_construct_with<t_scoped(*)(t_type*, double, double, double), xemmaix::cairo::t_solid_pattern::f_construct>,
		t_construct_with<t_scoped(*)(t_type*, double, double, double, double), xemmaix::cairo::t_solid_pattern::f_construct>
	>::t_bind<xemmaix::cairo::t_solid_pattern>::f_do(this, a_stack, a_n);
}

void t_type_of<xemmaix::cairo::t_surface_pattern>::f_define(t_extension* a_extension)
{
	using namespace xemmaix::cairo;
	t_define<t_surface_pattern, t_pattern>(a_extension, L"SurfacePattern"sv)
		(L"get_surface"sv, t_member<t_surface*(t_surface_pattern::*)() const, &t_surface_pattern::f_get_surface>())
		(L"set_extend"sv, t_member<void(t_surface_pattern::*)(cairo_extend_t), &t_surface_pattern::f_set_extend>())
		(L"get_extend"sv, t_member<cairo_extend_t(t_surface_pattern::*)() const, &t_surface_pattern::f_get_extend>())
		(L"set_filter"sv, t_member<void(t_surface_pattern::*)(cairo_filter_t), &t_surface_pattern::f_set_filter>())
		(L"get_filter"sv, t_member<cairo_filter_t(t_surface_pattern::*)() const, &t_surface_pattern::f_get_filter>())
	;
}

t_scoped t_type_of<xemmaix::cairo::t_surface_pattern>::f_do_construct(t_stacked* a_stack, size_t a_n)
{
	return t_construct_with<t_scoped(*)(t_type*, xemmaix::cairo::t_surface&), xemmaix::cairo::t_surface_pattern::f_construct>::t_bind<xemmaix::cairo::t_surface_pattern>::f_do(this, a_stack, a_n);
}

void t_type_of<cairo_extend_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_extend_t, intptr_t>(a_extension, L"Extend"sv)
		(L"NONE"sv, CAIRO_EXTEND_NONE)
		(L"REPEAT"sv, CAIRO_EXTEND_REPEAT)
		(L"REFLECT"sv, CAIRO_EXTEND_REFLECT)
		(L"PAD"sv, CAIRO_EXTEND_PAD)
	;
}

void t_type_of<cairo_filter_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_filter_t, intptr_t>(a_extension, L"Filter"sv)
		(L"FAST"sv, CAIRO_FILTER_FAST)
		(L"GOOD"sv, CAIRO_FILTER_GOOD)
		(L"BEST"sv, CAIRO_FILTER_BEST)
		(L"NEAREST"sv, CAIRO_FILTER_NEAREST)
		(L"BILINEAR"sv, CAIRO_FILTER_BILINEAR)
		(L"GAUSSIAN"sv, CAIRO_FILTER_GAUSSIAN)
	;
}

void t_type_of<cairo_pattern_type_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_pattern_type_t, intptr_t>(a_extension, L"PatternType"sv)
		(L"SOLID"sv, CAIRO_PATTERN_TYPE_SOLID)
		(L"SURFACE"sv, CAIRO_PATTERN_TYPE_SURFACE)
		(L"LINEAR"sv, CAIRO_PATTERN_TYPE_LINEAR)
		(L"RADIAL"sv, CAIRO_PATTERN_TYPE_RADIAL)
	;
}

void t_type_of<xemmaix::cairo::t_gradient>::f_define(t_extension* a_extension)
{
	using namespace xemmaix::cairo;
	t_define<t_gradient, t_pattern>(a_extension, L"Gradient"sv)
		(L"add_color_stop_rgb"sv, t_member<void(t_gradient::*)(double, double, double, double), &t_gradient::f_add_color_stop>())
		(L"add_color_stop_rgba"sv, t_member<void(t_gradient::*)(double, double, double, double, double), &t_gradient::f_add_color_stop>())
		(L"get_color_stop_count"sv, t_member<int(t_gradient::*)() const, &t_gradient::f_get_color_stop_count>())
		(L"get_color_stop_rgba"sv, t_member<t_scoped(t_gradient::*)(int) const, &t_gradient::f_get_color_stop_rgba>())
	;
}

void t_type_of<xemmaix::cairo::t_linear_gradient>::f_define(t_extension* a_extension)
{
	using namespace xemmaix::cairo;
	t_define<t_linear_gradient, t_gradient>(a_extension, L"LinearGradient"sv)
		(L"get_linear_points"sv, t_member<t_scoped(t_linear_gradient::*)() const, &t_linear_gradient::f_get_linear_points>())
	;
}

t_scoped t_type_of<xemmaix::cairo::t_linear_gradient>::f_do_construct(t_stacked* a_stack, size_t a_n)
{
	return t_construct_with<t_scoped(*)(t_type*, double, double, double, double), xemmaix::cairo::t_linear_gradient::f_construct>::t_bind<xemmaix::cairo::t_linear_gradient>::f_do(this, a_stack, a_n);
}

void t_type_of<xemmaix::cairo::t_radial_gradient>::f_define(t_extension* a_extension)
{
	using namespace xemmaix::cairo;
	t_define<t_radial_gradient, t_gradient>(a_extension, L"RadialGradient"sv)
		(L"get_radial_circles"sv, t_member<t_scoped(t_radial_gradient::*)() const, &t_radial_gradient::f_get_radial_circles>())
	;
}

t_scoped t_type_of<xemmaix::cairo::t_radial_gradient>::f_do_construct(t_stacked* a_stack, size_t a_n)
{
	return t_construct_with<t_scoped(*)(t_type*, double, double, double, double, double, double), xemmaix::cairo::t_radial_gradient::f_construct>::t_bind<xemmaix::cairo::t_radial_gradient>::f_do(this, a_stack, a_n);
}

}
