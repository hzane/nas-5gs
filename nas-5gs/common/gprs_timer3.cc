#include "../common.hh"

namespace{
/* * 3GPP TS 24.008 g10 10.5.7.4a */
static const value_string gsm_a_gm_gprs_timer3_unit_vals[] = {
    {0x00, "value is incremented in multiples of 10 minutes"},
    {0x01, "value is incremented in multiples of 1 hour"},
    {0x02, "value is incremented in multiples of 10 hours"},
    {0x03, "value is incremented in multiples of 2 seconds"},
    {0x04, "value is incremented in multiples of 30 seconds"},
    {0x05, "value is incremented in multiples of 1 minute"},
    {0x07, "value indicates that the timer is deactivated"},
    {0, nullptr},
};
const field_meta hf_gprs_timer3_unit = {
    "Unit",
    "gsm_a.gm.gmm.gprs_timer3_unit",
    ft::ft_uint8,
    fd::base_dec,
    (gsm_a_gm_gprs_timer3_unit_vals),
    nullptr,
    nullptr,
    0xe0,
};
const field_meta hf_gprs_timer3_value = {
    "Timer value",
    "gsm_a.gm.gmm.gprs_timer3_value",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x1f,
};
const field_meta hf_gprs_timer3 = {
    "GPRS Timer 3",
    "gsm_a.gm.gmm.gprs_timer3",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x1f,
};
} // namespace

/*  [10] 10.5.7.4a */
int cmn::dissect_gprs_timer3(dissector d, context *ctx) {
    auto        oct     = d.uint8();
    auto        val     = uint32_t(oct & 0x1fu);
    uint32_t    mul     = 1u;
    const char *unit    = "hr";

    switch (oct >> 5u) {
    case 0:
        unit = "min";
        mul = 10;
        break;
    case 1:
        unit = "hr";
        break;
    case 2:
        unit = "hr";
        mul = 10;
        break;
    case 3:
        unit = "sec";
        mul = 2;
        break;
    case 4:
        unit = "sec";
        mul  = 30;
        break;
    case 5:
        unit = "min";
        break;
    case 7:
        unit = "deactivated";
        break;
    }

    auto     subtree = d.add_item(1, "GPRS Timer : %u %s", val * mul, unit);
    use_tree ut(d, subtree);
    use_context uc(ctx, "GPRS Timer 3", d, -1);

    d.add_item(1, &hf_gprs_timer3_unit, enc::be);
    d.add_item(1, &hf_gprs_timer3_value, enc::be);
    d.step(1);

    return 1;
}
