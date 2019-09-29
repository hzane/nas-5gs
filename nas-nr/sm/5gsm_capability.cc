#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"

using namespace nas;
using namespace sm;

/*  9.11.4.1    5GSM capability */
int sm::dissect_nrsm_capability(dissector d, context* ctx) {
    const use_context        uc(ctx, "5gsm-capability", d, -1);

    static const bool_field* flags[] = {
        &hf_reflective_qos,
        nullptr,
    };
    d.add_bits(flags);
    d.step(1);

    return 1;
}

// 5GSM capability 9.11.4.1
const element_meta sm::nrsm_capability = {
    0x28,
    "5GSM capability",
    dissect_nrsm_capability,
};
const bool_field sm::hf_reflective_qos = {
    "Reflective QoS(RqoS)",
    0x01,
    tfs_supported_not_supported,
};
