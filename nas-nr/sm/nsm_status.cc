#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.3.16 5GSM status */
int dissect_sm_status(dissector d, context* ctx) {
    const use_context uc(ctx, "5gsm-status", d, -1);

    /* Direction: both */
    // both_link(d.pinfo);

    /* 5GSM cause    5GSM cause 9.11.4.1    M    V    1 */

    return 1;
}
