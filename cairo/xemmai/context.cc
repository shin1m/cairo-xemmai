#include "context.h"

#include <cassert>

namespace cairo
{

namespace xemmai
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

}

namespace xemmai
{

void t_type_of<t_context>::f_define(t_extension* a_extension)
{
	t_define<t_context, t_object>(a_extension, L"Context")
		(L"acquire", t_member<void (t_context::*)(), &t_context::f_acquire>())
		(L"release", t_member<void (t_context::*)(), &t_context::f_release>())
		(L"status", t_member<cairo_status_t (t_context::*)() const, &t_context::f_status>())
		(L"save", t_member<void (t_context::*)(), &t_context::f_save>())
		(L"restore", t_member<void (t_context::*)(), &t_context::f_restore>())
		(L"get_target", t_member<t_surface* (t_context::*)() const, &t_context::f_get_target>())
		(L"push_group", t_member<void (t_context::*)(), &t_context::f_push_group>())
		(L"push_group_with_content", t_member<void (t_context::*)(cairo_content_t), &t_context::f_push_group_with_content>())
		(L"pop_group", t_member<t_pattern* (t_context::*)(), &t_context::f_pop_group>())
		(L"pop_group_to_source", t_member<void (t_context::*)(), &t_context::f_pop_group_to_source>())
		(L"get_group_target", t_member<t_surface* (t_context::*)() const, &t_context::f_get_group_target>())
		(L"set_source_rgb", t_member<void (t_context::*)(double, double, double), &t_context::f_set_source_rgb>())
		(L"set_source_rgba", t_member<void (t_context::*)(double, double, double, double), &t_context::f_set_source_rgba>())
		(L"set_source",
			t_member<void (t_context::*)(t_pattern&), &t_context::f_set_source>(),
			t_member<void (t_context::*)(t_surface&, double, double), &t_context::f_set_source>()
		)
		(L"get_source", t_member<t_pattern* (t_context::*)() const, &t_context::f_get_source>())
		(L"set_antialias", t_member<void (t_context::*)(cairo_antialias_t), &t_context::f_set_antialias>())
		(L"get_antialias", t_member<cairo_antialias_t (t_context::*)() const, &t_context::f_get_antialias>())
		(L"set_dash", t_member<void (t_context::*)(const t_array&, double), &t_context::f_set_dash, t_with_lock_for_read>())
		(L"get_dash", t_member<t_transfer (t_context::*)() const, &t_context::f_get_dash>())
		(L"set_fill_rule", t_member<void (t_context::*)(cairo_fill_rule_t), &t_context::f_set_fill_rule>())
		(L"get_fill_rule", t_member<cairo_fill_rule_t (t_context::*)() const, &t_context::f_get_fill_rule>())
		(L"set_line_cap", t_member<void (t_context::*)(cairo_line_cap_t), &t_context::f_set_line_cap>())
		(L"get_line_cap", t_member<cairo_line_cap_t (t_context::*)() const, &t_context::f_get_line_cap>())
		(L"set_line_join", t_member<void (t_context::*)(cairo_line_join_t), &t_context::f_set_line_join>())
		(L"get_line_join", t_member<cairo_line_join_t (t_context::*)() const, &t_context::f_get_line_join>())
		(L"set_line_width", t_member<void (t_context::*)(double), &t_context::f_set_line_width>())
		(L"get_line_width", t_member<double (t_context::*)() const, &t_context::f_get_line_width>())
		(L"set_miter_limit", t_member<void (t_context::*)(double), &t_context::f_set_miter_limit>())
		(L"get_miter_limit", t_member<double (t_context::*)() const, &t_context::f_get_miter_limit>())
		(L"set_operator", t_member<void (t_context::*)(cairo_operator_t), &t_context::f_set_operator>())
		(L"get_operator", t_member<cairo_operator_t (t_context::*)() const, &t_context::f_get_operator>())
		(L"set_tolerance", t_member<void (t_context::*)(double), &t_context::f_set_tolerance>())
		(L"get_tolerance", t_member<double (t_context::*)() const, &t_context::f_get_tolerance>())
		(L"clip", t_member<void (t_context::*)(), &t_context::f_clip>())
		(L"clip_preserve", t_member<void (t_context::*)(), &t_context::f_clip_preserve>())
		(L"clip_extents", t_member<t_transfer (t_context::*)() const, &t_context::f_clip_extents>())
		(L"reset_clip", t_member<void (t_context::*)(), &t_context::f_reset_clip>())
		//(L"copy_clip_rectangle_list", t_member<cairo_rectangle_list_t* (t_context::*)() const, &t_context::f_copy_clip_rectangle_list>())
		(L"fill", t_member<void (t_context::*)(), &t_context::f_fill>())
		(L"fill_preserve", t_member<void (t_context::*)(), &t_context::f_fill_preserve>())
		(L"fill_extents", t_member<t_transfer (t_context::*)() const, &t_context::f_fill_extents>())
		(L"in_fill", t_member<bool (t_context::*)(double, double) const, &t_context::f_in_fill>())
		(L"mask",
			t_member<void (t_context::*)(t_pattern&), &t_context::f_mask>(),
			t_member<void (t_context::*)(t_surface&, double, double), &t_context::f_mask>()
		)
		(L"paint", t_member<void (t_context::*)(), &t_context::f_paint>())
		(L"paint_with_alpha", t_member<void (t_context::*)(double), &t_context::f_paint_with_alpha>())
		(L"stroke", t_member<void (t_context::*)(), &t_context::f_stroke>())
		(L"stroke_preserve", t_member<void (t_context::*)(), &t_context::f_stroke_preserve>())
		(L"storke_extents", t_member<t_transfer (t_context::*)() const, &t_context::f_stroke_extents>())
		(L"in_stroke", t_member<bool (t_context::*)(double, double) const, &t_context::f_in_stroke>())
		(L"copy_page", t_member<void (t_context::*)(), &t_context::f_copy_page>())
		(L"show_page", t_member<void (t_context::*)(), &t_context::f_show_page>())
		//(L"copy_path", t_member<cairo_path_t* (t_context::*)(), &t_context::f_copy_path>())
		//(L"copy_path_flat", t_member<cairo_path_t* (t_context::*)(), &t_context::f_copy_path_flat>())
		//(L"append_path", t_member<void (t_context::*)(cairo_path_t*), &t_context::f_append_path>())
		(L"has_current_point", t_member<bool (t_context::*)() const, &t_context::f_has_current_point>())
		(L"get_current_point", t_member<t_transfer (t_context::*)() const, &t_context::f_get_current_point>())
		(L"new_path", t_member<void (t_context::*)(), &t_context::f_new_path>())
		(L"new_sub_path", t_member<void (t_context::*)(), &t_context::f_new_sub_path>())
		(L"close_path", t_member<void (t_context::*)(), &t_context::f_close_path>())
		(L"arc", t_member<void (t_context::*)(double, double, double, double, double), &t_context::f_arc>())
		(L"arc_negative", t_member<void (t_context::*)(double, double, double, double, double), &t_context::f_arc_negative>())
		(L"curve_to", t_member<void (t_context::*)(double, double, double, double, double, double), &t_context::f_curve_to>())
		(L"line_to", t_member<void (t_context::*)(double, double), &t_context::f_line_to>())
		(L"move_to", t_member<void (t_context::*)(double, double), &t_context::f_move_to>())
		(L"rectangle", t_member<void (t_context::*)(double, double, double, double), &t_context::f_rectangle>())
		//(L"glyph_path", t_member<void (t_context::*)(const cairo_glyph_t*, int), &t_context::f_glyph_path>())
		(L"text_path", t_member<void (t_context::*)(const std::wstring&), &t_context::f_text_path>())
		(L"rel_curve_to", t_member<void (t_context::*)(double, double, double, double, double, double), &t_context::f_rel_curve_to>())
		(L"rel_line_to", t_member<void (t_context::*)(double, double), &t_context::f_rel_line_to>())
		(L"rel_move_to", t_member<void (t_context::*)(double, double), &t_context::f_rel_move_to>())
		(L"path_extents", t_member<t_transfer (t_context::*)() const, &t_context::f_path_extents>())
		(L"translate", t_member<void (t_context::*)(double, double), &t_context::f_translate>())
		(L"scale", t_member<void (t_context::*)(double, double), &t_context::f_scale>())
		(L"rotate", t_member<void (t_context::*)(double), &t_context::f_rotate>())
		(L"transform", t_member<void (t_context::*)(const t_matrix&), &t_context::f_transform>())
		(L"set_matrix", t_member<void (t_context::*)(const t_matrix&), &t_context::f_set_matrix>())
		(L"get_matrix", t_member<t_matrix (t_context::*)() const, &t_context::f_get_matrix>())
		(L"identity_matrix", t_member<void (t_context::*)(), &t_context::f_identity_matrix>())
		(L"user_to_device", t_member<t_transfer (t_context::*)(double, double) const, &t_context::f_user_to_device>())
		(L"user_to_device_distance", t_member<t_transfer (t_context::*)(double, double) const, &t_context::f_user_to_device_distance>())
		(L"device_to_user", t_member<t_transfer (t_context::*)(double, double) const, &t_context::f_device_to_user>())
		(L"device_to_user_distance", t_member<t_transfer (t_context::*)(double, double) const, &t_context::f_device_to_user_distance>())
		(L"select_font_face", t_member<void (t_context::*)(const std::wstring&, cairo_font_slant_t, cairo_font_weight_t), &t_context::f_select_font_face>())
		(L"set_font_size", t_member<void (t_context::*)(double), &t_context::f_set_font_size>())
		(L"set_font_matrix", t_member<void (t_context::*)(const t_matrix&), &t_context::f_set_font_matrix>())
		(L"get_font_matrix", t_member<t_matrix (t_context::*)() const, &t_context::f_get_font_matrix>())
		(L"set_font_options", t_member<void (t_context::*)(const t_font_options&), &t_context::f_set_font_options>())
		(L"get_font_options", t_member<t_transfer (t_context::*)() const, &t_context::f_get_font_options>())
		(L"set_font_face", t_member<void (t_context::*)(t_font_face*), &t_context::f_set_font_face>())
		(L"get_font_face", t_member<t_font_face* (t_context::*)() const, &t_context::f_get_font_face>())
		(L"set_scaled_font", t_member<void (t_context::*)(const t_scaled_font&), &t_context::f_set_scaled_font>())
		(L"get_scaled_font", t_member<t_scaled_font* (t_context::*)() const, &t_context::f_get_scaled_font>())
		(L"show_text", t_member<void (t_context::*)(const std::wstring&), &t_context::f_show_text>())
		//(L"show_glyphs", t_member<void (t_context::*)(const cairo_glyph_t*, int), &t_context::f_show_glyphs>())
		//(L"show_text_glyphs", t_member<void (t_context::*)(const char*, int, const cairo_glyph_t*, int, const cairo_text_cluster_t*, int, cairo_text_cluster_flags_t), &t_context::f_show_text_glyphs>())
		(L"font_extents", t_member<t_transfer (t_context::*)() const, &t_context::f_font_extents>())
		(L"text_extents", t_member<t_transfer (t_context::*)(const std::wstring&) const, &t_context::f_text_extents>())
		//(L"glyph_extents", t_member<t_transfer (t_context::*)(const cairo_glyph_t*, int) const, &t_context::f_glyph_extents>())
	;
}

t_type* t_type_of<t_context>::f_derive(t_object* a_this)
{
	return 0;
}

void t_type_of<t_context>::f_finalize(t_object* a_this)
{
	t_context* p = static_cast<t_context*>(a_this->f_pointer());
	assert(!*p);
	delete p;
}

void t_type_of<t_context>::f_construct(t_object* a_class, t_slot* a_stack, size_t a_n)
{
	t_construct_with<t_transfer (*)(t_object*, t_surface&), t_context::f_construct>::f_call(a_class, a_stack, a_n);
}

void t_type_of<t_context>::f_instantiate(t_object* a_class, t_slot* a_stack, size_t a_n)
{
	f_construct(a_class, a_stack, a_n);
}

void t_type_of<cairo_fill_rule_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_fill_rule_t, int>(a_extension, L"FillRule")
		(L"WINDING", CAIRO_FILL_RULE_WINDING)
		(L"EVEN_ODD", CAIRO_FILL_RULE_EVEN_ODD)
	;
}

void t_type_of<cairo_line_cap_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_line_cap_t, int>(a_extension, L"LineCap")
		(L"BUTT", CAIRO_LINE_CAP_BUTT)
		(L"ROUND", CAIRO_LINE_CAP_ROUND)
		(L"SQUARE", CAIRO_LINE_CAP_SQUARE)
	;
}

void t_type_of<cairo_line_join_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_line_join_t, int>(a_extension, L"LineJoin")
		(L"MITER", CAIRO_LINE_JOIN_MITER)
		(L"ROUND", CAIRO_LINE_JOIN_ROUND)
		(L"BEVEL", CAIRO_LINE_JOIN_BEVEL)
	;
}

void t_type_of<cairo_operator_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_operator_t, int>(a_extension, L"Operator")
		(L"CLEAR", CAIRO_OPERATOR_CLEAR)
		(L"SOURCE", CAIRO_OPERATOR_SOURCE)
		(L"OVER", CAIRO_OPERATOR_OVER)
		(L"IN", CAIRO_OPERATOR_IN)
		(L"OUT", CAIRO_OPERATOR_OUT)
		(L"ATOP", CAIRO_OPERATOR_ATOP)
		(L"DEST", CAIRO_OPERATOR_DEST)
		(L"DEST_OVER", CAIRO_OPERATOR_DEST_OVER)
		(L"DEST_IN", CAIRO_OPERATOR_DEST_IN)
		(L"DEST_OUT", CAIRO_OPERATOR_DEST_OUT)
		(L"DEST_ATOP", CAIRO_OPERATOR_DEST_ATOP)
		(L"XOR", CAIRO_OPERATOR_XOR)
		(L"ADD", CAIRO_OPERATOR_ADD)
		(L"SATURATE", CAIRO_OPERATOR_SATURATE)
	;
}

}
