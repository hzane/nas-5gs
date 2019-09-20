#include "../dissect_mm_msg.hh"
#include "../config.hh"

/*  8.2.29 5GMM status */
int mm::dissect_mm_status(dissector d, context* ctx) {
    const use_context uc(ctx, "5gmm-status", d, -1);

    /* Direction: both*/

    /* 5GMM cause 9.11.3.2    M    V    1 */
    (void) dissect_nrmm_cause(d, ctx);
    d.step(1);

    return 1;
}
