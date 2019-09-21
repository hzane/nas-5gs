#pragma once

#include <string>
#include "config.hh"
#include "val_string.hh"

using tf_string    = true_false_string;
using value_string = val_string;


inline const true_false_string true_false = {"true", "false"};

namespace ft {
inline const uint32_t none        = 0;
inline const uint32_t ft_signed   = 0x40;
inline const uint32_t ft_unsigned = 0x20;
inline const uint32_t protocol    = 18;
inline const uint32_t ft_boolean  = 17;
inline const uint32_t ft_struct   = 19;
inline const uint32_t ft_expert   = 20;
inline const uint32_t ft_bytes    = 21;
inline const uint32_t ft_uint8    = 1u | ft_unsigned;
inline const uint32_t ft_int8     = 1u | ft_signed;
inline const uint32_t ft_uint16   = 2u | ft_unsigned;
inline const uint32_t ft_int16    = 2u | ft_signed;
inline const uint32_t ft_uint24   = 3u | ft_unsigned;
inline const uint32_t ft_int24    = 3u | ft_signed;
inline const uint32_t ft_uint32   = 4u | ft_unsigned;
inline const uint32_t ft_int32    = 4u | ft_signed;
inline const uint32_t ft_uint48   = 6u | ft_unsigned;
inline const uint32_t ft_int48    = 6u | ft_signed;
inline const uint32_t ft_uint56   = 7u | ft_unsigned;
inline const uint32_t ft_int56    = 7u | ft_signed;
inline const uint32_t ft_uint64   = 8u | ft_unsigned;
inline const uint32_t ft_int64    = 8u | ft_signed;

inline bool is_unsigned(uint32_t t) { return (t & ft_unsigned); }
inline bool is_signed(uint32_t t) { return (t & ft_signed); }
inline bool is_integer(uint32_t t) { return is_unsigned(t) || is_signed(t); }

inline uint32_t integer_size(const uint32_t t) { return t & 0x7u; }

} // namespace ft

namespace fd {
inline const uint32_t base_none          = 0; /* none */
inline const uint32_t base_dec           = 1; /* decimal */
inline const uint32_t base_hex           = 2; /* hexadecimal */
inline const uint32_t base_oct           = 3; /* octal */
inline const uint32_t base_dec_hex       = 4; /* decimal (hexadecimal) */
inline const uint32_t base_hex_dec       = 5; /* hexadecimal (decimal) */
inline const uint32_t base_bin           = 6; // show as bit string
inline const uint32_t base_bit           = 7; // show as bit set
inline const uint32_t base_string        = 8; // raw string
inline const uint32_t bits7              = 9u;  // bits7 ascii string
inline const uint32_t ipv4               = 10u; // xxx.xxx.xxx.xxx
inline const uint32_t ipv6               = 11u; // 16 octets
inline const uint32_t timer3             = 12u; // gprs timer 3
inline const uint32_t timer2             = 13u; // gprs timer 2
inline const uint32_t timer              = 14u; // gprs timer 1
inline const uint32_t mmc                = 15u; //
inline const uint32_t mac                = 16u; // 6 octets
inline const uint32_t mcc                = 17u; // 3 octets
inline const uint32_t mnc                = 18u; // 3 octets, e212 little-endian
inline const uint32_t bcd                = 19u; // BCD Number
inline const uint32_t sep_dot            = 20u; // hex separated by .
inline const uint32_t sep_dash           = 21u; // hex separated by -
inline const uint32_t sep_colon          = 22u; // hex separated by ,
inline const uint32_t sep_space          = 23u; // hex separated by [space]
inline const uint32_t bstrn              = 24u; // BSTRs
inline const uint32_t extl               = 25u; // one or two byte
inline const uint32_t imei               = 26u;
inline const uint32_t timezone           = 27u;
inline const uint32_t timezone_time      = 28u;
inline const uint32_t ambr               = 29u;
inline const uint32_t link_local_address = 30u; // 8 octets
inline const uint32_t uint7              = 31u;
inline const uint32_t base_char          = 32u;
inline const uint32_t nibble             = 33u; // right half octet
inline const uint32_t right              = 33u;
inline const uint32_t left               = 35u; // left half octet

inline uint32_t get(uint32_t d) { return d & 0xff; }

} // namespace fd

using string = std::string;

struct field_meta : description {
    string format(const uint8_t* p, int len, uint32_t enc) const;
    [[nodiscard]] string format(uint64_t val) const;
};

namespace nt {
inline const uint32_t nt_none    = 0x00;
inline const uint32_t nt_signed  = 0x20;
inline const uint32_t nt_hex     = 0x40;
inline const uint32_t nt_dec     = 0x80;
inline const uint32_t nt_integer = 0x100;
inline const uint32_t nt_bytes   = 0x200;
inline const uint32_t nt_uint8   = 0x01 | nt_integer;
inline const uint32_t nt_uint16  = 0x02 | nt_integer;
inline const uint32_t nt_uint24  = 0x03 | nt_integer;
inline const uint32_t nt_uint32  = 0x04 | nt_integer;
inline const uint32_t nt_uint40  = 0x05 | nt_integer;
inline const uint32_t nt_uint48  = 0x06 | nt_integer;
inline const uint32_t nt_uint56  = 0x07 | nt_integer;
inline const uint32_t nt_uint64  = 0x08 | nt_integer;
inline const uint32_t nt_int8   = 0x01 | nt_integer | nt_signed;
inline const uint32_t nt_int16   = 0x02 | nt_integer | nt_signed;
inline const uint32_t nt_int24   = 0x03 | nt_integer | nt_signed;
inline const uint32_t nt_int32   = 0x04 | nt_integer | nt_signed;
inline const uint32_t nt_int40   = 0x05 | nt_integer | nt_signed;
inline const uint32_t nt_int48   = 0x06 | nt_integer | nt_signed;
inline const uint32_t nt_int56   = 0x07 | nt_integer | nt_signed;
inline const uint32_t nt_int64   = 0x08 | nt_integer | nt_signed;
inline const uint32_t nt_bin     = 0x09 | nt_bytes;
inline const uint32_t nt_boolean = 0x0a;
inline const uint32_t nt_string  = 0x0b;
inline const uint32_t nt_struct  = 0x0c;
inline const uint32_t nt_expert  = 0x0d;
inline const uint32_t nt_bit7    = 0x0e;
inline const uint32_t nt_ipv4    = 0x0f;
inline const uint32_t nt_ipv6    = 0x11;
inline const uint32_t nt_mac     = 0x12;
inline const uint32_t nt_ip64    = 0x13;
inline const uint32_t nt_timer_1 = 0x14;
inline const uint32_t nt_timer_2 = 0x15;
inline const uint32_t nt_timer_3 = 0x16;
inline const uint32_t nt_bcd     = 0x17;
inline const uint32_t nt_bstrn   = 0x18;
inline const uint32_t nt_char    = 0x19;
inline const uint32_t nt_imei    = 0x1a;
inline const uint32_t nt_xlen    = 0x1b;
inline const uint32_t nt_ambr    = 0x1c;
inline const uint32_t nt_addr8   = 0x1d;
inline const uint32_t nt_timezone = 0x1e;
inline const uint32_t nt_timezone_time = 0x1f;
} // namespace nt
