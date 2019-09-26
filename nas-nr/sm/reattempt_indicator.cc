#include "../common/dissector.hh"
#include "../common/use_context.hh"

// 9.11.4.17	Re-attempt indicator
int dissect_reattempt_indicator(dissector d, context* ctx) {
    const use_context uc(ctx, "reattempt-indicator", d, -1);

    return 1;
}
