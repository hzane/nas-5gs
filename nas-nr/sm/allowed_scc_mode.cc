#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"

using namespace nas;

const bool_field hf_ssc_mode_3 = {
    "SSC mode 3",
    0x04,
    nas::tfs_allowed_not_allowed,
};
const bool_field hf_ssc_mode_2 = {
    "SSC mode 2",
    0x02,
    nas::tfs_allowed_not_allowed,
};
const bool_field hf_ssc_mode_1 = {
    "SSC mode 1",
    0x01,
    sm::tfs_allowed_not_allowed,
};


/* 9.11.4.5    Allowed SSC mode */
int sm::dissect_allowed_ssc_mode(dissector d, context* ctx) {
    const use_context        uc(ctx, "allowed-scc-mode", d, -1);

    static const bool_field* flags[] = {
        &hf_ssc_mode_3,
        &hf_ssc_mode_2,
        &hf_ssc_mode_1,
        nullptr,
    };
    d.add_bits(flags);
    d.step(1);

    return 1;
}
