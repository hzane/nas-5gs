#include <cstdarg>
#include <cassert>
#include <iomanip>
#include <sstream>
#include <vector>
#include <bitset>
#include "field_meta.hh"
#include "tvbuff.hh"

string field_meta::format(data_t d, uint32_t enc) const {
    if (d.p && d.length == 0) return string();
    if (ftype == ft::none || ftype == ft::protocol) return string();

    if (ftype == ft::ft_boolean) {
        auto v  = d.get_uint8();
        if (bitmask) v = v & bitmask;

        auto tf = this->tf_strings ? tf_strings : &true_false;
        return v ? tf->true_string : tf->false_string;
    }
    if (ftype == ft::ft_char) {
        return formats("%c", d.get_uint8());
    }

    if (ftype == ft::ft_string) {
        assert(d.p);
        return std::string((const char*) d.p, d.length);
    }

    if (val_strings && ftype == ft::ft_bitset) {
        auto flags = find_bitset_string(val_strings, (uint32_t)d.get_val());
        return join(flags, " | ");
    }

    if (val_strings) {
        auto v = (uint32_t) d.get_val();
        auto s = find_val_string(val_strings, v);
        return formats("%s (%#x)", s, v);
    }

    if (ftype == ft::ft_bytes && (display&fd::base_bin)==fd::base_bin){
        assert(d.p);
        return format_bit(d.p, d.length, " ");
    }

    if (ftype == ft::ft_bin_string){
        assert(d.p);
        return format_bit(d.p, d.length, " ");
    }

    if (ftype == ft::ft_bytes || ftype == ft::ft_hex_string) {
        assert(d.p);
        const char *sep = " ";
        if ((display & 0xe0) == fd::sep_dot) sep = ".";
        if ((display & 0xe0) == fd::sep_dash) sep = "-";
        if ((display & 0xe0) == fd::sep_colon) sep = ";";
        return format_hex(d.p, d.length, sep);
    }

    // ft_float, ft_double

    auto v = d.get_val();
    if (bitmask) v = v & bitmask;
    return format_int(v, ftype, display);
}
