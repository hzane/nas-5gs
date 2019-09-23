#include "../common/dissect_mm_msg.hh"

/*0	indicates establishment of user-plane resources of the PDU session
 *was not requested in the Uplink data status IE
 *or establishment of user-plane resources of the PDU session
 *was not allowed in the Allowed PDU session status IE
 *or establishment of user-plane resource of the PDU session is successful.
 *1	indicates either establishment of user-plane resources of the PDU session
 *was requested in the Uplink data status IE
 *but establishment of user-plane resource of the PDU session is not successful
 *or indicates establishment of user-plane resources of the PDU session
 *was allowed in the Allowed PDU session status IE but establishment of
 *user-plane resource of the PDU session is either not performed or not successful.
 */

//  *   9.11.3.42    PDU session reactivation result
const true_false_string tfs_nas_5gs_pdu_ses_rect_res_psi = {
    "1",
    "0",
};

const field_meta        hf_pdu_session_reactivation_result_psi_7_b7 = {
    "PSI(7)",
    "nas.nr.pdu_ses_rect_res_psi_3_b7",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x80,
};

const field_meta hf_pdu_session_reactivation_result_psi_6_b6 = {
    "PSI(6)",
    "nas.nr.pdu_ses_rect_res_psi_3_b6",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x40,
};

const field_meta hf_pdu_session_reactivation_result_psi_5_b5 = {
    "PSI(5)",
    "nas.nr.pdu_ses_rect_res_psi_3_b5",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x20,
};

const field_meta hf_pdu_session_reactivation_result_psi_4_b4 = {
    "PSI(4)",
    "nas.nr.pdu_ses_rect_res_psi_3_b4",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x10,
};

const field_meta hf_pdu_session_reactivation_result_psi_3_b3 = {
    "PSI(3)",
    "nas.nr.pdu_ses_rect_res_psi_3_b3",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x08,
};

const field_meta hf_pdu_session_reactivation_result_psi_2_b2 = {
    "PSI(2)",
    "nas.nr.pdu_ses_rect_res_psi_2_b2",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x04,
};

const field_meta hf_pdu_session_reactivation_result_psi_1_b1 = {
    "PSI(1)",
    "nas.nr.pdu_ses_rect_res_psi_1_b1",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x02,
};

const field_meta hf_pdu_session_reactivation_result_psi_0_b0 = {
    "PSI(0) Spare",
    "nas.nr.pdu_ses_rect_res_psi_0_b0",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x01,
};

const field_meta hf_pdu_session_reactivation_result_psi_15_b7 = {
    "PSI(15)",
    "nas.nr.pdu_ses_sts_psi_15_b7",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x80,
};
const field_meta hf_pdu_session_reactivation_result_psi_14_b6 = {
    "PSI(14)",
    "nas.nr.pdu_ses_sts_psi_14_b6",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x40,
};
const field_meta hf_pdu_session_reactivation_result_psi_13_b5 = {
    "PSI(13)",
    "nas.nr.pdu_ses_sts_psi_13_b5",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x20,
};
const field_meta hf_pdu_session_reactivation_result_psi_12_b4 = {
    "PSI(12)",
    "nas.nr.pdu_ses_rect_res_psi_12_b4",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x10,
};
const field_meta hf_pdu_session_reactivation_result_psi_11_b3 = {
    "PSI(11)",
    "nas.nr.pdu_ses_rect_res_psi_11_b3",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x08,
};
const field_meta hf_pdu_session_reactivation_result_psi_10_b2 = {
    "PSI(10)",
    "nas.nr.pdu_ses_rect_res_psi_10_b2",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x04,
};
const field_meta hf_pdu_session_reactivation_result_psi_9_b1 = {
    "PSI(9)",
    "nas.nr.pdu_ses_rect_res_psi_9_b1",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x02,
};
const field_meta hf_pdu_session_reactivation_result_psi_8_b0 = {
    "PSI(8)",
    "nas.nr.pdu_ses_rect_res_psi_8_b0",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x01,
};

// PDU session reactivation result   9.11.3.42
int mm::dissect_pdu_session_reactive_result(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-reactivation-result", d, 30);

    static const field_meta* psi_0_7_flags[] = {
        &hf_pdu_session_reactivation_result_psi_7_b7,
        &hf_pdu_session_reactivation_result_psi_6_b6,
        &hf_pdu_session_reactivation_result_psi_5_b5,
        &hf_pdu_session_reactivation_result_psi_4_b4,
        &hf_pdu_session_reactivation_result_psi_3_b3,
        &hf_pdu_session_reactivation_result_psi_2_b2,
        &hf_pdu_session_reactivation_result_psi_1_b1,
        &hf_pdu_session_reactivation_result_psi_0_b0,
        nullptr,
    };

    static const field_meta* psi_8_15_flags[] = {
        &hf_pdu_session_reactivation_result_psi_15_b7,
        &hf_pdu_session_reactivation_result_psi_14_b6,
        &hf_pdu_session_reactivation_result_psi_13_b5,
        &hf_pdu_session_reactivation_result_psi_12_b4,
        &hf_pdu_session_reactivation_result_psi_11_b3,
        &hf_pdu_session_reactivation_result_psi_10_b2,
        &hf_pdu_session_reactivation_result_psi_9_b1,
        &hf_pdu_session_reactivation_result_psi_8_b0,
        nullptr,
    };
    d.add_bits(psi_0_7_flags);
    d.step(1);
    d.add_bits(psi_8_15_flags);
    d.step(1);

    // 5-34 is optional

    return uc.length;
}
