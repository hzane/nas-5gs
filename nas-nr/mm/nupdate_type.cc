#include "../common/dissector.hh"
#include "../common/use_context.hh"


// 9.11.3.9A 5GS update type
int dissect_update_type(dissector d, context* ctx) {
    const use_context        uc(ctx, "5gs-update-type", d, -1);

    return 1;
}
