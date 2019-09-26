#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 9.11.3.50    Service type page.396 */
int dissect_service_type(dissector d, context* ctx) {
    const use_context uc(ctx, "service-type", d, -1);

    return 1;
}
