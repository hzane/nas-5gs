#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"

// Integrity protection maximum data rate   9.11.4.7
extern const element_meta sm::integrity_protection_max_data_rate = {
    0x13,
    "Integrity protection maximum data rate",
    sm::dissect_integrity_protection_max_data_rate,

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

// * 9.11.4.7 Integrity protection maximum data rate
extern const value_string sm::integrity_protection_max_data_rate_values[] = {
    {0x0, "64 kbps"},
    {0xff, "Full data rate"},
    {0, nullptr},
};

const tag_field sm::hf_sm_integrity_protection_max_data_rate_ul = {
    "Integrity protection maximum data rate for uplink",
    0x0,
    sm::integrity_protection_max_data_rate_values,
};
const tag_field sm::hf_sm_integrity_protection_max_data_rate_dl = {
    "Integrity protection maximum data rate for downlink",
    0x0,
    sm::integrity_protection_max_data_rate_values,
};
