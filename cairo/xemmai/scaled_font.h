#ifndef CAIRO__XEMMAI__SCALED_FONT_H
#define CAIRO__XEMMAI__SCALED_FONT_H

#include "matrix.h"
#include "font_options.h"
#include "font_face.h"

namespace cairo
{

namespace xemmai
{

class t_scaled_font : public t_proxy_of<t_scaled_font, cairo_scaled_font_t>
{
	friend class t_proxy_of<t_scaled_font, cairo_scaled_font_t>;

	static cairo_status_t f_set_user_data(cairo_scaled_font_t* a_value, const cairo_user_data_key_t* a_key, void* a_user, cairo_destroy_func_t a_destroy)
	{
		return cairo_scaled_font_set_user_data(a_value, a_key, a_user, a_destroy);
	}
	static void* f_get_user_data(cairo_scaled_font_t* a_value, const cairo_user_data_key_t* a_key)
	{
		return cairo_scaled_font_get_user_data(a_value, a_key);
	}
	static cairo_scaled_font_t* f_reference(cairo_scaled_font_t* a_value)
	{
		return cairo_scaled_font_reference(a_value);
	}
	static void f_unreference(cairo_scaled_font_t* a_value)
	{
		cairo_scaled_font_destroy(a_value);
	}

	t_scaled_font(cairo_scaled_font_t* a_value) : t_base(t_session::f_instance()->f_extension()->f_type<t_scaled_font>(), a_value)
	{
	}

public:
	static t_scoped f_construct(t_object* a_class, t_font_face& a_font_face, const t_matrix& a_font_matrix, const t_matrix& a_ctm, const t_font_options& a_options)
	{
		return f_construct_shared<t_scaled_font>(cairo_scaled_font_create(a_font_face, &a_font_matrix, &a_ctm, t_font_options::f_to(&a_options)));
	}
	static t_scaled_font* f_wrap(cairo_scaled_font_t* a_value)
	{
		if (!a_value) return nullptr;
		t_scaled_font* p = f_from(a_value);
		return p ? p : new t_scaled_font(a_value);
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
		return cairo_scaled_font_status(v_value);
	}
	t_scoped f_font_extents() const
	{
		cairo_font_extents_t extents;
		cairo_scaled_font_extents(v_value, &extents);
		return f_tuple(f_global()->f_as(extents.ascent), f_global()->f_as(extents.descent), f_global()->f_as(extents.height), f_global()->f_as(extents.max_x_advance), f_global()->f_as(extents.max_y_advance));
	}
	t_scoped f_text_extents(const std::wstring& a_text) const
	{
		cairo_text_extents_t extents;
		cairo_scaled_font_text_extents(v_value, f_convert(a_text).c_str(), &extents);
		return f_tuple(f_global()->f_as(extents.x_bearing), f_global()->f_as(extents.y_bearing), f_global()->f_as(extents.width), f_global()->f_as(extents.height), f_global()->f_as(extents.x_advance), f_global()->f_as(extents.y_advance));
	}
	t_scoped f_glyph_extents(const cairo_glyph_t* a_glyphs, int a_n) const
	{
		cairo_text_extents_t extents;
		cairo_scaled_font_glyph_extents(v_value, a_glyphs, a_n, &extents);
		return f_tuple(f_global()->f_as(extents.x_bearing), f_global()->f_as(extents.y_bearing), f_global()->f_as(extents.width), f_global()->f_as(extents.height), f_global()->f_as(extents.x_advance), f_global()->f_as(extents.y_advance));
	}
	cairo_status_t f_text_to_glyphs(double a_x, double a_y, const char* a_utf8, int a_n0, cairo_glyph_t** a_glyphs, int* a_n1, cairo_text_cluster_t** a_clusters, int* a_n2, cairo_text_cluster_flags_t* a_cluster_flags) const
	{
		return cairo_scaled_font_text_to_glyphs(v_value, a_x, a_y, a_utf8, a_n0, a_glyphs, a_n1, a_clusters, a_n2, a_cluster_flags);
	}
	t_font_face* f_get_font_face() const
	{
		return t_font_face::f_wrap(cairo_scaled_font_get_font_face(v_value));
	}
	t_scoped f_get_font_options() const
	{
		t_scoped options = t_type_of<t_font_options>::f_construct();
		cairo_scaled_font_get_font_options(v_value, t_font_options::f_to(f_as<t_font_options*>(options)));
		return options;
	}
	t_matrix f_get_font_matrix() const
	{
		cairo_matrix_t matrix;
		cairo_scaled_font_get_font_matrix(v_value, &matrix);
		return matrix;
	}
	t_matrix f_get_ctm() const
	{
		cairo_matrix_t matrix;
		cairo_scaled_font_get_ctm(v_value, &matrix);
		return matrix;
	}
	t_matrix f_get_scale_matrix() const
	{
		cairo_matrix_t matrix;
		cairo_scaled_font_get_scale_matrix(v_value, &matrix);
		return matrix;
	}
	cairo_font_type_t f_get_type() const
	{
		return cairo_scaled_font_get_type(v_value);
	}
};

}

}

namespace xemmai
{

using cairo::xemmai::t_scaled_font;

template<>
struct t_type_of<t_scaled_font> : t_type
{
#include "cast.h"
	typedef cairo::xemmai::t_extension t_extension;

	static void f_define(t_extension* a_extension);

	using t_type::t_type;
	virtual t_type* f_derive(t_object* a_this);
	virtual void f_finalize(t_object* a_this);
	virtual t_scoped f_construct(t_object* a_class, t_scoped* a_stack, size_t a_n);
	virtual void f_instantiate(t_object* a_class, t_scoped* a_stack, size_t a_n);
};

}

#endif
