#include "../common/dissect_sm_msg.hh"

using namespace nas;

/* 9.11.4.5    Allowed SSC mode */
int sm::dissect_allowed_ssc_mode(dissector d, context* ctx) {
    const use_context        uc(ctx, "allowed-scc-mode", d, -1);

    static const field_meta* flags[] = {
        &hf_ssc_mode_3,
        &hf_ssc_mode_2,
        &hf_ssc_mode_1,
        nullptr,
    };
    d.add_bits(flags);
    d.step(1);

    return 1;
}
