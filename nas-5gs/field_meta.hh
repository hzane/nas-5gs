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

// [val_min, val_max]
struct range_string {
    uint32_t    val_min;
    uint32_t    val_max;
    const char* text;
};

__declspec(selectany) extern const true_false_string true_false = {"true", "false"};

namespace ft {
__declspec(selectany) extern const uint32_t none          = 0;
__declspec(selectany) extern const uint32_t ft_integer    = 0x80;
__declspec(selectany) extern const uint32_t ft_signed     = 0x40;
__declspec(selectany) extern const uint32_t protocol      = 17;
__declspec(selectany) extern const uint32_t ft_boolean    = 16;
__declspec(selectany) extern const uint32_t ft_uint7      = 15u | ft_integer;
__declspec(selectany) extern const uint32_t ft_uint8      = 1u | ft_integer;
__declspec(selectany) extern const uint32_t ft_int8       = 2u | ft_integer | ft_signed;
__declspec(selectany) extern const uint32_t ft_uint16     = 3u | ft_integer;
__declspec(selectany) extern const uint32_t ft_int16      = 4u | ft_integer | ft_signed;
__declspec(selectany) extern const uint32_t ft_uint24     = 5u | ft_integer;
__declspec(selectany) extern const uint32_t ft_int24      = 6u | ft_integer | ft_signed;
__declspec(selectany) extern const uint32_t ft_uint32     = 7u | ft_integer;
__declspec(selectany) extern const uint32_t ft_int32      = 8u | ft_integer | ft_signed;
__declspec(selectany) extern const uint32_t ft_uint48     = 9u | ft_integer;
__declspec(selectany) extern const uint32_t ft_int48      = 10u | ft_integer | ft_signed;
__declspec(selectany) extern const uint32_t ft_uint56     = 11u | ft_integer;
__declspec(selectany) extern const uint32_t ft_int56      = 12u | ft_integer | ft_signed;
__declspec(selectany) extern const uint32_t ft_uint64     = 13u | ft_integer;
__declspec(selectany) extern const uint32_t ft_int64      = 14u | ft_integer | ft_signed;

__declspec(selectany) extern const uint32_t ft_float      = 24;
__declspec(selectany) extern const uint32_t ft_double     = 25;
<<<<<<< HEAD
__declspec(selectany) extern const uint32_t ft_string     = 17;
=======
>>>>>>> af4b6cd421734f4f835baca91d3fdf0c8c4e5951
__declspec(selectany) extern const uint32_t ft_bytes      = 20;
__declspec(selectany) extern const uint32_t ft_char       = 22;

inline bool is_integer(uint32_t t){return t&ft_integer;}
inline bool is_unsigned(uint32_t t){ return is_integer(t) && !(t&ft_signed);}
inline bool is_signed(uint32_t t){ return is_integer(t) && (t&ft_signed);}
inline uint32_t integer_size(uint32_t t){
    return (t==ft_uint8||t==ft_int8)
           ? 1u: (t==ft_uint16||t==ft_int16)
           ? 2u: (t==ft_uint24||t==ft_int24)
           ? 3u: (t==ft_uint32||t==ft_int32)
           ? 4u: (t==ft_uint48||t==ft_int48)
           ? 6u: (t==ft_uint64||t==ft_int64)
           ? 8u: 0;
}
} // namespace ft

namespace fd {
__declspec(selectany) extern const uint32_t base_none    = 0; /* none */

// when ft== ft_int...
__declspec(selectany) extern const uint32_t base_dec     = 1; /* decimal */
__declspec(selectany) extern const uint32_t base_hex     = 2; /* hexadecimal */
__declspec(selectany) extern const uint32_t base_oct     = 3; /* octal */
__declspec(selectany) extern const uint32_t base_dec_hex = 4; /* decimal (hexadecimal) */
__declspec(selectany) extern const uint32_t base_hex_dec = 5; /* hexadecimal (decimal) */
__declspec(selectany) extern const uint32_t base_bin     = 6;
__declspec(selectany) extern const uint32_t base_bitset  = 7;
__declspec(selectany) extern const uint32_t base_string  = 0x10;

/* Byte separators  when ft == ft_bytes */
/* hexadecimal bytes with a period (.) between each byte */
__declspec(selectany) extern const uint32_t sep_dot   = 9u ;
__declspec(selectany) extern const uint32_t sep_dash  = 10u;
__declspec(selectany) extern const uint32_t sep_colon = 11u;
__declspec(selectany) extern const uint32_t sep_space = 12u;

inline uint32_t get(uint32_t d) { return d & 0xff; }

} // namespace fd

using string = std::string;

struct field_meta {
    const char*              name;       /* full name of this field */
    const char*              abbrev;     /* abbreviated name of this field */
    uint32_t                 ftype;       /* field_type::*/
    uint32_t                 display;    /* one of base_ */
    const val_string*        val_strings;
    const true_false_string* tf_strings;
    const range_string*      range_strings;
    uint64_t                 bitmask; /* bitmask of interesting bits */

    string format(const uint8_t*d, int len, uint32_t enc) const;
    string format(uint64_t val)const;
};
std::string formats(const char* format, ...);
std::string vformat(const char* format, va_list);

const char* find_val_string(const val_string* vstr, uint32_t id, const char*missing="Unknown");
const char* find_r_string(const range_string* rstr, uint32_t id, const char*missing="Unknown");
std::vector< std::string > find_bitset_string(const val_string* vstr, uint32_t bits);

std::string join(const std::vector< std::string >& strs, const char* sep = " ");

