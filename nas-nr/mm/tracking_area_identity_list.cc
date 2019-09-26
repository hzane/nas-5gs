#include "../common/dissector.hh"
#include "../common/use_context.hh"


// 9.11.3.9	5GS tracking area identity list
int dissect_tracking_area_id_list(dissector d, context* ctx) {
    const use_context uc(ctx, "5gs-tai-list", d, 0);

    return uc.length;
}
