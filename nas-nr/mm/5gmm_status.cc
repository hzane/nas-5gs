#include "../dissect_mm_msg.hh"

/*  8.2.29 5GMM status */
int mm::dissect_mm_status(dissector d, context* ctx) {
    const use_context uc(ctx, "5gmm-status", d, -1);

    /* Direction: both*/

    /* 5GMM cause 9.11.3.2    M    V    1 */
    (void) dissect_mm_cause(d, ctx);
    d.step(1);

    return 1;
}

struct nrmm_cause_t {
    uint8_t _;
};

struct mm_status_t {
    nrmm_cause_t cause;
};
