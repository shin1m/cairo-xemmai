#include "font_face.h"

#include <cassert>

namespace cairo
{

namespace xemmai
{

t_font_face* t_font_face::f_wrap(cairo_font_face_t* a_value)
{
	if (!a_value) return 0;
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

}

namespace xemmai
{

void t_type_of<cairo_font_slant_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_font_slant_t, int>(a_extension, L"FontSlant")
		(L"NORMAL", CAIRO_FONT_SLANT_NORMAL)
		(L"ITALIC", CAIRO_FONT_SLANT_ITALIC)
		(L"OBLIQUE", CAIRO_FONT_SLANT_OBLIQUE)
	;
}

void t_type_of<cairo_font_weight_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_font_weight_t, int>(a_extension, L"FontWeight")
		(L"NORMAL", CAIRO_FONT_WEIGHT_NORMAL)
		(L"BOLD", CAIRO_FONT_WEIGHT_BOLD)
	;
}

void t_type_of<t_font_face>::f_define(t_extension* a_extension)
{
	t_define<t_font_face, t_object>(a_extension, L"FontFace")
		(L"acquire", t_member<void (t_font_face::*)(), &t_font_face::f_acquire>())
		(L"release", t_member<void (t_font_face::*)(), &t_font_face::f_release>())
		(L"status", t_member<cairo_status_t (t_font_face::*)() const, &t_font_face::f_status>())
		(L"get_type", t_member<cairo_font_type_t (t_font_face::*)() const, &t_font_face::f_get_type>())
	;
}

t_type* t_type_of<t_font_face>::f_derive(t_object* a_this)
{
	return 0;
}

void t_type_of<t_font_face>::f_finalize(t_object* a_this)
{
	t_font_face* p = static_cast<t_font_face*>(a_this->f_pointer());
	assert(!*p);
	delete p;
}

void t_type_of<t_font_face>::f_construct(t_object* a_class, size_t a_n)
{
	t_throwable::f_throw(L"uninstantiatable.");
}

void t_type_of<t_font_face>::f_instantiate(t_object* a_class, size_t a_n)
{
	f_construct(a_class, a_n);
}

void t_type_of<cairo_font_type_t>::f_define(t_extension* a_extension)
{
	t_define<cairo_font_type_t, int>(a_extension, L"FontType")
		(L"TOY", CAIRO_FONT_TYPE_TOY)
		(L"FT", CAIRO_FONT_TYPE_FT)
		(L"WIN32", CAIRO_FONT_TYPE_WIN32)
		(L"QUARTZ", CAIRO_FONT_TYPE_QUARTZ)
		(L"USER", CAIRO_FONT_TYPE_USER)
	;
}

void t_type_of<t_toy_font_face>::f_define(t_extension* a_extension)
{
	t_define<t_toy_font_face, t_font_face>(a_extension, L"ToyFontFace")
		(L"get_family", t_member<std::wstring (t_toy_font_face::*)() const, &t_toy_font_face::f_get_family>())
		(L"get_slant", t_member<cairo_font_slant_t (t_toy_font_face::*)() const, &t_toy_font_face::f_get_slant>())
		(L"get_weight", t_member<cairo_font_weight_t (t_toy_font_face::*)() const, &t_toy_font_face::f_get_weight>())
	;
}

void t_type_of<t_toy_font_face>::f_construct(t_object* a_class, size_t a_n)
{
	t_construct_with<t_transfer (*)(t_object*, const std::wstring&, cairo_font_slant_t, cairo_font_weight_t), t_toy_font_face::f_construct>::f_call(a_class, a_n);
}

}
