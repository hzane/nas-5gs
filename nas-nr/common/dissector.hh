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

struct v_string;
struct tf_string;

struct uint8_field {
    const char* name = nullptr;
    uint8_t     mask = 0;
};
struct tag_field {
    const char*     name = nullptr;
    uint8_t         mask = 0;
    const v_string* tags = nullptr;
};
struct bool_field {
    const char* name         = nullptr;
    uint8_t     mask         = 0;
    tf_string values = {};
};
struct octet_field {
    const char* name = nullptr;
};

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
    int    add_item(const uint8_field* fm, bool step = false);
    int    add_item(const tag_field* fm, bool step = false);
    int    add_item(const octet_field* fm, int len, bool step = false);
    int    add_item(const bool_field* fm, bool step = false);
    node_t add_item(int len, const string& name, const string& val = none) const;
    node_t set_item(int len, const string& val) const;
    node_t add_expert(int len, const string& name) const;
    void   add_bits(const bool_field* metas[], bool step=false) ;
    auto   ptr() const -> const uint8_t*;
    auto   safe_length(int len) const -> int;
    auto   slice(int len) const -> dissector;
    auto   uint8(bool step = false) -> uint8_t;
    auto   uint16(bool step = false) -> uint16_t;
    auto   uint32() const -> uint32_t;
};
