#include "proto.hh"

#include <bitset>
#include <cstdarg>

#include "core.hh"
#include "field_meta.hh"
#include "tvbuff.hh"

void proto_node::set_length(int len) { length = len; }

std::string print_text(const field_meta* meta,
                       const uint8_t*    data,
                       int               len,
                       uint32_t          enc);

std::string print_text(const field_meta* meta, uint64_t v);

proto_item* proto_node::add_item(packet_info*      pinfo,
                                 tvbuff*           buf,
                                 int               start,
                                 int               len,
                                 const field_meta* field,
                                 uint32_t          encoding) {
    (void) pinfo;

    auto item    = new proto_node(buf->data, start, len, field);
    item->enc    = encoding;
    children.push_back(item);

    if (field && field->tag) {
        item->name = field->tag;
    }
    item->set_item(len, field, encoding);

    return item;
}

proto_item* proto_node::set_item(int len, const field_meta* field, uint32_t encoding) {
    enc = encoding;

    if (encoding == enc::na || encoding == enc::none) return this;

    if (field && ft::is_integer(field->typi)) {
        auto v = n2_uint(data, len);
        if (field->bitmask) {
            v = (v & field->bitmask) >> ws_ctz(field->bitmask);
        }
        val  = v;
        text = print_text(field, v);
    } else
        text = print_text(field, data, len, encoding);

    return this;
}

const field_meta hf_expert = {
    "Expert", "expert",
    ft::ft_expert,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0,
};

proto_item* proto_node::add_expert(packet_info* pinfo,
                                   tvbuff*      buf,
                                   int          start,
                                   int          len,
                                   const char*  format,
                                   ...) {
    auto item = add_item(pinfo, buf, start, len, &hf_expert, enc::na);
    va_list args;
    va_start(args, format);
    item->text = vformat(format, args);
    va_end(args);
    return item;
}

proto_tree* proto_node::add_subtree(packet_info* ,
                                    tvbuff*      buf,
                                    int          start,
                                    int          len,
                                    const char*  format,
                                    ...) {
    using namespace std;
    auto item    = new proto_tree(buf->data, start, len, nullptr);

    va_list args;
    va_start(args, format);
    if (format) item->name = vformat(format, args);
    va_end(args);

    children.push_back(item);
    return item;
}

proto_node::~proto_node() {
    for (auto node : children) {
        delete node;
    }
    children.clear();
}

proto_node::proto_node(const uint8_t* buffer, int offset, int length, const field_meta* m)
    : meta(m), data(buffer + offset), length(length), offset(offset) {}

std::string print_text(const field_meta* meta,
                       const uint8_t*    data,
                       int               len,
                       uint32_t          enc) {
    if (meta == nullptr) {
        return formats("%d bytes", len);
    }
    if (ft::is_integer(meta->typi)){
        auto v = n2_uint(data, len);
        if (meta->bitmask) {
            v = v & meta->bitmask;
            v = v >> ws_ctz(meta->bitmask);
        }
        return meta->format(v);
    }
    return meta->format(data, len, enc);
}


std::string print_text(const field_meta* meta, uint64_t v) {
    if (meta == nullptr) {
        return formats("%ud(%#x) value", v, v);
    }

    return meta->format(v);
}

void print_node(std::ostream& out, const proto_node* node, int indent) {
    if (!node->name.empty()) {
        const auto prefix = std::string(size_t(indent) + indent, char(' '));
        out << prefix << node->name ;

        if (!node->text.empty()) {
            out << " : " << node->text;
        }
        out << " [" << node->offset << "-" << node->length << "]" << std::endl;        
    }
    for (auto n : node->children) {
        print_node(out, n, indent + 1);
    }
}
