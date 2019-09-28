#include "core.hh"

#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <sstream>
#include <vector>

#include "format.hh"

#if defined(_WIN32) || defined (_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
// #include <DbgHelp.h>
#else
void OutputDebugStringA(const char*){}
#endif

// declared in config.hh
void diag(const char* format, ...) {

    va_list args;
    va_start(args, format);

    va_list cp;
    va_copy(cp, args);

    std::vector< char > buf(
        1 + static_cast< size_t >(std::vsnprintf(nullptr, 0, format, args)));
    va_end(args);


    vsnprintf(buf.data(), buf.size(), format, cp);
    va_end(cp);
    OutputDebugStringA(buf.data());
}

string context::path() const { return join(paths, "/"); }

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

string ambr_string(const uint8_t*d, int length) {
    if (!d || length <= 0) return string();
    const auto unit = uint32_t(d[0]);
    const auto val  = n2uint16(d + 1);
    return ambr_string(val, unit);
}

string ambr_string(uint32_t val, uint32_t unit){
    auto       unit_str = "";
    const auto multi = get_ext_ambr_unit(unit, &unit_str);
    return formats("%u %s (%u)", val * multi, unit_str, val);
}

// ascii strings
string bstrn_string(const uint8_t*d, int len){
    if (!d || !len) return string();

    string str(d, d + len);

    for (size_t i = 0; i < str.size();) {
        const auto next = str[i];
        str[i]          = '.';
        i               = i + next + 1;
    }
    return str;
}

string gprs_timer_string(const uint8_t*d, int len) {
    if (!d || len <= 0) return string();

    const auto  val   = static_cast< uint32_t >(d[0]) & 0x1fu;
    const auto  unitf = static_cast< int >(d[0] >> 5u);
    auto        unit  = "min";
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
    return formats("%u %s (%u)", val * mul, unit, val);
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




int ext_length(const uint8_t* d) {
    const auto msb = d[0];
    /* length in 2 octets */
    if ((msb & 0x80u) == 0) return (int(msb) << 8u) + int(d[1]);
    return int(msb & 0x7fu);
}


