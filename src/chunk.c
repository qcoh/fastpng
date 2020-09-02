#include <stdio.h>
#include <stdlib.h>

#include "chunk.h"
#include "util.h"

struct chunk * decode_chunk(FILE * fp) {
	u8 length_big_endian[4] = { 0 };
	fread(length_big_endian, 4, 1, fp);
	u32 length = decode_u32(length_big_endian);

	struct chunk *ret = malloc(sizeof(*ret) + length + sizeof(ret->data[0]));

	ret->length = length;
	
	fread(ret->chunk_type, 4, 1, fp);
	fread(ret->data, ret->length, 1, fp);
	fread(ret->crc, 4, 1, fp);

	return ret;
}