#include "../dissect_sm_msg.hh"

// SM PDU DN request container 9.11.4.15
const element_meta sm::sm_pdu_dn_req_cont = {
    0xffu,
    "PDU DN request container",
    dissect_pdu_dn_req_cont,
    nullptr,
};

// SM PDU DN request container 9.11.4.15
int sm::dissect_pdu_dn_req_cont(dissector d, context* ctx) { return d.length; }
