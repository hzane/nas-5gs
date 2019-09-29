#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"

// ABO (All PLMNs Back-off timer)
const bool_field hf_all_plmns_backoff_timer = {
    "All PLMNs Back-off timer (ABO)",
    0x01u,
    "The back-off timer is applied in the registered PLMN.",
    "The back-off timer is applied in all PLMNs.",
};

// 5GSM congestion re-attempt indicator 9.11.4.21
int sm::dissect_sm_congestion_reattempt(dissector d, context* ctx) {
    const use_context uc(ctx, "5gsm-congestion-reattempt-indicator", d, -1);

    // ABO (All PLMNs Back-off timer)
    d.add_item(&hf_all_plmns_backoff_timer);
    d.step(1);
    return 1;
}


