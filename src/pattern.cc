#include "pattern.h"

namespace xemmaix::cairo
{

t_pattern* t_pattern::f_wrap(cairo_pattern_t* a_value)
{
	if (!a_value) return nullptr;
	t_pattern* p = f_from(a_value);
	if (p) return p;
	auto library = t_session::f_instance()->f_library();
	switch (cairo_pattern_get_type(a_value)) {
	case CAIRO_PATTERN_TYPE_SOLID:
		return &f_new<t_solid_pattern>(library, a_value)->f_as<t_pattern>();
	case CAIRO_PATTERN_TYPE_SURFACE:
		return &f_new<t_surface_pattern>(library, a_value)->f_as<t_pattern>();
	case CAIRO_PATTERN_TYPE_LINEAR:
		return &f_new<t_linear_gradient>(library, a_value)->f_as<t_pattern>();
	case CAIRO_PATTERN_TYPE_RADIAL:
		return &f_new<t_radial_gradient>(library, a_value)->f_as<t_pattern>();
	default:
		f_throw(L"unknown pattern."sv);
	}
}

}

namespace xemmai
{

void t_type_of<xemmaix::cairo::t_pattern>::f_define(t_library* a_library)
{
	using namespace xemmaix::cairo;
	t_define{a_library}
		(L"acquire"sv, t_member<void(t_pattern::*)(), &t_pattern::f_acquire>())
		(L"release"sv, t_member<void(t_pattern::*)(), &t_pattern::f_release>())
		(L"status"sv, t_member<cairo_status_t(t_pattern::*)() const, &t_pattern::f_status>())
		(L"set_matrix"sv, t_member<void(t_pattern::*)(const t_matrix&), &t_pattern::f_set_matrix>())
		(L"get_matrix"sv, t_member<t_matrix(t_pattern::*)() const, &t_pattern::f_get_matrix>())
		(L"get_type"sv, t_member<cairo_pattern_type_t(t_pattern::*)() const, &t_pattern::f_get_type>())
	.f_derive<t_pattern, t_object>();
}

t_pvalue t_type_of<xemmaix::cairo::t_pattern>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	f_throw(L"uninstantiatable."sv);
}

void t_type_of<xemmaix::cairo::t_solid_pattern>::f_define(t_library* a_library)
{
	using namespace xemmaix::cairo;
	t_define{a_library}
		(L"get_rgba"sv, t_member<t_pvalue(t_solid_pattern::*)() const, &t_solid_pattern::f_get_rgba>())
	.f_derive<t_solid_pattern, t_pattern>();
}

t_pvalue t_type_of<xemmaix::cairo::t_solid_pattern>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_overload<
		t_construct_with<t_pvalue(*)(t_type*, double, double, double), xemmaix::cairo::t_solid_pattern::f_construct>,
		t_construct_with<t_pvalue(*)(t_type*, double, double, double, double), xemmaix::cairo::t_solid_pattern::f_construct>
	>::t_bind<xemmaix::cairo::t_solid_pattern>::f_do(this, a_stack, a_n);
}

void t_type_of<xemmaix::cairo::t_surface_pattern>::f_define(t_library* a_library)
{
	using namespace xemmaix::cairo;
	t_define{a_library}
		(L"get_surface"sv, t_member<t_surface*(t_surface_pattern::*)() const, &t_surface_pattern::f_get_surface>())
		(L"set_extend"sv, t_member<void(t_surface_pattern::*)(cairo_extend_t), &t_surface_pattern::f_set_extend>())
		(L"get_extend"sv, t_member<cairo_extend_t(t_surface_pattern::*)() const, &t_surface_pattern::f_get_extend>())
		(L"set_filter"sv, t_member<void(t_surface_pattern::*)(cairo_filter_t), &t_surface_pattern::f_set_filter>())
		(L"get_filter"sv, t_member<cairo_filter_t(t_surface_pattern::*)() const, &t_surface_pattern::f_get_filter>())
	.f_derive<t_surface_pattern, t_pattern>();
}

t_pvalue t_type_of<xemmaix::cairo::t_surface_pattern>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_construct_with<t_pvalue(*)(t_type*, xemmaix::cairo::t_surface&), xemmaix::cairo::t_surface_pattern::f_construct>::t_bind<xemmaix::cairo::t_surface_pattern>::f_do(this, a_stack, a_n);
}

t_object* t_type_of<cairo_extend_t>::f_define(t_library* a_library)
{
	t_define{a_library}.f_derive<cairo_extend_t, intptr_t>();
	return a_library->f_type<cairo_extend_t>()->f_do_derive({{}, t_define(a_library)
		(L"NONE"sv, CAIRO_EXTEND_NONE)
		(L"REPEAT"sv, CAIRO_EXTEND_REPEAT)
		(L"REFLECT"sv, CAIRO_EXTEND_REFLECT)
		(L"PAD"sv, CAIRO_EXTEND_PAD)
	});
}

t_object* t_type_of<cairo_filter_t>::f_define(t_library* a_library)
{
	t_define{a_library}.f_derive<cairo_filter_t, intptr_t>();
	return a_library->f_type<cairo_filter_t>()->f_do_derive({{}, t_define(a_library)
		(L"FAST"sv, CAIRO_FILTER_FAST)
		(L"GOOD"sv, CAIRO_FILTER_GOOD)
		(L"BEST"sv, CAIRO_FILTER_BEST)
		(L"NEAREST"sv, CAIRO_FILTER_NEAREST)
		(L"BILINEAR"sv, CAIRO_FILTER_BILINEAR)
		(L"GAUSSIAN"sv, CAIRO_FILTER_GAUSSIAN)
	});
}

t_object* t_type_of<cairo_pattern_type_t>::f_define(t_library* a_library)
{
	t_define{a_library}.f_derive<cairo_pattern_type_t, intptr_t>();
	return a_library->f_type<cairo_pattern_type_t>()->f_do_derive({{}, t_define(a_library)
		(L"SOLID"sv, CAIRO_PATTERN_TYPE_SOLID)
		(L"SURFACE"sv, CAIRO_PATTERN_TYPE_SURFACE)
		(L"LINEAR"sv, CAIRO_PATTERN_TYPE_LINEAR)
		(L"RADIAL"sv, CAIRO_PATTERN_TYPE_RADIAL)
	});
}

void t_type_of<xemmaix::cairo::t_gradient>::f_define(t_library* a_library)
{
	using namespace xemmaix::cairo;
	t_define{a_library}
		(L"add_color_stop_rgb"sv, t_member<void(t_gradient::*)(double, double, double, double), &t_gradient::f_add_color_stop>())
		(L"add_color_stop_rgba"sv, t_member<void(t_gradient::*)(double, double, double, double, double), &t_gradient::f_add_color_stop>())
		(L"get_color_stop_count"sv, t_member<int(t_gradient::*)() const, &t_gradient::f_get_color_stop_count>())
		(L"get_color_stop_rgba"sv, t_member<t_pvalue(t_gradient::*)(int) const, &t_gradient::f_get_color_stop_rgba>())
	.f_derive<t_gradient, t_pattern>();
}

void t_type_of<xemmaix::cairo::t_linear_gradient>::f_define(t_library* a_library)
{
	using namespace xemmaix::cairo;
	t_define{a_library}
		(L"get_linear_points"sv, t_member<t_pvalue(t_linear_gradient::*)() const, &t_linear_gradient::f_get_linear_points>())
	.f_derive<t_linear_gradient, t_gradient>();
}

t_pvalue t_type_of<xemmaix::cairo::t_linear_gradient>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_construct_with<t_pvalue(*)(t_type*, double, double, double, double), xemmaix::cairo::t_linear_gradient::f_construct>::t_bind<xemmaix::cairo::t_linear_gradient>::f_do(this, a_stack, a_n);
}

void t_type_of<xemmaix::cairo::t_radial_gradient>::f_define(t_library* a_library)
{
	using namespace xemmaix::cairo;
	t_define{a_library}
		(L"get_radial_circles"sv, t_member<t_pvalue(t_radial_gradient::*)() const, &t_radial_gradient::f_get_radial_circles>())
	.f_derive<t_radial_gradient, t_gradient>();
}

t_pvalue t_type_of<xemmaix::cairo::t_radial_gradient>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_construct_with<t_pvalue(*)(t_type*, double, double, double, double, double, double), xemmaix::cairo::t_radial_gradient::f_construct>::t_bind<xemmaix::cairo::t_radial_gradient>::f_do(this, a_stack, a_n);
}

}
