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
        const auto x = int16_t(~(v8 & 0x7fu) + 1u);
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

string vstring(const v_string* vstr, uint32_t id, const char* missing) {
    for (auto v = vstr; v->text; v++) {
        if (v->id == id) return formats("%s (%d)", v->text, id);
    }
    return formats("%s (%d)", missing, id);
}
string rstring(const range_string* rstr, uint32_t id, const char* missing) {
    for (auto v = rstr; v->text; v++) {
        if (v->val_min <= id && v->val_max >= id) {
            return formats("%s (%d)", v->text, id);
        }
    }
    return formats("%s (%d)", missing, id);
}

string bits_string(const v_string* strings, uint32_t bits) {
    std::vector< std::string > ret;
    for (auto vstr = strings; vstr->id; vstr++) {
        if ((vstr->id & bits) == vstr->id) {
            ret.emplace_back(vstr->text);
        }
    }
    return join(ret, " | ");
}


string format_bit(const uint8_t* data, int len, const char* sep) {
    stringstream ss;
    for (int i = 0; i < len; i++) {
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
    for (int i = 7; i > 8 - blen; i--) {
        ret.push_back((last & (1u << uint8_t(i))) ? '1' : '0');
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

string join(const vector< string >& strings, const char* sep) {
    if (sep==nullptr) sep="";

    stringstream ss;

    auto i = strings.begin();
    auto e = strings.end();
    if (i != e) ss << *i++;
    while (i != e) {
        ss << sep << *i++;
    }
    return ss.str();
}

// without prefix and separator
string format_bcd(const uint8_t* data, int len) {
    stringstream ss;

    for (int i = 0; i < len; i++) {
        auto l = data[i]&0x0fu, h = (data[i]&0xf0u)>>4u;
        if (l<10) ss<<char(l+'0');
        if (h<10) ss<<char(h+'0');
    }
    return ss.str();
}

string format_hex(const uint8_t* data, int len, std::string const&sep, std::string const&lf) {
    stringstream ss;
    ss << hex << setfill('0');

    for (int i = 0; i < len; i++) {
        ss << setw(2) << uint32_t(data[i]) << sep;

        if (i % 8 == 7) ss << sep;
        if (i % 16 == 15 && i != len - 1) ss << lf;
    }

    return ss.str();
}

inline int ws_ctz32(uint32_t x) {
    /* From http://graphics.stanford.edu/~seander/bithacks.html#ZerosOnRightMultLookup */
    static const uint8_t table[32] = {
        0,  1,  28, 2,  29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4,  8,
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6,  11, 5,  10, 9,
    };

    return table[((uint32_t)((x & (uint32_t)(0u - x)) * 0x077CB531U)) >> 27u];
}

uint8_t ws_ctz8(uint8_t x) {
    /* From http://graphics.stanford.edu/~seander/bithacks.html#ZerosOnRightMultLookup */
    static const uint8_t table[32] = {
        0,  1,  28, 2,  29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4,  8,
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6,  11, 5,  10, 9,
    };

    return table[((uint32_t)((x & (uint32_t)(0u - x)) * 0x077CB531U)) >> 27u];
}
uint8_t umask(uint8_t v, uint8_t mask){
    return mask ? (unsigned(v&mask)>>ws_ctz8(mask)) : v;
}

unsigned int ws_ctz(uint64_t x) {
    auto hi = uint32_t(x >> 32u);
    auto lo = (uint32_t) x;

    if (lo == 0)
        return 32 + ws_ctz32(hi);
    else
        return ws_ctz32(lo);
}

