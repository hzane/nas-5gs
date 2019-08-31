#include "proto.hh"
#include <bitset>
#include <cstdarg>
#include <vector>
#include "core.hh"
#include "tvbuff.hh"
#include "field_meta.hh"

void proto_node::set_length(int len) { this->length = len;}

std::string print_text(const field_meta* meta,
                       const uint8_t*    data,
                       int               len,
                       uint32_t          enc);

std::string print_text(const field_meta* meta, uint64_t v);

proto_item* proto_node::add_item(packet_info*      ,
                                 tvbuff*           buf,
                                 int               start,
                                 int               len,
                                 const field_meta* field,
                                 uint32_t          encoding) {
    auto item = new proto_node();
    item->meta = field;
    item->data = buf->data+ start;
    item->offset = start;
    item->length = len;
    item->enc    = encoding;
    children.push_back(item);

    //TODO:
    if (field){
        item->name = field->name;
    }
    if (encoding == enc::na || encoding == enc::none) return item;

    if (meta && ft::is_integer(meta->ftype)) {
        val = n2uint(item->data, len);
        if(meta->bitmask){
            val = (val&meta->bitmask)>>ws_ctz(meta->bitmask);
        }
    }
    item->text = print_text(field, item->data, len, encoding);

    return item;
}

// don't apply bitmask to v
proto_item* proto_node::set_uint(uint64_t v, uint32_t encode, const char* format, ...) {
    using namespace std;

    if (encode != enc::none) enc = encode;
    val = v;

    va_list args;
    va_start(args, format);
    if (format)
        text = vformat(format, args);
    else
        text = print_text(meta, v);
    va_end(args);
    return this;
}

proto_item* proto_node::set_int(int64_t v, uint32_t encode, const char* format, ...) {
    using namespace std;

    if (encode != enc::none) enc = encode;
    val = v;

    va_list args;
    va_start(args, format);
    if (format)
        text = vformat(format, args);
    else
        text = print_text(meta, v);
    va_end(args);


    return this;
}

proto_item* proto_node::set_string(const string &v) {
    enc = enc::be;

    text = v;
    return this;
}


proto_item* proto_node::add_expert(packet_info* ,
                                   tvbuff*      buf,
                                   int          start,
                                   int          len,
                                   const char*  format,
                                   ...) {
    using namespace std;
    auto item    = new proto_tree();
    item->data   = buf->data + start;
    item->length = len;

    va_list args;
    va_start(args, format);
    item->name = vformat(format, args);
    va_end(args);

    children.push_back(item);
    return item;
}

proto_tree* proto_node::add_subtree(packet_info* ,
                                    tvbuff*      buf,
                                    int          start,
                                    int          len,
                                    const char*  format,
                                    ...) {
    using namespace std;
    auto item    = new proto_tree();
    item->data   = buf->data + start;
    item->length = len;

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

std::string print_text(const field_meta* meta,
                       const uint8_t*    data,
                       int               len,
                       uint32_t          enc) {
    if (meta == nullptr){
        return format_hex(data, len, " ");
    }
    if (ft::is_integer(meta->ftype)){
        return meta->format(n2uint(data, len));
    }
    return meta->format(data, len, enc);
}


std::string print_text(const field_meta* meta, uint64_t v) {
    if (meta == nullptr) {
        return formats("%ud", v);
    }

    return meta->format(v);
}
