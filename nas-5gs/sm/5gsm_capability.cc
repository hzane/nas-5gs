#include "../dissect_sm_msg.hh"

using namespace nas;
using namespace sm;

/*  9.11.4.1    5GSM capability */
int sm::dissect_sm_cap(dissector d, context* ctx) {
    const use_context        uc(ctx, "5gsm-capability", d, -1);

    static const field_meta* flags[] = {
        &hf_spare_b7,
        &hf_spare_b6,
        &hf_spare_b5,
        &hf_spare_b4,
        &hf_spare_b3,
        &hf_spare_b2,
        &hf_spare_b1,
        &hf_sm_rqos_b0,
        nullptr,
    };
    d.add_bits(flags);
    d.step(1);

    return 1;
}

// 5GSM capability 9.11.4.1
const element_meta sm::sm_cap = {
    0x28,
    "5GSM capability",
    dissect_sm_cap,
    nullptr,
};
