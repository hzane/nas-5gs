#include <cstdarg>
#include <iomanip>
#include <sstream>
#include <vector>
#include "field_meta.hh"
#include "tvbuff.hh"

static inline int __ws_ctz32(uint32_t x) {
    /* From http://graphics.stanford.edu/~seander/bithacks.html#ZerosOnRightMultLookup */
    static const uint8_t table[32] = {0,  1,  28, 2,  29, 14, 24, 3,  30, 22, 20,
                                      15, 25, 17, 4,  8,  31, 27, 13, 23, 21, 19,
                                      16, 7,  26, 12, 18, 6,  11, 5,  10, 9};

    return table[((uint32_t)((x & (uint32_t)(0 - x)) * 0x077CB531U)) >> 27];
}

static inline int ws_ctz(uint64_t x) {
    uint32_t hi = x >> 32;
    uint32_t lo = (uint32_t) x;

    if (lo == 0)
        return 32 + __ws_ctz32(hi);
    else
        return __ws_ctz32(lo);
}

std::string field_meta::print_hex(uint64_t v) const {
    auto t   = field_type & 0x07;
    auto fmt = "%#0x";
    if (t == ft::ft_int8 || t == ft::ft_uint8) fmt = "%#02x";
    if (t == ft::ft_int16 || t == ft::ft_uint16) fmt = "%#04x";
    if (t == ft::ft_int24 || t == ft::ft_uint24) fmt = "%#06x";
    if (t == ft::ft_int32 || t == ft::ft_uint32) fmt = "%#08x";
    if (t == ft::ft_int64 || t == ft::ft_uint64) fmt = "%#016llx";
    return formats(fmt, v);
}
std::string field_meta::print_dec(uint64_t v) const {
    auto t   = field_type & 0x07;
    auto fmt = "%ud";
    if (t == ft::ft_int16 || t == ft::ft_int8 || t == ft::ft_int24 || t == ft::ft_int32)
        fmt = "%d";
    if (t == ft::ft_int64) fmt = "%lld";
    if (t == ft::ft_uint64) fmt = "%ulld";
    return formats(fmt, v);
}

const char* find_val_string(const val_string* vstr, uint32_t id) {
    for (auto v = vstr; v->text; v++) {
        if (v->id == id) return v->text;
    }
    return nullptr;
}
const char* find_r_string(const range_string* rstr, uint32_t id) {
    for (auto v = rstr; v->text; v++) {
        if (v->val_min <= id && v->val_max >= id) {
            return v->text;
        }
    }
    return nullptr;
}

std::string field_meta::print(uint64_t v) const {
    if (bitmask) v = v >> ws_ctz(bitmask);

    if (val_strings) {
        auto s = find_val_string(val_strings, uint32_t(v));
        if (s) {
            return formats("%s (%x)", s, v);
        } else {
            return formats("unknown (%x)", v);
        }
    }
    if (tf_strings && v) return tf_strings->true_string;
    if (tf_strings) return tf_strings->false_string;
    if (range_strings) {
        auto s = find_r_string(range_strings, uint32_t(v));
        if (s) {
            return formats("%s (%x)", s, v);            
        } else
            return formats("unknown(%x)", v);
    }

    if (field_type == ft::ft_boolean)
        return formats((v & 0xff) ? "true (%d)" : "false (%d)", v);
    if (field_type == ft::ft_char) return formats("%c (%02x)", (char) v, v);
    
    if ((display & 0x07) == fd::base_dec) return print_dec(v);
    if ((display & 0x07) == fd::base_hex) return print_hex(v);
    if (field_type == ft::none) return std::string();

    return formats("%d", v);
}

// FFFFFFFF FFFFFFFF   FFFFFFFF FFFFFFFF  ....
std::string field_meta::print_bytes(const uint8_t* data, int len, uint32_t) const {
    using namespace std;
    stringstream ss;
    ss << hex << setfill('0');

    auto l = len > 16 ? 16 : len;

    for (auto i = 0; i < l; i++) {
        ss << setw(2) << uint32_t(data + i) << " ";
        if (i % 4 == 3) {
            ss << " ";
        }
        if (i % 8 == 7) {
            ss << " ";
        }
    }
    if (l > 16) {
        ss << "...";
    }
    return ss.str();
}

std::string field_meta::print_data(const uint8_t* data, int len, uint32_t enc) const {
    if (len <= 0 || field_type == ft::none) return std::string();
    if (field_type == ft::ft_bytes || field_type == ft::ft_hex_string) {
        return print_bytes(data, len, enc);
    }
    if (field_type == ft::ft_char) {
        return formats("%c", uint32_t(*data));
    }
    if (field_type == ft::ft_string || field_type == ft::ft_stringz){
        return std::string((const char*) data, len);
    }
    if (field_type == ft::ft_boolean){
        return (*data) ? "true" : "false";
    }
    // ft_float, ft_double

    uint64_t v   = 0;
    auto tvb = tvbuff(data, len);
    if (len==1) {
        v = tvb.get_uint8(0);        
    }else if (len==2){
        v = tvb.get_ntohs(0);
    }else if(len==3){
        v = tvb.get_ntoh24(0);
    } else if (len == 4) {
        v = tvb.get_ntoh32(0);
    } else if (len == 8) {
        v = tvb.get_ntoh64(0);
    }
    return print(v);
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
