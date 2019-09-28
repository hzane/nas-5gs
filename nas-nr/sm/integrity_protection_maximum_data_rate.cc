#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"

// Integrity protection maximum data rate   9.11.4.7
extern const element_meta sm::integrity_protection_max_data_rate = {
    0x13,
    "Integrity protection maximum data rate",
    sm::dissect_integrity_protection_max_data_rate,
    nullptr,

};

//  * 9.11.4.7 Integrity protection maximum data rate
int sm::dissect_integrity_protection_max_data_rate(dissector d, context* ctx) {
    const use_context uc(ctx, "integrity-protection-max-data-rate", d, -1);

    /* Maximum data rate per UE for user-plane integrity protection for uplink */
    (void) d.add_item(1, &hf_sm_integrity_protection_max_data_rate_ul);
    d.step(1);

    /* Maximum data rate per UE for user-plane integrity protection for downlink */
    (void) d.add_item(1, &hf_sm_integrity_protection_max_data_rate_dl);
    d.step(1);

    return 2;
}

struct integrity_protection_max_data_rate_t {
    uint8_t uplink_max_rate;
    uint8_t downlink_max_rate;
};

// * 9.11.4.7 Integrity protection maximum data rate
extern const value_string sm::integrity_protection_max_data_rate_values[] = {
    {0x0, "64 kbps"},
    {0xff, "Full data rate"},
    {0, nullptr},
};

const field_meta sm::hf_sm_integrity_protection_max_data_rate_ul = {
    "Integrity protection maximum data rate for uplink",
    "nas.nr.sm.integrity.protection.maximum.data.rate.uplink",
    ft::ft_uint8,
    fd::base_dec,
    sm::integrity_protection_max_data_rate_values,
    nullptr,
    nullptr,
    0x0,
};
const field_meta sm::hf_sm_integrity_protection_max_data_rate_dl = {
    "Integrity protection maximum data rate for downlink",
    "nas.nr.sm.integrity.protection.maximum.data.rate.downlink",
    ft::ft_uint8,
    fd::base_dec,
    sm::integrity_protection_max_data_rate_values,
    nullptr,
    nullptr,
    0x0,
};
