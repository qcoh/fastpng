#pragma once

#include <stdio.h>

#include "types.h"

struct chunk {
	u32 length;
	u8 chunk_type[4];
	u8 crc[4];
	u8 data[];
};

struct chunk * decode_chunk(FILE *);