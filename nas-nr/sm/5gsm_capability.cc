#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"

using namespace nas;
using namespace sm;

const bool_field hf_reflective_qos = {
    "Reflective QoS(RqoS)",
    0x01,
    tfs_supported_not_supported,
};

/*  9.11.4.1    5GSM capability */
int sm::dissect_nrsm_capability(dissector d, context* ctx) {
    const use_context        uc(ctx, "5gsm-capability", d, -1);

    d.add_item(&hf_reflective_qos);
    d.step(1);

    return 1;
}

