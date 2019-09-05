#include "../dissect_sm_msg.hh"

//  Always-on PDU session requested  9.11.4.4
extern const element_meta sm::always_on_pdu_ses_req = {
    0xB0,
    "Always-on PDU session requested",
    dissect_always_on_pdu_ses_req,
    nullptr,
};

// 9.11.4.4 Always-on PDU session requested
int sm::dissect_always_on_pdu_ses_req(dissector d, context* ctx) {
    diag("no dissect\n");
    return d.length;
}
