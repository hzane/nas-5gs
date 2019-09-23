#include "../common/dissect_sm_msg.hh"

// 9.11.4.14    Session-AMBR
int sm::dissect_session_ambr(dissector d, context* ctx) {
    const use_context uc(ctx, "session-ambr", d, 0);

    /* Unit for Session-AMBR for downlink octet 3*/
    /* Session-AMBR for downlink (octets 4 and 5) */

    (void) d.add_item(3, &hf_session_ambr_downlink, enc::be);
    d.step(3);

    (void) d.add_item(3, &hf_session_ambr_uplink, enc::be);
    d.step(3);

    return uc.length;
}

// Session-AMBR 9.11.4.14
const element_meta sm::session_ambr = {
    0x2A,
    "Session AMBR",
    sm::dissect_session_ambr,
    nullptr,
};


//  *      9.11.4.14    Session-AMBR
extern const value_string sm::ambr_values[] = {
    {0x00, "value is not used"},
    {0x01, "value is incremented in multiples of 1 Kbps"},
    {0x02, "value is incremented in multiples of 4 Kbps"},
    {0x03, "value is incremented in multiples of 16 Kbps"},
    {0x04, "value is incremented in multiples of 64 Kbps"},
    {0x05, "value is incremented in multiples of 256 kbps"},
    {0x06, "value is incremented in multiples of 1 Mbps"},
    {0x07, "value is incremented in multiples of 4 Mbps"},
    {0x08, "value is incremented in multiples of 16 Mbps"},
    {0x09, "value is incremented in multiples of 64 Mbps"},
    {0x0a, "value is incremented in multiples of 256 Mbps"},
    {0x0b, "value is incremented in multiples of 1 Gbps"},
    {0x0c, "value is incremented in multiples of 4 Gbps"},
    {0x0d, "value is incremented in multiples of 16 Gbps"},
    {0x0e, "value is incremented in multiples of 64 Gbps"},
    {0x0f, "value is incremented in multiples of 256 Gbps"},
    {0x10, "value is incremented in multiples of 1 Tbps"},
    {0x11, "value is incremented in multiples of 4 Tbps"},
    {0x12, "value is incremented in multiples of 16 Tbps"},
    {0x13, "value is incremented in multiples of 64 Tbps"},
    {0x14, "value is incremented in multiples of 256 Tbps"},
    {0x15, "value is incremented in multiples of 1 Pbps"},
    {0x16, "value is incremented in multiples of 4 Pbps"},
    {0x17, "value is incremented in multiples of 16 Pbps"},
    {0x18, "value is incremented in multiples of 64 Pbps"},
    {0x19, "value is incremented in multiples of 256 Pbps"},
    {0, nullptr},
};

const field_meta sm::hf_session_ambr_downlink_unit = {
    "Unit for Session-AMBR for downlink",
    "nas.nr.sm.unit.for.session.ambr.downlink",
    ft::ft_uint8,
    fd::base_dec,
    sm::ambr_values,
    nullptr,
    nullptr,
    0x0,
};

const field_meta sm::hf_session_ambr_uplink_unit = {
    "Unit for Session-AMBR for uplink",
    "nas.nr.sm.unit.for.session.ambr.uplink",
    ft::ft_uint8,
    fd::base_dec,
    sm::ambr_values,
    nullptr,
    nullptr,
    0x0,
};

const field_meta sm::hf_session_ambr_downlink = {
    "Session-AMBR for downlink",
    "nas.nr.sm.session.ambr.downlink",
    ft::ft_bytes,
    fd::ambr,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta sm::hf_session_ambr_uplink = {
    "Session-AMBR for uplink",
    "nas.nr.sm.session.ambr.uplink",
    ft::ft_bytes,
    fd::ambr,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
