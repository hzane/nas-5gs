#include <iostream>
#include <cstdarg>

#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
// #include <windows.h>
// #include <DbgHelp.h>
#else
void OutputDebugStringA(const char*msg) {std::cerr<<msg;}
#endif

// declared in config.hh
void diag(const char* format, ...) {
    char    tmp[4096] = {};

    va_list args;
    va_start(args, format);

    vsnprintf(tmp, std::size(tmp) - 1, format, args);
    va_end(args);

    OutputDebugStringA(tmp);
}
