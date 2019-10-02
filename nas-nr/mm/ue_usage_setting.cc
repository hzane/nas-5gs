#include "../common/dissector.hh"
#include "../common/use_context.hh"


// 9.11.3.55
int dissect_usage_setting(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "ue-usage-setting", -1);

    /*   Spare	UE's usage setting    */

    return 1;
}
