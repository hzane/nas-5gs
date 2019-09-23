#include "../common/dissect_sm_msg.hh"

const field_meta hf_serving_plmn_rate_control = {
    "Serving PLMN rate control value",
    "nas.nr.serving.plmn.rate.control",
    ft::ft_uint16,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0,
};

// Serving PLMN rate control 9.11.4.20
// See subclause 9.9.4.28 in 3GPP TS 24.301
int dissect_serving_plmn_rate_control(dissector d, context*ctx) {
    const use_context uc(ctx, "serving-plmn-rate-control", d, -1);

    (void) d.add_item(2, &hf_serving_plmn_rate_control, enc::be);
    return 2;
}

const element_meta serving_plmn_rate_control = {
    0xffu,
    "Serving PLMN rate control",
    dissect_serving_plmn_rate_control,
    nullptr,
};
