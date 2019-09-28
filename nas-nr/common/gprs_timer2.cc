#include "common.hh"
#include "tvbuff.hh"
#include "../common/use_context.hh"

namespace{
/* [9] 10.5.7.3 GPRS Timer */
#if 0
static const value_string gsm_a_gm_gprs_timer_unit_vals[] = {
    {0x00, "value is incremented in multiples of 2 seconds"},
    {0x01, "value is incremented in multiples of 1 minute"},
    {0x02, "value is incremented in multiples of decihours"},
    {0x07, "value indicates that the timer is deactivated"},
    {0, nullptr},
};
#endif
const field_meta hf_gprs_timer2 = {
    "GPRS Timer 2",
    "gsm.timer2",
    ft::ft_uint8,
    fd::timer2,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
#if 0
const field_meta hf_gprs_timer2_unit = {
    "Unit",
    "gsm.timer2.unit",
    ft::ft_uint8,
    fd::base_dec,
    gsm_a_gm_gprs_timer_unit_vals,
    nullptr,
    nullptr,
    0xe0,
};
const field_meta hf_gprs_timer2_value = {
    "Timer 2 value",
    "gsm.timer2.value",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x1f,
};
#endif
} // namespace mm

/* * 3GPP TS 24.008 g10 10.5.7.4 */
// can only be used in opt_elem_tlv
int cmn::dissect_gprs_timer2_set(dissector d, context *ctx) {
    const use_context uc(ctx, "gprs-timer2", d, -1);

    (void) d.tree->set_item(1, &hf_gprs_timer2);
    d.step(1);

    return 1;
}
