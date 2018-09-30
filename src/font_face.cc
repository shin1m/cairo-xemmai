#include "font_face.h"

namespace xemmaix::cairo
{

t_font_face* t_font_face::f_wrap(cairo_font_face_t* a_value)
{
	if (!a_value) return nullptr;
	t_font_face* p = f_from(a_value);
	if (p) return p;
	switch (cairo_font_face_get_type(a_value)) {
	case CAIRO_SURFACE_TYPE_IMAGE:
		return new t_toy_font_face(a_value);
	default:
		return new t_font_face(a_value);
	}
}

}

namespace xemmai
{

void t_type_of<cairo_font_slant_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_font_slant_t, intptr_t>(a_extension, L"FontSlant"sv)
		(L"NORMAL"sv, CAIRO_FONT_SLANT_NORMAL)
		(L"ITALIC"sv, CAIRO_FONT_SLANT_ITALIC)
		(L"OBLIQUE"sv, CAIRO_FONT_SLANT_OBLIQUE)
	;
}

void t_type_of<cairo_font_weight_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_font_weight_t, intptr_t>(a_extension, L"FontWeight"sv)
		(L"NORMAL"sv, CAIRO_FONT_WEIGHT_NORMAL)
		(L"BOLD"sv, CAIRO_FONT_WEIGHT_BOLD)
	;
}

void t_type_of<xemmaix::cairo::t_font_face>::f_define(t_extension* a_extension)
{
	using namespace xemmaix::cairo;
	t_define<t_font_face, t_object>(a_extension, L"FontFace"sv)
		(L"acquire"sv, t_member<void(t_font_face::*)(), &t_font_face::f_acquire>())
		(L"release"sv, t_member<void(t_font_face::*)(), &t_font_face::f_release>())
		(L"status"sv, t_member<cairo_status_t(t_font_face::*)() const, &t_font_face::f_status>())
		(L"get_type"sv, t_member<cairo_font_type_t(t_font_face::*)() const, &t_font_face::f_get_type>())
	;
}

t_scoped t_type_of<xemmaix::cairo::t_font_face>::f_do_construct(t_stacked* a_stack, size_t a_n)
{
	f_throw(L"uninstantiatable."sv);
}

void t_type_of<cairo_font_type_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_font_type_t, intptr_t>(a_extension, L"FontType"sv)
		(L"TOY"sv, CAIRO_FONT_TYPE_TOY)
		(L"FT"sv, CAIRO_FONT_TYPE_FT)
		(L"WIN32"sv, CAIRO_FONT_TYPE_WIN32)
		(L"QUARTZ"sv, CAIRO_FONT_TYPE_QUARTZ)
		(L"USER"sv, CAIRO_FONT_TYPE_USER)
	;
}

void t_type_of<xemmaix::cairo::t_toy_font_face>::f_define(t_extension* a_extension)
{
	using namespace xemmaix::cairo;
	t_define<t_toy_font_face, t_font_face>(a_extension, L"ToyFontFace"sv)
		(L"get_family"sv, t_member<std::wstring(t_toy_font_face::*)() const, &t_toy_font_face::f_get_family>())
		(L"get_slant"sv, t_member<cairo_font_slant_t(t_toy_font_face::*)() const, &t_toy_font_face::f_get_slant>())
		(L"get_weight"sv, t_member<cairo_font_weight_t(t_toy_font_face::*)() const, &t_toy_font_face::f_get_weight>())
	;
}

t_scoped t_type_of<xemmaix::cairo::t_toy_font_face>::f_do_construct(t_stacked* a_stack, size_t a_n)
{
	return t_construct_with<t_scoped(*)(t_type*, std::wstring_view, cairo_font_slant_t, cairo_font_weight_t), xemmaix::cairo::t_toy_font_face::f_construct>::t_bind<xemmaix::cairo::t_toy_font_face>::f_do(this, a_stack, a_n);
}

}
