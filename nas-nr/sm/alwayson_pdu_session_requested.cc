#include "../dissect_sm_msg.hh"

//  Always-on PDU session requested  9.11.4.4
extern const element_meta sm::alwayson_pdu_session_requested = {
    0xB0,
    "Always-on PDU session requested",
    sm::dissect_alwayson_pdu_session_requested,
    nullptr,
};

const tf_string tfs_alwayson_pdu_session_requested = {
    "Always-on PDU session requested",
    "Always-on PDU session not requested",
};

const field_meta hf_alwayson_pdu_session_requested = {
    "APSR","nas.nr.sm.alwayson.pdu.session.requested",
    ft::ft_boolean, fd::base_dec,
    nullptr,
    &tfs_alwayson_pdu_session_requested,
    nullptr,
    0x01,
};

// 9.11.4.4 Always-on PDU session requested
int sm::dissect_alwayson_pdu_session_requested(dissector d, context* ctx) {
    const use_context uc(ctx, "alwayson-pdu-session-requested", d, -1);

    d.add_item(1, &hf_alwayson_pdu_session_requested, enc::be);
    d.step(1);

    return 1;
}

struct alwayson_pdu_session_requested_t {
    uint8_t requested;
};
