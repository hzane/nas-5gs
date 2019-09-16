#include "core.hh"
#include <cstdio>
#include <vector>
#include <ctime>
#include <cstdarg>
#include <sstream>

#if _WIN32
#include <windows.h>
// #include <DbgHelp.h>
#else
void OutputDebugStringA(const char*){}
#endif

// declared in config.hh
void diag(const char* format, ...) {
#if NASNR_COMPILER_CXX_VECTOR_DATA
    va_list args;
    va_start(args, format);

    va_list cp;
    va_copy(cp, args);

    std::vector< char > buf(
        1 + static_cast< size_t >(vsnprintf(nullptr, 0, format, args)));
    va_end(args);

    vsnprintf(buf.data(), buf.size(), format, cp);
    va_end(cp);
    OutputDebugStringA(buf.data());
#endif
}

string context::path() const { return join(paths, "/"); }

string bits7_string(const uint8_t* data, int len){
    NASNR_AUTO(ustring) d = ts_23_038_7bits_string(data, 0, (len<<3)/7);
    return string(d.begin(), d.end());
}

string   ipv6_link_local_string(const uint8_t* data, int len) {
    if (!data || !len) return string();

    std::stringstream ss;
    ss << "fe80:";
    for (int i = 0; i < len; i++) {
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

uint32_t get_ext_ambr_unit(uint32_t unit, const char** unit_str) {
    uint32_t mult = 1;

    if (unit == 0) {
        *unit_str = "Unit value 0, Illegal";
        return mult;
    }
    unit = unit - 1;

    if (unit <= 0x05) {
        mult      = 1 << (2 * unit); // pow4(guint32, unit);
        *unit_str = "Kbps";
    } else if (unit <= 0x0a) {
        mult      = 1 << (2 * (unit - 0x05)); // pow4(guint32, unit - 0x05);
        *unit_str = "Mbps";
    } else if (unit <= 0x0e) {
        mult      = 1 << (2 * (unit - 0x07)); // pow4(guint32, unit - 0x07);
        *unit_str = "Gbps";
    } else if (unit <= 0x14) {
        mult      = 1 << (2 * (unit - 0x0c)); // pow4(guint32, unit - 0x0c);
        *unit_str = "Tbps";
    } else if (unit <= 0x19) {
        mult      = 1 << (2 * (unit - 0x11)); // pow4(guint32, unit - 0x11);
        *unit_str = "Pbps";
    } else {
        mult      = 256;
        *unit_str = "Pbps";
    }
    return mult;
}

string ambr_string(const uint8_t*d, int length) {
    if (!d || length <= 0) return string();
    const NASNR_AUTO(uint32_t) unit = uint32_t(d[0]);
    const NASNR_AUTO(uint16_t) val  = n2uint16(d + 1);
    return ambr_string(val, unit);
}

string ambr_string(uint32_t val, uint32_t unit){
    NASNR_AUTO(const char*)       unit_str = "";
    const NASNR_AUTO(uint32_t) multi = get_ext_ambr_unit(unit, &unit_str);
    return formats("%u %s (%u)", val * multi, unit_str, val);
}

// ascii strings
string bstrn_string(const uint8_t*d, int len){
    if (!d || !len) return string();

    string str(d, d + len);

    for (size_t i = 0; i < str.size();) {
        const NASNR_AUTO(char) next = str[i];
        str[i]          = '.';
        i               = i + next + 1;
    }
    return str;
}

string gprs_timer_string(const uint8_t*d, int len) {
    if (!d || len <= 0) return string();

    const NASNR_AUTO(uint32_t)  val   = static_cast< uint32_t >(d[0]) & 0x1fu;
    const NASNR_AUTO(int)  unitf = static_cast< int >(d[0] >> 5u);
    NASNR_AUTO(const char*)        unit  = "min";
    uint32_t    mul   = 1;

    if (unitf == 0) {
        unit = "sec";
        mul  = 2;
    } else if (unitf == 1) {
        unit = "min";
    } else if (unitf == 2) {
        unit = "min";
        mul  = 6;
    } else if (unitf == 7) {
        unit = "deactivated";
    }
    return formats("%u %s (%u)", val * mul, unit, val);
}

string gprs_timer2_string(const uint8_t*d, int len) {
    if (!d || !len) return string();
    return gprs_timer2_format(d[0]);
}

string gprs_timer3_string(const uint8_t*d, int len) {
    if (!d || !len) return string();
    return gprs_timer3_format(d[0]);
}

/* * 3GPP TS 24.008 g10 10.5.7.4a */
string gprs_timer3_format(uint8_t oct) {
    NASNR_AUTO(uint8_t)        uf   = oct >> 5u;
    NASNR_AUTO(uint32_t)       val  = uint32_t(oct) & 0x1fu;
    const char* unit = "hr";
    uint32_t    mul  = 1;

    switch (uf) {
    case 0:
        unit = "min";
        mul  = 10;
        break;
    case 1:
        unit = "hr";
        break;
    case 2:
        unit = "hr";
        mul  = 10;
        break;
    case 3:
        unit = "sec";
        mul  = 2;
        break;
    case 4:
        unit = "sec";
        mul  = 30;
        break;
    case 5:
        unit = "min";
        break;
    case 7:
        break; // todo: what's timer is deactivated?
    default:
        break;
    }
    return formats("%u %s (%u)", val * mul, unit, val);
}

/* * 3GPP TS 24.008 g10 10.5.7.4 */
string gprs_timer2_format(uint8_t oct) {
    NASNR_AUTO(uint8_t)        val  = uint8_t(oct) & 0x1fu;
    const char* unit = "min";
    uint32_t    mul  = 1;
    switch (oct >> 5u) {
    case 0:
        unit = "sec";
        mul  = 2;
        break;
    case 1:
        unit = "min";
        break;
    case 2:
        unit = "min";
        mul  = 6;
        break;
    case 7:
        unit = "timer is deactivated";
    default:
        break;
    }
    return formats("%u %s (%u)", val * mul, unit, val);
}

// assure: iei != 0
const message_meta* find_dissector(uint8_t iei, const message_meta* meta) {
    while (meta->name) { // meta->type may be zero
        if (meta->type == iei) return meta;
        meta++;
    }
    return nullptr;
}


static char digit_tbcd[] =
    {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '?', 'B', 'C', '*', '#', '?'};

inline char d2asc(uint8_t v) { return v < 9 ? digit_tbcd[v] : char(v + 55); }

// Decode the MCC/MNC from 3 octets in 'octs'
string mcc_aux(const uint8_t* d, int length) {
    if (length < 3) return string();

    char mcc[4]={0};

    mcc[0] = d2asc(d[0] & 0x0fu);
    mcc[1] = d2asc((d[0] & 0xf0u) >> 4);
    mcc[2] = d2asc(d[1] & 0x0fu);
    mcc[3] = '\0';

    return string(static_cast< const char* >(mcc));
}
/* Little Endian
 * MNC of length 3:
 *
 *   8   7   6   5   4   3   2   1
 * +---+---+---+---+---+---+---+---+
 * |  MCC digit 2  |  MCC digit 1  |  octet x
 * +---------------+---------------+
 * |  MNC digit 3  |  MCC digit 3  |  octet x+1
 * +---------------+---------------+
 * |  MNC digit 2  |  MNC digit 1  |  octet x+2
 * +---------------+---------------+
 * */
string mnc_aux(const uint8_t* d, int length) {
    if (length < 3) return string();

    char mnc[4]={0};
    mnc[2]     = d2asc((d[1] & 0xf0u) >> 4);
    mnc[0]     = d2asc(d[2] & 0x0fu);
    mnc[1]     = d2asc((d[2] & 0xf0u) >> 4);

    if (mnc[1]=='F') // only 1 digit MNC
        mnc[1]='\0';
    else if (mnc[2]=='F') // only 2 digit MNC
        mnc[2] = '\0';
    else mnc[3] = '\0';

    return string(static_cast< const char* >(mnc));
}

static const char digits_bcd[] =
    {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '?', '?', '?', '?', '?', '?'};
// BCD number
string bcd_string(const uint8_t*d, int length){
    if (length<=0 || !d) return string();

    string ret = NASNR_LIST_INIT(string,);
    for(int i =0; i < length; i++) {
        const NASNR_AUTO(uint8_t) a   = d[i] & 0x0fu;
        ret.push_back(digits_bcd[a]);

        NASNR_AUTO(uint8_t) b   = (d[i] & 0xf0u) >> 4u;

        // if the last octet's lower-order nibble is 0x0f
        // ignore it
        if (i != length - 1 || b != 0x0fu) ret.push_back(digits_bcd[b]);
    }
    return ret;
}

string imei_string(const uint8_t*d, int length){
    if (length <= 0 || !d) return string();
    string ret= NASNR_LIST_INIT(string,);

    ret.push_back(digits_bcd[(d[0] & 0xf0u) >> 4]);
    for (int i = 1; i < length; ++i) {
        ret.push_back(digits_bcd[d[i] & 0x0fu]);
        if (i!=length-1||(d[i]&0xf0u)!=0xf0u){
            ret.push_back(digits_bcd[(d[i] & 0xf0u) >> 4u]);
        }
    }
    return ret;
}

int ext_length(const uint8_t* d) {
    const NASNR_AUTO(uint8_t) msb = d[0];
    /* length in 2 octets */
    if ((msb & 0x80u) == 0) return (int(msb) << 8) + int(d[1]);
    return int(msb & 0x7fu);
}

string asc_time(const tm* t) {
#if defined(_WIN32) || defined(_WIN64)
    char buf[128] = {0};
#if NASNR_COMPILER_CXX_STDSIZE
    auto e = asctime_s(buf, std::size(buf), t);
#else
	NASNR_AUTO(errno_t) e = asctime_s(buf, _countof(buf), t);
#endif

    return !e ? string(buf) : string();
#else
    auto x = asctime(t);
    return x ? string(x) : string();
#endif
}

string timezone_time_string(const uint8_t*d, int length){
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

    NASNR_AUTO(string) ts = asc_time(&t);
    if (ts.empty()) return ts;

    NASNR_AUTO(char) const sign     = (d[6] & 0x08u) ? '-' : '+';
    NASNR_AUTO(uint8_t)       quarters = (d[6] >> 4u) + (d[6] & 0x07u) * 10;
    NASNR_AUTO(uint8_t) const h        = quarters / 4;
    quarters            = quarters % 4 * 15;
    return formats("%s GMT %c %d hours %d minutes", ts.c_str(), sign, h, quarters);
}

string timezone_string(const uint8_t*d){
    NASNR_AUTO(char) const sign     = (d[0] & 0x08u) ? '-' : '+';
    NASNR_AUTO(uint8_t)    quarters = (d[0] >> 4u) + (d[0] & 0x07u) * 10;
    NASNR_AUTO(uint8_t) const h     = quarters / 4;
    quarters            = quarters % 4 * 15;
    return formats("GMT %c %d hours %d minutes", sign, h, quarters);
}

string w2utf8(const wchar_t* s) {
#if defined(_WIN32) || defined(_WIN64)
    const NASNR_AUTO(size_t) sz  = wcslen(s);
    NASNR_AUTO(char*) const out = new char[sz * 4 + 1]; // large enough
    (void) WideCharToMultiByte(
        CP_UTF8, 0, s, -1, out, static_cast< int >(sz), nullptr, nullptr);
    string ret(out);
    delete out;
    return ret;
#else
    return string();
#endif
}
