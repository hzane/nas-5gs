#include "../common/dissector.hh"
#include "../common/use_context.hh"

// 9.11.3.47 Request type page.390
int dissect_request_type(dissector d, context* ctx) {
    const use_context uc(ctx, "request-type", d, -1);

    return 1;
}
