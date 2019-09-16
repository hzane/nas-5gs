#pragma once
#include "description.hh"

#if NASNR_COMPILER_CXX_USING_ALIAS
using r_string = range_string;
#else
typedef range_string r_string;
#endif

