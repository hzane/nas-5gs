#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

// 9.11.4.17	Re-attempt indicator
result_t die_reattempt_indicator(dissector d, context* ctx, reattempt_indicator_t* ret){
    const use_context uc(&d, ctx, "reattempt-indicator", 0);
    de_uint8(d, ctx, &ret->ratc, 0x01u);
    de_uint8(d, ctx, &ret->eplmnc, 0x02u).step(d);
    return {1};
}