#include "../dissect_sm_msg.hh"

//  Always-on PDU session requested  9.11.4.4
extern const element_meta sm::alwayson_pdu_session_req = {
    0xB0,
    "Always-on PDU session requested",
    sm::dissect_always_on_pdu_ses_req,
    nullptr,
};

const tf_string tfs_apsr = {
    "Always-on PDU session requested",
    "Always-on PDU session not requested",
};

const field_meta hf_apsr = {
    "APSR","nas.nr.sm.apsr",
    ft::ft_boolean, fd::base_dec,
    nullptr,
    &tfs_apsr,
    nullptr,
    0x01,
};

// 9.11.4.4 Always-on PDU session requested
int sm::dissect_always_on_pdu_ses_req(dissector d, context* ctx) {
    const use_context uc(ctx, "alwayson-pdu-session-requested", d, -1);

    d.add_item(1, &hf_apsr, enc::be);
    d.step(1);

    return 1;
}
