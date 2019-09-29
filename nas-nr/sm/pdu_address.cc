#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"


const ipv6_field hf_pdu_address_ipv6 = {
    "PDU address information",

};

extern const tag_field hf_pdu_session_type;

extern const ipv4_field hf_pdu_address_ipv4 = {
    "PDU address information",
};

// PDU address 9.11.4.10 15 octets
int sm::dissect_pdu_address(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-address", d, 8);

    const auto val  = static_cast< uint32_t >(d.tvb->uint8(d.offset));
    (void) d.add_item(&hf_pdu_session_type);
    d.step(1);

    /* PDU address information */
    switch (val) {
    case 1: // ipv4
        (void) d.add_item(&hf_pdu_address_ipv4);
        d.step(4);
        break;
    case 2: // ipv6
        /* If the PDU session type value indicates IPv6, the PDU address information in
         * octet 4 to octet 11 contains an interface identifier for the IPv6 link local
         * address.
         */
        (void) d.add_item(&hf_pdu_address_ipv6, 8);
        d.step(8);
        break;
    case 3: // ipv6 and ipv4
        /* If the PDU session type value indicates IPv4v6, the PDU address information in
         * octet 4 to octet 11 contains an interface identifier for the IPv6 link local
         * address and in octet 12 to octet 15 contains an IPv4 address.
         */
        (void) d.add_item(&hf_pdu_address_ipv6, 8);
        d.step(8);
        (void) d.add_item(&hf_pdu_address_ipv4);
        d.step(4);
        break;
    default:
        diag("unknown pdu address %d", val);
    }
    return uc.length;
}


