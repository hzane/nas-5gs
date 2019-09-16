#include "proto.hh"
#include <bitset>
#include <cstdarg>
#include "core.hh"
#include "tvbuff.hh"
#include "field_meta.hh"

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

    NASNR_AUTO(proto_node*) item    = new proto_node(buf->data, start, len, field);
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
        NASNR_AUTO(uint64_t) v = n2_uint(data, len);
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
    NASNR_AUTO(proto_node*) item = add_item(pinfo, buf, start, len, &hf_expert, enc::na);
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
    NASNR_AUTO(proto_node*) item    = new proto_tree(buf->data, start, len, nullptr);

    va_list args;
    va_start(args, format);
    if (format) item->name = vformat(format, args);
    va_end(args);

    children.push_back(item);
    return item;
}

proto_node::~proto_node() {
#if NASNR_COMPILER_CXX_TYPE_DEDUCE
    for (auto node : children) {
        delete node;
    }
#else
	for(std::list<proto_node*>::const_iterator node = children.begin(); node != children.end(); ++node){
		delete *node;
	}
#endif
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
        NASNR_AUTO(uint64_t) v = n2_uint(data, len);
        if (meta->bitmask) {
            v = v & meta->bitmask;
            v = v >> ws_ctz(meta->bitmask);
        }
        return field_meta_format(meta, v);
    }
    return field_meta_format(meta, data, len, enc);
}


std::string print_text(const field_meta* meta, uint64_t v) {
    if (meta == nullptr) {
        return formats("%ud(%#x) value", v, v);
    }

    return field_meta_format(meta, v);
}

void print_node(std::ostream& out, const proto_node* node, int indent) {
    if (!node->name.empty()) {
        const NASNR_AUTO(string) prefix = std::string(size_t(indent) + indent, char(' '));
        out << prefix << node->name ;

        if (!node->text.empty()) {
            out << " : " << node->text;
        }
        out << " [" << node->offset << "-" << node->length << "]" << std::endl;        
    }
#if NASNR_COMPILER_CXX_TYPE_DEDUCE
    for (NASNR_AUTO(const proto_node*) n : node->children) {
        print_node(out, n, indent + 1);
    }
#else
	for(std::list<proto_node*>::const_iterator n = node->children.begin(); n!=node->children.end(); ++n){
		print_node(out, *n, indent + 1);
	}
#endif
}

proto_node::proto_node(){
}