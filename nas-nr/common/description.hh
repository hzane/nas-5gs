#pragma once

typedef unsigned char octet;
struct v_string;
struct tf_string;
struct r_string;

// NOLINTNEXTLINE
struct description {
    const char*              tag;           // full name of this field
    const char*              abbrev;        // abbreviated name of this field
    unsigned int             typi;          // field_type::
    unsigned int             display;       // one of base_
    const v_string*        val_strings;   //
    const tf_string* tf_strings;    //
    const r_string*      range_strings; //
    unsigned long long       bitmask;       // bitmask of interesting bits
};

struct v_string {
    unsigned int id;
    const char* text;
};

struct tf_string {
    const char* true_string;
    const char* false_string;
};

// [val_min, val_max]
struct r_string {
    unsigned int val_min;
    unsigned int val_max;
    const char*  text;
};
