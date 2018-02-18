#include "context.h"

namespace xemmaix::cairo
{

std::string f_convert(const std::wstring& a_string)
{
	return t_session::v_instance->v_convert.to_bytes(a_string);
}

std::wstring f_convert(const std::string& a_string)
{
	return t_session::v_instance->v_convert.from_bytes(a_string);
}

t_scoped f_tuple(t_scoped&& a_0, t_scoped&& a_1)
{
	t_scoped p = t_tuple::f_instantiate(2);
	t_tuple& tuple = f_as<t_tuple&>(p);
	tuple[0].f_construct(std::move(a_0));
	tuple[1].f_construct(std::move(a_1));
	return p;
}

t_scoped f_tuple(t_scoped&& a_0, t_scoped&& a_1, t_scoped&& a_2, t_scoped&& a_3)
{
	t_scoped p = t_tuple::f_instantiate(4);
	t_tuple& tuple = f_as<t_tuple&>(p);
	tuple[0].f_construct(std::move(a_0));
	tuple[1].f_construct(std::move(a_1));
	tuple[2].f_construct(std::move(a_2));
	tuple[3].f_construct(std::move(a_3));
	return p;
}

t_scoped f_tuple(t_scoped&& a_0, t_scoped&& a_1, t_scoped&& a_2, t_scoped&& a_3, t_scoped&& a_4)
{
	t_scoped p = t_tuple::f_instantiate(5);
	t_tuple& tuple = f_as<t_tuple&>(p);
	tuple[0].f_construct(std::move(a_0));
	tuple[1].f_construct(std::move(a_1));
	tuple[2].f_construct(std::move(a_2));
	tuple[3].f_construct(std::move(a_3));
	tuple[4].f_construct(std::move(a_4));
	return p;
}

t_scoped f_tuple(t_scoped&& a_0, t_scoped&& a_1, t_scoped&& a_2, t_scoped&& a_3, t_scoped&& a_4, t_scoped&& a_5)
{
	t_scoped p = t_tuple::f_instantiate(6);
	t_tuple& tuple = f_as<t_tuple&>(p);
	tuple[0].f_construct(std::move(a_0));
	tuple[1].f_construct(std::move(a_1));
	tuple[2].f_construct(std::move(a_2));
	tuple[3].f_construct(std::move(a_3));
	tuple[4].f_construct(std::move(a_4));
	tuple[5].f_construct(std::move(a_5));
	return p;
}

t_entry::t_entry() : v_previous(t_session::f_instance()), v_next(v_previous->v_next)
{
	v_previous->v_next = v_next->v_previous = this;
}

void t_entry::f_dispose()
{
	f_unlink();
}

XEMMAI__PORTABLE__THREAD t_session* t_session::v_instance;

#ifdef _WIN32
t_session* t_session::f_instance()
{
	if (!v_instance) t_throwable::f_throw(L"must be inside main.");
	return v_instance;
}
#endif

t_session::t_session(t_extension* a_extension) : t_entry(false), v_extension(a_extension)
{
	if (v_instance) t_throwable::f_throw(L"already inside main.");
	v_instance = this;
}

t_session::~t_session()
{
	while (v_next != this) v_next->f_dispose();
	cairo_debug_reset_static_data();
	v_instance = nullptr;
}

cairo_user_data_key_t t_proxy::v_key;

void t_proxy::f_destroy()
{
	if (v_previous) f_unlink();
	v_object = nullptr;
}

namespace
{

void f_main(t_extension* a_extension, const t_value& a_callable)
{
	t_session session(a_extension);
	a_callable();
}

}

t_extension::t_extension(t_object* a_module) : xemmai::t_extension(a_module)
{
	t_type_of<t_matrix>::f_define(this);
	t_type_of<cairo_status_t>::f_define(this);
	t_type_of<t_font_options>::f_define(this);
	t_type_of<cairo_antialias_t>::f_define(this);
	t_type_of<cairo_subpixel_order_t>::f_define(this);
	t_type_of<cairo_hint_style_t>::f_define(this);
	t_type_of<cairo_hint_metrics_t>::f_define(this);
	t_type_of<t_surface>::f_define(this);
	t_type_of<cairo_content_t>::f_define(this);
	t_type_of<cairo_surface_type_t>::f_define(this);
	t_type_of<t_image_surface>::f_define(this);
	t_type_of<cairo_format_t>::f_define(this);
	t_type_of<t_pattern>::f_define(this);
	t_type_of<t_solid_pattern>::f_define(this);
	t_type_of<t_surface_pattern>::f_define(this);
	t_type_of<t_gradient>::f_define(this);
	t_type_of<t_linear_gradient>::f_define(this);
	t_type_of<t_radial_gradient>::f_define(this);
	t_type_of<cairo_extend_t>::f_define(this);
	t_type_of<cairo_filter_t>::f_define(this);
	t_type_of<cairo_pattern_type_t>::f_define(this);
	t_type_of<t_font_face>::f_define(this);
	t_type_of<cairo_font_type_t>::f_define(this);
	t_type_of<cairo_font_slant_t>::f_define(this);
	t_type_of<cairo_font_weight_t>::f_define(this);
	t_type_of<t_toy_font_face>::f_define(this);
	t_type_of<t_scaled_font>::f_define(this);
	t_type_of<t_context>::f_define(this);
	t_type_of<cairo_fill_rule_t>::f_define(this);
	t_type_of<cairo_line_cap_t>::f_define(this);
	t_type_of<cairo_line_join_t>::f_define(this);
	t_type_of<cairo_operator_t>::f_define(this);
	f_define<void (*)(t_extension*, const t_value&), f_main>(this, L"main");
}

void t_extension::f_scan(t_scan a_scan)
{
	a_scan(v_type_matrix);
	a_scan(v_type_status);
	a_scan(v_type_font_options);
	a_scan(v_type_antialias);
	a_scan(v_type_subpixel_order);
	a_scan(v_type_hint_style);
	a_scan(v_type_hint_metrics);
	a_scan(v_type_surface);
	a_scan(v_type_content);
	a_scan(v_type_surface_type);
	a_scan(v_type_image_surface);
	a_scan(v_type_format);
	a_scan(v_type_pattern);
	a_scan(v_type_solid_pattern);
	a_scan(v_type_surface_pattern);
	a_scan(v_type_gradient);
	a_scan(v_type_linear_gradient);
	a_scan(v_type_radial_gradient);
	a_scan(v_type_extend);
	a_scan(v_type_filter);
	a_scan(v_type_pattern_type);
	a_scan(v_type_font_face);
	a_scan(v_type_font_type);
	a_scan(v_type_font_slant);
	a_scan(v_type_font_weight);
	a_scan(v_type_toy_font_face);
	a_scan(v_type_scaled_font);
	a_scan(v_type_context);
	a_scan(v_type_fill_rule);
	a_scan(v_type_line_cap);
	a_scan(v_type_line_join);
	a_scan(v_type_operator);
}

}

namespace xemmai
{

void t_type_of<cairo_status_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_status_t, intptr_t>(a_extension, L"Status")
		(L"SUCCESS", CAIRO_STATUS_SUCCESS)
		(L"NO_MEMORY", CAIRO_STATUS_NO_MEMORY)
		(L"INVALID_RESTORE", CAIRO_STATUS_INVALID_RESTORE)
		(L"INVALID_POP_GROUP", CAIRO_STATUS_INVALID_POP_GROUP)
		(L"NO_CURRENT_POINT", CAIRO_STATUS_NO_CURRENT_POINT)
		(L"INVALID_MATRIX", CAIRO_STATUS_INVALID_MATRIX)
		(L"INVALID_STATUS", CAIRO_STATUS_INVALID_STATUS)
		(L"NULL_POINTER", CAIRO_STATUS_NULL_POINTER)
		(L"INVALID_STRING", CAIRO_STATUS_INVALID_STRING)
		(L"INVALID_PATH_DATA", CAIRO_STATUS_INVALID_PATH_DATA)
		(L"READ_ERROR", CAIRO_STATUS_READ_ERROR)
		(L"WRITE_ERROR", CAIRO_STATUS_WRITE_ERROR)
		(L"SURFACE_FINISHED", CAIRO_STATUS_SURFACE_FINISHED)
		(L"SURFACE_TYPE_MISMATCH", CAIRO_STATUS_SURFACE_TYPE_MISMATCH)
		(L"PATTERN_TYPE_MISMATCH", CAIRO_STATUS_PATTERN_TYPE_MISMATCH)
		(L"INVALID_CONTENT", CAIRO_STATUS_INVALID_CONTENT)
		(L"INVALID_FORMAT", CAIRO_STATUS_INVALID_FORMAT)
		(L"INVALID_VISUAL", CAIRO_STATUS_INVALID_VISUAL)
		(L"FILE_NOT_FOUND", CAIRO_STATUS_FILE_NOT_FOUND)
		(L"INVALID_DASH", CAIRO_STATUS_INVALID_DASH)
		(L"INVALID_DSC_COMMENT", CAIRO_STATUS_INVALID_DSC_COMMENT)
		(L"INVALID_INDEX", CAIRO_STATUS_INVALID_INDEX)
		(L"CLIP_NOT_REPRESENTABLE", CAIRO_STATUS_CLIP_NOT_REPRESENTABLE)
		(L"TEMP_FILE_ERROR", CAIRO_STATUS_TEMP_FILE_ERROR)
		(L"INVALID_STRIDE", CAIRO_STATUS_INVALID_STRIDE)
		(L"FONT_TYPE_MISMATCH", CAIRO_STATUS_FONT_TYPE_MISMATCH)
		(L"USER_FONT_IMMUTABLE", CAIRO_STATUS_USER_FONT_IMMUTABLE)
		(L"USER_FONT_ERROR", CAIRO_STATUS_USER_FONT_ERROR)
		(L"NEGATIVE_COUNT", CAIRO_STATUS_NEGATIVE_COUNT)
		(L"INVALID_CLUSTERS", CAIRO_STATUS_INVALID_CLUSTERS)
		(L"INVALID_SLANT", CAIRO_STATUS_INVALID_SLANT)
		(L"INVALID_WEIGHT", CAIRO_STATUS_INVALID_WEIGHT)
	;
}

}

XEMMAI__MODULE__FACTORY(xemmai::t_object* a_module)
{
	return new xemmaix::cairo::t_extension(a_module);
}
