#pragma once

#include "config.hh"
#include "val_string.hh"
#include <string>


struct true_false_string {
    const char* true_string;
    const char* false_string;
};
using tf_string    = true_false_string;
using value_string = val_string;


inline const true_false_string true_false = {"true", "false"};

namespace ft {
inline extern const uint32_t none        = 0;
inline extern const uint32_t ft_signed   = 0x40;
inline extern const uint32_t ft_unsigned = 0x20;
inline extern const uint32_t protocol    = 17;
inline extern const uint32_t ft_boolean  = 16;
inline extern const uint32_t ft_uint7    = 15u | ft_unsigned;
inline extern const uint32_t ft_uint8    = 1u | ft_unsigned;
inline extern const uint32_t ft_int8     = 2u | ft_signed;
inline extern const uint32_t ft_uint16   = 3u | ft_unsigned;
inline extern const uint32_t ft_int16    = 4u | ft_signed;
inline extern const uint32_t ft_uint24   = 5u | ft_unsigned;
inline extern const uint32_t ft_int24    = 6u | ft_signed;
inline extern const uint32_t ft_uint32   = 7u | ft_unsigned;
inline extern const uint32_t ft_int32    = 8u | ft_signed;
inline extern const uint32_t ft_uint48   = 9u | ft_unsigned;
inline extern const uint32_t ft_int48    = 10u | ft_signed;
inline extern const uint32_t ft_uint56   = 11u | ft_unsigned;
inline extern const uint32_t ft_int56    = 12u | ft_signed;
inline extern const uint32_t ft_uint64   = 13u | ft_unsigned;
inline extern const uint32_t ft_int64    = 14u | ft_signed;

inline extern const uint32_t ft_float  = 24;
inline extern const uint32_t ft_double = 25;
inline extern const uint32_t ft_string = 17;
inline extern const uint32_t ft_bytes  = 20;
inline extern const uint32_t ft_char   = 22;
inline extern const uint32_t ft_nibble = 23;
inline extern const uint32_t ft_expert = 26;
inline extern const uint32_t ft_struct = 27;

inline bool is_unsigned(uint32_t t) { return (t & ft_unsigned); }
inline bool is_signed(uint32_t t) { return (t & ft_signed); }
inline bool is_integer(uint32_t t) { return is_unsigned(t) || is_signed(t); }

// clang-format off
inline uint32_t integer_size(const uint32_t t) {
    return (t==ft_uint8||t==ft_int8) ? 1u
                                     : (t==ft_uint16||t==ft_int16)  ? 2u
                                     : (t==ft_uint24||t==ft_int24)           ? 3u
                                     : (t==ft_uint32||t==ft_int32)           ? 4u
                                     : (t==ft_uint48||t==ft_int48)           ? 6u
                                     : (t==ft_uint64||t==ft_int64)           ? 8u: 0;
}
// clang-format on

} // namespace ft

namespace fd {
inline const uint32_t base_none    = 0; /* none */
inline const uint32_t base_dec     = 1; /* decimal */
inline const uint32_t base_hex     = 2; /* hexadecimal */
inline const uint32_t base_oct     = 3; /* octal */
inline const uint32_t base_dec_hex = 4; /* decimal (hexadecimal) */
inline const uint32_t base_hex_dec = 5; /* hexadecimal (decimal) */
inline const uint32_t base_bin     = 6; // show as bit string
inline const uint32_t base_bit     = 7; // show as bit set
inline const uint32_t base_string  = 8;
inline const uint32_t bits7        = 9u; // bits7 ascii string
inline const uint32_t ipv4         = 10u; // xxx.xxx.xxx.xxx
inline const uint32_t ipv6         = 11u; // xxxx:x:xx:xxx
inline const uint32_t timer3       = 12u; // gprs timer
inline const uint32_t timer2       = 13u; // gprs timer
inline const uint32_t timer        = 14u; // gprs timer
inline const uint32_t mmc          = 15u; //
inline const uint32_t mac          = 16u; //
inline const uint32_t mcc          = 17u; //
inline const uint32_t mnc          = 18u; //
inline const uint32_t bcd          = 19u; // BCD Number

/* Byte separators  when ft == ft_bytes */
/* hexadecimal bytes with a period (.) between each byte */
inline const uint32_t sep_dot   = 20u ;
inline const uint32_t sep_dash  = 21u;
inline const uint32_t sep_colon = 22u;
inline const uint32_t sep_space = 23u;
inline const uint32_t bstrn     = 24u;
inline const uint32_t ext_length = 25u;
inline const uint32_t imei       = 26u;
inline const uint32_t timezone   = 27u;
inline const uint32_t timezone_time      = 28u;
inline const uint32_t ambr       = 29u;
inline const uint32_t link_local_address = 30u;

inline uint32_t get(uint32_t d) { return d & 0xff; }

} // namespace fd

using string = std::string;

struct field_meta {
    const char*              name;    /* full name of this field */
    const char*              abbrev;  /* abbreviated name of this field */
    uint32_t                 ftype;   /* field_type::*/
    uint32_t                 display; /* one of base_ */
    const val_string*        val_strings;
    const tf_string*         tf_strings;
    const range_string*      range_strings;
    uint64_t                 bitmask; /* bitmask of interesting bits */

    string format(const uint8_t* p, int len, uint32_t enc) const;
    string format(uint64_t val) const;
};

