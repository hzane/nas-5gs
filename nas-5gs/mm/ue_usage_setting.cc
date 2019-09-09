#include "../dissect_mm_msg.hh"

using namespace nas;

// 9.11.3.55
int mm::dissect_usage_setting(dissector d, context* ctx) {
    const use_context        uc(ctx, "ue-usage-setting", d, -1);

    static const field_meta* flags[] = {
//        &hf_spare_b3,
//        &hf_spare_b2,
//        &hf_spare_b1,
        &hf_nas_5gs_mm_ue_usage_setting,
        nullptr,
    };
    d.add_bits(flags);
    return 1;
}
