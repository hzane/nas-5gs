#pragma once
#include <algorithm>

#include "config.hh"

struct tree_meta;
struct context;
using dissect_func_t = int (*)(dissector, context*, tree_meta const*);

struct tree_meta {
    uint8_t          iei       = 0;
    const char*      name      = nullptr;
    dissect_func_t   func      = nullptr;
};
