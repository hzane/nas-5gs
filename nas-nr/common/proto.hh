#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "config.hh"

struct node;
using node_t = std::shared_ptr< node >;

struct node {
    inline static string none = string();

    void   set_length(int len);
    void   set_item(int start, int len, const string& text);
    void   set_item(int len, const field_meta* field);
    node_t add_item(int start, int len, const field_meta* field);
    node_t add_item(int start, int len, const string& name, const string& text = none);
    node_t add_expert(int start, int len, const char* format, ...);

    int                   offset   = 0;
    int                   length   = 0;
    std::string           name     = {};
    std::string           text     = {};
    std::vector< node_t > children = {};
};

void print_node(std::ostream& out, node_t node, int indent = 0);
