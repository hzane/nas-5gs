#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"

const uint16_field hf_serving_plmn_rate_control = {
    "Serving PLMN rate control value",
    0,
};

// Serving PLMN rate control 9.11.4.20
// See subclause 9.9.4.28 in 3GPP TS 24.301
int dissect_serving_plmn_rate_control(dissector d, context*ctx) {
    const use_context uc(ctx, "serving-plmn-rate-control", d, -1);

    (void) d.add_item(&hf_serving_plmn_rate_control);
    d.step(2);

    return 2;
}
