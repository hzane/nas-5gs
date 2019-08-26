#include <cstdarg>
#include <cassert>
#include <iomanip>
#include <sstream>
#include <vector>
#include <bitset>
#include "field_meta.hh"
#include "tvbuff.hh"

string field_meta::format(const uint8_t*p , int length, uint32_t enc) const {
    if (p && length == 0) return string();
    if (ftype == ft::none || ftype == ft::protocol) return string();

    if (ftype == ft::ft_boolean) {
        auto v  = *p;
        if (bitmask) v = v & bitmask;

        auto tf = this->tf_strings ? tf_strings : &true_false;
        return v ? tf->true_string : tf->false_string;
    }
    if (ftype == ft::ft_char) {
        return formats("%c", (char)*p);
    }
    switch (display){
        case fd::base_string: return string((const char*)p, length);
        case fd::base_bin: return format_bit(p, length, " ");
        case fd::base_hex: return format_hex(p, length, " ");
        case fd::sep_colon: return format_hex(p, length, ";");
        case fd::sep_dash: return format_hex(p, length, "-");
        case fd::sep_dot: return format_hex(p, length, ".");
    }
    if (display == fd::base_string ) {
        return std::string((const char*) p, length);
    }

    return string();
}

string field_meta::format(uint64_t v) const {
    if (bitmask) v = v & bitmask;

    if (ftype == ft::none || ftype == ft::protocol) return string();

    if (ftype == ft::ft_boolean) {
        auto tf = this->tf_strings ? tf_strings : &true_false;
        return v ? tf->true_string : tf->false_string;
    }
    if (tf_strings){
        return v ? tf_strings->true_string: tf_strings->false_string;
    }
    if (ftype == ft::ft_char) {
        return formats("%c", (char)v);
    }

    if (val_strings && display == fd::base_bitset) {
        auto flags = find_bitset_string(val_strings, (uint32_t)v);
        return join(flags, " | ");
    }

    if (val_strings) {
        auto s = find_val_string(val_strings, uint32_t(v));
        return formats("%s (%#x)", s, uint32_t(v));
    }

    if (range_strings){
        auto s = find_r_string(range_strings, uint32_t(v));
        return formats("%s (%#x)", s, uint32_t(v));
    }

    return format_int(v, ftype, display);
}
