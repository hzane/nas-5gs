#include "../common/dissector.hh"
#include "../common/use_context.hh"

// Serving PLMN rate control 9.11.4.20
// See subclause 9.9.4.28 in 3GPP TS 24.301
int dissect_serving_plmn_rate_control(dissector d, context*ctx) {
    const use_context uc(&d, ctx, "serving-plmn-rate-control", -1);
    return 2;
}
