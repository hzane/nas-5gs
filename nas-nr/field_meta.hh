#pragma once

#include <string>
#include "config.hh"
#include "val_string.hh"

#if NASNR_COMPILER_CXX_USING_ALIAS
using tf_string    = true_false_string;
using value_string = val_string;
#else
typedef true_false_string tf_string;
typedef val_string value_string;
#endif

NASNR_INLINE const true_false_string true_false = {"true", "false"};

namespace ft {
NASNR_INLINE const uint32_t none        = 0;
NASNR_INLINE const uint32_t ft_signed   = 0x40;
NASNR_INLINE const uint32_t ft_unsigned = 0x20;
NASNR_INLINE const uint32_t protocol    = 18;
NASNR_INLINE const uint32_t ft_boolean  = 17;
NASNR_INLINE const uint32_t ft_struct   = 19;
NASNR_INLINE const uint32_t ft_expert   = 20;
NASNR_INLINE const uint32_t ft_bytes    = 21;
NASNR_INLINE const uint32_t ft_uint8    = 1u | ft_unsigned;
NASNR_INLINE const uint32_t ft_int8     = 1u | ft_signed;
NASNR_INLINE const uint32_t ft_uint16   = 2u | ft_unsigned;
NASNR_INLINE const uint32_t ft_int16    = 2u | ft_signed;
NASNR_INLINE const uint32_t ft_uint24   = 3u | ft_unsigned;
NASNR_INLINE const uint32_t ft_int24    = 3u | ft_signed;
NASNR_INLINE const uint32_t ft_uint32   = 4u | ft_unsigned;
NASNR_INLINE const uint32_t ft_int32    = 4u | ft_signed;
NASNR_INLINE const uint32_t ft_uint48   = 6u | ft_unsigned;
NASNR_INLINE const uint32_t ft_int48    = 6u | ft_signed;
NASNR_INLINE const uint32_t ft_uint56   = 7u | ft_unsigned;
NASNR_INLINE const uint32_t ft_int56    = 7u | ft_signed;
NASNR_INLINE const uint32_t ft_uint64   = 8u | ft_unsigned;
NASNR_INLINE const uint32_t ft_int64    = 8u | ft_signed;

inline bool is_unsigned(uint32_t t) { return !!(t & ft_unsigned); }
inline bool is_signed(uint32_t t) { return !!(t & ft_signed); }
inline bool is_integer(uint32_t t) { return is_unsigned(t) || is_signed(t); }

inline uint32_t integer_size(const uint32_t t) { return t & 0x7u; }

} // namespace ft

namespace fd {
NASNR_INLINE const uint32_t base_none          = 0; /* none */
NASNR_INLINE const uint32_t base_dec           = 1; /* decimal */
NASNR_INLINE const uint32_t base_hex           = 2; /* hexadecimal */
NASNR_INLINE const uint32_t base_oct           = 3; /* octal */
NASNR_INLINE const uint32_t base_dec_hex       = 4; /* decimal (hexadecimal) */
NASNR_INLINE const uint32_t base_hex_dec       = 5; /* hexadecimal (decimal) */
NASNR_INLINE const uint32_t base_bin           = 6; // show as bit string
NASNR_INLINE const uint32_t base_bit           = 7; // show as bit set
NASNR_INLINE const uint32_t base_string        = 8; // raw string
NASNR_INLINE const uint32_t bits7              = 9u;  // bits7 ascii string
NASNR_INLINE const uint32_t ipv4               = 10u; // xxx.xxx.xxx.xxx
NASNR_INLINE const uint32_t ipv6               = 11u; // 16 octets
NASNR_INLINE const uint32_t timer3             = 12u; // gprs timer 3
NASNR_INLINE const uint32_t timer2             = 13u; // gprs timer 2
NASNR_INLINE const uint32_t timer              = 14u; // gprs timer 1
NASNR_INLINE const uint32_t mmc                = 15u; //
NASNR_INLINE const uint32_t mac                = 16u; // 6 octets
NASNR_INLINE const uint32_t mcc                = 17u; // 3 octets
NASNR_INLINE const uint32_t mnc                = 18u; // 3 octets, e212 little-endian
NASNR_INLINE const uint32_t bcd                = 19u; // BCD Number
NASNR_INLINE const uint32_t sep_dot            = 20u; // hex seperatored by .
NASNR_INLINE const uint32_t sep_dash           = 21u; // hex speratored by -
NASNR_INLINE const uint32_t sep_colon          = 22u; // hex seperatored by ,
NASNR_INLINE const uint32_t sep_space          = 23u; // hex speratored by [space]
NASNR_INLINE const uint32_t bstrn              = 24u; // BSTRs
NASNR_INLINE const uint32_t extl               = 25u; // one or two byte
NASNR_INLINE const uint32_t imei               = 26u;
NASNR_INLINE const uint32_t timezone           = 27u;
NASNR_INLINE const uint32_t timezone_time      = 28u;
NASNR_INLINE const uint32_t ambr               = 29u;
NASNR_INLINE const uint32_t link_local_address = 30u; // 8 octets
NASNR_INLINE const uint32_t uint7              = 31u;
NASNR_INLINE const uint32_t base_char          = 32u;
NASNR_INLINE const uint32_t nibble             = 33u; // right half octet
NASNR_INLINE const uint32_t right              = 33u;
NASNR_INLINE const uint32_t left               = 35u; // left half octet

inline uint32_t get(uint32_t d) { return d & 0xff; }

} // namespace fd

#if NASNR_COMPILER_CXX_USING_ALIAS
using string = std::string;
#else
using std::string;
#endif

#if NASNR_COMPILER_CXX_DEFAULT_FUNCTIONS
struct field_meta : description {
    string format(const uint8_t* p, int len, uint32_t enc) const;
    string format(uint64_t val) const;
};

#else
struct field_meta  {
    const char*              tag;     /* full name of this field */
    const char*              abbrev;  /* abbreviated name of this field */
    unsigned int             typi;    /* field_type::*/
    unsigned int             display; /* one of base_ */
    const val_string*        val_strings;
    const true_false_string* tf_strings;
    const range_string*      range_strings;
    unsigned long long       bitmask; /* bitmask of interesting bits */
};

#endif
string field_meta_format(const field_meta* self, const uint8_t* p, int len, uint32_t enc);
string field_meta_format(const field_meta* self, uint64_t val);
