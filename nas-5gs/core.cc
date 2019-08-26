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
void bug(const char* format, ...) {

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
        bug("overflow at %d\n", d.offset);
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
