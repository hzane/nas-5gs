#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"
#include "common/packet.hh"

/* 8.3.16 5GSM status */
int sm::dissect_sm_status(dissector d, context* ctx) {
    const use_context uc(ctx, "5gsm-status", d, -1);

    /* Direction: both */
    // both_link(d.packet);

    /* 5GSM cause    5GSM cause 9.11.4.1    M    V    1 */
    (void) dissect_nrsm_cause(d, ctx);
    d.step(1);

    return 1;
}

