#include "ihdr.h"
#include "chunk.h"
#include "util.h"

struct IHDR parse_ihdr(struct chunk * chnk) {
	struct IHDR ret = { 0 };

	ret.width = decode_u32(&chnk->data[0]);
	ret.height = decode_u32(&chnk->data[4]);
	ret.bit_depth = chnk->data[8];
	ret.color_type = chnk->data[9];
	ret.compression_method = chnk->data[10];
	ret.filter_method = chnk->data[11];
	ret.interlace_method = chnk->data[12];

	return ret;
}