#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.3.16 5GSM status */
int dissect_sm_status(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "5gsm-status", -1);

    /* Direction: both */
    // both_link(d.pinfo);

    /* 5GSM cause    5GSM cause 9.11.4.1    M    V    1 */

    return 1;
}
result_t de_nsm_status(dissector d, context* ctx, nsm_status_t* ret) {
    const use_context uc(&d, ctx, "nsm-status", 0);
    de_nsm_header(d, ctx, &ret->header);

    de_uint8(d, ctx, &ret->cause).step(d);
    return {uc.consumed()};
}
