#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

/*40    Uplink data status    Uplink data status 9.11.3.57    O    TLV    4-34 */
int mm::dissect_uplink_data_status(dissector d, context* ctx) {
    const use_context        uc(ctx, "uplink-data-status", d, -1);

    static const field_meta* psi_0_7_flags[] = {
        &hf_ul_data_status_psi_7_b7,
        &hf_ul_data_status_psi_6_b6,
        &hf_ul_data_status_psi_5_b5,
        &hf_ul_data_status_psi_4_b4,
        &hf_ul_data_status_psi_3_b3,
        &hf_ul_data_status_psi_2_b2,
        &hf_ul_data_status_psi_1_b1,
        &hf_ul_data_status_psi_0_b0,
        nullptr,
    };

    static const field_meta* psi_8_15_flags[] = {
        &hf_ul_data_status_psi_15_b7,
        &hf_ul_data_status_psi_14_b6,
        &hf_ul_data_status_psi_13_b5,
        &hf_ul_data_status_psi_12_b4,
        &hf_ul_data_status_psi_11_b3,
        &hf_ul_data_status_psi_10_b2,
        &hf_ul_data_status_psi_9_b1,
        &hf_ul_data_status_psi_8_b0,
        nullptr,
    };

    d.add_bits(psi_0_7_flags);
    d.step(1);

    d.add_bits(psi_8_15_flags);
    d.step(1);

    return 2;
}


// Uplink data status  9.11.3.57
const element_meta mm::uplink_data_status = {
    0x40,
    "Uplink data status",
    mm::dissect_uplink_data_status,
    nullptr,
};
