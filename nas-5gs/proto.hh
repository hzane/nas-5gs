#pragma once
#include "config.hh"
#include <list>
#include <string>
#include <vector>
#include <iostream>

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

    proto_item* set_string(const string &v);

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
    uint64_t                 val      = 0;
    uint32_t                 enc    = enc::na; // enc::na
    const field_meta*        meta   = nullptr;
    const uint8_t*           data   = nullptr;
    int                      length = 0;
    int                      offset   = 0;

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


