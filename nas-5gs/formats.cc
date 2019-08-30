#include <bitset>
#include <cstdarg>
#include <sstream>
#include <iomanip>
#include <vector>
#include "config.hh"
#include "field_meta.hh"
#include "range_string.hh"

using namespace std;

string format_int_hex(uint64_t v, uint32_t ftype) {
    auto t   = ftype & 0x07u;
    auto fmt = "%#0x";
    if (t == ft::ft_int8 || t == ft::ft_uint8) fmt = "%#02x";
    if (t == ft::ft_int16 || t == ft::ft_uint16) fmt = "%#04x";
    if (t == ft::ft_int24 || t == ft::ft_uint24) fmt = "%#06x";
    if (t == ft::ft_int32 || t == ft::ft_uint32) fmt = "%#08x";
    if (t == ft::ft_int64 || t == ft::ft_uint64) fmt = "%#016llx";
    return formats(fmt, v);
}
std::string format_int_dec(uint64_t v, uint32_t ftype) {
    auto t   = ftype & 0x07u;
    auto fmt = "%ud";
    if (t == ft::ft_int16 || t == ft::ft_int8 || t == ft::ft_int24 || t == ft::ft_int32)
        fmt = "%d";
    if (t == ft::ft_int64) fmt = "%lld";
    if (t == ft::ft_uint64) fmt = "%ulld";
    auto ret = formats(fmt, v);

    for (int pos = (int) ret.size() - 3; pos > 0; pos -= 3) {
        ret.insert((size_t) pos, ",");
    }
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
            ret.push_back(std::string(vstr->text));
        }
    }
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
    if ((display & 0x07u) == fd::base_dec) return format_int_dec(v, ftype);
    if ((display & 0x07u) == fd::base_hex) return format_int_hex(v, ftype);
    return formats("%d", v);
}

// without prefix and seperator
string format_bcd(const uint8_t*data, int len){
    stringstream ss;
    ss<<hex<<setfill('0');
    for(auto i = 0; i < len; i++){
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

        if (i % 8 == 7)             ss << sep;
        if (i % 16 == 15)             ss << lf;
    }

    return ss.str();
}

static inline int ws_ctz32(uint32_t x) {
    /* From http://graphics.stanford.edu/~seander/bithacks.html#ZerosOnRightMultLookup */
    static const uint8_t table[32] = {0,  1,  28, 2,  29, 14, 24, 3,  30, 22, 20,
                                      15, 25, 17, 4,  8,  31, 27, 13, 23, 21, 19,
                                      16, 7,  26, 12, 18, 6,  11, 5,  10, 9,};

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

