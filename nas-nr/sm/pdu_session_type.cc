#include "../dissect_sm_msg.hh"
#include "../ber.hh"
#include "../common.hh"

// Selected PDU session type    PDU session type 9.11.4.11
extern const element_meta sm::selected_pdu_session_type = {
    0x90,
    "Selected PDU session type",
    sm::dissect_pdu_session_type,
    nullptr,
};

// PDU session type    PDU session type 9.11.4.11
extern const element_meta sm::pdu_session_type = {
    0x90,
    "PDU session type",
    sm::dissect_pdu_session_type,
    nullptr,
};

/*  9.11.4.10    PDU address  */
const value_string pdu_session_type_values[] = {
    {0x1, "IPv4"},
    {0x2, "IPv6"},
    {0x3, "IPv4v6"},
    {0, nullptr},
};

const field_meta sm::hf_pdu_session_type = {
    "PDU session type",
    "nas.nr.sm.pdu.session.type",
    ft::ft_uint8,
    fd::base_dec,
    pdu_session_type_values,
    nullptr,
    nullptr,
    0x0f,
};

// Selected PDU session type    PDU session type 9.11.4.11
int sm::dissect_pdu_session_type(dissector d, context* ctx) {
    const use_context uc(ctx, "selected-pdu-session-type", d, -1);

    (void) d.add_item(1, &hf_pdu_session_type, enc::be);
    d.step(1);

    return 1;
}

const val_string pdu_session_id_values[] = {
    {0x00, "No PDU session identity assigned"},
    {0x01, "Reserved"},
    {0x02, "Reserved"},
    {0x03, "Reserved"},
    {0x04, "Reserved"},
    {0x05, "PDU session identity value 5"},
    {0x06, "PDU session identity value 6"},
    {0x07, "PDU session identity value 7"},
    {0x08, "PDU session identity value 8"},
    {0x09, "PDU session identity value 9"},
    {0x0a, "PDU session identity value 10"},
    {0x0b, "PDU session identity value 11"},
    {0x0c, "PDU session identity value 12"},
    {0x0d, "PDU session identity value 13"},
    {0x0e, "PDU session identity value 14"},
    {0x0f, "PDU session identity value 15"},
    {0, nullptr},
};
const field_meta hfm_pdu_session_id = {
    "PDU session identity",
    "nas.nr.pdu.session.id",
    ft::ft_uint8,
    fd::base_dec,
    pdu_session_id_values,
    nullptr,
    nullptr,
    0x0,
};
const field_meta* nas::hf_pdu_session_id = &hfm_pdu_session_id;
