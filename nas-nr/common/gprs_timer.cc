#include "../common.hh"

// 3GPP TS 24.008 g10
namespace{
/* [9] 10.5.7.3 GPRS Timer */
#if 0
const value_string gsm_a_gm_gprs_timer_unit_vals[] = {
    {0x00, "value is incremented in multiples of 2 seconds"},
    {0x01, "value is incremented in multiples of 1 minute"},
    {0x02, "value is incremented in multiples of decihours"},
    {0x07, "value indicates that the timer is deactivated"},
    {0, nullptr},
};
#endif
const field_meta hf_gprs_timer = {
    "GPRS Timer",
    "gsm.gprs.timer",
    ft::ft_uint8,
    fd::timer,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

}

// can only be used in opt_elem_tlv
int cmn::dissect_gprs_timer_set(dissector d, context *ctx) {
    const use_context uc(ctx, "gprs-timer", d, -1);

    (void) d.tree->set_item(1, &hf_gprs_timer, enc::be);
    d.step(1);

    /* no length check possible */
    return 1;
}

struct gprs_timer{
    uint8_t unit;
    uint32_t value;
};
