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

/*
 * The encoding of the APN shall follow the Name Syntax defined in RFC 2181 [18], RFC 1035 [19] and RFC 1123 [20].
The APN consists of one or more labels. Each label is coded as a one octet length field followed by that number of
octets coded as 8 bit ASCII characters. Following RFC 1035 [19] the labels shall consist only of the alphabetic
characters (A-Z and a-z), digits (0-9) and the hyphen (-). Following RFC 1123 [20], the label shall begin and end with
either an alphabetic character or a digit. The case of alphabetic characters is not significant. The APN is not terminated
by a length byte of zero. */
// ascii strings
string apn_string(const uint8_t*d, int len){
    if (!d || !len) return string();

    string str(d, d + len);

    for (size_t i = 0; i < str.size();) {
        const auto next = str[i];
        str[i]          = '.';
        i               = i + next + 1;
    }
    return str;
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


