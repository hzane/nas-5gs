#pragma once
#include "config.hh"
#include "description.hh"

#if NASNR_COMPILER_CXX_USING_ALIAS
using v_string = val_string;
#else
typedef val_string v_string;
#endif