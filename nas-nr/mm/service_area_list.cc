#include "../common/dissector.hh"
#include "../common/use_context.hh"


// 9.11.3.49    Service area list page.391
result_t dissect_service_area_list(dissector d, context* ctx, service_area_list_t* ret) {
    return de_octet(d, ctx, ret);
}
