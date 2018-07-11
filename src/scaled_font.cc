#include "scaled_font.h"

namespace xemmai
{

void t_type_of<xemmaix::cairo::t_scaled_font>::f_define(t_extension* a_extension)
{
	using namespace xemmaix::cairo;
	t_define<t_scaled_font, t_object>(a_extension, L"ScaledFont")
		(L"acquire", t_member<void(t_scaled_font::*)(), &t_scaled_font::f_acquire>())
		(L"release", t_member<void(t_scaled_font::*)(), &t_scaled_font::f_release>())
		(L"status", t_member<cairo_status_t(t_scaled_font::*)() const, &t_scaled_font::f_status>())
		(L"font_extents", t_member<t_scoped(t_scaled_font::*)() const, &t_scaled_font::f_font_extents>())
		(L"text_extents", t_member<t_scoped(t_scaled_font::*)(const std::wstring&) const, &t_scaled_font::f_text_extents>())
		//(L"glyph_extents", t_member<t_scoped(t_scaled_font::*)(const cairo_glyph_t*, int) const, &t_scaled_font::f_glyph_extents>())
		//(L"text_to_glyphs", t_member<cairo_status_t(t_scaled_font::*)(double, double, const char*, int, cairo_glyph_t**, int*, cairo_text_cluster_t**, int*, cairo_text_cluster_flags_t*) const, &t_scaled_font::f_text_to_glyphs>())
		(L"get_font_face", t_member<t_font_face*(t_scaled_font::*)() const, &t_scaled_font::f_get_font_face>())
		(L"get_font_options", t_member<t_scoped(t_scaled_font::*)() const, &t_scaled_font::f_get_font_options>())
		(L"get_font_matrix", t_member<t_matrix(t_scaled_font::*)() const, &t_scaled_font::f_get_font_matrix>())
		(L"get_font_matrix", t_member<t_matrix(t_scaled_font::*)() const, &t_scaled_font::f_get_font_matrix>())
		(L"get_font_matrix", t_member<t_matrix(t_scaled_font::*)() const, &t_scaled_font::f_get_font_matrix>())
		(L"get_type", t_member<cairo_font_type_t(t_scaled_font::*)() const, &t_scaled_font::f_get_type>())
	;
}

t_scoped t_type_of<xemmaix::cairo::t_scaled_font>::f_construct(t_stacked* a_stack, size_t a_n)
{
	return t_construct_with<t_scoped(*)(t_type*, xemmaix::cairo::t_font_face&, const xemmaix::cairo::t_matrix&, const xemmaix::cairo::t_matrix&, const xemmaix::cairo::t_font_options&), xemmaix::cairo::t_scaled_font::f_construct>::t_bind<xemmaix::cairo::t_scaled_font>::f_do(this, a_stack, a_n);
}

}
