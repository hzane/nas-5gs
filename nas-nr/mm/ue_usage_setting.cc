#include "../dissect_mm_msg.hh"

using namespace nas;

// 9.11.3.55
int mm::dissect_usage_setting(dissector d, context* ctx) {
    const use_context        uc(ctx, "ue-usage-setting", d, -1);

    /*   Spare	UE's usage setting    */
    (void) d.add_item(1, &hf_ue_usage_setting, enc::be);
    d.step(1);

    return 1;
}
