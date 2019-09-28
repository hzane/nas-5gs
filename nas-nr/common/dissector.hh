#pragma once
#include <string>

struct packet;
struct proto_node;
struct buff_view;
struct field_meta;
struct context;
using string = std::string;

struct dissector {
    packet*     packet = nullptr;
    proto_node* tree   = nullptr;
    buff_view*  tvb    = nullptr;
    int         offset = 0;
    int         length = 0;
    void*       data   = nullptr;

    dissector& step(int consumed) {
        offset += consumed;
        length -= consumed;
        return *this;
    }
    proto_node* add_item(int len, const field_meta* fm) const;
    proto_node* add_item(int len, const string& name) const;
    proto_node* add_expert(int len, const string& name) const;
    void        add_bits(const field_meta* metas[]) const;
    auto        safe_ptr() const -> const uint8_t*;
    auto        safe_length(int len) const -> int;
    auto        slice(int len) const -> dissector;
    auto        use_elem(void* elem) const -> dissector;
    auto        uint8() const -> uint8_t;
    auto        uint16() const -> uint16_t;
    auto        uint32() const -> uint32_t;
};
