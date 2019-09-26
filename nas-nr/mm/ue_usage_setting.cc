#include "../common/dissector.hh"
#include "../common/use_context.hh"


// 9.11.3.55
int dissect_usage_setting(dissector d, context* ctx) {
    const use_context        uc(ctx, "ue-usage-setting", d, -1);

    /*   Spare	UE's usage setting    */

    return 1;
}
