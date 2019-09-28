#pragma once
#include <memory>
#include <string>

struct packet;
struct node;
struct buff_view;
struct field_meta;
struct context;
using string = std::string;
using node_t = std::shared_ptr< node >;

struct dissector {
    packet*    packet = nullptr;
    node_t     tree   = nullptr;
    buff_view* tvb    = nullptr;
    int        offset = 0;
    int        length = 0;
    void*      data   = nullptr;

    void step(int consumed);
    node_t add_item(int len, const field_meta* fm) const;
    node_t add_item(int len, const string& name) const;
    node_t add_item(int len, const string&name, const string&val)const;
    node_t set_item(int len, const string&val)const;
    node_t add_expert(int len, const string& name) const;
    void   add_bits(const field_meta* metas[]) const;
    auto   safe_ptr() const -> const uint8_t*;
    auto   safe_length(int len) const -> int;
    auto   slice(int len) const -> dissector;
    auto   uint8() const -> uint8_t;
    auto   uint16() const -> uint16_t;
    auto   uint32() const -> uint32_t;
};
