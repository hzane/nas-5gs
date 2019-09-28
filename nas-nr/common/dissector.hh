#pragma once
#include <memory>
#include <string>

#include "format.hh"

struct packet;
struct node;
struct buff_view;
struct field_meta;
struct context;
using string = std::string;
using node_t = std::shared_ptr< node >;

struct dissector {
    inline static string none = string();

    packet*    packet = nullptr;
    node_t     tree   = nullptr;
    buff_view* tvb    = nullptr;
    int        offset = 0;
    int        length = 0;
    void*      data   = nullptr;

    void   step(int consumed);
    node_t add_item(int len, const field_meta* fm) const;
    node_t add_item(int len, const string& name, const string& val = none) const;
    node_t set_item(int len, const string& val) const;
    node_t add_expert(int len, const string& name) const;
    void   add_bits(const field_meta* metas[]) const;
    auto   ptr() const -> const uint8_t*;
    auto   safe_length(int len) const -> int;
    auto   slice(int len) const -> dissector;
    auto   uint8(bool step = false) -> uint8_t;
    auto   uint16(bool step = false) -> uint16_t;
    auto   uint32() const -> uint32_t;
};

struct v_string;
struct true_false_string;

struct uint8_field {
    const char* name = nullptr;
    uint8_t     mask = 0;
    int         add(dissector d, context*) const;
};
struct tag_field {
    const char*     name = nullptr;
    uint8_t         mask = 0;
    const v_string* tags = nullptr;

    int add(dissector d, context*) const;
};
struct tf_field {
    const char*              name      = nullptr;
    uint8_t                  mask      = 0;
    const true_false_string* indicator = nullptr;

    int add(dissector d, context*) const;
};
struct octet_field {
    const char* name = nullptr;

    int add(dissector d, context*, int len) const;
};
