#include "proto.hh"

#include <bitset>
#include <cstdarg>

#include "buff_view.hh"
#include "core.hh"

void node::set_length(int len) { length = len; }

inline const element_field hf_expert = {
    "Expert",
};

node_t node::add_expert(int start, int len, const string& text) {
    return add_item(start, len, "Expert", text);
}

node_t node::add_item(int start, int len, const string& name, const string& val) {
    auto sub = std::make_shared< node >(node{offset, length, name, val});
    children.push_back(sub);
    return sub;
}

void node::set_item(int start, int len, const string& text) {
    this->text   = text;
    this->offset = start;
    if (len >= 0) this->length = len;
}

void print_node(std::ostream& out, const node_t node, int indent) {
    if (!node->name.empty()) {
        const auto prefix = std::string(size_t(indent) + indent, char(' '));
        out << prefix << node->name;

        if (!node->text.empty()) {
            out << " : " << node->text;
        }
        out << " [" << node->offset << "-" << node->length << "]" << std::endl;
    }
    for (auto n : node->children) {
        print_node(out, n, indent + 1);
    }
}
