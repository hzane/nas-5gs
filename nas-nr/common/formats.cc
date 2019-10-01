#include <bitset>
#include <cinttypes>
#include <cstdarg>
#include <iomanip>
#include <sstream>
#include <vector>

#include "config.hh"
#include "range_string.hh"
#include "formats.hh"

using namespace std;

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

string bstring(uint8_t v, const char* f, const char*t ){
    if (!f) f= "FALSE";
    if (!t) t = "TRUE";
    return formats("%s (%d)", v ? t : f, v);
}

string bitstring(const uint8_t* data, int bits, const char* sep) {
    if (!sep) sep="";

    stringstream ss;
    const auto clen = bits / 8;
    const auto blen = bits % 8;

    for (int i = 0; i < clen; i++) {
        bitset< 8 > v(data[i]);
        ss << v << sep;
    }

    if (!blen) return ss.str();

    ss<<sep;

    const auto last = data[clen];
    for (int i = 7; i > 8 - blen; i--) {
        ss<< ((last & (1u << uint8_t(i))) ? '1' : '0');
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

string join(const vector< string >& strings, const char* sep) {
    if (sep == nullptr) sep = "";

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
string bcd_string(const uint8_t* data, int len) {
    stringstream ss;

    for (int i = 0; i < len; i++) {
        auto l = data[i] & 0x0fu, h = (data[i] & 0xf0u) >> 4u;
        if (l < 10) ss << char(l + '0');
        if (h < 10) ss << char(h + '0');
    }
    return ss.str();
}

static const char digits_bcd[] =
    {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '?', '?', '?', '?', '?', '?'};

string imei_string(const uint8_t*d, int length){
    if (length <= 0 || !d) return string();
    string ret={};

    ret.push_back(digits_bcd[(d[0] & 0xf0u) >> 4u]);
    for (auto i = 1; i < length; ++i) {
        ret.push_back(digits_bcd[d[i] & 0x0fu]);
        if (i!=length-1||(d[i]&0xf0u)!=0xf0u){
            ret.push_back(digits_bcd[(d[i] & 0xf0u) >> 4u]);
        }
    }
    return ret;
}
string hstring(const uint8_t*     data,
                  int                len,
                  const char* sep,
                  const char* lf) {
    if (!sep) sep="";
    if (!lf) lf="";

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
uint16_t u16mask(uint16_t v, uint16_t mask){
    return mask ? unsigned(v&mask)>>ws_ctz32(mask) : v;
}
uint24_t u24mask(uint24_t v, uint24_t mask){
    return mask ?  unsigned(v&mask)>>ws_ctz32(mask):v;
}
uint8_t umask(uint8_t v, uint8_t mask) {
    return mask ? (unsigned(v & mask) >> ws_ctz8(mask)) : v;
}

unsigned int ws_ctz(uint64_t x) {
    auto hi = uint32_t(x >> 32u);
    auto lo = (uint32_t) x;

    if (lo == 0)
        return 32 + ws_ctz32(hi);
    else
        return ws_ctz32(lo);
}
string istring(uint8_t v){
    return formats("%u (0x%02x)", int(v), v);
}
string istring(uint16_t v){
    return formats("%u (0x%04x)", v, v);
}
string istring(uint32_t v){
    return formats("%u (0x%08x)", v, v);
}
string i24string(uint32_t v){
    return formats("%u (0x%02x%02x%02x)", v,
        (v>>16u)&0xffu,
        (v>>8)&0xffu,
        v&0xffu);
}

string istring(int8_t v){
    return formats("%d (0x%02x)", int(v), v);
}
string istring(int16_t v){
    return formats("%d (0x%04x)", v, v);
}
string istring(int32_t v){
    return formats("%d (0x%08x)", v, v);
}
string i24string(int32_t v){
    return formats("%d (0x%02x%02x%02x)", v,
        unsigned(v>>16)&0xffu,
        unsigned(v>>8)&0xffu, unsigned(v)&0xffu);
}


string asctime_string(const tm* t) {
#if defined(_WIN32) || defined(_WIN64)
    char buf[128] = {0};
    auto e = asctime_s(buf, std::size(buf), t);
    return !e ? string(buf) : string();
#else
    auto x = asctime(t);
    return x ? string(x) : string();
#endif
}

string utc_string(const uint8_t*d, int length){
    if (length < 7) return string();

    tm t = {0, 0, 0, 0, 0, 0, 0, 0, -1};

    int o = int(d[0]);
    t.tm_year = ((o & 0xf0) >> 4) + 100 + (o & 0x0f) * 10;

    o = d[1];
    t.tm_mon = (o & 0x0f) * 10 + ((o & 0xf0) >> 4) - 1;

    o = d[2];
    t.tm_mday = (o & 0x0f) * 10 + ((o & 0xf0) >> 4);

    o = d[3];
    t.tm_hour = (o & 0x0f) * 10 + ((o & 0xf0) >> 4);

    o = d[4];
    t.tm_min = (o & 0x0f) * 10 + ((o & 0xf0) >> 4);

    o= d[5];
    t.tm_sec = (o & 0x0f) * 10 + ((o & 0xf0) >> 4);

    auto ts = asctime_string(&t);
    if (ts.empty()) return ts;

    const auto sign     = (d[6] & 0x08u) ? '-' : '+';
    auto       quarters = (d[6] >> 4u) + (d[6] & 0x07u) * 10;
    const auto h        = quarters / 4;
    quarters            = quarters % 4 * 15;
    return formats("%s GMT %c %d hours %d minutes", ts.c_str(), sign, h, quarters);
}

string gmt_string(const uint8_t*d){
    const auto sign     = (d[0] & 0x08u) ? '-' : '+';
    auto       quarters = (d[0] >> 4u) + (d[0] & 0x07u) * 10;
    const auto h        = quarters / 4;
    quarters            = quarters % 4 * 15;
    return formats("GMT %c %d hours %d minutes", sign, h, quarters);
}

static char gbcd[] =
    {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '?', 'B', 'C', '*', '#', '?'};

inline char d2asc(uint8_t v) { return v < 9 ? gbcd[v] : char(v + 55); }

// Decode the MCC/MNC from 3 octets in 'octs'
string mcc_code(const uint8_t* d, int length) {
    if (length < 3) return string();

    char mcc[4]={0};

    mcc[0] = d2asc(d[0] & 0x0fu);
    mcc[1] = d2asc((d[0] & 0xf0u) >> 4u);
    mcc[2] = d2asc(d[1] & 0x0fu);
    mcc[3] = '\0';

    return string(static_cast< const char* >(mcc));
}

/* Little Endian*/
string mnc_code(const uint8_t* d, int length) {
    if (length < 3) return string();

    char mnc[4]={0};
    mnc[2]     = d2asc((d[1] & 0xf0u) >> 4u);
    mnc[0]     = d2asc(d[2] & 0x0fu);
    mnc[1]     = d2asc((d[2] & 0xf0u) >> 4u);

    if (mnc[1]=='F') // only 1 digit MNC
        mnc[1]='\0';
    else if (mnc[2]=='F') // only 2 digit MNC
        mnc[2] = '\0';
    else mnc[3] = '\0';

    return string(static_cast< const char* >(mnc));
}

string   ipv6_link_local_string(const uint8_t* data, const int len) {
    if (!data || !len) return string();

    std::stringstream ss;
    ss << "fe80:";
    for (int i = 0; i < len; ++i) {
        ss << ":" << std::hex << data[i];
    }
    return ss.str();
}

string ipv6_string(const uint8_t* d, int len) {
    if (!d || !len) return string();
    std::stringstream ss;
    ss << d[0];
    for (int i = 1; i<len; i++) {
        ss << ":" << std::hex << d[i];
    }
    return ss.str();
}

string gprs_timer_string(uint8_t d) {
    const auto  val   = static_cast< uint32_t >(d) & 0x1fu;
    const auto  uf = static_cast< int >(d >> 5u);

    const char*units[]={"sec", "min", "min", "min","min","min","min", "deactivated"};
    const int muls[]={2, 1, 6, 1, 1,1,0};
    auto        unit  = units[uf];
    uint32_t    mul   = muls[uf];

    return formats("%u %s (%u)", val * mul, unit, val);
}


/* * 3GPP TS 24.008 g10 10.5.7.4a */
string gprs_timer_3_string(uint8_t oct) {
    auto        uf   = oct >> 5u;
    auto        val  = uint32_t(oct) & 0x1fu;

    const char*units[]={"min", "hr","hr","sec","sec","min","hr","deactivated"};
    uint32_t muls []={10, 1, 10, 2, 30, 1, 320, 0};

    const char* unit = units[uf];
    uint32_t    mul  = muls[uf];

    return formats("%u %s (%u)", val * mul, unit, val);
}

/* * 3GPP TS 24.008 g10 10.5.7.4 */
string gprs_timer_2_string(uint8_t oct) {
    auto        val  = uint8_t(oct) & 0x1fu;
    const char *units[]={"sec", "min", "min", "min","min","min","min","deactivated"};
    const uint32_t muls[]={2, 1, 6, 1,1,1,1,0};

    const char* unit = units[oct>>5u];
    uint32_t    mul  = muls[oct>>5u];

    return formats("%u %s (%u)", val * mul, unit, val);
}

uint32_t get_ext_ambr_unit(uint32_t unit, const char** unit_str) {
    uint32_t mul = 1;

    if (unit == 0) {
        *unit_str = "Unit value 0, Illegal";
        return mul;
    }
    unit = unit - 1;

    if (unit <= 0x05) {
        mul       = 1u << (2 * unit);
        *unit_str = "Kbps";
    } else if (unit <= 0x0a) {
        mul       = 1u << (2 * (unit - 0x05));
        *unit_str = "Mbps";
    } else if (unit <= 0x0e) {
        mul       = 1u << (2 * (unit - 0x07));
        *unit_str = "Gbps";
    } else if (unit <= 0x14) {
        mul       = 1u << (2 * (unit - 0x0c));
        *unit_str = "Tbps";
    } else if (unit <= 0x19) {
        mul       = 1u << (2 * (unit - 0x11));
        *unit_str = "Pbps";
    } else {
        mul       = 256;
        *unit_str = "Pbps";
    }
    return mul;
}

string ambr_string(const uint8_t* d, int length) {
    if (!d || length <= 3) return string();
    const auto unit = uint32_t(d[0]);
    const auto val  = n2uint16(d + 1);
    return ambr_string(val, unit);
}

string ambr_string(uint32_t val, uint32_t unit) {
    auto       unit_str = "";
    const auto multi    = get_ext_ambr_unit(unit, &unit_str);
    return formats("%u %s (%u)", val * multi, unit_str, val);
}

/*
 * The encoding of the APN shall follow the Name Syntax defined in RFC 2181 [18], RFC 1035
[19] and RFC 1123 [20]. The APN consists of one or more labels. Each label is coded as a
one octet length field followed by that number of octets coded as 8 bit ASCII characters.
Following RFC 1035 [19] the labels shall consist only of the alphabetic characters (A-Z
and a-z), digits (0-9) and the hyphen (-). Following RFC 1123 [20], the label shall begin
and end with either an alphabetic character or a digit. The case of alphabetic characters
is not significant. The APN is not terminated by a length byte of zero. */
// ascii strings
string apn_string(const uint8_t* d, int len) {
    if (!d || !len) return string();

    string str(d, d + len);

    for (size_t i = 0; i < str.size();) {
        const auto next = str[i];
        str[i]          = '.';
        i               = i + next + 1;
    }
    return str;
}
