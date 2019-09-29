#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"

const bool_field hf_pdu_alwayson_session_ind = {
    "Always-on PDU session indication",
    0x01,
    "Always-on PDU session not allowed"
    "Always-on PDU session allowed",
};

/*  9.11.4.3 Always-on PDU session indication */
int sm::dissect_always_on_pdu_session_indication(dissector d, context* ctx) {
    const use_context uc(ctx, "always-on-pdu-session-indication", d, -1);

    (void) d.add_item(&hf_pdu_alwayson_session_ind);
    d.step(1);

    return 1;
}


// Always-on PDU session indication 9.11.4.3
const element_meta sm::alwayson_pdu_session_indication = {
    0x80,
    "Always-on PDU session indication",
    sm::dissect_always_on_pdu_session_indication,
};

