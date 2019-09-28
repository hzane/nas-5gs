#pragma once
#include <string>

typedef unsigned char octet;
struct v_string;
struct true_false_string;
struct range_string;

// NOLINTNEXTLINE
struct description {
    const char*              tag;           // full name of this field
    const char*              abbrev;        // abbreviated name of this field
    unsigned int             typi;          // field_type::
    unsigned int             display;       // one of base_
    const v_string*        v_strings;   //
    const true_false_string* tf_strings;    //
    const range_string*      range_strings; //
    unsigned long long       bitmask;       // bitmask of interesting bits
};

struct v_string {
    unsigned int id;
    const char* text;
};

struct true_false_string {
    const char* true_string;
    const char* false_string;
};

// [val_min, val_max]
struct range_string {
    unsigned int val_min;
    unsigned int val_max;
    const char*  text;
};

inline std::string vstring_format(uint64_t v, uint64_t mask, const v_string* vals){
    return std::string{};
}