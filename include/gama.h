#pragma once

#include "types.h"

struct chunk;

struct gAMA {
    u32 gamma;
};

struct gAMA parse_gama(struct chunk *);