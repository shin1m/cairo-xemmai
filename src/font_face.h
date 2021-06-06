#ifndef XEMMAIX__CAIRO__FONT_FACE_H
#define XEMMAIX__CAIRO__FONT_FACE_H

#include "cairo.h"

namespace xemmaix::cairo
{

class t_font_face : public t_proxy_of<t_font_face, cairo_font_face_t>
{
	friend class t_type_of<t_object>;
	friend class t_proxy_of<t_font_face, cairo_font_face_t>;

	static cairo_status_t f_set_user_data(cairo_font_face_t* a_value, const cairo_user_data_key_t* a_key, void* a_user, cairo_destroy_func_t a_destroy)
	{
		return cairo_font_face_set_user_data(a_value, a_key, a_user, a_destroy);
	}
	static void* f_get_user_data(cairo_font_face_t* a_value, const cairo_user_data_key_t* a_key)
	{
		return cairo_font_face_get_user_data(a_value, a_key);
	}
	static cairo_font_face_t* f_reference(cairo_font_face_t* a_value)
	{
		return cairo_font_face_reference(a_value);
	}
	static void f_unreference(cairo_font_face_t* a_value)
	{
		cairo_font_face_destroy(a_value);
	}

protected:
	using t_base::t_base;

public:
	static t_font_face* f_wrap(cairo_font_face_t* a_value);

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
		return cairo_font_face_status(v_value);
	}
	cairo_font_type_t f_get_type() const
	{
		return cairo_font_face_get_type(v_value);
	}
};

class t_toy_font_face : public t_font_face
{
	friend class t_proxy_of<t_font_face, cairo_font_face_t>;
	friend class t_font_face;

	using t_font_face::t_font_face;

public:
	static t_pvalue f_construct(t_type* a_class, std::wstring_view a_family, cairo_font_slant_t a_slant, cairo_font_weight_t a_weight)
	{
		return f_construct_shared<t_toy_font_face>(a_class, cairo_toy_font_face_create(f_convert(a_family).c_str(), a_slant, a_weight));
	}

	std::wstring f_get_family() const
	{
		return f_convert(cairo_toy_font_face_get_family(v_value));
	}
	cairo_font_slant_t f_get_slant() const
	{
		return cairo_toy_font_face_get_slant(v_value);
	}
	cairo_font_weight_t f_get_weight() const
	{
		return cairo_toy_font_face_get_weight(v_value);
	}
};

}

namespace xemmai
{

template<>
struct t_type_of<cairo_font_slant_t> : t_enum_of<cairo_font_slant_t, xemmaix::cairo::t_library>
{
	static t_object* f_define(t_library* a_library);

	using t_base::t_base;
};

template<>
struct t_type_of<cairo_font_weight_t> : t_enum_of<cairo_font_weight_t, xemmaix::cairo::t_library>
{
	static t_object* f_define(t_library* a_library);

	using t_base::t_base;
};

template<>
struct t_type_of<xemmaix::cairo::t_font_face> : xemmaix::cairo::t_holds<xemmaix::cairo::t_font_face>
{
	static void f_define(t_library* a_library);

	using t_base::t_base;
	t_pvalue f_do_construct(t_pvalue* a_stack, size_t a_n);
};

template<>
struct t_type_of<cairo_font_type_t> : t_enum_of<cairo_font_type_t, xemmaix::cairo::t_library>
{
	static t_object* f_define(t_library* a_library);

	using t_base::t_base;
};

template<>
struct t_type_of<xemmaix::cairo::t_toy_font_face> : t_bears<xemmaix::cairo::t_toy_font_face, t_type_of<xemmaix::cairo::t_font_face>>
{
	static void f_define(t_library* a_library);

	using t_base::t_base;
	t_pvalue f_do_construct(t_pvalue* a_stack, size_t a_n);
};

}

#endif
