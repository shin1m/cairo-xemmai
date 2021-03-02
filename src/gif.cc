#include "surface.h"

#include <cstdint>

namespace xemmaix::cairo
{

namespace
{

class t_gif_decoder
{
	t_image_source& v_source;
	size_t v_width;
	size_t v_height;
	uint32_t v_background;
	size_t v_aspect;
	uint32_t v_global_colors[256];
	unsigned char v_block_data[255];
	const unsigned char* v_block_p;
	const unsigned char* v_block_q;
	size_t v_block_bit;
	size_t v_code_size;
	size_t v_clear_code;
	size_t v_eoi;
	size_t v_bits_per_code;
	size_t v_next_code;
	int v_predecessors[4096];
	unsigned char v_indices[4096];
	unsigned char v_extracted_data[4096];
	size_t v_extracted_size;

	unsigned char f_read_byte()
	{
		return v_source.f_read_byte();
	}
	size_t f_read_word()
	{
		size_t a = f_read_byte();
		return f_read_byte() << 8 | a;
	}
	void f_skip_blocks();
	void f_read_colors(uint32_t* a_colors, size_t a_size);
	size_t f_read_code();
	size_t f_read_index();
	void f_read_rows(const uint32_t* a_colors, int a_transparent, size_t a_width, size_t a_height, size_t a_base, size_t a_step, unsigned char* a_data, size_t a_stride)
	{
		for (size_t i = a_base; i < a_height; i += a_step) {
			uint32_t* p = reinterpret_cast<uint32_t*>(a_data);
			for (size_t j = 0; j < a_width; ++j) {
				size_t index = f_read_index();
				*p++ = index == a_transparent ? 0 : a_colors[index];
			}
			a_data += a_stride * a_step;
		}
	}

public:
	t_gif_decoder(t_image_source& a_source) : v_source(a_source), v_background(0)
	{
	}
	void f_read_header();
	t_pvalue f_read_image();
	t_pvalue f_read_images();
};

void t_gif_decoder::f_skip_blocks()
{
	while (true) {
		unsigned char n = f_read_byte();
		if (n <= 0) break;
		do f_read_byte(); while (--n > 0);
	}
};

void t_gif_decoder::f_read_colors(uint32_t* a_colors, size_t a_size)
{
	for (size_t i = 0; i < a_size; ++i) {
		uint32_t pixel = f_read_byte();
		pixel <<= 8;
		pixel |= f_read_byte();
		pixel <<= 8;
		pixel |= f_read_byte();
		*a_colors++ = 0xff000000 | pixel;
	}
}

size_t t_gif_decoder::f_read_code()
{
	size_t code = 0;
	size_t i = 0;
	do {
		if (v_block_p >= v_block_q) {
			size_t n = f_read_byte();
			if (n <= 0) f_throw(L"unexpected block terminator."sv);
			for (size_t i = 0; i < n; ++i) v_block_data[i] = f_read_byte();
			v_block_p = v_block_data;
			v_block_q = v_block_p + n;
			v_block_bit = 0;
		}
		size_t n = std::min(8 - v_block_bit, v_bits_per_code - i);
		code |= (*v_block_p >> v_block_bit & ~(~0 << n)) << i;
		v_block_bit += n;
		if (v_block_bit >= 8) {
			++v_block_p;
			v_block_bit = 0;
		}
		i += n;
	} while (i < v_bits_per_code);
	return code;
}

size_t t_gif_decoder::f_read_index()
{
	if (v_extracted_size <= 0) {
		int code = f_read_code();
		while (code == v_clear_code) {
			v_bits_per_code = v_code_size + 1;
			v_next_code = v_eoi;
			code = f_read_code();
		}
		int c = code;
		while (true) {
			unsigned char index = v_indices[c];
			v_extracted_data[v_extracted_size++] = index;
			c = v_predecessors[c];
			if (c >= 0) continue;
			v_indices[v_next_code] = index;
			if (code == v_next_code) v_extracted_data[0] = index;
			break;
		}
		if (++v_next_code >= 4096) f_throw(L"invalid sequence."sv);
		v_predecessors[v_next_code] = code;
		if (v_next_code == 1 << v_bits_per_code) ++v_bits_per_code;
	}
	return v_extracted_data[--v_extracted_size];
}

void t_gif_decoder::f_read_header()
{
	unsigned char bs[6];
	for (size_t i = 0; i < 6; ++i) bs[i] = f_read_byte();
	if (bs[0] != 'G' || bs[1] != 'I' || bs[2] != 'F') f_throw(L"invalid signature."sv);
	if (bs[3] != '8' || (bs[4] != '7' && bs[4] != '9') || bs[5] != 'a') f_throw(L"unknown version."sv);
	v_width = f_read_word();
	v_height = f_read_word();
	unsigned char packed = f_read_byte();
	bool has_colors = (packed & 0x80) != 0;
	unsigned char background = f_read_byte();
	v_aspect = f_read_byte();
	if (has_colors) {
		f_read_colors(v_global_colors, 2 << (packed & 0x07));
		v_background = v_global_colors[background];
	}
}

t_pvalue t_gif_decoder::f_read_image()
{
	size_t disposal = 0;
	bool user_input = false;
	bool has_transparent = false;
	size_t delay = 0;
	int transparent = -1;
	while (true) {
		switch (f_read_byte()) {
		case 0x21:
			if (f_read_byte() == 0xf9) {
				f_read_byte();
				unsigned char packed = f_read_byte();
				disposal = packed >> 2 & 0x07;
				user_input = (packed & 0x02) != 0;
				has_transparent = (packed & 0x01) != 0;
				delay = f_read_word();
				unsigned char b = f_read_byte();
				transparent = has_transparent ? b : -1;
				f_read_byte();
			} else {
				f_skip_blocks();
			}
			continue;
		case 0x2c:
			break;
		default:
			return nullptr;
		}
		break;
	}
	size_t left = f_read_word();
	size_t top = f_read_word();
	size_t width = f_read_word();
	size_t height = f_read_word();
	unsigned char packed = f_read_byte();
	bool has_colors = (packed & 0x80) != 0;
	bool interlaced = (packed & 0x40) != 0;
	uint32_t local_colors[256];
	const uint32_t* colors = v_global_colors;
	if (has_colors) {
		f_read_colors(local_colors, 2 << (packed & 0x07));
		colors = local_colors;
	}
	v_block_p = v_block_q = 0;
	v_block_bit = 0;
	v_code_size = f_read_byte();
	v_clear_code = 1 << v_code_size;
	v_eoi = v_clear_code + 1;
	v_bits_per_code = v_code_size + 1;
	v_next_code = v_eoi;
	for (size_t i = 0; i < v_clear_code; ++i) {
		v_predecessors[i] = -1;
		v_indices[i] = i;
	}
	v_predecessors[v_eoi] = -1;
	v_indices[v_eoi] = 0;
	v_extracted_size = 0;
	int stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, width);
	auto data = t_bytes::f_instantiate(stride * height);
	auto& bytes = f_as<t_bytes&>(data);
	if (interlaced) {
		f_read_rows(colors, transparent, width, height, 0, 8, &bytes[0], stride);
		f_read_rows(colors, transparent, width, height, 4, 8, &bytes[0], stride);
		f_read_rows(colors, transparent, width, height, 2, 4, &bytes[0], stride);
		f_read_rows(colors, transparent, width, height, 1, 2, &bytes[0], stride);
	} else {
		f_read_rows(colors, transparent, width, height, 0, 1, &bytes[0], stride);
	}
	f_skip_blocks();
	auto p = t_image_surface::f_construct(t_session::f_instance()->f_extension()->f_type<t_image_surface>(), data, CAIRO_FORMAT_ARGB32, width, height, stride);
	p.f_put(t_symbol::f_instantiate(L"left"sv), f_global()->f_as(left));
	p.f_put(t_symbol::f_instantiate(L"top"sv), f_global()->f_as(top));
	p.f_put(t_symbol::f_instantiate(L"disposal"sv), f_global()->f_as(disposal));
	p.f_put(t_symbol::f_instantiate(L"user_input"sv), f_global()->f_as(user_input));
	p.f_put(t_symbol::f_instantiate(L"delay"sv), f_global()->f_as(delay));
	return p;
}

t_pvalue t_gif_decoder::f_read_images()
{
	auto p = t_array::f_instantiate();
	p->f_put(t_symbol::f_instantiate(L"width"sv), f_global()->f_as(v_width));
	p->f_put(t_symbol::f_instantiate(L"height"sv), f_global()->f_as(v_height));
	p->f_put(t_symbol::f_instantiate(L"background"sv), f_tuple(
		f_global()->f_as((v_background >> 16 & 0xff) / 255.0),
		f_global()->f_as((v_background >> 8 & 0xff) / 255.0),
		f_global()->f_as((v_background & 0xff) / 255.0),
		f_global()->f_as((v_background >> 24 & 0xff) / 255.0)
	));
	p->f_put(t_symbol::f_instantiate(L"aspect"sv), f_global()->f_as(v_aspect));
	auto& array = f_as<t_array&>(p);
	while (true) {
		auto q = f_read_image();
		if (!q) break;
		array.f_push(q);
	}
	return p;
}

t_pvalue f_read_images(t_image_source& a_source)
{
	t_gif_decoder decoder(a_source);
	decoder.f_read_header();
	return decoder.f_read_images();
}

}

t_pvalue t_image_surface::f_create_from_gif_source(t_image_source& a_source)
{
	t_gif_decoder decoder(a_source);
	decoder.f_read_header();
	return decoder.f_read_image();
}

t_pvalue t_image_surface::f_create_from_gif(std::wstring_view a_path)
{
	t_file_source source(a_path);
	return source ? f_create_from_gif_source(source) : nullptr;
}

t_pvalue t_image_surface::f_create_from_gif_stream(const t_pvalue& a_read)
{
	t_stream_source source(a_read);
	return f_create_from_gif_source(source);
}

t_pvalue t_image_surface::f_create_all_from_gif(std::wstring_view a_path)
{
	t_file_source source(a_path);
	return source ? f_read_images(source) : nullptr;
}

t_pvalue t_image_surface::f_create_all_from_gif_stream(const t_pvalue& a_read)
{
	t_stream_source source(a_read);
	return f_read_images(source);
}

}
