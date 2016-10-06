#ifndef CAIRO__XEMMAI__FONT_FACE_H
#define CAIRO__XEMMAI__FONT_FACE_H

#include "cairo.h"

namespace cairo
{

namespace xemmai
{

class t_font_face : public t_proxy_of<t_font_face, cairo_font_face_t>
{
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

	t_font_face(cairo_font_face_t* a_value) : t_base(t_session::f_instance()->f_extension()->f_type<t_font_face>(), a_value)
	{
	}

protected:
	t_font_face(t_object* a_class, cairo_font_face_t* a_value) : t_base(a_class, a_value)
	{
	}

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

	t_toy_font_face(cairo_font_face_t* a_value) : t_font_face(t_session::f_instance()->f_extension()->f_type<t_toy_font_face>(), a_value)
	{
	}

public:
	static t_scoped f_construct(t_object* a_class, const std::wstring& a_family, cairo_font_slant_t a_slant, cairo_font_weight_t a_weight)
	{
		return f_construct_shared<t_toy_font_face>(cairo_toy_font_face_create(f_convert(a_family).c_str(), a_slant, a_weight));
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

}

namespace xemmai
{

using cairo::xemmai::t_font_face;
using cairo::xemmai::t_toy_font_face;

template<>
struct t_type_of<cairo_font_slant_t> : t_enum_of<cairo_font_slant_t, cairo::xemmai::t_extension>
{
	static void f_define(t_extension* a_extension);

	using t_base::t_base;
};

template<>
struct t_type_of<cairo_font_weight_t> : t_enum_of<cairo_font_weight_t, cairo::xemmai::t_extension>
{
	static void f_define(t_extension* a_extension);

	using t_base::t_base;
};

template<>
struct t_type_of<t_font_face> : t_type
{
#include "cast.h"
	typedef cairo::xemmai::t_extension t_extension;

	static void f_define(t_extension* a_extension);

	using t_type::t_type;
	virtual t_type* f_derive(t_object* a_this);
	virtual void f_finalize(t_object* a_this);
	virtual t_scoped f_construct(t_object* a_class, t_stacked* a_stack, size_t a_n);
	virtual void f_instantiate(t_object* a_class, t_stacked* a_stack, size_t a_n);
};

template<>
struct t_type_of<cairo_font_type_t> : t_enum_of<cairo_font_type_t, cairo::xemmai::t_extension>
{
	static void f_define(t_extension* a_extension);

	using t_base::t_base;
};

template<>
struct t_type_of<t_toy_font_face> : t_type_of<t_font_face>
{
	static void f_define(t_extension* a_extension);

	using t_type_of<t_font_face>::t_type_of;
	virtual t_scoped f_construct(t_object* a_class, t_stacked* a_stack, size_t a_n);
};

}

#endif
