#pragma once
#include "config.hh"
#include <list>
#include <string>
#include <vector>
#include <iostream>

namespace enc {
__declspec(selectany) extern const uint32_t na   = 0;
__declspec(selectany) extern const uint32_t be   = 1; // big endian
__declspec(selectany) extern const uint32_t le   = 2; // little endian
__declspec(selectany) extern const uint32_t none = 4; // host order
} // namespace enc

union value_t {
    uint64_t               ui64;
    uint32_t               ui32;
    int32_t                i32;
    int64_t                i64;
};
struct proto_node {
    void set_length(int length);
    void set_generated(bool generated = true);

    proto_item* add_item(packet_info*      pinfo,
                         tvbuff*           buf,
                         int               offset,
                         int               length,
                         const field_meta* field,
                         uint32_t          encoding);

    proto_item* set_uint(uint64_t val, uint32_t enc, const char* format, ...);

    proto_item* set_int(int64_t val, uint32_t enc, const char* format, ...);

    proto_item* set_bitmask_list(const field_meta* fields[], uint64_t value);

    proto_item* add_expert(packet_info* pinfo,
                           tvbuff*      buf,
                           int          offset,
                           int          length,
                           const char*  format,
                           ...);

    proto_tree* add_subtree(packet_info* pinfo,
                            tvbuff*      buf,
                            int          offset,
                            int          length,
                            const char*  format,
                            ...);

    std::list< proto_node* > children = {};
    std::string              name     = {};
    std::string              text     = {};
    value_t                  val      = {0};
    proto_node*              parent = nullptr;
    uint32_t                 enc    = enc::na; // enc::na
    const field_meta*        meta   = nullptr;
    const uint8_t*           data   = nullptr;
    int                      length = 0;

    virtual ~proto_node();
    proto_node(){};
};

inline void print_node(std::ostream& out, proto_node* node, int indent = 0) {
    auto prefix = std::string(size_t(indent*4), char(' '));
    out << prefix << node->name;
    if (!node->text.empty()){
        out << " : " << node->text;
    }
    out << std::endl;

    for (auto node : node->children){
        print_node(out, node, indent + 1);
    }
}
