#pragma once
#include <string>

#include "v_string.hh"

using string = std::string;

string format_hex(const uint8_t* data,
                  int            len,
                  const string&    sep = " ",
                  const string&    lf  = "");

string bits_string(const v_string* strings, uint32_t bits);

string vstring(const v_string* strings,
               uint32_t          id,
               const char*       missing = "Unknown");
string rstring(const range_string* strings,
               uint32_t            id,
               const char*         missing = "Unknown");
