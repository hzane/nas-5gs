#include "field_meta.hh"
#include "format.hh"
#include "buff_view.hh"

string field_meta::format(const uint8_t* p, int length) const {

    if (!p || length <= 0) return string();

    if (ft::is_integer(typi)) {
        auto v = n2_uint(p, length);
        return format(v);
    }
    if (typi == ft::none) return string();
    if (typi == ft::protocol || typi == ft::ft_struct || typi == ft::ft_expert)
        return string();
    if (display == fd::base_none) return string();

    if (typi == ft::ft_boolean) {
        auto v  = *p;
        if (bitmask)
            v = (v & bitmask);

        const auto tf = this->tf_strings ? tf_strings : &true_false;
        return formats("%s (%d)", v ? tf->true_string : tf->false_string, v ? 1 : 0);
    }

    switch (display) {
        case fd::base_string: return string(reinterpret_cast< const char* >(p), length);
        case fd::base_bin: return bitstring(p, length<<3, " ");
        case fd::base_hex: return hstring(p, length, " ");
        case fd::sep_colon: return hstring(p, length, ";");
        case fd::sep_dash: return hstring(p, length, "-");
        case fd::sep_dot: return hstring(p, length, ".");
        case fd::base_char:
            return formats("%c", static_cast< char >(*p));
        case fd::imei:
            return imei_string(p, length);
        case fd::bcd:
            return bcd_string(p, length);
        case fd::bstrn:
            return apn_string(p, length);
        case fd::sep_space:
            return hstring(p, length, " ");
        case fd::bits7:
            return sms_string(p, length);
        case fd::ipv4:
            return formats("%u.%u.%u.%u", p[0], p[1], p[2], p[3]);
        case fd::link_local_address:
            return ipv6_link_local_string(p, length);
        case fd::ipv6:
            return ipv6_string(p, length);
        case fd::mac:
            return hstring(p, length, ":");
        case fd::mcc:
            return mcc_string(p, length);
        case fd::mnc:
            return mnc_string(p, length);
        case fd::timezone_time:
            return utc_string(p, length);
        case fd::timezone:
            return gmt_string(p);
        case fd::ambr:
            return ambr_string(p, length);
        case fd::extl:
            return formats("%d", ext_length(p));
        case fd::timer:
            return gprs_timer_string(*p);
        case fd::timer3:
            return gprs_timer_3_string(*p);
        case fd::timer2:
            return gprs_timer_2_string(*p);
        default:
            return formats("data %d bytes", length);
    }

}

string field_meta::format(uint64_t v) const {
    if (typi == ft::none || typi == ft::protocol) return string();
    if (display == fd::base_none) return string();

    if (typi == ft::ft_boolean || tf_strings) {
        const auto tf = this->tf_strings ? tf_strings : &true_false;
        return formats(
            "%s (%d)", v ? tf->true_string : tf->false_string, v ? 1 : 0);
    }

    if (display == fd::base_char) {
        return formats("%c", static_cast< char >(v));
    }

    if (v_strings && display == fd::base_bit) {
        return bits_string(v_strings, static_cast< uint32_t >(v));
    }

    if (v_strings) {
        return vstring(v_strings, uint32_t(v));
    }

    if (range_strings){
        return rstring(range_strings, uint32_t(v));
    }

    if(display == fd::timer) {
        auto v8 = static_cast< uint8_t >(v);
        return gprs_timer_string(v8);
    }

    if (display == fd::timer3) {
        return gprs_timer_3_string(uint8_t(v));
    }

    if (display == fd::timer2){
        return gprs_timer_2_string(uint8_t(v));
    }

    if (display == fd::right) {
        return formats("%1x", (v & 0x0fu));
    }
    if (display == fd::left) {
        return formats("%1x", (v & 0xf0u) >> 4u);
    }
    return formats("%d (%x)", v);
}

