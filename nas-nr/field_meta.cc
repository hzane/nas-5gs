#include "field_meta.hh"
#include "tvbuff.hh"

string field_meta::format(const uint8_t* p, int length, uint32_t enc) const {

    if (!p || length <= 0) return string();
    if (enc == enc::na || enc::none) {
        return string();
    }
    if (ft::is_integer(ftype)) {
        auto v = n2_uint(p, length);
        return format(v);
    }
    if (ftype == ft::none) return string();
    if (ftype == ft::protocol || ftype == ft::ft_struct || ftype == ft::ft_expert)
        return string();
    if (display == fd::base_none) return string();

    if (ftype == ft::ft_boolean) {
        auto v  = *p;
        if (bitmask)
            v = (v & bitmask);

        const auto tf = this->tf_strings ? tf_strings : &true_false;
        return formats("%s (%d)", v ? tf->true_string : tf->false_string, v ? 1 : 0);
    }

    switch (display) {
        case fd::base_string: return string(reinterpret_cast< const char* >(p), length);
        case fd::base_bin: return format_bit(p, length, " ");
        case fd::base_hex: return format_hex(p, length, " ");
        case fd::sep_colon: return format_hex(p, length, ";");
        case fd::sep_dash: return format_hex(p, length, "-");
        case fd::sep_dot: return format_hex(p, length, ".");
        case fd::base_char:
            return formats("%c", static_cast< char >(*p));
        case fd::imei:
            return imei_string(p, length);
        case fd::bcd:
            return bcd_string(p, length);
        case fd::bstrn:
            return bstrn_string(p, length);
        case fd::sep_space:
            return format_hex(p, length, " ");
        case fd::bits7:
            return bits7_string(p, length);
        case fd::ipv4:
            return formats("%u.%u.%u.%u", p[0], p[1], p[2], p[3]);
        case fd::link_local_address:
            return ipv6_link_local_string(p, length);
        case fd::ipv6:
            return ipv6_string(p, length);
        case fd::mac:
            return format_hex(p, length, ":");
        case fd::mcc:
            return mcc_string(p, length);
        case fd::mnc:
            return mcc_mnc_string(p, length);
        case fd::timezone_time:
            return timezone_time_string(p, length);
        case fd::timezone:
            return timezone_string(p);
        case fd::ambr:
            return ambr_string(p, length);
        case fd::extl:
            return formats("%d", ext_length(p));
        case fd::timer:
            return gprs_timer_string(p, length);
        case fd::timer3:
            return gprs_timer3_string(p, length);
        case fd::timer2:
            return gprs_timer2_string(p, length);
        default:
            return formats("data %d bytes", length);
    }

}

string field_meta::format(uint64_t v) const {
    if (ftype == ft::none || ftype == ft::protocol) return string();
    if (display == fd::base_none) return string();

    if (ftype == ft::ft_boolean || tf_strings) {
        const auto tf = this->tf_strings ? tf_strings : &true_false;
        return formats(
            "%s (%d)", v ? tf->true_string : tf->false_string, v ? 1 : 0);
    }

    if (display == fd::base_char) {
        return formats("%c", static_cast< char >(v));
    }

    if (val_strings && display == fd::base_bit) {
        const auto flags = find_bits_string(val_strings, static_cast< uint32_t >(v));
        return join(flags, " | ");
    }

    if (val_strings) {
        auto s = find_val_string(val_strings, uint32_t(v));
        return formats("%s (%#x)", s, uint32_t(v));
    }

    if (range_strings){
        const auto s = find_r_string(range_strings, uint32_t(v));
        return formats("%s (%#x)", s, uint32_t(v));
    }

    if(display == fd::timer) {
        auto v8 = static_cast< uint8_t >(v);
        return gprs_timer_string(&v8, 1);
    }

    if (display == fd::timer3) {
        return gprs_timer3_format(uint8_t(v));
    }

    if (display == fd::timer2){
        return gprs_timer2_format(uint8_t(v));
    }

    if (display == fd::base_bin) {
        return format_int_bit_mask(ftype, v, bitmask, nullptr);
    }

    if (display == fd::right) {
        return formats("%1x", (v & 0x0fu));
    }
    if (display == fd::left) {
        return formats("%1x", (v & 0xf0u) >> 4u);
    }

    return format_int(v, ftype, display);
}
