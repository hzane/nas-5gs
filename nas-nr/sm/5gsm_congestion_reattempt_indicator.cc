#include "../dissect_sm_msg.hh"

// 5GSM congestion re-attempt indicator 9.11.4.21
const element_meta sm::sm_congestion_reattempt = {
    0x61u,
    "5GSM congestion re-attempt indicator",
    sm::dissect_sm_congestion_reattempt,
    nullptr,
};

// 5GSM congestion re-attempt indicator 9.11.4.21
int sm::dissect_sm_congestion_reattempt(dissector d, context* ctx) {
    const use_context uc(ctx, "5gsm-congestion-reattempt-indicator", d, -1);

    // ABO (All PLMNs Back-off timer)
    d.add_item(1, &hf_all_plmns_backoff_timer, enc::be);
    d.step(1);
    return 1;
}

struct sm_congestion_reattempt_t {
    uint8_t abo;
};

const true_false_string tfs_abo = {
    "The back-off timer is applied in all PLMNs.",
    "The back-off timer is applied in the registered PLMN.",
};

// ABO (All PLMNs Back-off timer)
const field_meta sm::hf_all_plmns_backoff_timer = {
    "All PLMNs Back-off timer (ABO)",
    "nas.nr.sm.abo",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    &tfs_abo,
    nullptr,
    0x01u,
};
