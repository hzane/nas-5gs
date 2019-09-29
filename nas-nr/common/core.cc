#include "core.hh"

#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <sstream>
#include <vector>

#include "formats.hh"

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
