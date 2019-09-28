#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace nas;

// 9.11.3.55
int mm::dissect_usage_setting(dissector d, context* ctx) {
    const use_context        uc(ctx, "ue-usage-setting", d, -1);

    /*   Spare	UE's usage setting    */
    (void) d.add_item(1, &hf_ue_usage_setting);
    d.step(1);

    return 1;
}

// UE's usage setting    UE's usage setting         9.11.3.55
const true_false_string tfs_ue_usage_setting = {
    "Data centric",
    "Voice centric",
};

const field_meta mm::hf_ue_usage_setting = {
    "UE's usage setting",
    "nas.nr.mm.ue.usage.setting",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_ue_usage_setting,
    nullptr,
    0x01,
};
