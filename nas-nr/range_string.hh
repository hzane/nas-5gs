#pragma once
#include "config.hh"

// [val_min, val_max]
struct range_string {
    uint32_t    val_min;
    uint32_t    val_max;
    const char* text;
};
using r_string = range_string;
