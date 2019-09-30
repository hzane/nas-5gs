#include "proto.hh"

#include <bitset>
#include <cstdarg>

#include "buff_view.hh"
#include "core.hh"
#include "field_meta.hh"

void node::set_length(int len) { length = len; }

#if 0
std::string print_text(const field_meta* meta, const uint8_t* data, int len);

std::string print_text(const field_meta* meta, uint64_t v);

node_t node::add_item(int start, int len, const field_meta* field) {
    auto item = std::make_shared< node >(node{start, len});

    children.push_back(item);

    if (field && field->tag) {
        item->name = field->tag;
    }
    item->set_item(len, field);

    return item;
}

void node::set_item(int len, const field_meta* field) {
    (void)offset;
    diag("remove this function later\n");
}
#endif

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
    this->length = len;
}

#if 0
std::string print_text(const field_meta* meta, const uint8_t* data, int len) {
    if (meta == nullptr) {
        return formats("%d bytes", len);
    }
    if (ft::is_integer(meta->typi)) {
        auto v = n2_uint(data, len);
        if (meta->bitmask) {
            v = v & meta->bitmask;
            v = v >> ws_ctz(meta->bitmask);
        }
        return meta->format(v);
    }
    return meta->format(data, len);
}

std::string print_text(const field_meta* meta, uint64_t v) {
    if (meta == nullptr) {
        return formats("%ud(%#x) value", v, v);
    }

    return meta->format(v);
}
#endif

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
