#ifndef XEMMAIX__CAIRO__FONT_OPTIONS_H
#define XEMMAIX__CAIRO__FONT_OPTIONS_H

#include "cairo.h"

namespace xemmaix::cairo
{

struct t_font_options
{
	static t_font_options* f_from(cairo_font_options_t* a_p)
	{
		return reinterpret_cast<t_font_options*>(a_p);
	}
	static const t_font_options* f_from(const cairo_font_options_t* a_p)
	{
		return reinterpret_cast<const t_font_options*>(a_p);
	}
	static cairo_font_options_t* f_to(t_font_options* a_p)
	{
		return reinterpret_cast<cairo_font_options_t*>(a_p);
	}
	static const cairo_font_options_t* f_to(const t_font_options* a_p)
	{
		return reinterpret_cast<const cairo_font_options_t*>(a_p);
	}
	static t_font_options* f_create()
	{
		return f_from(cairo_font_options_create());
	}
	static t_font_options* f_copy(const t_font_options* a_original)
	{
		return f_from(cairo_font_options_copy(f_to(a_original)));
	}
	static void f_destroy(t_font_options* a_this)
	{
		cairo_font_options_destroy(f_to(a_this));
	}
	static cairo_status_t f_status(t_font_options* a_this)
	{
		return cairo_font_options_status(f_to(a_this));
	}
	static void f_merge(t_font_options* a_this, const t_font_options* a_other)
	{
		cairo_font_options_merge(f_to(a_this), f_to(a_other));
	}
	static intptr_t f_hash(const t_font_options* a_this)
	{
		return cairo_font_options_hash(f_to(a_this));
	}
	static bool f_equal(const t_font_options* a_this, const t_font_options* a_other)
	{
		return cairo_font_options_equal(f_to(a_this), f_to(a_other)) != 0;
	}
	static void f_set_antialias(t_font_options* a_this, cairo_antialias_t a_antialias)
	{
		cairo_font_options_set_antialias(f_to(a_this), a_antialias);
	}
	static cairo_antialias_t f_get_antialias(const t_font_options* a_this)
	{
		return cairo_font_options_get_antialias(f_to(a_this));
	}
	static void f_set_subpixel_order(t_font_options* a_this, cairo_subpixel_order_t a_subpixel_order)
	{
		cairo_font_options_set_subpixel_order(f_to(a_this), a_subpixel_order);
	}
	static cairo_subpixel_order_t f_get_subpixel_order(const t_font_options* a_this)
	{
		return cairo_font_options_get_subpixel_order(f_to(a_this));
	}
	static void f_set_hint_style(t_font_options* a_this, cairo_hint_style_t a_hint_style)
	{
		cairo_font_options_set_hint_style(f_to(a_this), a_hint_style);
	}
	static cairo_hint_style_t f_get_hint_style(const t_font_options* a_this)
	{
		return cairo_font_options_get_hint_style(f_to(a_this));
	}
	static void f_set_hint_metrics(t_font_options* a_this, cairo_hint_metrics_t a_hint_metrics)
	{
		cairo_font_options_set_hint_metrics(f_to(a_this), a_hint_metrics);
	}
	static cairo_hint_metrics_t f_get_hint_metrics(const t_font_options* a_this)
	{
		return cairo_font_options_get_hint_metrics(f_to(a_this));
	}
};

}

namespace xemmai
{

template<>
struct t_type_of<xemmaix::cairo::t_font_options> : xemmaix::cairo::t_instantiatable<t_bears<xemmaix::cairo::t_font_options>>
{
	using t_library = xemmaix::cairo::t_library;

	static t_pvalue f_construct(t_type* a_class)
	{
		auto object = f_engine()->f_allocate(sizeof(xemmaix::cairo::t_font_options*));
		object->f_as<xemmaix::cairo::t_font_options*>() = xemmaix::cairo::t_font_options::f_create();
		object->f_be(a_class);
		return object;
	}
	static t_pvalue f_construct(t_type* a_class, const xemmaix::cairo::t_font_options* a_original)
	{
		auto object = f_engine()->f_allocate(sizeof(xemmaix::cairo::t_font_options*));
		object->f_as<xemmaix::cairo::t_font_options*>() = xemmaix::cairo::t_font_options::f_copy(a_original);
		object->f_be(a_class);
		return object;
	}
	static t_pvalue f_construct()
	{
		return f_construct(xemmaix::cairo::t_session::f_instance()->f_library()->f_type<xemmaix::cairo::t_font_options>());
	}
	static void f_define(t_library* a_library);

	using t_base::t_base;
	static void f_do_finalize(t_object* a_this);
	t_pvalue f_do_construct(t_pvalue* a_stack, size_t a_n);
};

template<>
struct t_type_of<cairo_antialias_t> : t_enum_of<cairo_antialias_t, xemmaix::cairo::t_library>
{
	static t_object* f_define(t_library* a_library);

	using t_base::t_base;
};

template<>
struct t_type_of<cairo_subpixel_order_t> : t_enum_of<cairo_subpixel_order_t, xemmaix::cairo::t_library>
{
	static t_object* f_define(t_library* a_library);

	using t_base::t_base;
};

template<>
struct t_type_of<cairo_hint_style_t> : t_enum_of<cairo_hint_style_t, xemmaix::cairo::t_library>
{
	static t_object* f_define(t_library* a_library);

	using t_base::t_base;
};

template<>
struct t_type_of<cairo_hint_metrics_t> : t_enum_of<cairo_hint_metrics_t, xemmaix::cairo::t_library>
{
	static t_object* f_define(t_library* a_library);

	using t_base::t_base;
};

}

#endif
