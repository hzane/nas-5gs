#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"

//  Always-on PDU session requested  9.11.4.4
extern const element_meta sm::alwayson_pdu_session_requested = {
    0xB0,
    "Always-on PDU session requested",
    sm::dissect_alwayson_pdu_session_requested,
};

const bool_field hf_alwayson_pdu_session_requested = {
    "APSR","nas.nr.sm.alwayson.pdu.session.requested",
    0x01,
    "Always-on PDU session not requested",
    "Always-on PDU session requested",
};

// 9.11.4.4 Always-on PDU session requested
int sm::dissect_alwayson_pdu_session_requested(dissector d, context* ctx) {
    const use_context uc(ctx, "alwayson-pdu-session-requested", d, -1);

    d.add_item(&hf_alwayson_pdu_session_requested);
    d.step(1);

    return 1;
}
