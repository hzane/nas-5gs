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

//TODO:
    if (field){
        item->name = field->name;
        item->text = print_text(field, buf->data + offset, length, encoding);
    }
    children.push_back(item);
    return item;
}

proto_item* proto_node::set_uint(uint64_t v, uint32_t enc, const char* format, ...) {
    if (enc != enc::none) this->enc = enc;
    using namespace std;
    val.ui64 = v;
    // TODO:
    text = formats("%08x", v);

    va_list args;
    va_start(args, format);
    if (format) name = vformat(format, args);
    va_end(args);
    return this;
}

proto_item* proto_node::set_int(int64_t v, uint32_t enc, const char* format, ...) {
    if (enc != enc::none) this->enc = enc;
    using namespace std;
    val.i64 = v;

    va_list args;
    va_start(args, format);
    if (format) name = vformat(format, args);
    va_end(args);

    text = formats("%d", (int) v);

    return this;
}

proto_item* proto_node::set_bitmask_list(const field_meta* fields[], uint64_t value) {
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

std::string print_text(const field_meta* meta, const uint8_t* data, int len, uint32_t enc){
    using namespace std;
    stringstream ss;
    ss << hex << setfill('0');

    auto l = len > 16 ? 16 : len;

    for(auto i = 0; i<l; i++){
        ss << uint32_t(data + i) << " ";
        if (i % 8 == 7) {
            ss << endl;
        }
    }
    if (l>16){
        ss << "...";
    }
    return ss.str();
}

std::string vformat(const char* format, va_list args) {
    using namespace std;

    va_list va2;
    va_copy(va2, args);
    auto len = vsnprintf(nullptr, 0, format, va2);
    va_end(va2);

    vector< char > zc(len + 1);
    vsnprintf(zc.data(), zc.size(), format, args);
    return string(zc.data(), zc.size());
}
std::string formats(const char* format, ...) {
    va_list args;
    va_start(args, format);
    auto ret = vformat(format, args);
    va_end(args);
    return ret;
}
