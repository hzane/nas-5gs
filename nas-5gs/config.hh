#pragma once
#include <cstdint>
#include <string>

typedef unsigned int uint_t;
typedef int int_t;

struct tvbuff;
typedef tvbuff tvbuff_t;
typedef tvbuff buffer_t;

struct packet_info;
struct proto_node;
struct context;

struct protocol_meta;
struct field_meta;
struct tree_meta;
struct expert_meta;

struct val_string;
struct true_false_string;
struct range_string;

typedef proto_node proto_tree;
typedef proto_node proto_item;

using std::string;

namespace enc {
__declspec(selectany) extern const uint32_t na   = 0;
__declspec(selectany) extern const uint32_t be   = 1; // big endian
__declspec(selectany) extern const uint32_t le   = 2; // little endian
__declspec(selectany) extern const uint32_t none = 4; // host order
} // namespace enc

/*
typedef int (
    *dissect_fnc_t)(packet_info*, proto_node*, tvbuff*, int offset, int len, context*);

typedef dissect_fnc_t dissect_msg_fnc_t;
typedef dissect_fnc_t dissect_elem_fnc_t;
*/

struct dissector {
    packet_info* pinfo  = nullptr;
    proto_node*  tree   = nullptr;
    tvbuff*      tvb    = nullptr;
    int          offset = 0;
    int          length = 0;
    void*        data   = nullptr;
};

typedef int (*dissect_fnc_t)(dissector, context* ctx);

inline uint8_t  n2uint7(const uint8_t* d){
    return *d&0x7F;
};
inline uint8_t  n2uint8(const uint8_t* d) { return *d; };
inline uint16_t n2uint16(const uint8_t*data){
    uint16_t a = data[0];
    uint16_t b = data[1];
    return a << 8 | b;
};
inline uint32_t n2uint24(const uint8_t*data){
    uint32_t a = data[0];
    uint32_t b = data[0 + 1];
    uint32_t c = data[0 + 2];
    return a << 16 | b << 8 | c;
};
inline uint32_t n2uint32(const uint8_t* data) {
    uint32_t a = data[0];
    uint32_t b = data[0 + 1];
    uint32_t c = data[0 + 2];
    uint32_t d = data[0 + 3];
    return a << 24 | b << 16 | c << 8 | d;
};
inline uint64_t n2uint48(const uint8_t*data){
    uint64_t a = data[0];
    uint64_t b = data[0 + 1];
    uint64_t c = data[0 + 2];
    uint64_t d = data[0 + 3];
    uint64_t e = data[0 + 4];
    uint64_t f = data[0 + 5];
    return a << 40 | b << 32 | c << 24 | d << 16 | e << 8 | f;
};
inline uint64_t n2uint64(const uint8_t* data) {
    uint64_t a = data[0];
    uint64_t b = data[0 + 1];
    uint64_t c = data[0 + 2];
    uint64_t d = data[0 + 3];
    uint64_t e = data[0 + 4];
    uint64_t f = data[0 + 5];
    uint64_t g = data[0 + 4];
    uint64_t h = data[0 + 5];
    return a << 56 | b << 48 | c << 40 | d << 32 | e << 24 | f << 16 | g << 8 | h;
};

string format_hex(const uint8_t* data, int len, const char* sep = " ");
string format_bit(const uint8_t* data, int len, const char* sep = " ");
string format_int(uint64_t v, uint32_t ftype, uint32_t display);
string format_int_hex(uint64_t v, uint32_t ftype);
string format_int_dec(uint64_t v, uint32_t ftype);
