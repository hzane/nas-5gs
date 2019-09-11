#include <bitset>
#include <cinttypes>
#include <cstdarg>
#include <iomanip>
#include <sstream>
#include <vector>
#include "config.hh"
#include "field_meta.hh"
#include "range_string.hh"

using namespace std;

string format_int_hex(uint64_t v, uint32_t ftype) {
    auto t   = ftype & 0x07u;
    auto fmt = "%#0x";

    if (t == ft::ft_int8 || t == ft::ft_uint8) fmt = "%#04x";
    if (t == ft::ft_int16 || t == ft::ft_uint16) fmt = "%#06x";
    if (t == ft::ft_int24 || t == ft::ft_uint24) fmt = "%#08x";
    if (t == ft::ft_int32 || t == ft::ft_uint32) fmt = "%#010x";
    if (t == ft::ft_int64 || t == ft::ft_uint64) fmt = "%#018llx";
    return formats(fmt, v);
}

inline int16_t int8to16(uint64_t v) {
    const auto v8   = uint8_t(v);
    const auto sign = v8 & 0x80u;
    if (sign) {
        const auto x = int16_t(~v8 & 0x7fu + 1);
        return -x;
    }
    return int16_t(v8);
}

inline int32_t int24to32(uint64_t v) {
    const auto v24  = uint32_t(v);
    const auto sign = v24 & 0xff'800000u;
    if (sign) {
        auto x = ~v24 & 0x00'7fffffu + 1;
        return int32_t(x);
    }
    return int32_t(v24);
}
inline int64_t int48to64(uint64_t v) {
    const auto sign = v & 0xffff8000'00000000u;
    if (sign) {
        auto x = ~v & 0x00007fff'ffffffffu + 1;
        return int64_t(x);
    }
    return int64_t(v);
}
std::string format_int_dec(uint64_t v, uint32_t ftype) {
    const auto lc = setlocale(LC_NUMERIC, "");

    const auto t = ftype & 0xffu;
    string     ret;

    switch (t) {
    case ft::ft_int8:
        ret = formats("%hhd (0x%02hhx)", int8to16(v), uint8_t(v));
        break;
    case ft::ft_int16:
        ret = formats("%hd (0x%04hx)", int16_t(v), uint16_t(v));
        break;
    case ft::ft_int24:
        ret = formats("%d (0x%06x)", int24to32(v), uint32_t(v));
        break;
    case ft::ft_int32:
        ret = formats("%d (0x%08x)", int32_t(v), uint32_t(v));
        break;
    case ft::ft_int48:
        ret = formats("%lld (0x%012x)", int48to64(v), v);
        break;
    case ft::ft_int64:
        ret = formats("%lld (0x%016llx)", int64_t(v), uint64_t(v));
        break;
    case ft::ft_uint8:
        ret = formats("%hhu (0x%02hhx)", uint16_t(v), uint16_t(v));
        break;
    case ft::ft_uint16:
        ret = formats("%hd (0x%04hx)", uint16_t(v), uint16_t(v));
        break;
    case ft::ft_uint24:
        ret = formats("%d (0x%06x)", uint32_t(v), uint32_t(v));
        break;
    case ft::ft_uint32:
        ret = formats("%d (0x%08x)", uint32_t(v), uint32_t(v));
        break;
    case ft::ft_uint48:
        ret = formats("%lld (0x%012x)", v, v);
        break;
    case ft::ft_uint64:
        ret = formats("%lld (0x%016llx)", v, v);
        break;
    default:
        ret = formats("%d (0x%x)", v, v);
        break;
    }
    if (lc) (void) setlocale(LC_NUMERIC, lc);

    return ret;
}

const char* find_val_string(const val_string* vstr, uint32_t id, const char* missing) {
    for (auto v = vstr; v->text; v++) {
        if (v->id == id) return v->text;
    }
    return missing;
}
const char* find_r_string(const range_string* rstr, uint32_t id, const char* missing) {
    for (auto v = rstr; v->text; v++) {
        if (v->val_min <= id && v->val_max >= id) {
            return v->text;
        }
    }
    return missing;
}

std::vector< std::string > find_bits_string(const val_string* strings, uint32_t bits) {
    std::vector< std::string > ret;
    for (auto vstr = strings; vstr->id; vstr++) {
        if ((vstr->id & bits) == vstr->id) {
            ret.emplace_back(vstr->text);
        }
    }
    return ret;
}

string format_int_bit_mask(uint32_t ftype, uint64_t v, uint64_t mask, const char* ) {
    size_t cnt = 0;
    if (mask) {
        v = (v & mask) >> ws_ctz(mask);
        cnt = ws_ctz(~(mask >> ws_ctz(mask)));
    }
    stringstream ss;
    switch (ftype) {
    case ft::ft_int64:
    case ft::ft_uint64:
        ss << bitset< 8 >((v & 0xff00'0000'0000'0000u) >> 56) ;
    case ft::ft_int48:
    case ft::ft_uint48:
        ss << bitset< 8 >((v & 0xff00'0000'0000u) >> 40) ;
    case ft::ft_int32:
    case ft::ft_uint32:
        ss << bitset< 8 >((v & 0xff00'0000u) >> 24) ;
    case ft::ft_int24:
    case ft::ft_uint24:
        ss << bitset< 8 >((v & 0xff'0000u) >> 16) ;
    case ft::ft_int16:
    case ft::ft_uint16:
        ss << bitset< 8 >((v & 0xff00u) >> 8u) ;
    case ft::ft_int8:
    case ft::ft_uint8:
        ss << bitset< 8 >(v & 0xffu) ;
    default:
        break;
    }
    auto ret = ss.str();
    if (cnt) ret = ret.substr(0, cnt);
    return ret;
}

string format_bit(const uint8_t* data, int len, const char* sep) {
    stringstream ss;
    for (auto i = 0; i < len; i++) {
        bitset< 8 > v(data[i]);
        ss << v << sep;
    }

    return ss.str();
}

string      format_bits(const uint8_t* data, int bits, const char* sep) {
    const auto clen = bits / 8;
    const auto blen = bits % 8;
    auto ret    = format_bit(data, clen, sep);
    if (!blen) return ret;

    if (sep != nullptr) ret = ret + sep;

    const auto last = data[clen];
    for (auto i = 7; i > 8 - blen; i--) {
        ret.push_back((last & (1u << i)) ? '1' : '0');
    }
    return ret;
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

using namespace std;
string join(const vector< string >& strs, const char* sep) {
    stringstream ss;

    auto i = strs.begin();
    auto e = strs.end();
    if (i != e) ss << *i++;
    while (i != e) {
        ss << sep << *i++;
    }
    return ss.str();
}

std::string format_int(uint64_t v, uint32_t ftype, uint32_t display) {
    if (display == fd::base_dec) return format_int_dec(v, ftype);
    if (display == fd::base_hex) return format_int_hex(v, ftype);
    return formats("%d", v);
}

// without prefix and seperator
string format_bcd(const uint8_t* data, int len) {
    stringstream ss;
    ss << hex << setfill('0');
    for (auto i = 0; i < len; i++) {
        ss << setw(2) << uint32_t(data[i]);
    }
    return ss.str();
}
// FFFFFFFF FFFFFFFF   FFFFFFFF FFFFFFFF  ....
string format_hex(const uint8_t* data, int len, const char* sep, const char* lf) {
    if (sep == nullptr) sep = "";
    if (lf == nullptr) lf = "";

    stringstream ss;
    ss << hex << setfill('0');

    for (auto i = 0; i < len; i++) {
        ss << setw(2) << uint32_t(data[i]) << sep;

        if (i % 8 == 7) ss << sep;
        if (i % 16 == 15 && i != len - 1) ss << lf;
    }

    return ss.str();
}

static inline int ws_ctz32(uint32_t x) {
    /* From http://graphics.stanford.edu/~seander/bithacks.html#ZerosOnRightMultLookup */
    static const uint8_t table[32] = {
        0,  1,  28, 2,  29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4,  8,
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6,  11, 5,  10, 9,
    };

    return table[((uint32_t)((x & (uint32_t)(0u - x)) * 0x077CB531U)) >> 27u];
}

int ws_ctz(uint64_t x) {
    auto hi = uint32_t(x >> 32u);
    auto lo = (uint32_t) x;

    if (lo == 0)
        return 32 + ws_ctz32(hi);
    else
        return ws_ctz32(lo);
}

