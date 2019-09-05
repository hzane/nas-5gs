#include "../dissect_sm_msg.hh"

// 5GSM cause 9.11.4.2
int sm::dissect_sm_cause(dissector d, context* ctx) {
    d.add_item(1, &hf_sm_cause, enc::be);

    return 1;
}
