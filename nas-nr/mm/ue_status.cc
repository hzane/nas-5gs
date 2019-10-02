#include "../common/dissector.hh"
#include "../common/use_context.hh"

// 9.11.3.56
int dissect_ue_status(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "ue-status", -1);

    /* 0     0     0     0     0     0 Spare    S1  mode reg */
    return 1;
}
