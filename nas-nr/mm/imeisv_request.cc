#include "../common/dissect_mm_msg.hh"

// IMEISV request     9.11.3.28
int mm::dissect_imeisv_request(dissector d, context* ctx) {
    const use_context uc(ctx, "imeisv-request", d, -1);

    // See subclause 10.5.5.10 in 3GPP TS 24.008 [12].
    diag("no dissect %s\n", ctx->path().c_str());

    return d.length;
}

struct imeisv_request_t {};
