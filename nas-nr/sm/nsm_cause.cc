#include "../common/dissector.hh"
#include "../common/use_context.hh"

// 5GSM cause 9.11.4.2
int dissect_nrsm_cause(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "5gsm-cause", -1);

    return 1;
}
