#include "../common.hh"
#include "../tvbuff.hh"

namespace{
/* [9] 10.5.7.3 GPRS Timer */
static const value_string gsm_a_gm_gprs_timer_unit_vals[] = {
    {0x00, "value is incremented in multiples of 2 seconds"},
    {0x01, "value is incremented in multiples of 1 minute"},
    {0x02, "value is incremented in multiples of decihours"},
    {0x07, "value indicates that the timer is deactivated"},
    {0, nullptr},
};
const field_meta hf_gprs_timer2 = {
    "GPRS Timer 2",
    "gsm_a.gm.gmm.gprs_timer2",
    ft::ft_uint8,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta hf_gprs_timer2_unit = {
    "Unit",
    "gsm_a.gm.gmm.gprs_timer2_unit",
    ft::ft_uint8,
    fd::base_dec,
    gsm_a_gm_gprs_timer_unit_vals,
    nullptr,
    nullptr,
    0xe0,
};
const field_meta hf_gprs_timer2_value = {
    "Timer value",
    "gsm_a.gm.gmm.gprs_timer2_value",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x1f,
};
} // namespace mm

/* * 3GPP TS 24.008 g10 10.5.7.4 */
int cmn::dissect_gprs_timer2(dissector d, context *ctx) {
    auto        oct     = d.tvb->uint8(d.offset);
    auto        val     = uint32_t(oct & 0x1fu);
    uint32_t    mul     = 1u;
    const char *unit    = "min";

    switch (oct >> 5u) {
    case 0:
        unit = "sec";
        mul  = 2;
        break;
    case 1:
        unit = "min";
        break;
    case 2:
        unit = "min";
        mul  = 6;
        break;
    case 7:
        unit = "deactivated";
        break;
    }

    auto     subtree = d.add_item(1, "GPRS Timer: %u %s ", val * mul, unit);
    use_tree ut(d, subtree);
    use_context uc(ctx, "GPRS Timer 2", d, -1);

    d.add_item(1, &hf_gprs_timer2_unit, enc::be);
    d.add_item(1, &hf_gprs_timer2_value, enc::be);
    d.step(1);

    return 1;
}
