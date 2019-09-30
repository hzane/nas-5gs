#include "../common/ber.hh"
#include "../common/common.hh"
#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"


/*  9.11.4.10    PDU address  */
const v_string pdu_session_type_values[] = {
    {0x1, "IPv4"},
    {0x2, "IPv6"},
    {0x3, "IPv4v6"},
    {0, nullptr},
};

extern const tag_field hf_pdu_session_type = {
    "PDU session type",
    0x0f,
    pdu_session_type_values,
};

// Selected PDU session type    PDU session type 9.11.4.11
int sm::dissect_pdu_session_type(dissector d, context* ctx) {
    const use_context uc(ctx, "selected-pdu-session-type", d, -1);

    (void) d.add_item(&hf_pdu_session_type);
    d.step(1);

    return 1;
}

const v_string pdu_session_id_values[] = {
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
const tag_field hfm_pdu_session_id = {
    "PDU session identity",
    0x0,
    pdu_session_id_values,
};
