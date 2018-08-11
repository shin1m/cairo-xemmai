#include "surface.h"

#include <cstdint>
extern "C" {
#include <jpeglib.h>
}

namespace xemmaix::cairo
{

namespace
{

struct t_scoped_decompress : jpeg_decompress_struct
{
	static void f_error(j_common_ptr cinfo);

	struct jpeg_error_mgr jerr;

	t_scoped_decompress()
	{
		err = jpeg_std_error(&jerr);
		err->error_exit = f_error;
		jpeg_create_decompress(this);
	}
	~t_scoped_decompress()
	{
		jpeg_destroy_decompress(this);
	}
	t_scoped f_decompress();
};

void t_scoped_decompress::f_error(j_common_ptr cinfo)
{
	char buffer[JMSG_LENGTH_MAX];
	cinfo->err->format_message(cinfo, buffer);
	f_throw(f_convert(buffer));
}

t_scoped t_scoped_decompress::f_decompress()
{
	jpeg_read_header(this, TRUE);
	jpeg_start_decompress(this);
	cairo_format_t format;
	switch (out_color_space) {
	case JCS_GRAYSCALE:
		format = CAIRO_FORMAT_A8;
		break;
	case JCS_RGB:
	case JCS_CMYK:
		format = CAIRO_FORMAT_RGB24;
		break;
	default:
		f_throw(L"unsupported color space.");
	}
	int stride = cairo_format_stride_for_width(format, output_width);
	t_scoped data = t_bytes::f_instantiate(stride * output_height);
	t_bytes& bytes = f_as<t_bytes&>(data);
	unsigned char* row = &bytes[0];
	if (out_color_space == JCS_GRAYSCALE) {
		while (output_scanline < output_height) {
			JSAMPLE* buffer[] = {row};
			jpeg_read_scanlines(this, buffer, 1);
			row += stride;
		}
	} else {
		JSAMPARRAY buffer = mem->alloc_sarray(reinterpret_cast<j_common_ptr>(this), JPOOL_IMAGE, output_width * output_components, 1);
		while (output_scanline < output_height) {
			jpeg_read_scanlines(this, buffer, 1);
			JSAMPLE* p = buffer[0];
			uint32_t* q = reinterpret_cast<uint32_t*>(row);
			for (size_t i = 0; i < output_width; ++i) {
				if (out_color_space == JCS_RGB) {
					uint32_t pixel = *p++ << 16;
					pixel |= *p++ << 8;
					pixel |= *p++;
					*q++ = pixel;
				} else {
					int c = *p++;
					int m = *p++;
					int y = *p++;
					int k = *p++;
					if (!saw_Adobe_marker) {
						c = 255 - c;
						m = 255 - m;
						y = 255 - y;
						k = 255 - k;
					}
					uint32_t pixel = k * c / 255 << 16;
					pixel |= k * m / 255 << 8;
					pixel |= k * y / 255;
					*q++ = pixel;
				}
			}
			row += stride;
		}
	}
	jpeg_finish_decompress(this);
	return t_image_surface::f_construct(nullptr, std::move(data), format, output_width, output_height, stride);
}

struct t_jpeg_source : jpeg_source_mgr
{
	static void f_initialize(j_decompress_ptr cinfo);
	static boolean f_fill(j_decompress_ptr cinfo);
	static void f_skip(j_decompress_ptr cinfo, long a_n);
	static void f_terminate(j_decompress_ptr cinfo);

	t_image_source& v_source;

	t_jpeg_source(t_image_source& a_source) : v_source(a_source)
	{
		init_source = f_initialize;
		fill_input_buffer = f_fill;
		skip_input_data = f_skip;
		resync_to_restart = jpeg_resync_to_restart;
		term_source = f_terminate;
		next_input_byte = v_source.f_head();
		bytes_in_buffer = v_source.f_tail() - v_source.f_head();
	}
	boolean f_fill()
	{
		v_source.f_rewind();
		v_source.f_fill();
		unsigned char* bytes = v_source.f_head();
		size_t n = v_source.f_tail() - bytes;
		if (n <= 0) {
			bytes[0] = static_cast<JOCTET>(0xFF);
			bytes[1] = static_cast<JOCTET>(JPEG_EOI);
			n = 2;
		}
		next_input_byte = bytes;
		bytes_in_buffer = n;
		return TRUE;
	}
	void f_skip(long a_n)
	{
		while (a_n > static_cast<long>(bytes_in_buffer)) {
			a_n -= bytes_in_buffer;
			f_fill();
		}
		next_input_byte += a_n;
		bytes_in_buffer -= a_n;
	}
};

void t_jpeg_source::f_initialize(j_decompress_ptr cinfo)
{
}

boolean t_jpeg_source::f_fill(j_decompress_ptr cinfo)
{
	return static_cast<t_jpeg_source*>(cinfo->src)->f_fill();
}

void t_jpeg_source::f_skip(j_decompress_ptr cinfo, long a_n)
{
	static_cast<t_jpeg_source*>(cinfo->src)->f_skip(a_n);
}

void t_jpeg_source::f_terminate(j_decompress_ptr cinfo)
{
}

}

t_scoped t_image_surface::f_create_from_jpeg_source(t_image_source& a_source)
{
	t_jpeg_source source(a_source);
	t_scoped_decompress cinfo;
	cinfo.src = &source;
	return cinfo.f_decompress();
}

t_scoped t_image_surface::f_create_from_jpeg(const std::wstring& a_path)
{
	t_file_source source(a_path);
	return source ? f_create_from_jpeg_source(source) : nullptr;
}

t_scoped t_image_surface::f_create_from_jpeg_stream(const t_value& a_read)
{
	t_stream_source source(a_read);
	return f_create_from_jpeg_source(source);
}

}
