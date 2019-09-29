#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"

// This bit indicates network's capability for Ethernet PDN type in S1 mode.
const bool_field hf_epts1 = {
    "Ethernet PDN type in S1 mode (IEPT-S1)",
    0,
    "Ethernet PDN type in S1 mode not supported",
    "Ethernet PDN type in S1 mode supported",
};

// 5GSM network feature support 9.11.4.18
int dissect_sm_network_feature_support(dissector d, context* ctx){
    const use_context uc(ctx, "5gsm-network-feature-support", d, 12);

    (void) d.add_item(&hf_epts1);
    d.step(1);

    return uc.length;
}

