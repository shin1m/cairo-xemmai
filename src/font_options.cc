#include "font_options.h"

namespace xemmai
{

void t_type_of<xemmaix::cairo::t_font_options>::f_define(t_extension* a_extension)
{
	using namespace xemmaix::cairo;
	t_define<t_font_options, t_object>(a_extension, L"FontOptions")
		(L"status", t_member<cairo_status_t(*)(t_font_options*), t_font_options::f_status>())
		(L"merge", t_member<void(*)(t_font_options*, const t_font_options*), t_font_options::f_merge>())
		(L"hash", t_member<intptr_t(*)(const t_font_options*), t_font_options::f_hash>())
		(L"equal", t_member<bool(*)(const t_font_options*, const t_font_options*), t_font_options::f_equal>())
		(L"set_antialias", t_member<void(*)(t_font_options*, cairo_antialias_t), t_font_options::f_set_antialias>())
		(L"get_antialias", t_member<cairo_antialias_t(*)(const t_font_options*), t_font_options::f_get_antialias>())
		(L"set_subpixel_order", t_member<void(*)(t_font_options*, cairo_subpixel_order_t), t_font_options::f_set_subpixel_order>())
		(L"get_subpixel_order", t_member<cairo_subpixel_order_t(*)(const t_font_options*), t_font_options::f_get_subpixel_order>())
		(L"set_hint_style", t_member<void(*)(t_font_options*, cairo_hint_style_t), t_font_options::f_set_hint_style>())
		(L"get_hint_style", t_member<cairo_hint_style_t(*)(const t_font_options*), t_font_options::f_get_hint_style>())
		(L"set_hint_metrics", t_member<void(*)(t_font_options*, cairo_hint_metrics_t), t_font_options::f_set_hint_metrics>())
		(L"get_hint_metrics", t_member<cairo_hint_metrics_t(*)(const t_font_options*), t_font_options::f_get_hint_metrics>())
	;
}

t_type* t_type_of<xemmaix::cairo::t_font_options>::f_derive(t_object* a_this)
{
	return nullptr;
}

void t_type_of<xemmaix::cairo::t_font_options>::f_finalize(t_object* a_this)
{
	xemmaix::cairo::t_font_options::f_destroy(f_as<xemmaix::cairo::t_font_options*>(a_this));
}

t_scoped t_type_of<xemmaix::cairo::t_font_options>::f_construct(t_object* a_class, t_stacked* a_stack, size_t a_n)
{
	return t_overload<
		t_construct_with<t_scoped(*)(t_object*), f_construct>,
		t_construct_with<t_scoped(*)(t_object*, const xemmaix::cairo::t_font_options*), f_construct>
	>::t_bind<xemmaix::cairo::t_font_options>::f_do(a_class, a_stack, a_n);
}

void t_type_of<xemmaix::cairo::t_font_options>::f_instantiate(t_object* a_class, t_stacked* a_stack, size_t a_n)
{
	t_destruct_n destruct(a_stack, a_n);
	a_stack[0].f_construct(f_construct(a_class, a_stack, a_n));
}

void t_type_of<cairo_antialias_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_antialias_t, intptr_t>(a_extension, L"Antialias")
		(L"DEFAULT", CAIRO_ANTIALIAS_DEFAULT)
		(L"NONE", CAIRO_ANTIALIAS_NONE)
		(L"GRAY", CAIRO_ANTIALIAS_GRAY)
		(L"SUBPIXEL", CAIRO_ANTIALIAS_SUBPIXEL)
	;
}

void t_type_of<cairo_subpixel_order_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_subpixel_order_t, intptr_t>(a_extension, L"SubpixelOrder")
		(L"DEFAULT", CAIRO_SUBPIXEL_ORDER_DEFAULT)
		(L"RGB", CAIRO_SUBPIXEL_ORDER_RGB)
		(L"BGR", CAIRO_SUBPIXEL_ORDER_BGR)
		(L"VRGB", CAIRO_SUBPIXEL_ORDER_VRGB)
		(L"VBGR", CAIRO_SUBPIXEL_ORDER_VBGR)
	;
}

void t_type_of<cairo_hint_style_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_hint_style_t, intptr_t>(a_extension, L"HintStyle")
		(L"DEFAULT", CAIRO_HINT_STYLE_DEFAULT)
		(L"NONE", CAIRO_HINT_STYLE_NONE)
		(L"SLIGHT", CAIRO_HINT_STYLE_SLIGHT)
		(L"MEDIUM", CAIRO_HINT_STYLE_MEDIUM)
		(L"FULL", CAIRO_HINT_STYLE_FULL)
	;
}

void t_type_of<cairo_hint_metrics_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_hint_metrics_t, intptr_t>(a_extension, L"HintMetrics")
		(L"DEFAULT", CAIRO_HINT_METRICS_DEFAULT)
		(L"OFF", CAIRO_HINT_METRICS_OFF)
		(L"ON", CAIRO_HINT_METRICS_ON)
	;
}

}
