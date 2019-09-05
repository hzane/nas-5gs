#include "../dissect_sm_msg.hh"


// Selected PDU session type    PDU session type 9.11.4.11
extern const element_meta sm::pdu_ses_type = {
    0x90,
    "Selected PDU session type",
    dissect_pdu_ses_type,
    nullptr,
};

/*  9.11.4.10    PDU address  */
const value_string nas_5gs_sm_pdu_ses_type_vals[] = {
    {0x1, "IPv4"},
    {0x2, "IPv6"},
    {0x3, "IPv4v6"},
    {0, nullptr},
};

const field_meta sm::hf_sm_pdu_ses_type = {
    "PDU session type",
    "nas_5gs.sm.pdu_ses_type",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_sm_pdu_ses_type_vals),
    nullptr,
    nullptr,
    0x0f,
};

// Selected PDU session type    PDU session type 9.11.4.11
int sm::dissect_pdu_ses_type(dissector d, context* ctx) {
    d.add_item(1, &hf_sm_pdu_ses_type, enc::be);
    return 1;
}
