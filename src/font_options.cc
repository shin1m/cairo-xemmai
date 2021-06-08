#include "font_options.h"

namespace xemmai
{

void t_type_of<xemmaix::cairo::t_font_options>::f_define(t_library* a_library)
{
	using namespace xemmaix::cairo;
	t_define{a_library}
		(L"status"sv, t_member<cairo_status_t(*)(t_font_options*), t_font_options::f_status>())
		(L"merge"sv, t_member<void(*)(t_font_options*, const t_font_options*), t_font_options::f_merge>())
		(L"hash"sv, t_member<intptr_t(*)(const t_font_options*), t_font_options::f_hash>())
		(L"equal"sv, t_member<bool(*)(const t_font_options*, const t_font_options*), t_font_options::f_equal>())
		(L"set_antialias"sv, t_member<void(*)(t_font_options*, cairo_antialias_t), t_font_options::f_set_antialias>())
		(L"get_antialias"sv, t_member<cairo_antialias_t(*)(const t_font_options*), t_font_options::f_get_antialias>())
		(L"set_subpixel_order"sv, t_member<void(*)(t_font_options*, cairo_subpixel_order_t), t_font_options::f_set_subpixel_order>())
		(L"get_subpixel_order"sv, t_member<cairo_subpixel_order_t(*)(const t_font_options*), t_font_options::f_get_subpixel_order>())
		(L"set_hint_style"sv, t_member<void(*)(t_font_options*, cairo_hint_style_t), t_font_options::f_set_hint_style>())
		(L"get_hint_style"sv, t_member<cairo_hint_style_t(*)(const t_font_options*), t_font_options::f_get_hint_style>())
		(L"set_hint_metrics"sv, t_member<void(*)(t_font_options*, cairo_hint_metrics_t), t_font_options::f_set_hint_metrics>())
		(L"get_hint_metrics"sv, t_member<cairo_hint_metrics_t(*)(const t_font_options*), t_font_options::f_get_hint_metrics>())
	.f_derive<t_font_options, t_object>();
}

void t_type_of<xemmaix::cairo::t_font_options>::f_do_finalize(t_object* a_this)
{
	xemmaix::cairo::t_font_options::f_destroy(a_this->f_as<xemmaix::cairo::t_font_options*>());
}

t_pvalue t_type_of<xemmaix::cairo::t_font_options>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_overload<
		t_construct_with<t_pvalue(*)(t_type*), f_construct>,
		t_construct_with<t_pvalue(*)(t_type*, const xemmaix::cairo::t_font_options*), f_construct>
	>::t_bind<xemmaix::cairo::t_font_options>::f_do(this, a_stack, a_n);
}

t_object* t_type_of<cairo_antialias_t>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"DEFAULT"sv, CAIRO_ANTIALIAS_DEFAULT)
		(L"NONE"sv, CAIRO_ANTIALIAS_NONE)
		(L"GRAY"sv, CAIRO_ANTIALIAS_GRAY)
		(L"SUBPIXEL"sv, CAIRO_ANTIALIAS_SUBPIXEL)
		;
	});
}

t_object* t_type_of<cairo_subpixel_order_t>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"DEFAULT"sv, CAIRO_SUBPIXEL_ORDER_DEFAULT)
		(L"RGB"sv, CAIRO_SUBPIXEL_ORDER_RGB)
		(L"BGR"sv, CAIRO_SUBPIXEL_ORDER_BGR)
		(L"VRGB"sv, CAIRO_SUBPIXEL_ORDER_VRGB)
		(L"VBGR"sv, CAIRO_SUBPIXEL_ORDER_VBGR)
		;
	});
}

t_object* t_type_of<cairo_hint_style_t>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"DEFAULT"sv, CAIRO_HINT_STYLE_DEFAULT)
		(L"NONE"sv, CAIRO_HINT_STYLE_NONE)
		(L"SLIGHT"sv, CAIRO_HINT_STYLE_SLIGHT)
		(L"MEDIUM"sv, CAIRO_HINT_STYLE_MEDIUM)
		(L"FULL"sv, CAIRO_HINT_STYLE_FULL)
		;
	});
}

t_object* t_type_of<cairo_hint_metrics_t>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"DEFAULT"sv, CAIRO_HINT_METRICS_DEFAULT)
		(L"OFF"sv, CAIRO_HINT_METRICS_OFF)
		(L"ON"sv, CAIRO_HINT_METRICS_ON)
		;
	});
}

}
