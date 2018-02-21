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

std::string f_convert(const std::wstring& a_string);
std::wstring f_convert(const std::string& a_string);

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
	friend std::string f_convert(const std::wstring& a_string);
	friend std::wstring f_convert(const std::string& a_string);

	static XEMMAI__PORTABLE__THREAD t_session* v_instance;

	t_extension* v_extension;
	std::wstring_convert<std::codecvt_utf8<wchar_t>> v_convert;

public:
#ifdef _WIN32
	static XEMMAIX__CAIRO__EXPORT t_session* f_instance();
#else
	static t_session* f_instance()
	{
		if (!v_instance) t_throwable::f_throw(L"must be inside main.");
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
	t_session* v_session;
	t_scoped v_object;

protected:
	static XEMMAIX__CAIRO__EXPORT cairo_user_data_key_t v_key;

	static void f_destroy(void* a_p)
	{
		static_cast<t_proxy*>(a_p)->f_destroy();
	}
	static t_scoped f_transfer(t_proxy* a_proxy)
	{
		++a_proxy->v_n;
		return a_proxy->v_object;
	}

	size_t v_n = 0;

	t_proxy(t_object* a_class) : v_session(t_session::f_instance()), v_object(t_object::f_allocate(a_class))
	{
		v_object.f_pointer__(this);
	}
	XEMMAIX__CAIRO__EXPORT virtual void f_destroy();

public:
	XEMMAIX__CAIRO__EXPORT virtual ~t_proxy() = default;
	bool f_valid() const
	{
		return v_session == t_session::f_instance();
	}
	t_object* f_object() const
	{
		return v_object;
	}
};

template<typename T, typename T_value>
class t_proxy_of : public t_proxy
{
protected:
	typedef t_proxy_of t_base;

	template<typename T_type>
	static t_scoped f_construct_shared(T_value* a_value)
	{
		T* p = f_from(a_value);
		if (p) {
			if (p->v_n > 0) T::f_unreference(a_value);
			return f_transfer(p);
		} else {
			return f_transfer(new T_type(a_value));
		}
	}

	T_value* v_value;

	t_proxy_of(t_object* a_class, T_value* a_value) : t_proxy(a_class), v_value(a_value)
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
	static t_scoped f_construct(T_value* a_value)
	{
		return f_transfer(new T(a_value));
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
	template<typename T, typename T_super> friend class xemmai::t_define;

	t_slot v_type_matrix;
	t_slot v_type_status;
	t_slot v_type_font_options;
	t_slot v_type_antialias;
	t_slot v_type_subpixel_order;
	t_slot v_type_hint_style;
	t_slot v_type_hint_metrics;
	t_slot v_type_surface;
	t_slot v_type_content;
	t_slot v_type_surface_type;
	t_slot v_type_image_surface;
	t_slot v_type_format;
	t_slot v_type_pattern;
	t_slot v_type_solid_pattern;
	t_slot v_type_surface_pattern;
	t_slot v_type_gradient;
	t_slot v_type_linear_gradient;
	t_slot v_type_radial_gradient;
	t_slot v_type_extend;
	t_slot v_type_filter;
	t_slot v_type_pattern_type;
	t_slot v_type_font_face;
	t_slot v_type_font_type;
	t_slot v_type_font_slant;
	t_slot v_type_font_weight;
	t_slot v_type_toy_font_face;
	t_slot v_type_scaled_font;
	t_slot v_type_context;
	t_slot v_type_fill_rule;
	t_slot v_type_line_cap;
	t_slot v_type_line_join;
	t_slot v_type_operator;

	template<typename T>
	void f_type__(t_scoped&& a_type);

public:
	t_extension(t_object* a_module);
	virtual void f_scan(t_scan a_scan);
	template<typename T>
	const T* f_extension() const
	{
		return f_global();
	}
	template<typename T>
	t_object* f_type() const
	{
		return f_global()->f_type<T>();
	}
	template<typename T>
	t_scoped f_as(const T& a_value) const
	{
		typedef t_type_of<typename t_fundamental<T>::t_type> t;
		return t::f_transfer(f_extension<typename t::t_extension>(), a_value);
	}
};

template<>
inline void t_extension::f_type__<t_matrix>(t_scoped&& a_type)
{
	v_type_matrix = std::move(a_type);
}

template<>
inline void t_extension::f_type__<cairo_status_t>(t_scoped&& a_type)
{
	v_type_status = std::move(a_type);
}

template<>
inline void t_extension::f_type__<t_font_options>(t_scoped&& a_type)
{
	v_type_font_options = std::move(a_type);
}

template<>
inline void t_extension::f_type__<cairo_antialias_t>(t_scoped&& a_type)
{
	v_type_antialias = std::move(a_type);
}

template<>
inline void t_extension::f_type__<cairo_subpixel_order_t>(t_scoped&& a_type)
{
	v_type_subpixel_order = std::move(a_type);
}

template<>
inline void t_extension::f_type__<cairo_hint_style_t>(t_scoped&& a_type)
{
	v_type_hint_style = std::move(a_type);
}

template<>
inline void t_extension::f_type__<cairo_hint_metrics_t>(t_scoped&& a_type)
{
	v_type_hint_metrics = std::move(a_type);
}

template<>
inline void t_extension::f_type__<t_surface>(t_scoped&& a_type)
{
	v_type_surface = std::move(a_type);
}

template<>
inline void t_extension::f_type__<cairo_content_t>(t_scoped&& a_type)
{
	v_type_content = std::move(a_type);
}

template<>
inline void t_extension::f_type__<cairo_surface_type_t>(t_scoped&& a_type)
{
	v_type_surface_type = std::move(a_type);
}

template<>
inline void t_extension::f_type__<t_image_surface>(t_scoped&& a_type)
{
	v_type_image_surface = std::move(a_type);
}

template<>
inline void t_extension::f_type__<cairo_format_t>(t_scoped&& a_type)
{
	v_type_format = std::move(a_type);
}

template<>
inline void t_extension::f_type__<t_pattern>(t_scoped&& a_type)
{
	v_type_pattern = std::move(a_type);
}

template<>
inline void t_extension::f_type__<t_solid_pattern>(t_scoped&& a_type)
{
	v_type_solid_pattern = std::move(a_type);
}

template<>
inline void t_extension::f_type__<t_surface_pattern>(t_scoped&& a_type)
{
	v_type_surface_pattern = std::move(a_type);
}

template<>
inline void t_extension::f_type__<t_gradient>(t_scoped&& a_type)
{
	v_type_gradient = std::move(a_type);
}

template<>
inline void t_extension::f_type__<t_linear_gradient>(t_scoped&& a_type)
{
	v_type_linear_gradient = std::move(a_type);
}

template<>
inline void t_extension::f_type__<t_radial_gradient>(t_scoped&& a_type)
{
	v_type_radial_gradient = std::move(a_type);
}

template<>
inline void t_extension::f_type__<cairo_extend_t>(t_scoped&& a_type)
{
	v_type_extend = std::move(a_type);
}

template<>
inline void t_extension::f_type__<cairo_filter_t>(t_scoped&& a_type)
{
	v_type_filter = std::move(a_type);
}

template<>
inline void t_extension::f_type__<cairo_pattern_type_t>(t_scoped&& a_type)
{
	v_type_pattern_type = std::move(a_type);
}

template<>
inline void t_extension::f_type__<t_font_face>(t_scoped&& a_type)
{
	v_type_font_face = std::move(a_type);
}

template<>
inline void t_extension::f_type__<cairo_font_type_t>(t_scoped&& a_type)
{
	v_type_font_type = std::move(a_type);
}

template<>
inline void t_extension::f_type__<cairo_font_slant_t>(t_scoped&& a_type)
{
	v_type_font_slant = std::move(a_type);
}

template<>
inline void t_extension::f_type__<cairo_font_weight_t>(t_scoped&& a_type)
{
	v_type_font_weight = std::move(a_type);
}

template<>
inline void t_extension::f_type__<t_toy_font_face>(t_scoped&& a_type)
{
	v_type_toy_font_face = std::move(a_type);
}

template<>
inline void t_extension::f_type__<t_scaled_font>(t_scoped&& a_type)
{
	v_type_scaled_font = std::move(a_type);
}

template<>
inline void t_extension::f_type__<t_context>(t_scoped&& a_type)
{
	v_type_context = std::move(a_type);
}

template<>
inline void t_extension::f_type__<cairo_fill_rule_t>(t_scoped&& a_type)
{
	v_type_fill_rule = std::move(a_type);
}

template<>
inline void t_extension::f_type__<cairo_line_cap_t>(t_scoped&& a_type)
{
	v_type_line_cap = std::move(a_type);
}

template<>
inline void t_extension::f_type__<cairo_line_join_t>(t_scoped&& a_type)
{
	v_type_line_join = std::move(a_type);
}

template<>
inline void t_extension::f_type__<cairo_operator_t>(t_scoped&& a_type)
{
	v_type_operator = std::move(a_type);
}

template<>
inline const t_extension* t_extension::f_extension<t_extension>() const
{
	return this;
}

template<>
inline t_object* t_extension::f_type<t_matrix>() const
{
	return v_type_matrix;
}

template<>
inline t_object* t_extension::f_type<cairo_status_t>() const
{
	return v_type_status;
}

template<>
inline t_object* t_extension::f_type<t_font_options>() const
{
	return v_type_font_options;
}

template<>
inline t_object* t_extension::f_type<cairo_antialias_t>() const
{
	return v_type_antialias;
}

template<>
inline t_object* t_extension::f_type<cairo_subpixel_order_t>() const
{
	return v_type_subpixel_order;
}

template<>
inline t_object* t_extension::f_type<cairo_hint_style_t>() const
{
	return v_type_hint_style;
}

template<>
inline t_object* t_extension::f_type<cairo_hint_metrics_t>() const
{
	return v_type_hint_metrics;
}

template<>
inline t_object* t_extension::f_type<t_surface>() const
{
	return v_type_surface;
}

template<>
inline t_object* t_extension::f_type<cairo_content_t>() const
{
	return v_type_content;
}

template<>
inline t_object* t_extension::f_type<cairo_surface_type_t>() const
{
	return v_type_surface_type;
}

template<>
inline t_object* t_extension::f_type<t_image_surface>() const
{
	return v_type_image_surface;
}

template<>
inline t_object* t_extension::f_type<cairo_format_t>() const
{
	return v_type_format;
}

template<>
inline t_object* t_extension::f_type<t_pattern>() const
{
	return v_type_pattern;
}

template<>
inline t_object* t_extension::f_type<t_solid_pattern>() const
{
	return v_type_solid_pattern;
}

template<>
inline t_object* t_extension::f_type<t_surface_pattern>() const
{
	return v_type_surface_pattern;
}

template<>
inline t_object* t_extension::f_type<t_gradient>() const
{
	return v_type_gradient;
}

template<>
inline t_object* t_extension::f_type<t_linear_gradient>() const
{
	return v_type_linear_gradient;
}

template<>
inline t_object* t_extension::f_type<t_radial_gradient>() const
{
	return v_type_radial_gradient;
}

template<>
inline t_object* t_extension::f_type<cairo_extend_t>() const
{
	return v_type_extend;
}

template<>
inline t_object* t_extension::f_type<cairo_filter_t>() const
{
	return v_type_filter;
}

template<>
inline t_object* t_extension::f_type<cairo_pattern_type_t>() const
{
	return v_type_pattern_type;
}

template<>
inline t_object* t_extension::f_type<t_font_face>() const
{
	return v_type_font_face;
}

template<>
inline t_object* t_extension::f_type<cairo_font_type_t>() const
{
	return v_type_font_type;
}

template<>
inline t_object* t_extension::f_type<cairo_font_slant_t>() const
{
	return v_type_font_slant;
}

template<>
inline t_object* t_extension::f_type<cairo_font_weight_t>() const
{
	return v_type_font_weight;
}

template<>
inline t_object* t_extension::f_type<t_toy_font_face>() const
{
	return v_type_toy_font_face;
}

template<>
inline t_object* t_extension::f_type<t_scaled_font>() const
{
	return v_type_scaled_font;
}

template<>
inline t_object* t_extension::f_type<t_context>() const
{
	return v_type_context;
}

template<>
inline t_object* t_extension::f_type<cairo_fill_rule_t>() const
{
	return v_type_fill_rule;
}

template<>
inline t_object* t_extension::f_type<cairo_line_cap_t>() const
{
	return v_type_line_cap;
}

template<>
inline t_object* t_extension::f_type<cairo_line_join_t>() const
{
	return v_type_line_join;
}

template<>
inline t_object* t_extension::f_type<cairo_operator_t>() const
{
	return v_type_operator;
}

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
