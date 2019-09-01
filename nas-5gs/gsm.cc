#include "gsm.hh"
#include "core.hh"

// 3GPP TS 24.008 g10

/*
 * [9] 10.5.7.3 GPRS Timer
 */
static const value_string gsm_a_gm_gprs_timer_unit_vals[] = {
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
    nullptr,nullptr,nullptr,
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
    nullptr,nullptr,nullptr,
    0x1f,
};

const field_meta hf_gprs_timer2 = {
    "GPRS Timer",
    "gsm_a.gm.gmm.gprs_timer2",
    ft::ft_uint8,
    fd::base_hex,
    nullptr,nullptr,nullptr,
    0x0,
};
const field_meta hf_gprs_timer3 = {
    "Unit",
    "gsm_a.gm.gmm.gprs_timer2_unit",
    ft::ft_uint8,
    fd::base_dec,
    (gsm_a_gm_gprs_timer_unit_vals),
    nullptr,
    nullptr,
    0xe0,
};

int dissect_gprs_timer(dissector d, context *ctx) {
    proto_node *subtree = nullptr;
    auto        oct     = d.tvb->uint8(d.offset);
    auto        val     = oct & 0x1fu;
    const char *unit    = "";

    switch (oct >> 5u) {
    case 0:
        unit = "sec";
        val *= 2;
        break;
    case 1:
        unit = "min";
        break;
    case 2:
        unit = "min";
        val *= 6;
        break;
    case 7:
        subtree = d.add_item(1, "GPRS Timer: timer is deactivated");
        break;
    default:
        unit = "min";
    }
    if (!subtree) subtree = d.add_item(1, "GPRS Timer: %u %s", val, unit);
    use_tree ut(d, subtree);
    d.add_item(1, &hf_gprs_timer_unit, enc::be);
    d.add_item(1, &hf_gprs_timer_value, enc::be);

    /* no length check possible */
    return 1;
}

/* * 3GPP TS 24.008 g10 10.5.7.4 */
int dissect_gprs_timer2(dissector d, context*ctx) {
    proto_node *subtree = nullptr;
    auto        oct     = d.tvb->uint8(d.offset);
    auto        val     = oct & 0x1fu;
    const char *unit    = "";

    switch (oct >> 5u) {
    case 0:
        unit = "sec";
        val *= 2;
        break;
    case 1:
        unit = "min";
        break;
    case 2:
        unit = "min";
        val *= 6;
        break;
    case 7:
        subtree = d.add_item(1, "GPRS Timer: timer is deactivated");
        break;
    default:
        unit = "min";
    }

    if (!subtree) {
        subtree = d.add_item(1, "GPRS Timer: %u %s ", val, unit);
    }
    use_tree ut(d, subtree);

    d.add_item(1, &hf_gprs_timer_unit, enc::be);
    d.add_item(1, &hf_gprs_timer_value, enc::be);

    return 1;
}

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


int dissect_gprs_timer3(dissector d, context *ctx) {
    proto_node *subtree = nullptr;
    auto        oct     = d.tvb->uint8(d.offset);
    auto        val     = oct & 0x1fu;
    const char *unit    = "";

    switch (oct >> 5u) {
    case 0:
        unit = "min";
        val *= 10;
        break;
    case 1:
        unit = "hr";
        break;
    case 2:
        unit = "hr";
        val *= 10;
        break;
    case 3:
        unit = "sec";
        val *= 2;
        break;
    case 4:
        unit = "sec";
        val *= 30;
        break;
    case 5:
        unit = "min";
        break;
    case 7:
        subtree = d.add_item(1, "GPRS Timer : timer is deactivated");
        break;
    default:
        unit = "hr";
    }

    if (!subtree)
        subtree = d.add_item(1, "GPRS Timer : %u %s", val, unit);
    use_tree ut(d, subtree);

    d.add_item(1, &hf_gprs_timer3_unit, enc::be);
    d.add_item(1, &hf_gprs_timer3_value, enc::be);

    return 1;
}
