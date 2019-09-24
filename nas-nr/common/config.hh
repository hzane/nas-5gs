#pragma once
// #include "nas-nr-compiler-detection.hh"
#include <cstdint>
#include <string>
#include <vector>
#include <optional>
#include <variant>
#include <array>

#if _MSC_VER
#define unused
#else
#define unused  __attribute__((unused))
#endif

struct bufview;

struct packet_info;
struct proto_node;
struct context;

struct protocol_meta;
struct field_meta;
struct tree_meta;

struct v_string;
struct tf_string;
struct r_string;

using proto_tree = proto_node;
using proto_item = proto_node;
using string     = std::string;
using payload_t  = std::vector< uint8_t >;
using ustring    = std::vector< uint8_t >;
template<typename t> using optional = std::optional<t>;

extern void diag(const char* format, ...);

namespace direction {
inline extern const int unknown unused = 0;
inline extern const int ul      = 1;
inline extern const int dl      = 2;
inline extern const int both    = 3;
} // namespace direction

namespace enc {
inline const uint32_t na   = 0;
inline const uint32_t be   = 1; // big endian
inline const uint32_t none = 4; // host order
} // namespace enc

struct dissector {
    packet_info* pinfo  = nullptr;
    proto_node*  tree   = nullptr;
    bufview*      tvb    = nullptr;
    int          offset = 0;
    int          length = 0;
    void*        data   = nullptr;

    dissector& step(int consumed) {
        offset += consumed;
        length -= consumed;
        return *this;
    }
    proto_node* add_item(int len, const field_meta* fm, uint32_t e = enc::be) const;
    proto_node* set_item(int len, const field_meta* fm, uint32_t e= enc::be) const unused;
    proto_node* add_tree(int len, const string&name) const;
    proto_node* add_expert(int len, const string&name)const unused;
    void        add_bits(const field_meta* metas[]) const;
    void        extraneous_data_check(int max_len, context* ctx = nullptr) const;
    auto        safe_ptr() const -> const uint8_t*;
    auto        safe_length(int len) const -> int;
    auto        slice(int len) const -> dissector;
    auto        use_elem(void* elem) const -> dissector;
    auto        uint8() const -> uint8_t;
    auto        ntohs() const -> uint16_t;
    auto        uint32() const -> uint32_t;
};

struct use_tree {
    dissector&  d;
    proto_node* prev unused;

    use_tree&   operator=(const use_tree&) = delete;

    use_tree()                             = delete;
    use_tree(const use_tree&)              = delete;

    use_tree(dissector& d, proto_node* p) : d(d), prev(d.tree) { d.tree = p; }
    ~use_tree() { d.tree = prev; }
};

typedef int (*dissect_fnc_t)(dissector, context* ctx);

struct nr_security_context {
    uint8_t  activated         unused = 0;
    uint8_t  security_type     unused = 0; // 33.401
    uint8_t  nas_ksi           unused = 0; // NAS key set identifier for E-UTRAN
    int      vector_index      unused = 0; // pointer of vector, -1 means invalid
    uint8_t  cyphering_key[16] unused = {};
    uint8_t  integrity_key[16] unused = {};
    uint32_t dl_count_overflow unused = 0; // downlink count parameters
    uint32_t dl_count_seq_no   unused = 0;
    uint32_t ul_count_overflow unused = 0;
    uint32_t ul_count_seq_no   unused = 0;
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
    } selected_algorithm unused ;           // AMF selected algorithm
};

struct context : nr_security_context {
    bool                       security_context_available unused = false;
    uint32_t                   msg_auth_code        = 0;
    uint8_t                    payload_content_type = 0;
    std::vector< std::string > paths                = {};
    std::string  path() const;
};

struct use_context {
    context*         ctx    = nullptr;
    int              offset = 0;
    int              length = 0;
    int              maxlen unused = 0;
    const dissector& d;

    use_context& operator=(const use_context&) = delete;
    use_context()                              = delete;
    use_context(const use_context&) = delete;

    use_context(context* ctx, const char* path, dissector const& d, const int maxlen = 0)
        : ctx(ctx), offset(d.offset), length(d.length), maxlen(maxlen), d(d) {
        if (!ctx) return;
        if (path == nullptr) path = ".";
        ctx->paths.emplace_back(path);
        diag("%s%s %d-%d\n",
             string(ctx->paths.size() << 1u, ' ').c_str(),
             path,
             offset,
             length);
    }
    ~use_context() {
        d.extraneous_data_check(maxlen, ctx);
        if (ctx) {
            ctx->paths.pop_back();
        }
    }
};

inline void store_payload_content_type(context* ctx, uint8_t pct) {
    if (ctx) ctx->payload_content_type = pct;
}

inline uint8_t retrieve_payload_content_type(context* ctx) {
    return ctx ? ctx->payload_content_type : 0;
}
// code is host order
inline void store_msg_auth_code(context*ctx, uint32_t code){
    if (ctx) ctx->msg_auth_code = code;
}

inline uint32_t retrieve_msg_auth_code (context*ctx) {
    return ctx ? ctx->msg_auth_code : 0;
}

inline string paths(context* ctx) {
    if (!ctx) return string();
    return ctx->path();
}

inline uint8_t  n2uint8(const uint8_t* d) { return *d; }

inline uint16_t n2uint16(const uint8_t* data) {
    const uint16_t a = data[0];
    const uint16_t b = data[1];
    return unsigned(a) << 8u | b ;
}

inline uint32_t n2uint24(const uint8_t* data) {
    uint32_t a = data[0];
    uint32_t b = data[0 + 1];
    uint32_t c = data[0 + 2];
    return a << 16u | b << 8u | c;
}

inline uint32_t n2uint32(const uint8_t* data) {
    uint32_t a = data[0];
    uint32_t b = data[0 + 1];
    uint32_t c = data[0 + 2];
    uint32_t d = data[0 + 3];
    return a << 24u | b << 16u | c << 8u | d;
}

inline uint64_t n2uint48(const uint8_t* data) {
    uint64_t a = data[0];
    uint64_t b = data[0 + 1];
    uint64_t c = data[0 + 2];
    uint64_t d = data[0 + 3];
    uint64_t e = data[0 + 4];
    uint64_t f = data[0 + 5];
    return a << 40u | b << 32u | c << 24u | d << 16u | e << 8u | f;
}

inline uint64_t n2uint64(const uint8_t* data) {
    uint64_t a = data[0];
    uint64_t b = data[0 + 1];
    uint64_t c = data[0 + 2];
    uint64_t d = data[0 + 3];
    uint64_t e = data[0 + 4];
    uint64_t f = data[0 + 5];
    uint64_t g = data[0 + 4];
    uint64_t h = data[0 + 5];
    return a << 56u | b << 48u | c << 40u | d << 32u | e << 24u | f << 16u | g << 8u | h;
}

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

string format_hex(const uint8_t* data,
                  int            len,
                  const char*    sep = " ",
                  const char*    lf  = nullptr);

string format_bit(const uint8_t* data, int len, const char* sep = " ");

string format_bits(const uint8_t* data, int bits, const char* sep = nullptr) unused;

string format_int_bit_mask(uint32_t    ftype,
                           uint64_t    v,
                           uint64_t    mask,
                           const char* sep = nullptr);

string format_int(uint64_t v, uint32_t ftype, uint32_t display);
string format_int_hex(uint64_t v, uint32_t ftype);
string format_int_dec(uint64_t v, uint32_t ftype);

string formats(const char* format, ...);
string vformat(const char* format, va_list);

const char* find_val_string(const v_string* strings,
                            uint32_t          id,
                            const char*       missing = "Unknown");
const char* find_r_string(const r_string* strings,
                          uint32_t            id,
                          const char*         missing = "Unknown");

std::vector< std::string > find_bits_string(const v_string* strings, uint32_t bits);

string join(const std::vector< string >& strings, const char* sep = " ");

string bits7_string(const uint8_t* data, int len);

ustring ts_23_038_7bits_string(const uint8_t* ptr, int bit_offset, int no_of_chars);

unsigned int ws_ctz(uint64_t mask);

uint32_t get_ext_ambr_unit(uint32_t unit, const char** unit_str);

string ambr_string(const uint8_t* d, int length);
string ambr_string(uint32_t val, uint32_t unit);

string bstrn_string(const uint8_t* d, int len);

string gprs_timer3_format(uint8_t oct);
string gprs_timer2_format(uint8_t oct);

string gprs_timer2_string(const uint8_t*d, int len);
string gprs_timer3_string(const uint8_t* d, int len);
string gprs_timer_string(const uint8_t* d, int len);

string ipv6_string(const uint8_t*d, int length);
string ipv6_link_local_string(const uint8_t* d, int length);

//  [3] 10.5.1.13 PLMN list TS24.008
string mcc_string(const uint8_t* d, int length = 3);
string mcc_mnc_string(const uint8_t* d, int length = 3);

// BCD number
string bcd_string(const uint8_t* d, int length);
string imei_string(const uint8_t* d, int length); // 0xf0 terminated if even
string timezone_time_string(const uint8_t* d, int length);
string timezone_string(const uint8_t* d);

int ext_length(const uint8_t* d);

struct authentication_vector {
    uint8_t kasme[32] unused ;    // ASME key
    uint8_t rand[16] unused ;     // random challenge parameter
    uint8_t autn[16] unused ;     // Authentication token parameters
    uint8_t xresult_size unused ; //
    uint8_t xresult[16] unused ;  // expected authentication response parameter
} unused;

int nas_nr_decrypt(const uint8_t*       from,
                   uint8_t*             to,
                   int                  length,
                   uint8_t              type,
                   uint32_t             code,
                   uint8_t              seq,
                   nr_security_context* ctx) unused ;

uint32_t nas_calc_auth_code(const uint8_t*       data,
                            int                  length,
                            int                  direction,
                            nr_security_context* ctx) unused ;
