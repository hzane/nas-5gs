#include "../dissect_sm_msg.hh"

// 5GSM congestion re-attempt indicator 9.11.4.21
const element_meta sm::sm_congestion_reattempt = {
    0x61u,
    "5GSM congestion re-attempt indicator",
    dissect_sm_congestion_reattempt,
    nullptr,
};

// 5GSM congestion re-attempt indicator 9.11.4.21
int sm::dissect_sm_congestion_reattempt(dissector d, context* ctx) {
    d.add_item(1, &hf_abo, enc::be);
    d.step(1);
    return 1;
}
