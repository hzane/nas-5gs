#include "core.hh"
#include <cstdio>
#include <vector>

#if _WIN32
#include <windows.h>
#include <DbgHelp.h>
#else
void OutputDebugStringA(const char*){}
#endif

// declared in config.hh
void diag(const char* format, ...) {

    va_list args;
    va_start(args, format);

    va_list cp;
    va_copy(cp, args);

    std::vector< char > buf(1 + std::vsnprintf(nullptr, 0, format, args));
    va_end(args);


    vsnprintf(buf.data(), buf.size(), format, cp);
    va_end(cp);
    OutputDebugStringA(buf.data());
}

void extraneous_data_check(dissector d, int maxlen) {
    if (d.length < 0) {
        diag("overflow at %d\n", d.offset);
    }
    if (d.length > maxlen) {
        d.tree->add_expert(d.pinfo,
                           d.tvb,
                           d.offset,
                           d.length - maxlen,
                           "extraneous data (%d) bytes",
                           (d.length - maxlen));
    }
}

string context::path() const { return join(paths, "/"); }

string bits7_string(const uint8_t* data, int len){
    auto d = ts_23_038_7bits_string(data, 0, (len<<3)/7);
    return string(d.begin(), d.end());
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

string ambr_string(uint32_t val, uint32_t unit){
    const char* unit_str = "";
    auto multi = get_ext_ambr_unit(unit, &unit_str);
    return formats("%u %s (%u)", val * multi, unit_str, val);
}

// ascii strings
string bstrn_string(const uint8_t*d, int len){
    if (!d || !len) return string();

    string str(d, d + len);
    size_t i = 0;
    while (i < str.size()) {
        auto next = str[i];
        str[i]    = '.';
        i         = i + next + 1;
    }
    return str;
}

/* * 3GPP TS 24.008 g10 10.5.7.4a */
string gprs_timer3_format(uint8_t oct) {
    auto        uf   = oct >> 5u;
    auto        val  = uint32_t(oct) & 0x1fu;
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
    return formats("GPRS Timer : %u %s (%u)", val * mul, unit, val);
}

/* * 3GPP TS 24.008 g10 10.5.7.4 */
string gprs_timer2_format(uint8_t oct) {
    auto        val  = uint8_t(oct) & 0x1fu;
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
        break; // timer is deactivated
    default:
        break;
    }
    return formats("GPRS Timer : %u %s (%u)", val * mul, unit, val);
}

// assure: iei != 0
const message_meta* find_dissector(uint8_t iei, const message_meta* meta) {
    while (meta->name) { // meta->type may be zero
        if (meta->type == iei) return meta;
        meta++;
    }
    return nullptr;
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
uint32_t mcc_mnc3(const uint8_t*d, uint32_t*mcc, uint32_t *mnc){
    /* Mobile country code MCC */
    auto octet = (uint32_t)d[0];
    auto mcc1 = octet & 0x0fu;
    auto mcc2 = octet >> 4u;

    octet = d[1];
    auto mcc3 = octet & 0x0fu;
    /* MNC, Mobile network code (octet 3 bits 5 to 8, octet 4)  */
    auto mnc3 = octet >> 4u;

    octet = d[2];
    auto mnc1 = octet & 0x0fu;
    auto mnc2 = octet >> 4u;

    *mcc = 100 * mcc1 + 10 * mcc2 + mcc3;
    *mnc = 100 * mnc1 + 10*mnc2 + mnc3;
    return (*mcc)*1000 + *mnc;
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

    return string((const char*) mcc);
}

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

    return string((const char*) mnc);
}

namespace{
static const char digits_bcd[] =
    {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '?', '?', '?', '?', '?', '?'};
}
// BCD number
string bcd_string(const uint8_t*d, int length){
    if (length<=0 || !d) return string();

    string ret = {};
    for(int i =0; i < length; i++){
        auto a   = d[i] & 0x0fu;
        ret.push_back(digits_bcd[a]);

        auto b   = (d[i] & 0xf0u) >> 4;

        // if the last octet's lower-order nibble is 0x0f
        // ignore it
        if (i != length - 1 || b != 0x0fu) ret.push_back(digits_bcd[b]);
    }
    return ret;
}

string imei_string(const uint8_t*d, int length){
    if (length <= 0 || !d) return string();
    string ret={};

    ret.push_back(digits_bcd[(d[0] & 0xf0u) >> 4]);
    for (auto i = 1; i < length; ++i) {
        ret.push_back(digits_bcd[d[i] & 0x0fu]);
        if (i!=length-1||(d[i]&0xf0u)!=0xf0u){
            ret.push_back(digits_bcd[(d[i] & 0xf0u) >> 4u]);
        }
    }
    return ret;
}

void extraneous_data_check(int offset, int len, int maxlen, context*ctx){
    if (len<0){
        diag("underflow %s %d:%d\n", paths(ctx).c_str(), offset, len);
        return;
    }
    if (len>maxlen){
        diag("extraneous data %s %d:%d\n", paths(ctx).c_str(), offset, len);
    }
}

uint64_t uintmap(uint64_t f, uint64_t mask) {
    return mask ? (f&mask)>>ws_ctz(mask) : f;
}

int ext_length(const uint8_t* d) {
    const auto msb = d[0];
    /* length in 2 octets */
    if ((msb & 0x80u) == 0) return (int(msb) << 8) + int(d[1]);
    return int(msb & 0x7fu);
}
