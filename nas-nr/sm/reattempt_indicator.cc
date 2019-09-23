#include "../common/dissect_sm_msg.hh"

const tf_string tfs_ratc = {
    "UE is not allowed to re-attempt the procedure in S1 mode",
    "UE is allowed to re-attempt the procedure in S1 mode",
};

const field_meta hf_ratc = {
    "RATC",
    "nas.nr.ratc",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_ratc,
    nullptr,
    0x01u,
};

const tf_string tfs_eplmnc = {
    "UE is not allowed to re-attempt the procedure in an equivalent PLMN",
    "UE is allowed to re-attempt the procedure in an equivalent PLMN",
};
const field_meta hf_eplmnc = {
    "EPLMNC",
    "nas.nr.eplmnc",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_eplmnc,
    nullptr,
    0x02u,
};

// 9.11.4.17	Re-attempt indicator
int sm::dissect_reattempt_indicator(dissector d, context* ctx) {
    const use_context uc(ctx, "reattempt-indicator", d, -1);

    (void) d.add_item(1, &hf_ratc, enc::be);
    (void) d.add_item(1, &hf_eplmnc, enc::be);
    d.step(1);

    return 1;
}

struct reattempt_indicator_t {
    uint8_t ratc;
    uint8_t eplmnc;
};
