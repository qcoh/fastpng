#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint32_t u32;

static const u8 expected_file_signature[] = { 137, 80, 78, 71, 13, 10, 26, 10 };

u32 decode_u32(const u8 *data) {
	return data[3]
		+ (data[2] << 8)
		+ (data[1] << 16)
		+ (data[0] << 24);
}

struct chunk {
	u32 length;
	u8 chunk_type[4];
	u8 crc[4];
	u8 data[];
};

struct chunk *parse_chunk(FILE *fp) {
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

struct IHDR {
	u32 width;
	u32 height;
	u8 bit_depth;
	u8 color_type;
	u8 compression_method;
	u8 filter_method;
	u8 interlace_method;
};

struct IHDR parse_ihdr(const struct chunk *chnk) {
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

int main(int argc, char *argv[]) {
	assert(argc == 2);

	FILE *fp = fopen(argv[1], "rb");
	assert(fp != NULL);

	u8 file_signature[8] = { 0 };
	fread(file_signature, sizeof(file_signature), 1, fp);

	assert(memcmp(file_signature, expected_file_signature, 8) == 0);

	printf("file signature check!\n");

	struct chunk *first = parse_chunk(fp);

	printf("lenght: %d\n", first->length);
	printf(
		"chunk_type: %c%c%c%c\n",
		first->chunk_type[0],
		first->chunk_type[1],
		first->chunk_type[2],
		first->chunk_type[3]
	);

	struct IHDR ihdr = parse_ihdr(first);

	printf("width: %d, height: %d\n", ihdr.width, ihdr.height);

	free(first);
	fclose(fp);
	return 0;
}

