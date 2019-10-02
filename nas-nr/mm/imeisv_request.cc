#include "../common/core.hh"
#include "../common/dissector.hh"
#include "../common/use_context.hh"

// IMEISV request     9.11.3.28
int dissect_imeisv_request(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "imeisv-request", -1);

    // See subclause 10.5.5.10 in 3GPP TS 24.008 [12].
    diag("no dissect %s\n", join(ctx->paths).c_str());

    return d.length;
}
