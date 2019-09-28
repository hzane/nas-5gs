#include "../common/ber.hh"
#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace nas;
using namespace mm;

/* 8.2.16 Service request page.317 */
int mm::dissect_service_request(dissector d, context* ctx) {
    const use_context uc(ctx, "service-request", d, 0);
    // UE to network
    up_link(d.pinfo);

    /* ngKSI     NAS key set identifier 9.11.3.32    M    V    1/2 */
    dissect_v(nullptr, &nas_ksi, d, ctx);

    // Service type 9.11.3.50 M V 1 / 2
    (void) dissect_service_type(d, ctx);
    d.step(1);

    /* 5G-S-TMSI    5GS mobile identity 9.11.3.4    M    LV    9 */
    auto consumed = dissect_lv_e(nullptr, &s_tmsi, d, ctx);
    d.step(consumed);

    /*40 Uplink data status  9.11.3.57   O   TLV  4 - 34*/
    consumed = dissect_opt_tlv(nullptr, &uplink_data_status, d, ctx);
    d.step(consumed);

    /*50 PDU session status  9.11.3.44  O  TLV   4 - 34*/
    consumed = dissect_opt_tlv(nullptr, &pdu_session_status, d, ctx);
    d.step(consumed);

    /*25 Allowed PDU session status  9.11.3.13  O    TLV    4 - 34*/
    consumed = dissect_opt_tlv(nullptr, &allowed_pdu_session_status, d, ctx);
    d.step(consumed);

    /* 71  NAS message container 9.11.3.33    O    TLV-E    4-n */
    consumed = dissect_opt_tlv_e(nullptr, &nas_msg_container, d, ctx);
    d.step(consumed);

    return uc.length;
}
namespace mm {
const element_meta s_tmsi = {
    0xff,
    "5GS mobile identity - 5G-S-TMSI",
    dissect_mobile_id,
    nullptr,
};

/* 9.11.3.57    Uplink data status */
const true_false_string tfs_ul_data_sts_psi = {
    "uplink data are pending",
    "no uplink data are pending",
};

const field_meta hf_ul_data_status_psi_7_b7 = {
    "PSI(7)",
    "nas.nr.psi",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_ul_data_sts_psi,
    nullptr,
    0x80,
};
const field_meta hf_ul_data_status_psi_6_b6 = {
    "PSI(6)",
    "nas.nr.psi",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_ul_data_sts_psi,
    nullptr,
    0x40,
};
const field_meta hf_ul_data_status_psi_5_b5 = {
    "PSI(5)",
    "nas.nr.psi",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_ul_data_sts_psi,
    nullptr,
    0x20,
};
const field_meta hf_ul_data_status_psi_4_b4 = {
    "PSI(4)",
    "nas.nr.psi",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_ul_data_sts_psi,
    nullptr,
    0x10,
};
const field_meta hf_ul_data_status_psi_3_b3 = {
    "PSI(3)",
    "nas.nr.psi",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_ul_data_sts_psi,
    nullptr,
    0x08,
};
const field_meta hf_ul_data_status_psi_2_b2 = {
    "PSI(2)",
    "nas.nr.psi",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_ul_data_sts_psi,
    nullptr,
    0x04,
};
const field_meta hf_ul_data_status_psi_1_b1 = {
    "PSI(1)",
    "nas.nr.psi",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_ul_data_sts_psi,
    nullptr,
    0x02,
};
const field_meta hf_ul_data_status_psi_0_b0 = {
    "Spare",
    "nas.nr.psi",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x01,
};

const field_meta hf_ul_data_status_psi_15_b7 = {
    "PSI(15)",
    "nas.nr.psi",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_ul_data_sts_psi,
    nullptr,
    0x80,
};
const field_meta hf_ul_data_status_psi_14_b6 = {
    "PSI(14)",
    "nas.nr.psi",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_ul_data_sts_psi,
    nullptr,
    0x40,
};
const field_meta hf_ul_data_status_psi_13_b5 = {
    "PSI(13)",
    "nas.nr.psi",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_ul_data_sts_psi,
    nullptr,
    0x20,
};
const field_meta hf_ul_data_status_psi_12_b4 = {
    "PSI(12)",
    "nas.nr.psi",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_ul_data_sts_psi,
    nullptr,
    0x10,
};
const field_meta hf_ul_data_status_psi_11_b3 = {
    "PSI(11)",
    "nas.nr.psi",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_ul_data_sts_psi,
    nullptr,
    0x08,
};
const field_meta hf_ul_data_status_psi_10_b2 = {
    "PSI(10)",
    "nas.nr.psi",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_ul_data_sts_psi,
    nullptr,
    0x04,
};
const field_meta hf_ul_data_status_psi_9_b1  = {
    "PSI(9)",
    "nas.nr.psi",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_ul_data_sts_psi,
    nullptr,
    0x02,
};
const field_meta hf_ul_data_status_psi_8_b0  = {
    "PSI(8)",
    "nas.nr.psi",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_ul_data_sts_psi,
    nullptr,
    0x01,
};

}
