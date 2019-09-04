#pragma once
#include "../core.hh"

namespace pdu_ses {
int dissect_sm_congestion_reattempt(dissector d, context* ctx);
int dissect_always_on_pdu_ses_req(dissector d, context* ctx);

extern const element_meta sm_congestion_reattempt;

extern const element_meta
    always_on_pdu_ses_req; //  Always-on PDU session requested  9.11.4.4
}
