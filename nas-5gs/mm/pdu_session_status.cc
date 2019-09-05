#include "../dissect_mm_msg.hh"



/* 9.11.3.44    PDU session status  */
namespace mm {
static true_false_string tfs_nas_5gs_pdu_ses_sts_psi = {
    "Not PDU SESSION INACTIVE",
    "PDU SESSION INACTIVE",
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_7_b7 = {
    "PSI(7)",
    "nas_5gs.pdu_ses_sts_psi_7_b7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x80,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_6_b6 = {
    "PSI(6)",
    "nas_5gs.pdu_ses_sts_psi_6_b6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x40,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_5_b5 = {
    "PSI(5)",
    "nas_5gs.pdu_ses_sts_psi_5_b5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x20,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_4_b4 = {
    "PSI(4)",
    "nas_5gs.pdu_ses_sts_psi_4_b4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x10,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_3_b3 = {
    "PSI(3)",
    "nas_5gs.pdu_ses_sts_psi_3_b3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x08,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_2_b2 = {
    "PSI(2)",
    "nas_5gs.pdu_ses_sts_psi_2_b2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x04,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_1_b1 = {
    "PSI(1)",
    "nas_5gs.pdu_ses_sts_psi_1_b1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x02,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_0_b0 = {
    "Spare",
    "nas_5gs.pdu_ses_sts_psi_0_b0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x01,
};

const field_meta hf_nas_5gs_pdu_ses_sts_psi_15_b7 = {
    "PSI(15)",
    "nas_5gs.pdu_ses_sts_psi_15_b7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x80,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_14_b6 = {
    "PSI(14)",
    "nas_5gs.pdu_ses_sts_psi_14_b6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x40,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_13_b5 = {
    "PSI(13)",
    "nas_5gs.pdu_ses_sts_psi_13_b5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x20,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_12_b4 = {
    "PSI(12)",
    "nas_5gs.pdu_ses_sts_psi_12_b4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x10,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_11_b3 = {
    "PSI(11)",
    "nas_5gs.pdu_ses_sts_psi_11_b3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x08,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_10_b2 = {
    "PSI(10)",
    "nas_5gs.pdu_ses_sts_psi_10_b2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x04,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_9_b1 = {
    "PSI(9)",
    "nas_5gs.pdu_ses_sts_psi_9_b1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x02,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_8_b0 = {
    "PSI(8)",
    "nas_5gs.pdu_ses_sts_psi_8_b0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x01,
};
} // namespace mm

// PDU session status   9.11.3.44
int mm::dissect_pdu_ses_status(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-status", d, 0);

    static const field_meta* psi_0_7_flags[] = {
        &hf_nas_5gs_pdu_ses_sts_psi_7_b7,
        &hf_nas_5gs_pdu_ses_sts_psi_6_b6,
        &hf_nas_5gs_pdu_ses_sts_psi_5_b5,
        &hf_nas_5gs_pdu_ses_sts_psi_4_b4,
        &hf_nas_5gs_pdu_ses_sts_psi_3_b3,
        &hf_nas_5gs_pdu_ses_sts_psi_2_b2,
        &hf_nas_5gs_pdu_ses_sts_psi_1_b1,
        &hf_nas_5gs_pdu_ses_sts_psi_0_b0,
        nullptr,
    };

    static const field_meta* psi_8_15_flags[] = {
        &hf_nas_5gs_pdu_ses_sts_psi_15_b7,
        &hf_nas_5gs_pdu_ses_sts_psi_14_b6,
        &hf_nas_5gs_pdu_ses_sts_psi_13_b5,
        &hf_nas_5gs_pdu_ses_sts_psi_12_b4,
        &hf_nas_5gs_pdu_ses_sts_psi_11_b3,
        &hf_nas_5gs_pdu_ses_sts_psi_10_b2,
        &hf_nas_5gs_pdu_ses_sts_psi_9_b1,
        &hf_nas_5gs_pdu_ses_sts_psi_8_b0,
        nullptr,
    };

    d.add_bits(psi_0_7_flags);
    d.step(1);

    d.add_bits(psi_8_15_flags);
    d.step(1);

    // All bits in octet 5 to 34 are spare and shall be coded as zero,
    // if the respective octet is included in the information element
    // d.extraneous_data_check(0);
    return uc.length;
}
