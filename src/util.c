#include "util.h"

u32 decode_u32(const u8 * data) {
	return data[3]
		+ (data[2] << 8)
		+ (data[1] << 16)
		+ (data[0] << 24);
}