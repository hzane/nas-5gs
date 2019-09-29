#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"

const bool_field hf_ratc = {
    "RATC",
    0x01u,
    "UE is allowed to re-attempt the procedure in S1 mode",
    "UE is not allowed to re-attempt the procedure in S1 mode",
};


const bool_field hf_eplmnc = {
    "EPLMNC",
    0x02u,
    "UE is allowed to re-attempt the procedure in an equivalent PLMN",
    "UE is not allowed to re-attempt the procedure in an equivalent PLMN",
};

// 9.11.4.17	Re-attempt indicator
int sm::dissect_reattempt_indicator(dissector d, context* ctx) {
    const use_context uc(ctx, "reattempt-indicator", d, -1);

    (void) d.add_item( &hf_ratc);
    (void) d.add_item( &hf_eplmnc);
    d.step(1);

    return 1;
}
