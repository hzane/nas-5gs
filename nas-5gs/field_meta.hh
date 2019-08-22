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
__declspec(selectany) extern const uint32_t protocol      = 128;
__declspec(selectany) extern const uint32_t ft_boolean    = 256;
__declspec(selectany) extern const uint32_t ft_uint7      = 15;
__declspec(selectany) extern const uint32_t ft_uint8      = 1;
__declspec(selectany) extern const uint32_t ft_int8       = 2;
__declspec(selectany) extern const uint32_t ft_uint16     = 3;
__declspec(selectany) extern const uint32_t ft_int16      = 4;
__declspec(selectany) extern const uint32_t ft_uint24     = 5;
__declspec(selectany) extern const uint32_t ft_int24      = 6;
__declspec(selectany) extern const uint32_t ft_uint32     = 7;
__declspec(selectany) extern const uint32_t ft_int32      = 8;
__declspec(selectany) extern const uint32_t ft_uint48     = 9;
__declspec(selectany) extern const uint32_t ft_int48      = 10;
__declspec(selectany) extern const uint32_t ft_uint56     = 11;
__declspec(selectany) extern const uint32_t ft_int56      = 12;
__declspec(selectany) extern const uint32_t ft_uint64     = 13;
__declspec(selectany) extern const uint32_t ft_int64     = 14;

__declspec(selectany) extern const uint32_t ft_float      = 24;
__declspec(selectany) extern const uint32_t ft_double     = 25;
__declspec(selectany) extern const uint32_t ft_string     = 17;
__declspec(selectany) extern const uint32_t ft_hex_string = 18;
__declspec(selectany) extern const uint32_t ft_bin_string = 19;
__declspec(selectany) extern const uint32_t ft_bytes      = 20;
__declspec(selectany) extern const uint32_t ft_char       = 22;
__declspec(selectany) extern const uint32_t ft_bitset     = 23;
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
__declspec(selectany) extern const uint32_t base_string  = 8;

/* Byte separators  when ft == ft_bytes */
/* hexadecimal bytes with a period (.) between each byte */
__declspec(selectany) extern const uint32_t sep_dot   = 32;
__declspec(selectany) extern const uint32_t sep_dash  = 33;
__declspec(selectany) extern const uint32_t sep_colon = 34;
__declspec(selectany) extern const uint32_t sep_space = 35;

inline uint32_t get(uint32_t d) { return d & 0xff; }

} // namespace fd

struct data_t {
    uint8_t* p;
    union {
        uint64_t val;
        int      length;
    };
    uint8_t  get_uint7() const { return (p ? *p : (uint8_t) val) & 0x7f; };
    uint8_t  get_uint8() const { return p ? *p : (uint8_t) val; };

    uint16_t get_uint16(uint32_t e = enc::be) const {
        // always use big-endian
        return p ? n2uint16(p) : (uint16_t)val;
    };
    uint32_t get_uint24(uint32_t e = enc::be)const{
        return p ? n2uint24(p) : uint32_t(val & 0xFFFFFF);
    }
    uint32_t get_uint32(uint32_t e = enc::be) const{
        return p ? n2uint32(p) : (uint32_t) val;
    };
    uint64_t get_uint48(uint32_t e = enc::be) const { return p ? n2uint48(p) : val; };
    uint64_t get_uint64(uint32_t e = enc::be) const { return p ? n2uint64(p) : val; };
    uint64_t get_val(uint32_t e= enc::be)const{
        if (!p) return val;
        if (length<=0) return 0;
        if (length==1) return get_uint8();
        if (length ==2) return get_uint16();
        if (length == 3) return get_uint24();
        if (length == 4) return get_uint32();
        if (length == 6) return get_uint48();
        if (length == 8) return get_uint64();
    }
};

using std::string;
typedef std::string (*printer_t)(const field_meta*, data_t);

struct field_meta {
    const char*              name;       /* full name of this field */
    const char*              abbrev;     /* abbreviated name of this field */
    uint32_t                 ftype;       /* field_type::*/
    uint32_t                 display;    /* one of base_ */
    const val_string*        val_strings;
    const true_false_string* tf_strings;
    const range_string*      range_strings;
    uint64_t                 bitmask; /* bitmask of interesting bits */

    string format(data_t d, uint32_t enc) const;
};
std::string formats(const char* format, ...);
std::string vformat(const char* format, va_list);

const char* find_val_string(const val_string* vstr, uint32_t id, const char*missing="Unknown");
const char* find_r_string(const range_string* rstr, uint32_t id, const char*missing="Unknown");
std::vector< std::string > find_bitset_string(const val_string* vstr, uint32_t bits);

std::string join(const std::vector< std::string >& strs, const char* sep = " ");

std::string print_dec(data_t v, bool with_comma = true);
std::string print_hex(data_t v, bool with_prefix = true);
std::string print_bits(data_t);
std::string print_dec_hex(data_t v, bool with_prefix = false, bool with_comma = true);
std::string print_hex_dec(data_t v, bool with_prefix = false, bool with_comma = false);
std::string print_string(data_t v);

std::string printer_dec(const field_meta*, data_t v);
std::string printer_hex(const field_meta*, data_t v);
std::string printer_bits(const field_meta*, data_t v);
std::string printer_string(const field_meta*, data_t v);
std::string printer_bytes(const field_meta*, data_t v);
