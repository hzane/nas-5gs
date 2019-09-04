#include "../config.hh"
#include "pdu_ses.hh"

// 5GSM congestion re-attempt indicator 9.11.4.21
const element_meta pdu_ses::sm_congestion_reattempt = {
    0x61u,
    "5GSM congestion re-attempt indicator",
    dissect_sm_congestion_reattempt,
    nullptr,
};
const true_false_string tfs_abo = {
    "The back-off timer is applied in all PLMNs.",
    "The back-off timer is applied in the registered PLMN.",
};
const field_meta hf_abo = {
    "ABO",
    "",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    &tfs_abo,
    nullptr,
    0,
};

// 5GSM congestion re-attempt indicator 9.11.4.21
int pdu_ses::dissect_sm_congestion_reattempt(dissector d, context* ctx) {
    d.add_item(1, &hf_abo, enc::be);
    d.step(1);
    return 1;
}

//  Always-on PDU session requested  9.11.4.4
extern const element_meta pdu_ses::always_on_pdu_ses_req = {
    0xB0,
    "Always-on PDU session requested",
    dissect_always_on_pdu_ses_req,
    nullptr,
};


// 9.11.4.4 Always-on PDU session requested
int pdu_ses::dissect_always_on_pdu_ses_req(dissector d, context* ctx) {
    diag("no dissect\n");
    return d.length;
}
