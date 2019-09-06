#include "../dissect_sm_msg.hh"


// PDU address 9.11.4.10
extern const element_meta sm::pdu_address = {
    0x29,
    "PDU address",
    dissect_pdu_address,
    nullptr,
};

const field_meta hf_pdu_addr_ipv4 = {
    "PDU address information",
    "nas_5gs.sm.pdu_addr_inf_ipv4",
    ft::ft_uint32,
    fd::ipv4,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta sm::hf_pdu_addr_ipv6 = {
    "PDU address information",
    "nas_5gs.sm.pdu_addr_inf_ipv6",
    ft::ft_bytes,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

// PDU address 9.11.4.10 15 octets
int sm::dissect_pdu_address(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-address", d, 8);
    
    const auto val  = static_cast< uint32_t >(d.tvb->uint8(d.offset));
    auto     item = d.add_item(1, &hf_sm_pdu_ses_type, enc::be);
    d.step(1);

    /* PDU address information */
    switch (val) {
    case 1: // ipv4
        d.add_item(4, &hf_pdu_addr_ipv4, enc::be);
        d.step(4);
        break;
    case 2: // ipv6
        /* If the PDU session type value indicates IPv6, the PDU address information in
         * octet 4 to octet 11 contains an interface identifier for the IPv6 link local
         * address.
         */
        d.add_item(8, &hf_pdu_addr_ipv6, enc::na);
        d.step(8);
        break;
    case 3: // ipv6 and ipv4
        /* If the PDU session type value indicates IPv4v6, the PDU address information in
         * octet 4 to octet 11 contains an interface identifier for the IPv6 link local
         * address and in octet 12 to octet 15 contains an IPv4 address.
         */
        d.add_item(8, &hf_pdu_addr_ipv6, enc::na);
        d.step(8);
        d.add_item(4, &hf_pdu_addr_ipv4, enc::be);
        d.step(4);
        break;
    default:
        diag("unknown pdu address %d", val);
    }
    return uc.length;
}

const field_meta sm::hf_pdu_addr_ipv4 = {
    "PDU address information",
    "nas_5gs.sm.pdu_addr_inf_ipv4",
    ft::ft_uint32, // FT_IPv4,
    fd::ipv4,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
