#ifndef XEMMAIX__CAIRO__CAIRO_H
#define XEMMAIX__CAIRO__CAIRO_H

#ifdef _WIN32
#ifndef XEMMAIX__CAIRO__EXPORT
#define XEMMAIX__CAIRO__EXPORT __declspec(dllimport)
#endif
#else
#define XEMMAIX__CAIRO__EXPORT
#endif

#include <xemmai/convert.h>
#include <cairo.h>

namespace xemmaix::cairo
{

using namespace xemmai;

class t_proxy;
struct t_library;
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

template<typename C0, typename C1>
struct t_converter : private portable::t_iconv
{
	using portable::t_iconv::t_iconv;
	int f_to(char** a_p, size_t* a_n, auto a_out) const
	{
		char cs[16];
		char* p = cs;
		size_t n = sizeof(cs);
		while (iconv(v_cd, a_p, a_n, &p, &n) == size_t(-1)) {
			auto e = errno;
			if (e == EINTR) continue;
			a_out(reinterpret_cast<const C1*>(cs), (p - cs) / sizeof(C1));
			if (e != E2BIG) return e;
			p = cs;
			n = sizeof(cs);
		}
		a_out(reinterpret_cast<const C1*>(cs), (p - cs) / sizeof(C1));
		return 0;
	}
	std::basic_string<C1> operator()(std::basic_string_view<C0> a_x) const
	{
		std::basic_string<C1> s;
		auto p = reinterpret_cast<char*>(const_cast<C0*>(a_x.data()));
		size_t n = a_x.size() * sizeof(C0);
		auto append = [&](auto a_p, auto a_n)
		{
			s.append(a_p, a_p + a_n);
		};
		auto e = f_to(&p, &n, append);
		if (e == 0) e = f_to(nullptr, nullptr, append);
		if (e == 0) return s;
		throw std::system_error(e, std::generic_category());
	}
};

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

	t_library* v_library;
	t_converter<wchar_t, char> v_to_utf8;
	t_converter<char, wchar_t> v_from_utf8;

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

	t_session(t_library* a_library);
	~t_session();
	t_library* f_library() const
	{
		return v_library;
	}
};

class t_proxy : public t_entry
{
	t_session* v_session = t_session::f_instance();
	t_root v_object = t_object::f_of(this);

protected:
	static XEMMAIX__CAIRO__EXPORT cairo_user_data_key_t v_key;

	static void f_destroy(void* a_p)
	{
		static_cast<t_proxy*>(a_p)->f_destroy();
	}
	static t_pvalue f_transfer(const t_pvalue& a_value)
	{
		++a_value->f_as<t_proxy>().v_n;
		return a_value;
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
	using t_base = t_proxy_of;

	template<typename T_type>
	static t_pvalue f_construct_shared(t_type* a_class, T_value* a_value)
	{
		T* p = f_from(a_value);
		if (p) {
			if (p->v_n > 0) T::f_unreference(a_value);
			return f_transfer(t_object::f_of(p));
		} else {
			return f_transfer(a_class->f_new<T_type>(a_value));
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
	static t_pvalue f_construct(t_type* a_class, T_value* a_value)
	{
		return f_transfer(a_class->f_new<T>(a_value));
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

struct t_library : xemmai::t_library
{
#define XEMMAIX__CAIRO__TYPES(_)\
	_(matrix)\
	_##_AS(cairo_status_t, status)\
	_(font_options)\
	_##_AS(cairo_antialias_t, antialias)\
	_##_AS(cairo_subpixel_order_t, subpixel_order)\
	_##_AS(cairo_hint_style_t, hint_style)\
	_##_AS(cairo_hint_metrics_t, hint_metrics)\
	_(surface)\
	_##_AS(cairo_content_t, content)\
	_##_AS(cairo_surface_type_t, surface_type)\
	_(image_surface)\
	_##_JUST(gif_surface)\
	_##_JUST(gif_surfaces)\
	_##_AS(cairo_format_t, format)\
	_(pattern)\
	_(solid_pattern)\
	_(surface_pattern)\
	_##_AS(cairo_extend_t, extend)\
	_##_AS(cairo_filter_t, filter)\
	_##_AS(cairo_pattern_type_t, pattern_type)\
	_(gradient)\
	_(linear_gradient)\
	_(radial_gradient)\
	_##_AS(cairo_font_slant_t, font_slant)\
	_##_AS(cairo_font_weight_t, font_weight)\
	_(font_face)\
	_##_AS(cairo_font_type_t, font_type)\
	_(toy_font_face)\
	_(scaled_font)\
	_(context)\
	_##_AS(cairo_fill_rule_t, fill_rule)\
	_##_AS(cairo_line_cap_t, line_cap)\
	_##_AS(cairo_line_join_t, line_join)\
	_##_AS(cairo_operator_t, operator)
	XEMMAIX__CAIRO__TYPES(XEMMAI__TYPE__DECLARE)

	using xemmai::t_library::t_library;
	XEMMAI__LIBRARY__MEMBERS
};

XEMMAI__LIBRARY__BASE(t_library, t_global, f_global())
#define XEMMAI__TYPE__LIBRARY t_library
XEMMAIX__CAIRO__TYPES(XEMMAI__TYPE__DEFINE)
#undef XEMMAI__TYPE__LIBRARY

template<typename T_base>
struct t_instantiatable : T_base
{
	using t_base = t_instantiatable;

	using T_base::T_base;
	void f_do_instantiate(t_pvalue* a_stack, size_t a_n)
	{
		a_stack[0] = this->f_construct(a_stack, a_n);
	}
};

template<typename T>
struct t_holds : t_instantiatable<t_bears<T>>
{
	template<typename U>
	static U& f_cast(auto&& a_object)
	{
		auto& p = static_cast<t_object*>(a_object)->f_as<U>();
		if (!p.f_valid()) f_throw(L"accessing from other thread."sv);
		if (!p) f_throw(L"already destroyed."sv);
		return p;
	}
	template<typename U>
	struct t_cast
	{
		static U f_as(auto&& a_object)
		{
			return f_cast<typename t_fundamental<U>::t_type>(std::forward<decltype(a_object)>(a_object));
		}
		static bool f_is(t_object* a_object)
		{
			return reinterpret_cast<uintptr_t>(a_object) >= c_tag__OBJECT && a_object->f_type()->f_derives<typename t_fundamental<U>::t_type>();
		}
	};
	template<typename U>
	struct t_cast<U*>
	{
		static U* f_as(auto&& a_object)
		{
			return static_cast<t_object*>(a_object) ? &f_cast<U>(std::forward<decltype(a_object)>(a_object)) : nullptr;
		}
		static bool f_is(t_object* a_object)
		{
			return reinterpret_cast<uintptr_t>(a_object) == c_tag__NULL || reinterpret_cast<uintptr_t>(a_object) >= c_tag__OBJECT && a_object->f_type()->f_derives<typename t_fundamental<U>::t_type>();
		}
	};
	using t_library = xemmaix::cairo::t_library;
	using t_base = t_holds;

	static t_pvalue f_transfer(auto* a_library, auto&& a_value)
	{
		return t_object::f_of(a_value);
	}

	using t_instantiatable<t_bears<T>>::t_instantiatable;
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
struct t_type_of<cairo_status_t> : t_enum_of<cairo_status_t, xemmaix::cairo::t_library>
{
	static t_object* f_define(t_library* a_library);

	using t_base::t_base;
};

}

#endif
