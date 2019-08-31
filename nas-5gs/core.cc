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
