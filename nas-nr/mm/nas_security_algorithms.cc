#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* *   9.11.3.34    NAS security algorithms */
int dissect_security_algo(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "sec-algo", -1);

    return 1;
}
