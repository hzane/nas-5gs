#pragma once
#include <iostream>
#include <list>
#include <string>

#include "config.hh"

struct proto_node { // NOLINT: special-member-functions
    void set_length(int len);
    proto_item* add_item(packet_info*      pinfo,
                         tvbuff*           buf,
                         int               start,
                         int               len,
                         const field_meta* field,
                         uint32_t          encoding);

    proto_item* set_item(int len,
                         const field_meta* field,
                         uint32_t          encoding);

    proto_item* add_expert(packet_info* pinfo,
                           tvbuff*      buf,
                           int          start,
                           int          len,
                           const char*  format,
                           ...);

    proto_tree* add_subtree(packet_info* pinfo,
                            tvbuff*      buf,
                            int          start,
                            int          len,
                            const char*  format,
                            ...);

    std::list< proto_node* > children    = {};
    std::string              name        = {};
    std::string              text        = {};
    uint64_t                 val         = 0;
    uint32_t                 enc         = enc::na; // enc::na
    const field_meta*        meta        = nullptr;
    const uint8_t*           data        = nullptr;
    int                      length      = 0;
    int                      offset      = 0;
    uint8_t                  unused_bits = 0;
    uint8_t                  unit        = 0;

    virtual ~proto_node();
    proto_node()= default;
    proto_node(const uint8_t*    buffer,
               int               offset,
               int               length,
               const field_meta* m = nullptr);
};


void print_node(std::ostream& out, const proto_node* node, int indent = 0);
