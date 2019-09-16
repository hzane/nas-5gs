#include "../dissect_sm_msg.hh"

using namespace nas;
using namespace sm;

/*  9.11.4.1    5GSM capability */
int sm::dissect_sm_capability(dissector d, context* ctx) {
    const use_context        uc(ctx, "5gsm-capability", d, -1);

    static const field_meta* flags[] = {
        &hf_reflective_qos_b0,
        nullptr,
    };
    d.add_bits(flags);
    d.step(1);

    return 1;
}

// 5GSM capability 9.11.4.1
const element_meta sm::sm_capability = {
    0x28,
    "5GSM capability",
    dissect_sm_capability,
    nullptr,
};
const field_meta sm::hf_reflective_qos_b0 = {
    "Reflective QoS(RqoS)",
    "nas.nr.sm.reflective.qos",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &nas::tfs_supported_not_supported,
    nullptr,
    0x01,
};

