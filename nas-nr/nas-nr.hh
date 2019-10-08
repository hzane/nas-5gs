#pragma once

#if defined NASNRTS24501_EXPORTS

#if defined(_WIN32) || defined (_WIN64)
// NOLINTNEXTLINE
#define NASNRAPI __declspec(dllexport)
#else
#define NASNRAPI __attribute__((visibility("default")))
#endif

#else
#define NASNRAPI
#endif

#include "common/dissects.hh"

