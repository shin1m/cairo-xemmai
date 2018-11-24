#ifndef XEMMAIX__CAIRO__CAIRO_H
#define XEMMAIX__CAIRO__CAIRO_H

#ifdef _WIN32
#ifndef XEMMAIX__CAIRO__EXPORT
#define XEMMAIX__CAIRO__EXPORT __declspec(dllimport)
#endif
#else
#define XEMMAIX__CAIRO__EXPORT
#endif

#include <codecvt>
#include <iterator>
#include <locale>
#include <xemmai/convert.h>
#include <xemmai/array.h>
#include <xemmai/bytes.h>
#include <cairo.h>

namespace xemmaix::cairo
{

using namespace xemmai;

class t_proxy;
class t_extension;
struct t_matrix;
struct t_font_options;
class t_surface;
class t_image_surface;
class t_pattern;
class t_solid_pattern;
class t_surface_pattern;
class t_gradient;
class t_linear_gradient;
class t_radial_gradient;
class t_font_face;
class t_toy_font_face;
class t_scaled_font;
class t_context;

std::string f_convert(std::wstring_view a_x);
std::wstring f_convert(std::string_view a_x);

class t_entry
{
protected:
	t_entry* v_previous;
	t_entry* v_next;

	t_entry(bool) : v_previous(this), v_next(this)
	{
	}
	XEMMAIX__CAIRO__EXPORT t_entry();
	void f_unlink()
	{
		v_previous->v_next = v_next;
		v_next->v_previous = v_previous;
		v_previous = v_next = nullptr;
	}

public:
	XEMMAIX__CAIRO__EXPORT virtual void f_dispose();
};

class t_session : public t_entry
{
	friend class t_proxy;
	friend std::string f_convert(std::wstring_view a_x);
	friend std::wstring f_convert(std::string_view a_x);

	static XEMMAI__PORTABLE__THREAD t_session* v_instance;

	t_extension* v_extension;
	std::wstring_convert<std::codecvt_utf8<wchar_t>> v_convert;

public:
#ifdef _WIN32
	static XEMMAIX__CAIRO__EXPORT t_session* f_instance();
#else
	static t_session* f_instance()
	{
		if (!v_instance) f_throw(L"must be inside main."sv);
		return v_instance;
	}
#endif

	t_session(t_extension* a_extension);
	~t_session();
	t_extension* f_extension() const
	{
		return v_extension;
	}
};

class t_proxy : public t_entry
{
	t_session* v_session = t_session::f_instance();
	t_scoped v_object = t_object::f_of(this);

protected:
	static XEMMAIX__CAIRO__EXPORT cairo_user_data_key_t v_key;

	static void f_destroy(void* a_p)
	{
		static_cast<t_proxy*>(a_p)->f_destroy();
	}
	static t_scoped f_transfer(t_scoped&& a_value)
	{
		++a_value->f_as<t_proxy>().v_n;
		return std::move(a_value);
	}

	size_t v_n = 0;

	XEMMAIX__CAIRO__EXPORT virtual void f_destroy();

public:
	XEMMAIX__CAIRO__EXPORT virtual ~t_proxy() = default;
	bool f_valid() const
	{
		return v_session == t_session::f_instance();
	}
};

template<typename T, typename T_value>
class t_proxy_of : public t_proxy
{
protected:
	typedef t_proxy_of t_base;

	template<typename T_type>
	static t_scoped f_construct_shared(t_type* a_class, T_value* a_value)
	{
		T* p = f_from(a_value);
		if (p) {
			if (p->v_n > 0) T::f_unreference(a_value);
			return f_transfer(t_object::f_of(p));
		} else {
			return f_transfer(a_class->template f_new<T_type>(false, a_value));
		}
	}

	T_value* v_value;

	t_proxy_of(T_value* a_value) : v_value(a_value)
	{
		cairo_status_t status = T::f_set_user_data(v_value, &v_key, this, t_proxy::f_destroy);
	}
	virtual void f_destroy()
	{
		v_value = nullptr;
		t_proxy::f_destroy();
	}

public:
	static T* f_from(T_value* a_value)
	{
		return static_cast<T*>(T::f_get_user_data(a_value, &v_key));
	}
	static t_scoped f_construct(t_type* a_class, T_value* a_value)
	{
		return f_transfer(a_class->template f_new<T>(false, a_value));
	}

	virtual void f_dispose()
	{
		t_proxy::f_dispose();
		if (v_n > 0) {
			v_n = 0;
			T::f_unreference(v_value);
		}
	}
	operator T_value*() const
	{
		return v_value;
	}
	void f_acquire()
	{
		if (v_n <= 0) T::f_reference(v_value);
		++v_n;
	}
	void f_release()
	{
		if (v_n > 0 && --v_n <= 0) T::f_unreference(v_value);
	}
};

class t_extension : public xemmai::t_extension
{
	t_slot_of<t_type> v_type_matrix;
	t_slot_of<t_type> v_type_status;
	t_slot_of<t_type> v_type_font_options;
	t_slot_of<t_type> v_type_antialias;
	t_slot_of<t_type> v_type_subpixel_order;
	t_slot_of<t_type> v_type_hint_style;
	t_slot_of<t_type> v_type_hint_metrics;
	t_slot_of<t_type> v_type_surface;
	t_slot_of<t_type> v_type_content;
	t_slot_of<t_type> v_type_surface_type;
	t_slot_of<t_type> v_type_image_surface;
	t_slot_of<t_type> v_type_format;
	t_slot_of<t_type> v_type_pattern;
	t_slot_of<t_type> v_type_solid_pattern;
	t_slot_of<t_type> v_type_surface_pattern;
	t_slot_of<t_type> v_type_gradient;
	t_slot_of<t_type> v_type_linear_gradient;
	t_slot_of<t_type> v_type_radial_gradient;
	t_slot_of<t_type> v_type_extend;
	t_slot_of<t_type> v_type_filter;
	t_slot_of<t_type> v_type_pattern_type;
	t_slot_of<t_type> v_type_font_face;
	t_slot_of<t_type> v_type_font_type;
	t_slot_of<t_type> v_type_font_slant;
	t_slot_of<t_type> v_type_font_weight;
	t_slot_of<t_type> v_type_toy_font_face;
	t_slot_of<t_type> v_type_scaled_font;
	t_slot_of<t_type> v_type_context;
	t_slot_of<t_type> v_type_fill_rule;
	t_slot_of<t_type> v_type_line_cap;
	t_slot_of<t_type> v_type_line_join;
	t_slot_of<t_type> v_type_operator;

public:
	t_extension(t_object* a_module);
	virtual void f_scan(t_scan a_scan);
	template<typename T>
	const T* f_extension() const
	{
		return f_global();
	}
	template<typename T>
	t_slot_of<t_type>& f_type_slot()
	{
		return f_global()->f_type_slot<T>();
	}
	template<typename T>
	t_type* f_type() const
	{
		return const_cast<t_extension*>(this)->f_type_slot<T>();
	}
	template<typename T>
	t_scoped f_as(T&& a_value) const
	{
		typedef t_type_of<typename t_fundamental<T>::t_type> t;
		return t::f_transfer(f_extension<typename t::t_extension>(), std::forward<T>(a_value));
	}
};

template<>
inline const t_extension* t_extension::f_extension<t_extension>() const
{
	return this;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<t_matrix>()
{
	return v_type_matrix;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<cairo_status_t>()
{
	return v_type_status;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<t_font_options>()
{
	return v_type_font_options;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<cairo_antialias_t>()
{
	return v_type_antialias;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<cairo_subpixel_order_t>()
{
	return v_type_subpixel_order;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<cairo_hint_style_t>()
{
	return v_type_hint_style;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<cairo_hint_metrics_t>()
{
	return v_type_hint_metrics;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<t_surface>()
{
	return v_type_surface;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<cairo_content_t>()
{
	return v_type_content;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<cairo_surface_type_t>()
{
	return v_type_surface_type;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<t_image_surface>()
{
	return v_type_image_surface;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<cairo_format_t>()
{
	return v_type_format;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<t_pattern>()
{
	return v_type_pattern;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<t_solid_pattern>()
{
	return v_type_solid_pattern;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<t_surface_pattern>()
{
	return v_type_surface_pattern;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<t_gradient>()
{
	return v_type_gradient;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<t_linear_gradient>()
{
	return v_type_linear_gradient;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<t_radial_gradient>()
{
	return v_type_radial_gradient;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<cairo_extend_t>()
{
	return v_type_extend;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<cairo_filter_t>()
{
	return v_type_filter;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<cairo_pattern_type_t>()
{
	return v_type_pattern_type;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<t_font_face>()
{
	return v_type_font_face;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<cairo_font_type_t>()
{
	return v_type_font_type;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<cairo_font_slant_t>()
{
	return v_type_font_slant;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<cairo_font_weight_t>()
{
	return v_type_font_weight;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<t_toy_font_face>()
{
	return v_type_toy_font_face;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<t_scaled_font>()
{
	return v_type_scaled_font;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<t_context>()
{
	return v_type_context;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<cairo_fill_rule_t>()
{
	return v_type_fill_rule;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<cairo_line_cap_t>()
{
	return v_type_line_cap;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<cairo_line_join_t>()
{
	return v_type_line_join;
}

template<>
inline t_slot_of<t_type>& t_extension::f_type_slot<cairo_operator_t>()
{
	return v_type_operator;
}

template<typename T_base>
struct t_instantiatable : T_base
{
	typedef t_instantiatable t_base;

	using T_base::T_base;
	void f_do_instantiate(t_stacked* a_stack, size_t a_n)
	{
		t_destruct_n destruct(a_stack, a_n);
		a_stack[0].f_construct(this->f_construct(a_stack, a_n));
	}
};

template<typename T>
struct t_holds : t_instantiatable<t_underivable<t_bears<T>>>
{
	template<typename T0>
	struct t_cast
	{
		template<typename T1>
		static T0& f_call(T1&& a_object)
		{
			auto& p = t_base::f_object(std::forward<T1>(a_object))->template f_as<T0>();
			if (!p.f_valid()) f_throw(L"accessing from other thread."sv);
			if (!p) f_throw(L"already destroyed."sv);
			return p;
		}
	};
	template<typename T0>
	struct t_as
	{
		template<typename T1>
		static T0 f_call(T1&& a_object)
		{
			return t_cast<typename t_fundamental<T0>::t_type>::f_call(std::forward<T1>(a_object));
		}
	};
	template<typename T0>
	struct t_as<T0*>
	{
		template<typename T1>
		static T0* f_call(T1&& a_object)
		{
			return reinterpret_cast<size_t>(t_base::f_object(std::forward<T1>(a_object))) == t_value::e_tag__NULL ? nullptr : &t_cast<T0>::f_call(std::forward<T1>(a_object));
		}
	};
	template<typename T0>
	struct t_is
	{
		template<typename T1>
		static bool f_call(T1&& a_object)
		{
			auto p = t_base::f_object(std::forward<T1>(a_object));
			return reinterpret_cast<size_t>(p) >= t_value::e_tag__OBJECT && p->f_type()->template f_derives<typename t_fundamental<T0>::t_type>();
		}
	};
	template<typename T0>
	struct t_is<T0*>
	{
		template<typename T1>
		static bool f_call(T1&& a_object)
		{
			auto p = t_base::f_object(std::forward<T1>(a_object));
			switch (reinterpret_cast<size_t>(p)) {
			case t_value::e_tag__NULL:
				return true;
			case t_value::e_tag__BOOLEAN:
			case t_value::e_tag__INTEGER:
			case t_value::e_tag__FLOAT:
				return false;
			default:
				return p->f_type()->template f_derives<typename t_fundamental<T0>::t_type>();
			}
		}
	};
	typedef xemmaix::cairo::t_extension t_extension;
	typedef t_holds t_base;

	template<typename T_extension, typename T_value>
	static t_scoped f_transfer(T_extension* a_extension, T_value&& a_value)
	{
		return t_object::f_of(a_value);
	}

	using t_instantiatable<t_underivable<t_bears<T>>>::t_instantiatable;
	static void f_do_finalize(t_object* a_this)
	{
		auto& p = a_this->f_as<T>();
		assert(!p);
		p.~T();
	}
};

}

namespace xemmai
{

template<>
struct t_type_of<cairo_status_t> : t_enum_of<cairo_status_t, xemmaix::cairo::t_extension>
{
	static void f_define(t_extension* a_extension);

	using t_base::t_base;
};

}

#endif
