#include "../config.hh"
#include "pdu_ses.hh"


const element_meta pdu_ses::sm_congestion_reattempt = {
    0x61u,
    "5GSM congestion re-attempt indicator",
    dissect_sm_congestion_reattempt,
    nullptr,
};

int pdu_ses::dissect_sm_congestion_reattempt(dissector d, context* ctx) {
    return d.length;
}

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
