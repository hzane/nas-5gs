#include "../dissect_mm_msg.hh"

using namespace cmn;
using namespace nas;

// 9.11.3.56
int mm::dissect_ue_status(dissector d, context* ctx) {
    const use_context        uc(ctx, "ue-status", d, -1);

    static const field_meta* flags[] = {
        &hf_5gmm_registration_status,
        &hf_emm_registration_status,
        nullptr,
    };
    /* 0     0     0     0     0     0 Spare    S1  mode reg */
    d.add_bits(flags);
    return 1;
}
