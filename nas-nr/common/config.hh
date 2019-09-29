#pragma once
// #include "nas-nr-compiler-detection.hh"
#include <cstdint>
#include <string>
#include <vector>
#include <optional>
#include <variant>
#include <array>
#include "description.hh"
#include "dissector.hh"

template <typename... Args> inline void unused(Args&&...) {}

struct buff_view;

struct packet;
struct node;
struct context;

struct protocol_meta;
struct field_meta;
struct tree_meta;

struct v_string;
struct tf_string;
struct range_string;

using proto_tree = node;
using proto_item = node;
using string     = std::string;
using payload_t  = std::vector< uint8_t >;
using ustring    = std::vector< uint8_t >;

extern void diag(const char* format, ...);

namespace direction {
inline extern const int unknown = 0;
inline extern const int ul      = 1;
inline extern const int dl      = 2;
} // namespace direction

namespace enc {
inline const uint32_t na   = 0;
inline const uint32_t be   = 1; // big endian
inline const uint32_t none = 4; // host order
} // namespace enc



struct use_tree {
    dissector&  d;
    node_t prev;

    use_tree&   operator=(const use_tree&) = delete;

    use_tree()                             = delete;
    use_tree(const use_tree&)              = delete;

    use_tree(dissector& d, node_t p) : d(d), prev(d.tree) { d.tree = p; }
    ~use_tree() { d.tree = prev; }
};

typedef int (*dissect_fnc_t)(dissector, context* ctx);

struct nr_security_context {
    uint8_t  activated         = 0;
    uint8_t  security_type     = 0; // 33.401
    uint8_t  nas_ksi           = 0; // NAS key set identifier for E-UTRAN
    int      vector_index      = 0; // p of vector, -1 means invalid
    uint8_t  cyphering_key[16] = {};
    uint8_t  integrity_key[16] = {};
    uint32_t dl_count_overflow = 0; // downlink count parameters
    uint32_t dl_count_seq_no   = 0;
    uint32_t ul_count_overflow = 0;
    uint32_t ul_count_seq_no   = 0;
    struct {
        uint8_t ciphering_nr   = 0; // ciphering algo for nr
        uint8_t integrity_nr   = 0; // integrity algo for nr
        uint8_t ciphering_umts = 0; // algorithm for ciphering
        uint8_t integrity_umts = 0; // algorithm for integrity
        uint8_t ciphering_gprs = 0; // algorithm used for ciphering
        uint8_t integrity_gprs = 0; // unused
        bool    umts_present   = false;
        bool    gprs_present   = false;
    } capability; // UE network capability
    struct {
        uint8_t ciphering_type = 0;
        uint8_t integrity_type = 0; // for integrity protection
    } selected_algorithm;           // AMF selected algorithm
};

struct context : nr_security_context {
    bool                       security_context_available = false;
    uint32_t                   msg_auth_code        = 0;
    uint8_t                    payload_content_type = 0;
    std::vector< std::string > paths                = {};
    std::string  path() const;
};


inline uint8_t retrieve_payload_content_type(context* ctx) {
    return ctx ? ctx->payload_content_type : 0;
}
// code is host order
inline void store_msg_auth_code(context*ctx, uint32_t code){
    if (ctx) ctx->msg_auth_code = code;
}
inline uint32_t retrieve_msg_auth_code(context*ctx){
    return ctx ? ctx->msg_auth_code : 0;
}

inline string paths(context* ctx) {
    if (!ctx) return string();
    return ctx->path();
}

inline uint8_t  n2uint8(const uint8_t* d) { return *d; };
inline uint16_t n2uint16(const uint8_t* data) {
    const uint16_t a = data[0];
    uint16_t b = data[1];
    return a << 8 | b;
};
inline uint32_t n2uint24(const uint8_t* data) {
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
inline uint64_t n2uint48(const uint8_t* data) {
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

inline uint64_t n2_uint(const uint8_t* data, int len) {
    if (!len || !data) return 0;

    switch (len) {
    case 1:
        return n2uint8(data);
    case 2:
        return n2uint16(data);
    case 3:
        return n2uint24(data);
    case 4:
        return n2uint32(data);
    case 6:
        return n2uint48(data);
    case 8:
        return n2uint64(data);
    default:
        return 0;
    }
}

string formats(const char* format, ...);
string vformat(const char* format, va_list);

unsigned int ws_ctz(uint64_t mask);

uint32_t get_ext_ambr_unit(uint32_t unit, const char** unit_str);

string ambr_string(uint32_t val, uint32_t unit);


string ipv6_string(const uint8_t*d, int length);

int ext_length(const uint8_t* d);

struct authentication_vector {
    uint8_t kasme[32];    // ASME key
    uint8_t rand[16];     // random challenge parameter
    uint8_t autn[16];     // Authentication token parameters
    uint8_t xresult_size; //
    uint8_t xresult[16];  // expected authentication response parameter
};

int nas_nr_decrypt(const uint8_t*       from,
                   uint8_t*             to,
                   int                  length,
                   uint8_t              type,
                   uint32_t             code,
                   uint8_t              seq,
                   nr_security_context* ctx);

uint32_t nas_calc_auth_code(const uint8_t*       data,
                            int                  length,
                            int                  direction,
                            nr_security_context* ctx);
