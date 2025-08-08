#include "context.h"

namespace xemmaix::cairo
{

std::string f_convert(std::wstring_view a_x)
{
	return t_session::v_instance->v_to_utf8(a_x);
}

std::wstring f_convert(std::string_view a_x)
{
	return t_session::v_instance->v_from_utf8(a_x);
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
	if (!v_instance) f_throw(L"must be inside main."sv);
	return v_instance;
}
#endif

t_session::t_session(t_library* a_library) : t_entry(false), v_library(a_library), v_to_utf8("utf-8", "wchar_t"), v_from_utf8("wchar_t", "utf-8")
{
	if (v_instance) f_throw(L"already inside main."sv);
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

void f_main(t_library* a_library, const t_pvalue& a_callable)
{
	t_session session(a_library);
	a_callable();
}

}

void t_library::f_scan(t_scan a_scan)
{
	XEMMAIX__CAIRO__TYPES(XEMMAI__TYPE__SCAN)
}

std::vector<std::pair<t_root, t_rvalue>> t_library::f_define()
{
	t_type_of<t_matrix>::f_define(this);
	t_type_of<t_font_options>::f_define(this);
	t_type_of<t_surface>::f_define(this);
	t_type_of<t_image_surface>::f_define(this);
	t_type_of<t_pattern>::f_define(this);
	t_type_of<t_solid_pattern>::f_define(this);
	t_type_of<t_surface_pattern>::f_define(this);
	t_type_of<t_gradient>::f_define(this);
	t_type_of<t_linear_gradient>::f_define(this);
	t_type_of<t_radial_gradient>::f_define(this);
	t_type_of<t_font_face>::f_define(this);
	t_type_of<t_toy_font_face>::f_define(this);
	t_type_of<t_scaled_font>::f_define(this);
	t_type_of<t_context>::f_define(this);
	return t_define(this)
	(L"Matrix"sv, static_cast<t_object*>(v_type_matrix))
	(L"Status"sv, t_type_of<cairo_status_t>::f_define(this))
	(L"FontOptions"sv, static_cast<t_object*>(v_type_font_options))
	(L"Antialias"sv, t_type_of<cairo_antialias_t>::f_define(this))
	(L"SubpixelOrder"sv, t_type_of<cairo_subpixel_order_t>::f_define(this))
	(L"HintStyle"sv, t_type_of<cairo_hint_style_t>::f_define(this))
	(L"HintMetrics"sv, t_type_of<cairo_hint_metrics_t>::f_define(this))
	(L"Surface"sv, static_cast<t_object*>(v_type_surface))
	(L"Content"sv, t_type_of<cairo_content_t>::f_define(this))
	(L"SurfaceType"sv, t_type_of<cairo_surface_type_t>::f_define(this))
	(L"ImageSurface"sv, static_cast<t_object*>(v_type_image_surface))
	(L"Format"sv, t_type_of<cairo_format_t>::f_define(this))
	(L"Pattern"sv, static_cast<t_object*>(v_type_pattern))
	(L"SolidPattern"sv, static_cast<t_object*>(v_type_solid_pattern))
	(L"SurfacePattern"sv, static_cast<t_object*>(v_type_surface_pattern))
	(L"Extend"sv, t_type_of<cairo_extend_t>::f_define(this))
	(L"Filter"sv, t_type_of<cairo_filter_t>::f_define(this))
	(L"PatternType"sv, t_type_of<cairo_pattern_type_t>::f_define(this))
	(L"Gradient"sv, static_cast<t_object*>(v_type_gradient))
	(L"LinearGradient"sv, static_cast<t_object*>(v_type_linear_gradient))
	(L"RadialGradient"sv, static_cast<t_object*>(v_type_radial_gradient))
	(L"FontSlant"sv, t_type_of<cairo_font_slant_t>::f_define(this))
	(L"FontWeight"sv, t_type_of<cairo_font_weight_t>::f_define(this))
	(L"FontFace"sv, static_cast<t_object*>(v_type_font_face))
	(L"FontType"sv, t_type_of<cairo_font_type_t>::f_define(this))
	(L"ToyFontFace"sv, static_cast<t_object*>(v_type_toy_font_face))
	(L"ScaledFont"sv, static_cast<t_object*>(v_type_scaled_font))
	(L"Context"sv, static_cast<t_object*>(v_type_context))
	(L"FillRule"sv, t_type_of<cairo_fill_rule_t>::f_define(this))
	(L"LineCap"sv, t_type_of<cairo_line_cap_t>::f_define(this))
	(L"LineJoin"sv, t_type_of<cairo_line_join_t>::f_define(this))
	(L"Operator"sv, t_type_of<cairo_operator_t>::f_define(this))
	(L"main"sv, t_static<void(*)(t_library*, const t_pvalue&), f_main>())
	;
}

}

namespace xemmai
{

t_object* t_type_of<cairo_status_t>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"SUCCESS"sv, CAIRO_STATUS_SUCCESS)
		(L"NO_MEMORY"sv, CAIRO_STATUS_NO_MEMORY)
		(L"INVALID_RESTORE"sv, CAIRO_STATUS_INVALID_RESTORE)
		(L"INVALID_POP_GROUP"sv, CAIRO_STATUS_INVALID_POP_GROUP)
		(L"NO_CURRENT_POINT"sv, CAIRO_STATUS_NO_CURRENT_POINT)
		(L"INVALID_MATRIX"sv, CAIRO_STATUS_INVALID_MATRIX)
		(L"INVALID_STATUS"sv, CAIRO_STATUS_INVALID_STATUS)
		(L"NULL_POINTER"sv, CAIRO_STATUS_NULL_POINTER)
		(L"INVALID_STRING"sv, CAIRO_STATUS_INVALID_STRING)
		(L"INVALID_PATH_DATA"sv, CAIRO_STATUS_INVALID_PATH_DATA)
		(L"READ_ERROR"sv, CAIRO_STATUS_READ_ERROR)
		(L"WRITE_ERROR"sv, CAIRO_STATUS_WRITE_ERROR)
		(L"SURFACE_FINISHED"sv, CAIRO_STATUS_SURFACE_FINISHED)
		(L"SURFACE_TYPE_MISMATCH"sv, CAIRO_STATUS_SURFACE_TYPE_MISMATCH)
		(L"PATTERN_TYPE_MISMATCH"sv, CAIRO_STATUS_PATTERN_TYPE_MISMATCH)
		(L"INVALID_CONTENT"sv, CAIRO_STATUS_INVALID_CONTENT)
		(L"INVALID_FORMAT"sv, CAIRO_STATUS_INVALID_FORMAT)
		(L"INVALID_VISUAL"sv, CAIRO_STATUS_INVALID_VISUAL)
		(L"FILE_NOT_FOUND"sv, CAIRO_STATUS_FILE_NOT_FOUND)
		(L"INVALID_DASH"sv, CAIRO_STATUS_INVALID_DASH)
		(L"INVALID_DSC_COMMENT"sv, CAIRO_STATUS_INVALID_DSC_COMMENT)
		(L"INVALID_INDEX"sv, CAIRO_STATUS_INVALID_INDEX)
		(L"CLIP_NOT_REPRESENTABLE"sv, CAIRO_STATUS_CLIP_NOT_REPRESENTABLE)
		(L"TEMP_FILE_ERROR"sv, CAIRO_STATUS_TEMP_FILE_ERROR)
		(L"INVALID_STRIDE"sv, CAIRO_STATUS_INVALID_STRIDE)
		(L"FONT_TYPE_MISMATCH"sv, CAIRO_STATUS_FONT_TYPE_MISMATCH)
		(L"USER_FONT_IMMUTABLE"sv, CAIRO_STATUS_USER_FONT_IMMUTABLE)
		(L"USER_FONT_ERROR"sv, CAIRO_STATUS_USER_FONT_ERROR)
		(L"NEGATIVE_COUNT"sv, CAIRO_STATUS_NEGATIVE_COUNT)
		(L"INVALID_CLUSTERS"sv, CAIRO_STATUS_INVALID_CLUSTERS)
		(L"INVALID_SLANT"sv, CAIRO_STATUS_INVALID_SLANT)
		(L"INVALID_WEIGHT"sv, CAIRO_STATUS_INVALID_WEIGHT)
		;
	});
}

}

XEMMAI__MODULE__FACTORY(xemmai::t_library::t_handle* a_handle)
{
	return xemmai::f_new<xemmaix::cairo::t_library>(a_handle);
}
