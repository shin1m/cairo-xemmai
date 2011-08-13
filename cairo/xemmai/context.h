#ifndef CAIRO__XEMMAI__CONTEXT_H
#define CAIRO__XEMMAI__CONTEXT_H

#include "pattern.h"
#include "scaled_font.h"

namespace cairo
{

namespace xemmai
{

class t_context : public t_proxy_of<t_context, cairo_t>
{
	friend class t_proxy_of<t_context, cairo_t>;

	static cairo_status_t f_set_user_data(cairo_t* a_value, const cairo_user_data_key_t* a_key, void* a_user, cairo_destroy_func_t a_destroy)
	{
		return cairo_set_user_data(a_value, a_key, a_user, a_destroy);
	}
	static void* f_get_user_data(cairo_t* a_value, const cairo_user_data_key_t* a_key)
	{
		return cairo_get_user_data(a_value, a_key);
	}
	static cairo_t* f_reference(cairo_t* a_value)
	{
		return cairo_reference(a_value);
	}
	static void f_unreference(cairo_t* a_value)
	{
		cairo_destroy(a_value);
	}

	t_context(cairo_t* a_value) : t_base(t_session::f_instance()->f_extension()->f_type<t_context>(), a_value)
	{
	}

public:
	using t_base::f_construct;
	static t_transfer f_construct(t_object* a_class, t_surface& a_target)
	{
		return f_transfer(new t_context(cairo_create(a_target)));
	}

	void f_acquire()
	{
		t_base::f_acquire();
	}
	void f_release()
	{
		t_base::f_release();
	}
	cairo_status_t f_status() const
	{
		return cairo_status(v_value);
	}
	void f_save()
	{
		cairo_save(v_value);
	}
	void f_restore()
	{
		cairo_restore(v_value);
	}
	t_surface* f_get_target() const
	{
		return t_surface::f_wrap(cairo_get_target(v_value));
	}
	void f_push_group()
	{
		cairo_push_group(v_value);
	}
	void f_push_group_with_content(cairo_content_t a_content)
	{
		cairo_push_group_with_content(v_value, a_content);
	}
	t_pattern* f_pop_group()
	{
		return t_pattern::f_wrap(cairo_pop_group(v_value));
	}
	void f_pop_group_to_source()
	{
		cairo_pop_group_to_source(v_value);
	}
	t_surface* f_get_group_target() const
	{
		return t_surface::f_wrap(cairo_get_group_target(v_value));
	}
	void f_set_source_rgb(double a_red, double a_green, double a_blue)
	{
		cairo_set_source_rgb(v_value, a_red, a_green, a_blue);
	}
	void f_set_source_rgba(double a_red, double a_green, double a_blue, double a_alpha)
	{
		cairo_set_source_rgba(v_value, a_red, a_green, a_blue, a_alpha);
	}
	void f_set_source(t_pattern& a_source)
	{
		cairo_set_source(v_value, a_source);
	}
	void f_set_source(t_surface& a_surface, double a_x, double a_y)
	{
		cairo_set_source_surface(v_value, a_surface, a_x, a_y);
	}
	t_pattern* f_get_source() const
	{
		return t_pattern::f_wrap(cairo_get_source(v_value));
	}
	void f_set_antialias(cairo_antialias_t a_antialias)
	{
		cairo_set_antialias(v_value, a_antialias);
	}
	cairo_antialias_t f_get_antialias() const
	{
		return cairo_get_antialias(v_value);
	}
	void f_set_dash(const t_array& a_dashes, double a_offset);
	t_transfer f_get_dash() const
	{
		int n = cairo_get_dash_count(v_value);
		std::vector<double> dashes(n);
		double offset;
		cairo_get_dash(v_value, &dashes[0], &offset);
		t_transfer p = t_array::f_instantiate();
		t_array& array = f_as<t_array&>(p);
		for (int i = 0; i < n; ++i) array.f_push(f_global()->f_as(dashes[i]));
		return f_tuple(p, f_global()->f_as(offset));
	}
	void f_set_fill_rule(cairo_fill_rule_t a_fill_rule)
	{
		cairo_set_fill_rule(v_value, a_fill_rule);
	}
	cairo_fill_rule_t f_get_fill_rule() const
	{
		return cairo_get_fill_rule(v_value);
	}
	void f_set_line_cap(cairo_line_cap_t a_line_cap)
	{
		cairo_set_line_cap(v_value, a_line_cap);
	}
	cairo_line_cap_t f_get_line_cap() const
	{
		return cairo_get_line_cap(v_value);
	}
	void f_set_line_join(cairo_line_join_t a_line_join)
	{
		cairo_set_line_join(v_value, a_line_join);
	}
	cairo_line_join_t f_get_line_join() const
	{
		return cairo_get_line_join(v_value);
	}
	void f_set_line_width(double a_width)
	{
		cairo_set_line_width(v_value, a_width);
	}
	double f_get_line_width() const
	{
		return cairo_get_line_width(v_value);
	}
	void f_set_miter_limit(double a_limit)
	{
		cairo_set_miter_limit(v_value, a_limit);
	}
	double f_get_miter_limit() const
	{
		return cairo_get_miter_limit(v_value);
	}
	void f_set_operator(cairo_operator_t a_operator)
	{
		cairo_set_operator(v_value, a_operator);
	}
	cairo_operator_t f_get_operator() const
	{
		return cairo_get_operator(v_value);
	}
	void f_set_tolerance(double a_tolerance)
	{
		cairo_set_tolerance(v_value, a_tolerance);
	}
	double f_get_tolerance() const
	{
		return cairo_get_tolerance(v_value);
	}
	void f_clip()
	{
		cairo_clip(v_value);
	}
	void f_clip_preserve()
	{
		cairo_clip_preserve(v_value);
	}
	t_transfer f_clip_extents() const
	{
		double x0;
		double y0;
		double x1;
		double y1;
		cairo_clip_extents(v_value, &x0, &y0, &x1, &y1);
		return f_tuple(f_global()->f_as(x0), f_global()->f_as(y0), f_global()->f_as(x1), f_global()->f_as(y1));
	}
	void f_reset_clip()
	{
		cairo_reset_clip(v_value);
	}
	cairo_rectangle_list_t* f_copy_clip_rectangle_list() const
	{
		return cairo_copy_clip_rectangle_list(v_value);
	}
	void f_fill()
	{
		cairo_fill(v_value);
	}
	void f_fill_preserve()
	{
		cairo_fill_preserve(v_value);
	}
	t_transfer f_fill_extents() const
	{
		double x0;
		double y0;
		double x1;
		double y1;
		cairo_fill_extents(v_value, &x0, &y0, &x1, &y1);
		return f_tuple(f_global()->f_as(x0), f_global()->f_as(y0), f_global()->f_as(x1), f_global()->f_as(y1));
	}
	bool f_in_fill(double a_x, double a_y) const
	{
		return cairo_in_fill(v_value, a_x, a_y);
	}
	void f_mask(t_pattern& a_pattern)
	{
		cairo_mask(v_value, a_pattern);
	}
	void f_mask(t_surface& a_surface, double a_x, double a_y)
	{
		cairo_mask_surface(v_value, a_surface, a_x, a_y);
	}
	void f_paint()
	{
		cairo_paint(v_value);
	}
	void f_paint_with_alpha(double a_alpha)
	{
		cairo_paint_with_alpha(v_value, a_alpha);
	}
	void f_stroke()
	{
		cairo_stroke(v_value);
	}
	void f_stroke_preserve()
	{
		cairo_stroke_preserve(v_value);
	}
	t_transfer f_stroke_extents() const
	{
		double x0;
		double y0;
		double x1;
		double y1;
		cairo_stroke_extents(v_value, &x0, &y0, &x1, &y1);
		return f_tuple(f_global()->f_as(x0), f_global()->f_as(y0), f_global()->f_as(x1), f_global()->f_as(y1));
	}
	bool f_in_stroke(double a_x, double a_y) const
	{
		return cairo_in_stroke(v_value, a_x, a_y);
	}
	void f_copy_page()
	{
		cairo_copy_page(v_value);
	}
	void f_show_page()
	{
		cairo_show_page(v_value);
	}
	cairo_path_t* f_copy_path()
	{
		return cairo_copy_path(v_value);
	}
	cairo_path_t* f_copy_path_flat()
	{
		return cairo_copy_path_flat(v_value);
	}
	void f_append_path(cairo_path_t* a_path)
	{
		cairo_append_path(v_value, a_path);
	}
	bool f_has_current_point() const
	{
		return cairo_has_current_point(v_value);
	}
	t_transfer f_get_current_point() const
	{
		double x;
		double y;
		cairo_get_current_point(v_value, &x, &y);
		return f_tuple(f_global()->f_as(x), f_global()->f_as(y));
	}
	void f_new_path()
	{
		cairo_new_path(v_value);
	}
	void f_new_sub_path()
	{
		cairo_new_sub_path(v_value);
	}
	void f_close_path()
	{
		cairo_close_path(v_value);
	}
	void f_arc(double a_xc, double a_yc, double a_radius, double a_angle0, double a_angle1)
	{
		cairo_arc(v_value, a_xc, a_yc, a_radius, a_angle0, a_angle1);
	}
	void f_arc_negative(double a_xc, double a_yc, double a_radius, double a_angle0, double a_angle1)
	{
		cairo_arc_negative(v_value, a_xc, a_yc, a_radius, a_angle0, a_angle1);
	}
	void f_curve_to(double a_x0, double a_y0, double a_x1, double a_y1, double a_x2, double a_y2)
	{
		cairo_curve_to(v_value, a_x0, a_y0, a_x1, a_y1, a_x2, a_y2);
	}
	void f_line_to(double a_x, double a_y)
	{
		cairo_line_to(v_value, a_x, a_y);
	}
	void f_move_to(double a_x, double a_y)
	{
		cairo_move_to(v_value, a_x, a_y);
	}
	void f_rectangle(double a_x, double a_y, double a_width, double a_height)
	{
		cairo_rectangle(v_value, a_x, a_y, a_width, a_height);
	}
	void f_glyph_path(const cairo_glyph_t* a_glyphs, int a_n)
	{
		cairo_glyph_path(v_value, a_glyphs, a_n);
	}
	void f_text_path(const std::wstring& a_text)
	{
		cairo_text_path(v_value, f_convert(a_text).c_str());
	}
	void f_rel_curve_to(double a_x0, double a_y0, double a_x1, double a_y1, double a_x2, double a_y2)
	{
		cairo_rel_curve_to(v_value, a_x0, a_y0, a_x1, a_y1, a_x2, a_y2);
	}
	void f_rel_line_to(double a_x, double a_y)
	{
		cairo_rel_line_to(v_value, a_x, a_y);
	}
	void f_rel_move_to(double a_x, double a_y)
	{
		cairo_rel_move_to(v_value, a_x, a_y);
	}
	t_transfer f_path_extents() const
	{
		double x0;
		double y0;
		double x1;
		double y1;
		cairo_path_extents(v_value, &x0, &y0, &x1, &y1);
		return f_tuple(f_global()->f_as(x0), f_global()->f_as(y0), f_global()->f_as(x1), f_global()->f_as(y1));
	}
	void f_translate(double a_x, double a_y)
	{
		cairo_translate(v_value, a_x, a_y);
	}
	void f_scale(double a_x, double a_y)
	{
		cairo_scale(v_value, a_x, a_y);
	}
	void f_rotate(double a_angle)
	{
		cairo_rotate(v_value, a_angle);
	}
	void f_transform(const t_matrix& a_matrix)
	{
		cairo_transform(v_value, &a_matrix);
	}
	void f_set_matrix(const t_matrix& a_matrix)
	{
		cairo_set_matrix(v_value, &a_matrix);
	}
	t_matrix f_get_matrix() const
	{
		cairo_matrix_t matrix;
		cairo_get_matrix(v_value, &matrix);
		return matrix;
	}
	void f_identity_matrix()
	{
		cairo_identity_matrix(v_value);
	}
	t_transfer f_user_to_device(double a_x, double a_y) const
	{
		cairo_user_to_device(v_value, &a_x, &a_y);
		return f_tuple(f_global()->f_as(a_x), f_global()->f_as(a_y));
	}
	t_transfer f_user_to_device_distance(double a_x, double a_y) const
	{
		cairo_user_to_device_distance(v_value, &a_x, &a_y);
		return f_tuple(f_global()->f_as(a_x), f_global()->f_as(a_y));
	}
	t_transfer f_device_to_user(double a_x, double a_y) const
	{
		cairo_device_to_user(v_value, &a_x, &a_y);
		return f_tuple(f_global()->f_as(a_x), f_global()->f_as(a_y));
	}
	t_transfer f_device_to_user_distance(double a_x, double a_y) const
	{
		cairo_device_to_user_distance(v_value, &a_x, &a_y);
		return f_tuple(f_global()->f_as(a_x), f_global()->f_as(a_y));
	}
	void f_select_font_face(const std::wstring& a_family, cairo_font_slant_t a_slant, cairo_font_weight_t a_weight)
	{
		cairo_select_font_face(v_value, f_convert(a_family).c_str(), a_slant, a_weight);
	}
	void f_set_font_size(double a_size)
	{
		cairo_set_font_size(v_value, a_size);
	}
	void f_set_font_matrix(const t_matrix& a_matrix)
	{
		cairo_set_font_matrix(v_value, &a_matrix);
	}
	t_matrix f_get_font_matrix() const
	{
		cairo_matrix_t matrix;
		cairo_get_font_matrix(v_value, &matrix);
		return matrix;
	}
	void f_set_font_options(const t_font_options& a_options)
	{
		cairo_set_font_options(v_value, t_font_options::f_to(&a_options));
	}
	t_transfer f_get_font_options() const
	{
		t_transfer options = t_type_of<t_font_options>::f_construct();
		cairo_get_font_options(v_value, t_font_options::f_to(f_as<t_font_options*>(options)));
		return options;
	}
	void f_set_font_face(t_font_face* a_font_face)
	{
		if (a_font_face)
			cairo_set_font_face(v_value, *a_font_face);
		else
			cairo_set_font_face(v_value, NULL);
	}
	t_font_face* f_get_font_face() const
	{
		return t_font_face::f_wrap(cairo_get_font_face(v_value));
	}
	void f_set_scaled_font(const t_scaled_font& a_scaled_font)
	{
		cairo_set_scaled_font(v_value, a_scaled_font);
	}
	t_scaled_font* f_get_scaled_font() const
	{
		return t_scaled_font::f_wrap(cairo_get_scaled_font(v_value));
	}
	void f_show_text(const std::wstring& a_text)
	{
		cairo_show_text(v_value, f_convert(a_text).c_str());
	}
	void f_show_glyphs(const cairo_glyph_t* a_glyphs, int a_n)
	{
		cairo_show_glyphs(v_value, a_glyphs, a_n);
	}
	void f_show_text_glyphs(const char* a_utf8, int a_n0, const cairo_glyph_t* a_glyphs, int a_n1, const cairo_text_cluster_t* a_clusters, int a_n2, cairo_text_cluster_flags_t a_cluster_flags)
	{
		cairo_show_text_glyphs(v_value, a_utf8, a_n0, a_glyphs, a_n1, a_clusters, a_n2, a_cluster_flags);
	}
	t_transfer f_font_extents() const
	{
		cairo_font_extents_t extents;
		cairo_font_extents(v_value, &extents);
		return f_tuple(f_global()->f_as(extents.ascent), f_global()->f_as(extents.descent), f_global()->f_as(extents.height), f_global()->f_as(extents.max_x_advance), f_global()->f_as(extents.max_y_advance));
	}
	t_transfer f_text_extents(const std::wstring& a_text) const
	{
		cairo_text_extents_t extents;
		cairo_text_extents(v_value, f_convert(a_text).c_str(), &extents);
		return f_tuple(f_global()->f_as(extents.x_bearing), f_global()->f_as(extents.y_bearing), f_global()->f_as(extents.width), f_global()->f_as(extents.height), f_global()->f_as(extents.x_advance), f_global()->f_as(extents.y_advance));
	}
	t_transfer f_glyph_extents(const cairo_glyph_t* a_glyphs, int a_n) const
	{
		cairo_text_extents_t extents;
		cairo_glyph_extents(v_value, a_glyphs, a_n, &extents);
		return f_tuple(f_global()->f_as(extents.x_bearing), f_global()->f_as(extents.y_bearing), f_global()->f_as(extents.width), f_global()->f_as(extents.height), f_global()->f_as(extents.x_advance), f_global()->f_as(extents.y_advance));
	}
};

}

}

namespace xemmai
{

using cairo::xemmai::t_context;

template<>
struct t_type_of<t_context> : t_type
{
#include "cast.h"
	typedef cairo::xemmai::t_extension t_extension;

	static void f_define(t_extension* a_extension);

	t_type_of(const t_transfer& a_module, const t_transfer& a_super) : t_type(a_module, a_super)
	{
	}
	virtual t_type* f_derive(t_object* a_this);
	virtual void f_finalize(t_object* a_this);
	virtual void f_construct(t_object* a_class, t_slot* a_stack, size_t a_n);
	virtual void f_instantiate(t_object* a_class, t_slot* a_stack, size_t a_n);
};

template<>
struct t_type_of<cairo_fill_rule_t> : t_enum_of<cairo_fill_rule_t, cairo::xemmai::t_extension>
{
	static void f_define(t_extension* a_extension);

	t_type_of(const t_transfer& a_module, const t_transfer& a_super) : t_base(a_module, a_super)
	{
	}
};

template<>
struct t_type_of<cairo_line_cap_t> : t_enum_of<cairo_line_cap_t, cairo::xemmai::t_extension>
{
	static void f_define(t_extension* a_extension);

	t_type_of(const t_transfer& a_module, const t_transfer& a_super) : t_base(a_module, a_super)
	{
	}
};

template<>
struct t_type_of<cairo_line_join_t> : t_enum_of<cairo_line_join_t, cairo::xemmai::t_extension>
{
	static void f_define(t_extension* a_extension);

	t_type_of(const t_transfer& a_module, const t_transfer& a_super) : t_base(a_module, a_super)
	{
	}
};

template<>
struct t_type_of<cairo_operator_t> : t_enum_of<cairo_operator_t, cairo::xemmai::t_extension>
{
	static void f_define(t_extension* a_extension);

	t_type_of(const t_transfer& a_module, const t_transfer& a_super) : t_base(a_module, a_super)
	{
	}
};

}

#endif
