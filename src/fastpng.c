#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "chunk.h"
#include "ihdr.h"
#include "util.h"

static const u8 expected_file_signature[] = { 137, 80, 78, 71, 13, 10, 26, 10 };

int main(int argc, char *argv[]) {
	assert(argc == 2);

	FILE *fp = fopen(argv[1], "rb");
	assert(fp != NULL);

	u8 file_signature[8] = { 0 };
	fread(file_signature, sizeof(file_signature), 1, fp);

	assert(memcmp(file_signature, expected_file_signature, 8) == 0);

	printf("file signature check!\n");

	struct chunk *first = decode_chunk(fp);

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

	for (;;) {
		struct chunk *chnk = decode_chunk(fp);
		printf("lenght: %d\n", chnk->length);
		printf(
			"chunk_type: %c%c%c%c\n",
			chnk->chunk_type[0],
			chnk->chunk_type[1],
			chnk->chunk_type[2],
			chnk->chunk_type[3]
		);

		const bool iend 
			=  chnk->chunk_type[0] == 'I'
			&& chnk->chunk_type[1] == 'E'
			&& chnk->chunk_type[2] == 'N'
			&& chnk->chunk_type[3] == 'D';

		free(chnk);

		if (iend) {
			break;
		}
	}

	free(first);
	fclose(fp);
	return 0;
}

