#include "../dissect_sm_msg.hh"


// Integrity protection maximum data rate   9.11.4.7
extern const element_meta sm::int_prot_max_data_rate = {
    0x13,
    "Integrity protection maximum data rate",
    dissect_int_prot_max_data_rate,
    nullptr,

};

//  * 9.11.4.7 Integrity protection maximum data rate
int sm::dissect_int_prot_max_data_rate(dissector d, context* ctx) {
    const use_context uc(ctx, "integrity-protection-max-data-rate", d, -1);

    /* Maximum data rate per UE for user-plane integrity protection for uplink */
    d.add_item(1, &hf_sm_int_prot_max_data_rate_ul, enc::be);
    d.step(1);

    /* Maximum data rate per UE for user-plane integrity protection for downlink */
    d.add_item(1, &hf_sm_int_prot_max_data_rate_dl, enc::be);
    d.step(1);

    return 2;
}
