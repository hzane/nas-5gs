#include "../common/dissector.hh"
#include "../common/use_context.hh"


// 9.11.3.9A 5GS update type
int dissect_update_type(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "5gs-update-type", -1);

    return 1;
}
