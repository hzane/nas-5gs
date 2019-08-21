#pragma once
// defined in core.hh

#include "config.hh"
#include <string>

struct val_string {
    uint32_t    id;
    const char* text;
};

struct true_false_string {
    const char* true_string;
    const char* false_string;
};

// [val_min, val_max)
struct range_string {
    uint32_t    val_min;
    uint32_t    val_max;
    const char* text;
};


namespace ft {
__declspec(selectany) extern const uint32_t none          = 0;
__declspec(selectany) extern const uint32_t protocol      = 1;
__declspec(selectany) extern const uint32_t ft_boolean    = 2;
__declspec(selectany) extern const uint32_t ft_uint8      = 3;
__declspec(selectany) extern const uint32_t ft_uint16     = 4;
__declspec(selectany) extern const uint32_t ft_uint24     = 5;
__declspec(selectany) extern const uint32_t ft_uint32     = 6;
__declspec(selectany) extern const uint32_t ft_uint64     = 7;
__declspec(selectany) extern const uint32_t ft_int8       = 8;
__declspec(selectany) extern const uint32_t ft_int16      = 9;
__declspec(selectany) extern const uint32_t ft_int24      = 10;
__declspec(selectany) extern const uint32_t ft_int32      = 11;
__declspec(selectany) extern const uint32_t ft_int64      = 12;
__declspec(selectany) extern const uint32_t ft_float      = 13;
__declspec(selectany) extern const uint32_t ft_double     = 14;
__declspec(selectany) extern const uint32_t ft_string     = 15;
__declspec(selectany) extern const uint32_t ft_stringz    = 16;
__declspec(selectany) extern const uint32_t ft_hex_string = 17;
__declspec(selectany) extern const uint32_t ft_bin_string = 18;
__declspec(selectany) extern const uint32_t ft_bytes      = 19;
__declspec(selectany) extern const uint32_t ft_char       = 20;
__declspec(selectany) extern const uint32_t ft_bitset     = 21;
} // namespace ft

namespace fd {
__declspec(selectany) extern const uint32_t base_none    = 0; /* none */
__declspec(selectany) extern const uint32_t base_dec     = 1; /* decimal */
__declspec(selectany) extern const uint32_t base_hex     = 2; /* hexadecimal */
__declspec(selectany) extern const uint32_t base_oct     = 3; /* octal */
__declspec(selectany) extern const uint32_t base_dec_hex = 4; /* decimal (hexadecimal) */
__declspec(selectany) extern const uint32_t base_hex_dec = 5; /* hexadecimal (decimal) */
__declspec(selectany) extern const uint32_t base_bin     = 6;
__declspec(selectany) extern const uint32_t base_custom =
    7; /* call custom routine (in ->strings) to format */
__declspec(selectany) extern const uint32_t base_ext_string = 8;

__declspec(selectany) extern const uint32_t base_float =
    base_none; /**< decimal-format float */

__declspec(selectany) extern const uint32_t str_ascii =
    0; /* shows non-printable ASCII characters as C-style escapes */
__declspec(selectany) extern const uint32_t str_unicode =
    9; /* shows non-printable UNICODE characters as \\uXXXX */
__declspec(selectany) extern const uint32_t str_utf8 = 10;

/* Byte separators */
__declspec(selectany) extern const uint32_t sep_dot =
    12; /* hexadecimal bytes with a period (.) between each byte */
__declspec(selectany) extern const uint32_t sep_dash =
    9; /* hexadecimal bytes with a dash (-) between each byte */
__declspec(selectany) extern const uint32_t sep_colon =
    10; /* hexadecimal bytes with a colon (:) between each byte */
__declspec(selectany) extern const uint32_t sep_space =
    11; /* hexadecimal bytes with a space between each byte */

// field_display mask
__declspec(selectany) extern const uint32_t range_string     = 0x00000100;
__declspec(selectany) extern const uint32_t allow_zero       = 0x00000800;
__declspec(selectany) extern const uint32_t unit_string      = 0x00001000;
__declspec(selectany) extern const uint32_t no_display_value = 0x00002000;
__declspec(selectany) extern const uint32_t special_vals     = 0x00008000;
__declspec(selectany) extern const uint32_t ascii_printable  = 0x00010000;

inline uint32_t get(uint32_t d) { return d & 0xff; }
inline bool     is_base_dual(uint32_t d) {
    d = get(d);
    return d == base_dec_hex || d == base_hex_dec;
}
} // namespace fd

struct field_meta {
    const char*              name;       /* full name of this field */
    const char*              abbrev;     /* abbreviated name of this field */
    uint32_t                 field_type; /* field_type::*/
    uint32_t                 display;    /* one of base_                             */
    const val_string*        val_strings;
    const true_false_string* tf_strings;
    const range_string*      range_strings;
    uint64_t                 bitmask; /* bitmask of interesting bits */

    std::string print(uint64_t v) const;
    std::string print_dec(uint64_t v) const;
    std::string print_hex(uint64_t v) const;
    std::string print_bytes(const uint8_t* data, int len, uint32_t enc) const;
    std::string print_data(const uint8_t* data, int len, uint32_t enc) const;
};
std::string formats(const char* format, ...);
std::string vformat(const char* format, va_list);

const char* find_val_string(const val_string* vstr, uint32_t id, const char*missing="Unknown");
const char* find_r_string(const range_string* rstr, uint32_t id, const char*missing="Unknown");
std::vector< std::string > find_bitset_string(const val_string* vstr, uint32_t bits);

std::string join(const std::vector< std::string >& strs, const char* sep = " ");
