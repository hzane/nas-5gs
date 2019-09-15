#include "../dissect_mm_msg.hh"
#include "../gsm.hh"
#include "../ber.hh"

using namespace cmn;
using namespace mm;
using namespace nas;


/* * 8.2.6 Registration request */
int mm::dissect_registration_req(dissector d, context* ctx) {
    const use_context uc(ctx, "registration-request", d, -1);

    // UE to network
    up_link(d.pinfo);
    // get private data

    /*   5GS registration type  9.11.3.7    M    V    1/2  H0*/
    (void) dissect_registration_request_type(d, ctx);
    /*    ngKSI    NAS key set identifier 9.11.3.32    M    V    1/2 H1*/
    (void) d.add_item(1, &hf_nas_ksi, enc::be);
    d.step(1);

    /* 5GS mobile identity 9.11.3.4    M    LV-E    6-n*/
    auto consumed = dissect_lv_e(nullptr, &mobile_id, d, ctx);
    d.step(consumed);

    /*C-    Non-current native NAS KSI    NAS key set identifier 9.11.3.32    O    TV 1*/
    // ELEM_OPT_TV_SHORT( 0xc0, , DE_NAS_5GS_MM_NAS_KEY_SET_ID, " - native KSI");
    consumed = dissect_opt_tv_short(nullptr, &nc_native_nas_ksi, d, ctx);
    d.step(consumed);

    /*10    5GMM capability  9.11.3.1    O    TLV    3-15*/
    consumed = dissect_opt_tlv(nullptr, &mm_cap, d, ctx);
    d.step(consumed);

    /*2E    UE security capability   9.11.3.54    O    TLV 4-10*/
    consumed = dissect_opt_tlv(nullptr, &ue_security_capability, d, ctx);
    d.step(consumed);

    /*2F    Requested NSSAI    NSSAI 9.11.3.37    O    TLV    4-74*/
    consumed = dissect_opt_tlv(nullptr, &requested_nssai, d, ctx);
    d.step(consumed);

    /*52 Last visited registered TAI 5GS tracking area identity 9.11.3.8 O TV  7 */
    // ELEM_OPT_TV(0x52, DE_NAS_5GS_MM_5GS_TA_ID, " - Last visited registered TAI");
    consumed = dissect_opt_tv(nullptr, &last_visited_tai, d, ctx);
    d.step(consumed);

    /*17    S1 UE network capability  9.11.3.48    O    TLV  4-15 */
    // ELEM_OPT_TLV(0x17, , DE_EMM_UE_NET_CAP, NULL);
    consumed = dissect_opt_tlv(nullptr, &s1_ue_net_capability, d, ctx);
    d.step(consumed);

    /*40    Uplink data status  9.11.3.57    O    TLV    4-34 */
    // ELEM_OPT_TLV(0x40, , DE_NAS_5GS_MM_UL_DATA_STATUS, NULL);
    consumed = dissect_opt_tlv(nullptr, &uplink_data_status, d, ctx);
    d.step(consumed);

    /*50    PDU session status  9.11.3.44    O    TLV    4-34 */
    // ELEM_OPT_TLV(0x50, , DE_NAS_5GS_MM_PDU_SES_STATUS, NULL);
    consumed = dissect_opt_tlv(nullptr, &pdu_ses_status, d, ctx);
    d.step(consumed);

    /*B-  MICO indication 9.11.3.31    O    TV    1*/
    // ELEM_OPT_TV_SHORT(0xb0, , DE_NAS_5GS_MM_MICO_IND, NULL);
    consumed = dissect_opt_tv_short(nullptr, &mico_indication, d, ctx);
    d.step(consumed);

    /*2B UE status 9.11.3.56    O    TLV    3*/
    // ELEM_OPT_TLV(0x2b, , DE_NAS_5GS_MM_UE_STATUS, NULL);
    consumed = dissect_opt_tlv(nullptr, &ue_status, d, ctx);
    d.step(consumed);

    /*77    Additional GUTI    5GS mobile identity 9.11.3.4    O    TLV-E    14 */
    // ELEM_OPT_TLV_E(0x77, , DE_NAS_5GS_MM_5GS_MOBILE_ID, " -  Additional GUTI");
    consumed = dissect_opt_tlv_e(nullptr, &aguti_mobile_id, d, ctx);
    d.step(consumed);

    /*25    Allowed PDU session status    9.11.3.13  O    TLV    4 - 34 */
    // ELEM_OPT_TLV(0x25, , DE_NAS_5GS_MM_ALLOW_PDU_SES_STS, NULL);
    consumed = dissect_opt_tlv(nullptr, &allowed_pdu_ses_status, d, ctx);
    d.step(consumed);

    /*18    UE's usage setting    9.11.3.55    O    TLV    3 */
    // ELEM_OPT_TLV(0x18, , DE_NAS_5GS_MM_UE_USAGE_SET, NULL);
    consumed = dissect_opt_tlv(nullptr, &ue_usage_setting, d, ctx);
    d.step(consumed);

    /* 51    Requested DRX parameters    5GS DRX parameters 9.11.3.2A    O    TLV    3 */
    /* ELEM_OPT_TLV(0x51,DE_NAS_5GS_MM_5GS_DRX_PARAM, " - Requested DRX parameters"); */
    consumed = dissect_opt_tlv(nullptr, &requested_drx_param, d, ctx);
    d.step(consumed);

    /* 70    EPS NAS message container  9.11.3.24    O    TLV-E 4-n */
    // ELEM_OPT_TLV_E(0x70, , DE_NAS_5GS_MM_EPS_NAS_MSG_CONT, NULL);
    consumed = dissect_opt_tlv_e(nullptr, &eps_nas_msg_container, d, ctx);
    d.step(consumed);

    /* 74    LADN indication  9.11.3.29    O    TLV-E    3-811 */
    // ELEM_OPT_TLV_E(0x74, , DE_NAS_5GS_MM_LADN_IND, NULL);
    consumed = dissect_opt_tlv_e(nullptr, &ladn_indication, d, ctx);
    d.step(consumed);

    /* 8-    Payload container type  9.11.3.40    O    TV    1 */
    // ELEM_OPT_TV_SHORT(0x80, , DE_NAS_5GS_MM_PLD_CONT_TYPE, NULL);
    consumed = dissect_opt_tv_short(nullptr, &payload_container_type, d, ctx);
    d.step(consumed);

    /* 7B    Payload container  9.11.3.39    O    TLV-E    4-65538 */
    // ELEM_OPT_TLV_E(0x7B, , DE_NAS_5GS_MM_PLD_CONT, NULL);
    consumed = dissect_opt_tlv_e(nullptr, &payload_container, d, ctx);
    d.step(consumed);

    /* 9-    Network slicing indication 9.11.3.36    O    TV 1 */
    // ELEM_OPT_TV_SHORT(0x90, , DE_NAS_5GS_MM_NW_SLICING_IND, NULL);
    consumed = dissect_opt_tv_short(nullptr, &nw_slicing_ind, d, ctx);
    d.step(consumed);

    /* 53    5GS update type 9.11.3.9A    O    TLV    3 */
    // ELEM_OPT_TLV(0x53, , DE_NAS_5GS_MM_UPDATE_TYPE, NULL);
    consumed = dissect_opt_tlv(nullptr, &update_type, d, ctx);
    d.step(consumed);

    /*TBD	Mobile station classmark 2	9.11.3.61	O	TLV	5
     *TBD	Supported codecs	Supported codec list 9.11.3.62	O	TLV	5-n */


    /* 71    NAS message container 9.11.3.33    O    TLV-E    4-n */
    // ELEM_OPT_TLV_E(0x71, , DE_NAS_5GS_MM_NAS_MSG_CONT, NULL);
    consumed = dissect_opt_tlv_e(nullptr, &nas_msg_container, d, ctx);
    d.step(consumed);

    /*60	EPS bearer context status	9.11.3.59	O	TLV	4 */
    consumed = dissect_opt_tlv(nullptr, &eps_bearer_ctx_status, d, ctx);
    d.step(consumed);

    /* XX	Requested extended DRX parameters 9.11.3.60	O TLV 3*/
    /* TBD	T3324 value	GPRS timer 3 9.11.2.5	O	TLV	3 */

    return uc.length;
}

namespace mm {
const true_false_string tfs_supp_or_not = {
    "Supported",
    "Not supported",
};

const field_meta hf_ea0 = {
    "5G-EA0",
    "nas.nr.mm.5g.ea0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x80,
};
const field_meta hf_ea1 = {
    "128-5G-EA1",
    "nas.nr.mm.128.5g.ea1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x40,
};
const field_meta hf_ea2 = {
    "128-5G-EA2",
    "nas.nr.mm.128.5g.ea2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x20,
};
const field_meta hf_ea3 = {
    "128-5G-EA3",
    "nas.nr.mm.128.5g.ea3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x10,
};

} // namespace mm


namespace mm {
// S1 UE network capability 9.11.3.48
const true_false_string nas_eps_emm_ucs2_supp_flg_value = {
    "The UE has no preference between the use of the default alphabet and the use of "
    "UCS2",
    "The UE has a preference for the default alphabet",
};

const field_meta hf_nas_eps_emm_eea0 = {
    "EEA0",
    "nas_eps.emm.eea0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x80,
};

const field_meta hf_nas_eps_emm_128eea1 = {
    "128-EEA1",
    "nas_eps.emm.128eea1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x40,
};

const field_meta hf_nas_eps_emm_128eea2 = {
    "128-EEA2",
    "nas_eps.emm.128eea2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x20,
};

const field_meta hf_nas_eps_emm_eea3 = {
    "128-EEA3",
    "nas_eps.emm.eea3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x10,
};
const field_meta hf_nas_eps_emm_eea4 = {
    "EEA4",
    "nas_eps.emm.eea4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x08,
};
const field_meta hf_nas_eps_emm_eea5 = {
    "EEA5",
    "nas_eps.emm.eea5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x04,
};
const field_meta hf_nas_eps_emm_eea6 = {
    "EEA6",
    "nas_eps.emm.eea6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x02,
};
const field_meta hf_nas_eps_emm_eea7 = {
    "EEA7",
    "nas_eps.emm.eea7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x01,
};

const field_meta hf_nas_eps_emm_eia0 = {
    "EIA0",
    "nas_eps.emm.eia0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x80,
};
const field_meta hf_nas_eps_emm_128eia1 = {
    "128-EIA1",
    "nas_eps.emm.128eia1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x40,
};
const field_meta hf_nas_eps_emm_128eia2 = {
    "128-EIA2",
    "nas_eps.emm.128eia2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x20,
};
const field_meta hf_nas_eps_emm_eia3 = {
    "128-EIA3",
    "nas_eps.emm.eia3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x10,
};
const field_meta hf_nas_eps_emm_eia4 = {
    "EIA4",
    "nas_eps.emm.eia4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x08,
};
const field_meta hf_nas_eps_emm_eia5 = {
    "EIA5",
    "nas_eps.emm.eia5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x04,
};
const field_meta hf_nas_eps_emm_eia6 = {
    "EIA6",
    "nas_eps.emm.eia6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x02,
};
const field_meta hf_nas_eps_emm_eia7 = {
    "EIA7",
    "nas_eps.emm.eia7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x01,
};

const field_meta hf_nas_eps_emm_uea0 = {
    "UEA0",
    "nas_eps.emm.uea0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x80,
};
const field_meta hf_nas_eps_emm_uea1 = {
    "UEA1",
    "nas_eps.emm.uea1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x40,
};
const field_meta hf_nas_eps_emm_uea2 = {
    "UEA2",
    "nas_eps.emm.uea2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x20,
};
const field_meta hf_nas_eps_emm_uea3 = {
    "UEA3",
    "nas_eps.emm.uea3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x10,
};
const field_meta hf_nas_eps_emm_uea4 = {
    "UEA4",
    "nas_eps.emm.uea4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x08,
};
const field_meta hf_nas_eps_emm_uea5 = {
    "UEA5",
    "nas_eps.emm.uea5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x04,
};
const field_meta hf_nas_eps_emm_uea6 = {
    "UEA6",
    "nas_eps.emm.uea6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x02,
};
const field_meta hf_nas_eps_emm_uea7 = {
    "UEA7",
    "nas_eps.emm.uea7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x01,
};

const field_meta hf_nas_eps_emm_ucs2_supp = {
    "UCS2 support (UCS2)",
    "nas_eps.emm.emm_ucs2_supp",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &nas_eps_emm_ucs2_supp_flg_value,
    nullptr,
    0x80,
};
const field_meta hf_nas_eps_emm_uia1 = {
    "UMTS integrity algorithm UIA1",
    "nas_eps.emm.uia1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x40,
};
const field_meta hf_nas_eps_emm_uia2 = {
    "UMTS integrity algorithm UIA2",
    "nas_eps.emm.uia2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x20,
};
const field_meta hf_nas_eps_emm_uia3 = {
    "UMTS integrity algorithm UIA3",
    "nas_eps.emm.uia3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x10,
};
const field_meta hf_nas_eps_emm_uia4 = {
    "UMTS integrity algorithm UIA4",
    "nas_eps.emm.uia4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x08,
};
const field_meta hf_nas_eps_emm_uia5 = {
    "UMTS integrity algorithm UIA5",
    "nas_eps.emm.uia5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x04,
};
const field_meta hf_nas_eps_emm_uia6 = {
    "UMTS integrity algorithm UIA6",
    "nas_eps.emm.uia6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x02,
};
const field_meta hf_nas_eps_emm_uia7 = {
    "UMTS integrity algorithm UIA7",
    "nas_eps.emm.uia7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x01,
};

const field_meta hf_nas_eps_emm_prose_dd_cap = {
    "ProSe direct discovery",
    "nas_eps.emm.prose_dd_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x80,
};
const field_meta hf_nas_eps_emm_prose_cap = {
    "ProSe",
    "nas_eps.emm.prose_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x40,
};
const field_meta hf_nas_eps_emm_h245_ash_cap = {
    "H.245 After SRVCC Handover",
    "nas_eps.emm.h245_ash_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x20,
};
const field_meta hf_access_class_control_csfb_cap = {
    "Access class control for CSFB",
    "nas_eps.emm.acc_csfb_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x10,
};
const field_meta hf_nas_eps_emm_lpp_cap = {
    "LTE Positioning Protocol",
    "nas.mm.lpp.capability",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x08,
};
const field_meta hf_nas_eps_emm_lcs_cap = {
    "Location services (LCS) notification mechanisms",
    "nas_eps.emm.lcs_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x04,
};
const field_meta hf_nas_eps_emm_1xsrvcc_cap = {
    "SRVCC from E-UTRAN to cdma2000 1xCS",
    "nas_eps.emm.1xsrvcc_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x02,
};
const field_meta hf_nas_eps_emm_nf_cap = {
    "Notification procedure",
    "nas_eps.emm.nf_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x01,
};

const field_meta hf_nas_eps_emm_epco_cap = {
    "Extended protocol configuration options",
    "nas_eps.emm.epco_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x80,
};
const field_meta hf_nas_eps_emm_hc_cp_ciot_cap = {
    "Header compression for control plane CIoT EPS optimization",
    "nas_eps.emm.hc_cp_ciot_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x40,
};
const field_meta hf_nas_eps_emm_er_wo_pdn_cap = {
    "EMM-REGISTERED w/o PDN connectivity",
    "nas_eps.emm.er_wo_pdn_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x20,
};
const field_meta hf_nas_eps_emm_s1u_data_cap = {
    "S1-U data transfer",
    "nas_eps.emm.s1u_data_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x10,
};
const field_meta hf_nas_eps_emm_up_ciot_cap = {
    "User plane CIoT EPS optimization",
    "nas_eps.emm.up_ciot_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x08,
};
const field_meta hf_nas_eps_emm_cp_ciot_cap = {
    "Control plane CIoT EPS optimization",
    "nas_eps.emm.cp_ciot_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x04,
};
const field_meta hf_nas_eps_emm_prose_relay_cap = {
    "ProSe UE-to-network relay",
    "nas_eps.emm.prose_relay_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x02,
};
const field_meta hf_nas_eps_emm_prose_dc_cap = {
    "ProSe direct communication",
    "nas_eps.emm.prose_dc_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x01,
};

const field_meta hf_nas_eps_15_bearers_cap = {
    "Signalling for a maximum number of 15 EPS bearer contexts",
    "nas_eps.emm.15_bearers_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x80,
};
const field_meta hf_nas_eps_sgc_cap = {
    "Service gap control",
    "nas_eps.emm.sgc_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x40,
};
const field_meta hf_nas_eps_n1mode_cap = {
    "N1 mode",
    "nas_eps.emm.n1mode_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x20,
};
const field_meta hf_nas_eps_dcnr_cap = {
    "Dual connectivity with NR",
    "nas_eps.emm.dcnr_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x10,
};
const field_meta hf_nas_eps_cp_backoff_cap = {
    "Control plane data backoff",
    "nas_eps.emm.cp_backoff_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x08,
};
const field_meta hf_nas_eps_restrict_ec_cap = {
    "Restriction on use of enhanced coverage",
    "nas_eps.emm.restrict_ec_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x04,
};
const field_meta hf_nas_eps_v2x_pc5_cap = {
    "V2X communication over PC5",
    "nas_eps.emm.v2x_pc5_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x02,
};
const field_meta hf_nas_eps_multiple_drb_cap = {
    "Multiple DRB",
    "nas_eps.emm.multiple_drb_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x01,
};

const field_meta hf_nas_eps_spare_bits = {
    "Spare bit(s)",
    "nas_eps.spare_bits",
    ft::ft_uint8,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

} // namespace mm


const true_false_string tfs_nas_5gs_mm_n1_mod = { // NOLINT
    "UE is in 5GMM-REGISTERED state",
    "UE is not in 5GMM-REGISTERED state",
};


/* 9.11.3.9A    5GS update type */
const true_false_string tfs_nas5gs_sms_requested = { // NOLINT
    "SMS over NAS supported",
    "SMS over NAS not supported",
};

const true_false_string tfs_needed_not_needed = {
    "Needed",
    "Not Needed",
};

const field_meta        mm::hf_ng_ran_rcu        = {
    "NG-RAN Radio Capability Update (NG-RAN-RCU)",
    "nas.nr.mm.ng_ran_rcu",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_needed_not_needed,
    nullptr,
    0x02,
};

const val_string pnb_ciot_values[] = {
    {0, "no additional information"},
    {1, "control plane CIot 5GS optimization"},
    {2, "user plane CIot 5GS optimization"},
    {3, "reserved"},
    {0, nullptr},
};

const field_meta mm::hf_pnb_ciot = {
    "",
    "nas.nr.mm.pnb_ciot",
    ft::ft_uint8,
    fd::base_dec,
    pnb_ciot_values,
    nullptr,
    nullptr,
    0,
};

