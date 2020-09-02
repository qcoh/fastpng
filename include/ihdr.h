#pragma once

#include "types.h"

struct chunk;

struct IHDR {
	u32 width;
	u32 height;
	u8 bit_depth;
	u8 color_type;
	u8 compression_method;
	u8 filter_method;
	u8 interlace_method;
};

struct IHDR parse_ihdr(struct chunk *);