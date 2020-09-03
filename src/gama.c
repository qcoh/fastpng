#include "gama.h"
#include "chunk.h"
#include "util.h"

struct gAMA parse_gama(struct chunk * chnk) {
    struct gAMA ret = { 0 };

    ret.gamma = decode_u32(chnk->data);

    return ret
}