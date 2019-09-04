#include "common.hh"

// 3GPP TS 24.008 g10
namespace{
/* [9] 10.5.7.3 GPRS Timer */
const value_string gsm_a_gm_gprs_timer_unit_vals[] = {
    {0x00, "value is incremented in multiples of 2 seconds"},
    {0x01, "value is incremented in multiples of 1 minute"},
    {0x02, "value is incremented in multiples of decihours"},
    {0x07, "value indicates that the timer is deactivated"},
    {0, nullptr},
};
const field_meta hf_gprs_timer = {
    "GPRS Timer",
    "gsm_a.gm.gmm.gprs_timer",
    ft::ft_uint8,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta hf_gprs_timer_unit = {
    "Unit",
    "gsm_a.gm.gmm.gprs_timer_unit",
    ft::ft_uint8,
    fd::base_dec,
    (gsm_a_gm_gprs_timer_unit_vals),
    nullptr,
    nullptr,
    0xe0,
};
const field_meta hf_gprs_timer_value = {
    "Timer value",
    "gsm_a.gm.gmm.gprs_timer_value",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x1f,
};
}

int cmn::dissect_gprs_timer(dissector d, context *ctx) {
    auto        oct     = d.uint8();
    auto        val     = (uint32_t) oct & 0x1fu;
    auto        mulf    = oct >> 5u;
    const char *unit    = "min";
    uint32_t    mul     = 1;

    if (mulf == 0) {
        unit = "sec";
        mul  = 2;
    } else if (mulf == 1) {
        unit = "min";
    } else if (mulf == 2) {
        unit = "min";
        mul  = 6;
    } else if (mulf == 7) {
        unit = "deactivated";
    }

    auto        subtree = d.add_item(1, "GPRS Timer: %u %s", val * mul, unit);
    use_tree    ut(d, subtree);
    use_context uc(ctx, "GPRS Timer", d, -1);
    d.add_item(1, &hf_gprs_timer_unit, enc::be);
    d.add_item(1, &hf_gprs_timer_value, enc::be);
    d.step(1);

    /* no length check possible */
    return 1;
}


