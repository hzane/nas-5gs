#include "../dissect_sm_msg.hh"

// This bit indicates network's capability for Ethernet PDN type in S1 mode.
const tf_string tfs_epts1 = {
    "Ethernet PDN type in S1 mode supported",
    "Ethernet PDN type in S1 mode not supported",
};

const field_meta hf_epts1 = {
    "Ethernet PDN type in S1 mode (IEPT-S1)",
    "nas.nr.sm.nw.feature.iept.s1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_epts1,
    nullptr,
    0,
};

// 5GSM network feature support 9.11.4.18
int dissect_sm_nw_feature_support(dissector d, context* ctx){
    const use_context uc(ctx, "5gsm-network-feature-support", d, 12);

    (void) d.add_item(1, &hf_epts1, enc::be);
    d.step(1);

    return uc.length;
}

struct sm_network_feature_support_t {
    uint8_t ethernet_pdn_type;
};
