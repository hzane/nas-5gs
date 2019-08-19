#include "core.hh"
#include <cstdio>
#include <vector>
#include <windows.h>
#include <DbgHelp.h>

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
