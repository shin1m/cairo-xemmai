#include "context.h"

namespace xemmaix::cairo
{

void t_context::f_set_dash(const t_array& a_dashes, double a_offset)
{
	size_t n = a_dashes.f_size();
	std::vector<double> dashes(n);
	for (size_t i = 0; i < n; ++i) {
		const t_slot& dash = a_dashes[i];
		f_check<double>(dash, L"dash");
		dashes[i] = f_as<double>(dash);
	}
	cairo_set_dash(v_value, &dashes[0], n, a_offset);
}

}

namespace xemmai
{

void t_type_of<xemmaix::cairo::t_context>::f_define(t_extension* a_extension)
{
	using namespace xemmaix::cairo;
	t_define<t_context, t_object>(a_extension, L"Context"sv)
		(L"acquire"sv, t_member<void(t_context::*)(), &t_context::f_acquire>())
		(L"release"sv, t_member<void(t_context::*)(), &t_context::f_release>())
		(L"status"sv, t_member<cairo_status_t(t_context::*)() const, &t_context::f_status>())
		(L"save"sv, t_member<void(t_context::*)(), &t_context::f_save>())
		(L"restore"sv, t_member<void(t_context::*)(), &t_context::f_restore>())
		(L"get_target"sv, t_member<t_surface*(t_context::*)() const, &t_context::f_get_target>())
		(L"push_group"sv, t_member<void(t_context::*)(), &t_context::f_push_group>())
		(L"push_group_with_content"sv, t_member<void(t_context::*)(cairo_content_t), &t_context::f_push_group_with_content>())
		(L"pop_group"sv, t_member<t_pattern*(t_context::*)(), &t_context::f_pop_group>())
		(L"pop_group_to_source"sv, t_member<void(t_context::*)(), &t_context::f_pop_group_to_source>())
		(L"get_group_target"sv, t_member<t_surface*(t_context::*)() const, &t_context::f_get_group_target>())
		(L"set_source_rgb"sv, t_member<void(t_context::*)(double, double, double), &t_context::f_set_source_rgb>())
		(L"set_source_rgba"sv, t_member<void(t_context::*)(double, double, double, double), &t_context::f_set_source_rgba>())
		(L"set_source"sv,
			t_member<void(t_context::*)(t_pattern&), &t_context::f_set_source>(),
			t_member<void(t_context::*)(t_surface&, double, double), &t_context::f_set_source>()
		)
		(L"get_source"sv, t_member<t_pattern*(t_context::*)() const, &t_context::f_get_source>())
		(L"set_antialias"sv, t_member<void(t_context::*)(cairo_antialias_t), &t_context::f_set_antialias>())
		(L"get_antialias"sv, t_member<cairo_antialias_t(t_context::*)() const, &t_context::f_get_antialias>())
		(L"set_dash"sv, t_member<void(t_context::*)(const t_array&, double), &t_context::f_set_dash, t_with_lock_for_read>())
		(L"get_dash"sv, t_member<t_scoped(t_context::*)() const, &t_context::f_get_dash>())
		(L"set_fill_rule"sv, t_member<void(t_context::*)(cairo_fill_rule_t), &t_context::f_set_fill_rule>())
		(L"get_fill_rule"sv, t_member<cairo_fill_rule_t(t_context::*)() const, &t_context::f_get_fill_rule>())
		(L"set_line_cap"sv, t_member<void(t_context::*)(cairo_line_cap_t), &t_context::f_set_line_cap>())
		(L"get_line_cap"sv, t_member<cairo_line_cap_t(t_context::*)() const, &t_context::f_get_line_cap>())
		(L"set_line_join"sv, t_member<void(t_context::*)(cairo_line_join_t), &t_context::f_set_line_join>())
		(L"get_line_join"sv, t_member<cairo_line_join_t(t_context::*)() const, &t_context::f_get_line_join>())
		(L"set_line_width"sv, t_member<void(t_context::*)(double), &t_context::f_set_line_width>())
		(L"get_line_width"sv, t_member<double(t_context::*)() const, &t_context::f_get_line_width>())
		(L"set_miter_limit"sv, t_member<void(t_context::*)(double), &t_context::f_set_miter_limit>())
		(L"get_miter_limit"sv, t_member<double(t_context::*)() const, &t_context::f_get_miter_limit>())
		(L"set_operator"sv, t_member<void(t_context::*)(cairo_operator_t), &t_context::f_set_operator>())
		(L"get_operator"sv, t_member<cairo_operator_t(t_context::*)() const, &t_context::f_get_operator>())
		(L"set_tolerance"sv, t_member<void(t_context::*)(double), &t_context::f_set_tolerance>())
		(L"get_tolerance"sv, t_member<double(t_context::*)() const, &t_context::f_get_tolerance>())
		(L"clip"sv, t_member<void(t_context::*)(), &t_context::f_clip>())
		(L"clip_preserve"sv, t_member<void(t_context::*)(), &t_context::f_clip_preserve>())
		(L"clip_extents"sv, t_member<t_scoped(t_context::*)() const, &t_context::f_clip_extents>())
		(L"reset_clip"sv, t_member<void(t_context::*)(), &t_context::f_reset_clip>())
		//(L"copy_clip_rectangle_list"sv, t_member<cairo_rectangle_list_t*(t_context::*)() const, &t_context::f_copy_clip_rectangle_list>())
		(L"fill"sv, t_member<void(t_context::*)(), &t_context::f_fill>())
		(L"fill_preserve"sv, t_member<void(t_context::*)(), &t_context::f_fill_preserve>())
		(L"fill_extents"sv, t_member<t_scoped(t_context::*)() const, &t_context::f_fill_extents>())
		(L"in_fill"sv, t_member<bool(t_context::*)(double, double) const, &t_context::f_in_fill>())
		(L"mask"sv,
			t_member<void(t_context::*)(t_pattern&), &t_context::f_mask>(),
			t_member<void(t_context::*)(t_surface&, double, double), &t_context::f_mask>()
		)
		(L"paint"sv, t_member<void(t_context::*)(), &t_context::f_paint>())
		(L"paint_with_alpha"sv, t_member<void(t_context::*)(double), &t_context::f_paint_with_alpha>())
		(L"stroke"sv, t_member<void(t_context::*)(), &t_context::f_stroke>())
		(L"stroke_preserve"sv, t_member<void(t_context::*)(), &t_context::f_stroke_preserve>())
		(L"storke_extents"sv, t_member<t_scoped(t_context::*)() const, &t_context::f_stroke_extents>())
		(L"in_stroke"sv, t_member<bool(t_context::*)(double, double) const, &t_context::f_in_stroke>())
		(L"copy_page"sv, t_member<void(t_context::*)(), &t_context::f_copy_page>())
		(L"show_page"sv, t_member<void(t_context::*)(), &t_context::f_show_page>())
		//(L"copy_path"sv, t_member<cairo_path_t*(t_context::*)(), &t_context::f_copy_path>())
		//(L"copy_path_flat"sv, t_member<cairo_path_t*(t_context::*)(), &t_context::f_copy_path_flat>())
		//(L"append_path"sv, t_member<void(t_context::*)(cairo_path_t*), &t_context::f_append_path>())
		(L"has_current_point"sv, t_member<bool(t_context::*)() const, &t_context::f_has_current_point>())
		(L"get_current_point"sv, t_member<t_scoped(t_context::*)() const, &t_context::f_get_current_point>())
		(L"new_path"sv, t_member<void(t_context::*)(), &t_context::f_new_path>())
		(L"new_sub_path"sv, t_member<void(t_context::*)(), &t_context::f_new_sub_path>())
		(L"close_path"sv, t_member<void(t_context::*)(), &t_context::f_close_path>())
		(L"arc"sv, t_member<void(t_context::*)(double, double, double, double, double), &t_context::f_arc>())
		(L"arc_negative"sv, t_member<void(t_context::*)(double, double, double, double, double), &t_context::f_arc_negative>())
		(L"curve_to"sv, t_member<void(t_context::*)(double, double, double, double, double, double), &t_context::f_curve_to>())
		(L"line_to"sv, t_member<void(t_context::*)(double, double), &t_context::f_line_to>())
		(L"move_to"sv, t_member<void(t_context::*)(double, double), &t_context::f_move_to>())
		(L"rectangle"sv, t_member<void(t_context::*)(double, double, double, double), &t_context::f_rectangle>())
		//(L"glyph_path"sv, t_member<void(t_context::*)(const cairo_glyph_t*, int), &t_context::f_glyph_path>())
		(L"text_path"sv, t_member<void(t_context::*)(std::wstring_view), &t_context::f_text_path>())
		(L"rel_curve_to"sv, t_member<void(t_context::*)(double, double, double, double, double, double), &t_context::f_rel_curve_to>())
		(L"rel_line_to"sv, t_member<void(t_context::*)(double, double), &t_context::f_rel_line_to>())
		(L"rel_move_to"sv, t_member<void(t_context::*)(double, double), &t_context::f_rel_move_to>())
		(L"path_extents"sv, t_member<t_scoped(t_context::*)() const, &t_context::f_path_extents>())
		(L"translate"sv, t_member<void(t_context::*)(double, double), &t_context::f_translate>())
		(L"scale"sv, t_member<void(t_context::*)(double, double), &t_context::f_scale>())
		(L"rotate"sv, t_member<void(t_context::*)(double), &t_context::f_rotate>())
		(L"transform"sv, t_member<void(t_context::*)(const t_matrix&), &t_context::f_transform>())
		(L"set_matrix"sv, t_member<void(t_context::*)(const t_matrix&), &t_context::f_set_matrix>())
		(L"get_matrix"sv, t_member<t_matrix(t_context::*)() const, &t_context::f_get_matrix>())
		(L"identity_matrix"sv, t_member<void(t_context::*)(), &t_context::f_identity_matrix>())
		(L"user_to_device"sv, t_member<t_scoped(t_context::*)(double, double) const, &t_context::f_user_to_device>())
		(L"user_to_device_distance"sv, t_member<t_scoped(t_context::*)(double, double) const, &t_context::f_user_to_device_distance>())
		(L"device_to_user"sv, t_member<t_scoped(t_context::*)(double, double) const, &t_context::f_device_to_user>())
		(L"device_to_user_distance"sv, t_member<t_scoped(t_context::*)(double, double) const, &t_context::f_device_to_user_distance>())
		(L"select_font_face"sv, t_member<void(t_context::*)(std::wstring_view, cairo_font_slant_t, cairo_font_weight_t), &t_context::f_select_font_face>())
		(L"set_font_size"sv, t_member<void(t_context::*)(double), &t_context::f_set_font_size>())
		(L"set_font_matrix"sv, t_member<void(t_context::*)(const t_matrix&), &t_context::f_set_font_matrix>())
		(L"get_font_matrix"sv, t_member<t_matrix(t_context::*)() const, &t_context::f_get_font_matrix>())
		(L"set_font_options"sv, t_member<void(t_context::*)(const t_font_options&), &t_context::f_set_font_options>())
		(L"get_font_options"sv, t_member<t_scoped(t_context::*)() const, &t_context::f_get_font_options>())
		(L"set_font_face"sv, t_member<void(t_context::*)(t_font_face*), &t_context::f_set_font_face>())
		(L"get_font_face"sv, t_member<t_font_face*(t_context::*)() const, &t_context::f_get_font_face>())
		(L"set_scaled_font"sv, t_member<void(t_context::*)(const t_scaled_font&), &t_context::f_set_scaled_font>())
		(L"get_scaled_font"sv, t_member<t_scaled_font*(t_context::*)() const, &t_context::f_get_scaled_font>())
		(L"show_text"sv, t_member<void(t_context::*)(std::wstring_view), &t_context::f_show_text>())
		//(L"show_glyphs"sv, t_member<void(t_context::*)(const cairo_glyph_t*, int), &t_context::f_show_glyphs>())
		//(L"show_text_glyphs"sv, t_member<void(t_context::*)(const char*, int, const cairo_glyph_t*, int, const cairo_text_cluster_t*, int, cairo_text_cluster_flags_t), &t_context::f_show_text_glyphs>())
		(L"font_extents"sv, t_member<t_scoped(t_context::*)() const, &t_context::f_font_extents>())
		(L"text_extents"sv, t_member<t_scoped(t_context::*)(std::wstring_view) const, &t_context::f_text_extents>())
		//(L"glyph_extents"sv, t_member<t_scoped(t_context::*)(const cairo_glyph_t*, int) const, &t_context::f_glyph_extents>())
	;
}

t_scoped t_type_of<xemmaix::cairo::t_context>::f_do_construct(t_stacked* a_stack, size_t a_n)
{
	return t_construct_with<t_scoped(*)(t_type*, xemmaix::cairo::t_surface&), xemmaix::cairo::t_context::f_construct>::t_bind<xemmaix::cairo::t_context>::f_do(this, a_stack, a_n);
}

void t_type_of<cairo_fill_rule_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_fill_rule_t, intptr_t>(a_extension, L"FillRule"sv)
		(L"WINDING"sv, CAIRO_FILL_RULE_WINDING)
		(L"EVEN_ODD"sv, CAIRO_FILL_RULE_EVEN_ODD)
	;
}

void t_type_of<cairo_line_cap_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_line_cap_t, intptr_t>(a_extension, L"LineCap"sv)
		(L"BUTT"sv, CAIRO_LINE_CAP_BUTT)
		(L"ROUND"sv, CAIRO_LINE_CAP_ROUND)
		(L"SQUARE"sv, CAIRO_LINE_CAP_SQUARE)
	;
}

void t_type_of<cairo_line_join_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_line_join_t, intptr_t>(a_extension, L"LineJoin"sv)
		(L"MITER"sv, CAIRO_LINE_JOIN_MITER)
		(L"ROUND"sv, CAIRO_LINE_JOIN_ROUND)
		(L"BEVEL"sv, CAIRO_LINE_JOIN_BEVEL)
	;
}

void t_type_of<cairo_operator_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_operator_t, intptr_t>(a_extension, L"Operator"sv)
		(L"CLEAR"sv, CAIRO_OPERATOR_CLEAR)
		(L"SOURCE"sv, CAIRO_OPERATOR_SOURCE)
		(L"OVER"sv, CAIRO_OPERATOR_OVER)
		(L"IN"sv, CAIRO_OPERATOR_IN)
		(L"OUT"sv, CAIRO_OPERATOR_OUT)
		(L"ATOP"sv, CAIRO_OPERATOR_ATOP)
		(L"DEST"sv, CAIRO_OPERATOR_DEST)
		(L"DEST_OVER"sv, CAIRO_OPERATOR_DEST_OVER)
		(L"DEST_IN"sv, CAIRO_OPERATOR_DEST_IN)
		(L"DEST_OUT"sv, CAIRO_OPERATOR_DEST_OUT)
		(L"DEST_ATOP"sv, CAIRO_OPERATOR_DEST_ATOP)
		(L"XOR"sv, CAIRO_OPERATOR_XOR)
		(L"ADD"sv, CAIRO_OPERATOR_ADD)
		(L"SATURATE"sv, CAIRO_OPERATOR_SATURATE)
	;
}

}
