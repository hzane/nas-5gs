#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "config.hh"

struct node;
using node_t = std::shared_ptr<node>;

struct node { // NOLINT: special-member-functions
    void set_length(int len);
    node_t add_item(packet*      pinfo,
                         buff_view*           buf,
                         int               start,
                         int               len,
                         const field_meta* field);

    void set_item(int len,
                         const field_meta* field);

    node_t add_expert(packet* pinfo,
                           buff_view*      buf,
                           int          start,
                           int          len,
                           const char*  format,
                           ...);

    node_t add_subtree(packet* pinfo,
                            buff_view*      buf,
                            int          start,
                            int          len,
                            const char*  format,
                            ...);

    std::vector< node_t > children    = {};
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

    node()=default;
    node(const uint8_t*    buffer,
               int               offset,
               int               length,
               const field_meta* m = nullptr);
};


void print_node(std::ostream& out, const node_t node, int indent = 0);
