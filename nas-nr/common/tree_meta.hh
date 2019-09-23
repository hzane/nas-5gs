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
    uint32_t         node_type = 0;
    uint64_t         mask      = 0;
    const char*      keywords  = nullptr;
    const v_string*  tags      = nullptr;
    const tf_string* ind       = nullptr;
    const range_string*  x         = nullptr;
};
