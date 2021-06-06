#include "scaled_font.h"

namespace xemmai
{

void t_type_of<xemmaix::cairo::t_scaled_font>::f_define(t_library* a_library)
{
	using namespace xemmaix::cairo;
	t_define{a_library}
		(L"acquire"sv, t_member<void(t_scaled_font::*)(), &t_scaled_font::f_acquire>())
		(L"release"sv, t_member<void(t_scaled_font::*)(), &t_scaled_font::f_release>())
		(L"status"sv, t_member<cairo_status_t(t_scaled_font::*)() const, &t_scaled_font::f_status>())
		(L"font_extents"sv, t_member<t_pvalue(t_scaled_font::*)() const, &t_scaled_font::f_font_extents>())
		(L"text_extents"sv, t_member<t_pvalue(t_scaled_font::*)(std::wstring_view) const, &t_scaled_font::f_text_extents>())
		//(L"glyph_extents"sv, t_member<t_pvalue(t_scaled_font::*)(const cairo_glyph_t*, int) const, &t_scaled_font::f_glyph_extents>())
		//(L"text_to_glyphs"sv, t_member<cairo_status_t(t_scaled_font::*)(double, double, const char*, int, cairo_glyph_t**, int*, cairo_text_cluster_t**, int*, cairo_text_cluster_flags_t*) const, &t_scaled_font::f_text_to_glyphs>())
		(L"get_font_face"sv, t_member<t_font_face*(t_scaled_font::*)() const, &t_scaled_font::f_get_font_face>())
		(L"get_font_options"sv, t_member<t_pvalue(t_scaled_font::*)() const, &t_scaled_font::f_get_font_options>())
		(L"get_font_matrix"sv, t_member<t_matrix(t_scaled_font::*)() const, &t_scaled_font::f_get_font_matrix>())
		(L"get_font_matrix"sv, t_member<t_matrix(t_scaled_font::*)() const, &t_scaled_font::f_get_font_matrix>())
		(L"get_font_matrix"sv, t_member<t_matrix(t_scaled_font::*)() const, &t_scaled_font::f_get_font_matrix>())
		(L"get_type"sv, t_member<cairo_font_type_t(t_scaled_font::*)() const, &t_scaled_font::f_get_type>())
	.f_derive<t_scaled_font, t_object>();
}

t_pvalue t_type_of<xemmaix::cairo::t_scaled_font>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_construct_with<t_pvalue(*)(t_type*, xemmaix::cairo::t_font_face&, const xemmaix::cairo::t_matrix&, const xemmaix::cairo::t_matrix&, const xemmaix::cairo::t_font_options&), xemmaix::cairo::t_scaled_font::f_construct>::t_bind<xemmaix::cairo::t_scaled_font>::f_do(this, a_stack, a_n);
}

}
