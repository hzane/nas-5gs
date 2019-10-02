#include "../common/dissector.hh"
#include "../common/use_context.hh"


// 9.11.3.49    Service area list page.391
int dissect_service_area_list(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "service-area-list", 0);

    return uc.length;
}
