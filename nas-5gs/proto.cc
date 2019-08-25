#include "core.hh"
#include "proto.hh"
#include "tvbuff.hh"
#include <cstdarg>
#include <vector>
#include <sstream>
#include <iomanip>
#include <bitset>

void proto_node::set_length(int length) {}

void proto_node::set_generated(bool generated) {}

std::string print_text(const field_meta* meta,
                       const uint8_t*    data,
                       int               len,
                       uint32_t          enc);

std::string print_text(const field_meta* meta, uint64_t v);

proto_item* proto_node::add_item(packet_info*      pinfo,
                                 tvbuff*           buf,
                                 int               offset,
                                 int               length,
                                 const field_meta* field,
                                 uint32_t          encoding) {
    auto item = new proto_node();
    item->meta = field;
    item->data = buf->data+offset;
    item->length = length;
    item->enc    = encoding;
    children.push_back(item);

    //TODO:
    if (field){
        item->name = field->name;
    }
    if (encoding != enc::none){
        item->text = print_text(field, buf->data + offset, length, encoding);
    }
    return item;
}

proto_item* proto_node::set_uint(uint64_t v, uint32_t enc, const char* format, ...) {
    using namespace std;

    if (enc != enc::none) this->enc = enc;
    val.ui64 = v;

    // TODO:
    va_list args;
    va_start(args, format);
    if (format)
        text = vformat(format, args);
    else
        text = print_text(meta, v);
    va_end(args);
    return this;
}

proto_item* proto_node::set_int(int64_t v, uint32_t enc, const char* format, ...) {
    using namespace std;

    if (enc != enc::none) this->enc = enc;
    val.i64 = v;

    va_list args;
    va_start(args, format);
    if (format)
        text = vformat(format, args);
    else
        text = print_text(meta, v);
    va_end(args);


    return this;
}

proto_item* proto_node::set_bitmask_list(const field_meta* fields, uint64_t value) {
    using namespace std;
    val.ui64 = value;

    // name = "what's the name";
    bitset< 64 > x(value);
    text = x.to_string();

    return this;
}

proto_item* proto_node::add_expert(packet_info* pinfo,
                                   tvbuff*      buf,
                                   int          offset,
                                   int          length,
                                   const char*  format,
                                   ...) {
    using namespace std;
    auto item    = new proto_tree();
    item->data   = buf->data + offset;
    item->length = length;

    va_list args;
    va_start(args, format);
    item->name = vformat(format, args);
    va_end(args);

    children.push_back(item);
    return item;
}

proto_tree* proto_node::add_subtree(packet_info* pinfo,
                                    tvbuff*      buf,
                                    int          offset,
                                    int          length,
                                    const char*  format,
                                    ...) {
    using namespace std;
    auto item    = new proto_tree();
    item->data   = buf->data + offset;
    item->length = length;

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
