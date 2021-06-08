#include "font_face.h"

namespace xemmaix::cairo
{

t_font_face* t_font_face::f_wrap(cairo_font_face_t* a_value)
{
	if (!a_value) return nullptr;
	t_font_face* p = f_from(a_value);
	if (p) return p;
	auto library = t_session::f_instance()->f_library();
	switch (cairo_font_face_get_type(a_value)) {
	case CAIRO_SURFACE_TYPE_IMAGE:
		return &f_new<t_toy_font_face>(library, a_value)->f_as<t_font_face>();
	default:
		return &f_new<t_font_face>(library, a_value)->f_as<t_font_face>();
	}
}

}

namespace xemmai
{

t_object* t_type_of<cairo_font_slant_t>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"NORMAL"sv, CAIRO_FONT_SLANT_NORMAL)
		(L"ITALIC"sv, CAIRO_FONT_SLANT_ITALIC)
		(L"OBLIQUE"sv, CAIRO_FONT_SLANT_OBLIQUE)
		;
	});
}

t_object* t_type_of<cairo_font_weight_t>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"NORMAL"sv, CAIRO_FONT_WEIGHT_NORMAL)
		(L"BOLD"sv, CAIRO_FONT_WEIGHT_BOLD)
		;
	});
}

void t_type_of<xemmaix::cairo::t_font_face>::f_define(t_library* a_library)
{
	using namespace xemmaix::cairo;
	t_define{a_library}
		(L"acquire"sv, t_member<void(t_font_face::*)(), &t_font_face::f_acquire>())
		(L"release"sv, t_member<void(t_font_face::*)(), &t_font_face::f_release>())
		(L"status"sv, t_member<cairo_status_t(t_font_face::*)() const, &t_font_face::f_status>())
		(L"get_type"sv, t_member<cairo_font_type_t(t_font_face::*)() const, &t_font_face::f_get_type>())
	.f_derive<t_font_face, t_object>();
}

t_pvalue t_type_of<xemmaix::cairo::t_font_face>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	f_throw(L"uninstantiatable."sv);
}

t_object* t_type_of<cairo_font_type_t>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"TOY"sv, CAIRO_FONT_TYPE_TOY)
		(L"FT"sv, CAIRO_FONT_TYPE_FT)
		(L"WIN32"sv, CAIRO_FONT_TYPE_WIN32)
		(L"QUARTZ"sv, CAIRO_FONT_TYPE_QUARTZ)
		(L"USER"sv, CAIRO_FONT_TYPE_USER)
		;
	});
}

void t_type_of<xemmaix::cairo::t_toy_font_face>::f_define(t_library* a_library)
{
	using namespace xemmaix::cairo;
	t_define{a_library}
		(L"get_family"sv, t_member<std::wstring(t_toy_font_face::*)() const, &t_toy_font_face::f_get_family>())
		(L"get_slant"sv, t_member<cairo_font_slant_t(t_toy_font_face::*)() const, &t_toy_font_face::f_get_slant>())
		(L"get_weight"sv, t_member<cairo_font_weight_t(t_toy_font_face::*)() const, &t_toy_font_face::f_get_weight>())
	.f_derive<t_toy_font_face, t_font_face>();
}

t_pvalue t_type_of<xemmaix::cairo::t_toy_font_face>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_construct_with<t_pvalue(*)(t_type*, std::wstring_view, cairo_font_slant_t, cairo_font_weight_t), xemmaix::cairo::t_toy_font_face::f_construct>::t_bind<xemmaix::cairo::t_toy_font_face>::f_do(this, a_stack, a_n);
}

}
