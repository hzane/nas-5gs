#include "../dissect_mm_msg.hh"
// 9.11.3.9A 5GS update type
const element_meta mm::update_type = {
    0x53,
    "5GS update type",
    dissect_update_type,
    nullptr,
};


// 9.11.3.9A 5GS update type
int mm::dissect_update_type(dissector d, context* ctx) {
    const use_context        uc(ctx, "5gs-update-type", d, -1);

    static const field_meta* flags[] = {
        &nas::hf_spare_b3,
        &hf_pnb_ciot,
        &hf_ng_ran_rcu,
        &hf_sms_requested,
        nullptr,
    };
    d.add_bits(flags);
    return 1;
}
