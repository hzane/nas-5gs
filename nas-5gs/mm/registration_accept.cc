#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_reg_accept {
extern const element_meta plmn_list;
extern const element_meta eap_message;
extern const element_meta nego_drx_param;
extern const element_meta t3512_gprs_timer_3;
extern const element_meta rejected_nssai;
extern const element_meta ladn_inf;
extern const element_meta mico_ind;
extern const element_meta nssai_inclusion_mode;
extern const element_meta t3502_gprs_timer_2;
extern const element_meta emerg_num_list;
extern const element_meta nw_slicing_ind;
extern const element_meta configured_nssai;
extern const element_meta nw_feat_sup;
extern const element_meta de_reg_timer_gprs_timer2;
extern const element_meta sal;
extern const element_meta pdu_ses_react_res_err_c;
extern const element_meta pdu_ses_react_res;
extern const element_meta emerg_num_list_7a;
extern const element_meta operator_defined_acd;
extern const element_meta allowed_nssai;
extern const element_meta ta_id_list;
extern const element_meta guti_5gs_mobile_id;
extern const element_meta reg_res;
extern const element_meta sor_trans_cont;
} // namespace mm_reg_accept

/*
 * 8.2.7    Registration accept
 */
int mm::registration_accept(dissector d, context* ctx) {
    use_context uc(ctx, "registration-accept");

    using namespace mm_reg_accept;

    /*      5GS registration result    5GS registration result     9.11.3.6    M    LV 2*/
    auto consumed = dissect_elem_lv(nullptr, &reg_res, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*77    5G-GUTI    5GS mobile identity 9.11.3.4    O    TLV-E    14 */
    // ELEM_OPT_TLV_E(0x77, , DE_NAS_5GS_MM_5GS_MOBILE_ID, " - 5G-GUTI");
    consumed = dissect_opt_elem_tlv_e(nullptr, &guti_5gs_mobile_id, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*4A    Equivalent PLMNs    PLMN list     9.11.3.33    O    TLV    5-47*/
    // ELEM_OPT_TLV(0x4a, GSM_A_PDU_TYPE_COMMON, DE_PLMN_LIST, " - Equivalent PLMNs");
    consumed = dissect_opt_elem_tlv(nullptr, &plmn_list, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*54    TAI list    Tracking area identity list     9.11.3.9    O    TLV    8-98*/
    // ELEM_OPT_TLV(0x54, , DE_NAS_5GS_MM_5GS_TA_ID_LIST, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &ta_id_list, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*15    Allowed NSSAI    NSSAI     9.11.3.28    O    TLV    4-74*/
    // ELEM_OPT_TLV(0x15, , DE_NAS_5GS_MM_NSSAI, " - Allowed NSSAI");
    consumed = dissect_opt_elem_tlv(nullptr, &allowed_nssai, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*11    Rejected NSSAI    Rejected NSSAI     9.11.3.35    O    TLV    4-42*/
    // ELEM_OPT_TLV(0x11, , DE_NAS_5GS_MM_REJ_NSSAI, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &rejected_nssai, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*31    Configured NSSAI    NSSAI 9.11.3.34    O    TLV    4-146 */
    // ELEM_OPT_TLV(0x31, , DE_NAS_5GS_MM_NSSAI, " - Configured NSSAI");
    consumed = dissect_opt_elem_tlv(nullptr, &configured_nssai, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*21    5GS network feature support    5GS network feature support 9.11.3.5    O TLV
     * 3-5 */
    // ELEM_OPT_TLV(0x21, , DE_NAS_5GS_MM_5GS_NW_FEAT_SUP, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &nw_feat_sup, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*50    PDU session status    PDU session status     9.10.2.2    O    TLV    4*/
    // ELEM_OPT_TLV(0x50, , DE_NAS_5GS_MM_PDU_SES_STATUS, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &pdu_ses_status, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*26    PDU session reactivation result    PDU session reactivation
     * result     9.11.3.32    O    TLV    4-32*/
    // ELEM_OPT_TLV(0x26, , DE_NAS_5GS_MM_PDU_SES_REACT_RES, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &pdu_ses_react_res, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*72    PDU session reactivation result error cause PDU session reactivation result
     * error cause 9.11.3.40  O TLV-E  5-515*/
    // ELEM_OPT_TLV_E(
    // 0x72, , DE_NAS_5GS_MM_PDU_SES_REACT_RES_ERR_C, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &pdu_ses_react_res_err_c, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*79    LADN information    LADN information     9.11.3.19    O    TLV-E    11-1579*/
    // ELEM_OPT_TLV_E(0x79, , DE_NAS_5GS_MM_LADN_INF, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ladn_inf, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*B-    MICO indication    MICO indication     9.11.3.21    O    TV    1*/
    // ELEM_OPT_TV_SHORT(0xb0, , DE_NAS_5GS_MM_MICO_IND, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &mico_ind, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /* 9-    Network slicing indication    Network slicing indication 9.11.3.36    O    TV
     * 1 */
    // ELEM_OPT_TV_SHORT(0x90, , DE_NAS_5GS_MM_NW_SLICING_IND, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &nw_slicing_ind, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*27    Service area list    Service area list     9.11.3.47    O    TLV    6-194*/
    // ELEM_OPT_TLV(0x27, , DE_NAS_5GS_MM_SAL, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &sal, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*5E    T3512 value    GPRS timer 3     9.11.3.21    O    TLV    3*/
    // ELEM_OPT_TLV(0x5E, GSM_A_PDU_TYPE_GM, DE_GPRS_TIMER_3, " - T3512 value");
    consumed = dissect_opt_elem_tlv(nullptr, &t3512_gprs_timer_3, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*5D    Non-3GPP de-registration timer value    GPRS timer 2     9.11.3.20    O    TLV
     * 3*/
    // ELEM_OPT_TLV(0x5D, , DE_GPRS_TIMER_2, " - Non-3GPP de-registration timer value");
    consumed = dissect_opt_elem_tlv(nullptr, &de_reg_timer_gprs_timer2, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*16    T3502 value    GPRS timer 2     9.10.2.4     O    TLV    3*/
    // ELEM_OPT_TLV(0x16, GSM_A_PDU_TYPE_GM, DE_GPRS_TIMER_2, " - T3502 value");
    consumed = dissect_opt_elem_tlv(nullptr, &t3502_gprs_timer_2, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*34    Emergency number list    Emergency number list     9.11.3.17    O    TLV
     * 5-50*/
    // ELEM_OPT_TLV(0x34, GSM_A_PDU_TYPE_DTAP, DE_EMERGENCY_NUM_LIST, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &emerg_num_list, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*7A    Extended emergency number list    Extended emergency number list 9.11.3.24
     * O    TLV    TBD*/
    // ELEM_OPT_TLV(0x7A, NAS_PDU_TYPE_EMM, DE_EMM_EXT_EMERG_NUM_LIST, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &emerg_num_list_7a, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*73    SOR transparent container    SOR transparent container 9.11.3.51    O    TLV-E
     * 20-2048 */
    // ELEM_OPT_TLV_E(0x73, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_SOR_TRASP_CONT, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &sor_trans_cont, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*78    EAP message    EAP message 9.10.2.2    O    TLV-E    7-1503 */
    // ELEM_OPT_TLV_E(0x78, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eap_message, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /* A-    NSSAI inclusion mode    NSSAI inclusion mode 9.11.3.37A    O    TV    1 */
    // ELEM_OPT_TV_SHORT(0xA0, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_NSSAI_INC_MODE, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &nssai_inclusion_mode, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /* 76    Operator-defined access category definitions    Operator-defined access
     * category definitions 9.11.3.38    O    TLV-E    3-TBD */
    // ELEM_OPT_TLV_E(0x76, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_OP_DEF_ACC_CAT_DEF, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &operator_defined_acd, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /* 51    Negotiated DRX parameters    5GS DRX parameters 9.11.3.2A    O    TLV    3 */
    // ELEM_OPT_TLV(0x51,,DE_NAS_5GS_MM_5GS_DRX_PARAM," -  Negotiated DRX parameters");
    consumed = dissect_opt_elem_tlv(nullptr, &nego_drx_param, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);

    return d.tvb->reported_length;
}
namespace mm_reg_accept {
int                dissect_reg_res(dissector d, context* ctx = nullptr);
const element_meta reg_res = {
    0xff,
    "5GS registration result",
    dissect_reg_res,
};

int                dissect_guti_5gs_mobile_id(dissector d, context* ctx = nullptr);
const element_meta guti_5gs_mobile_id = {
    0x77,
    "",
    dissect_guti_5gs_mobile_id,
};

int                dissect_plmn_list(dissector d, context* ctx = nullptr);
const element_meta plmn_list = {
    0x4a,
    "Equivalent PLMNs",
    dissect_plmn_list,
};

int                dissect_ta_id_list(dissector d, context* ctx = nullptr);
const element_meta ta_id_list = {
    0x54,
    "TAI list",
    dissect_ta_id_list,
};

int                dissect_allowed_nssai(dissector d, context* ctx = nullptr);
const element_meta allowed_nssai = {
    0x15,
    "Allowed NSSAI",
    dissect_allowed_nssai,
};

int                dissect_rejected_nssai(dissector d, context* ctx = nullptr);
const element_meta rejected_nssai = {
    0x11,
    "Rejected NSSAI",
    dissect_rejected_nssai,
};

int                dissect_configured_nssai(dissector d, context* ctx = nullptr);
const element_meta configured_nssai = {
    0x31,
    "Configured NSSAI",
    dissect_configured_nssai,
};

int                dissect_nw_feat_sup(dissector d, context* ctx = nullptr);
const element_meta nw_feat_sup = {
    0x21,
    "5GS network feature support",
    dissect_nw_feat_sup,
};

int                dissect_pdu_ses_react_res(dissector d, context* ctx = nullptr);
const element_meta pdu_ses_react_res = {
    0x26,
    "PDU session reactivation result",
    dissect_pdu_ses_react_res,
};

int                dissect_pdu_ses_react_res_err_c(dissector d, context* ctx = nullptr);
const element_meta pdu_ses_react_res_err_c = {
    0x72,
    "PDU session reactivation result error cause",
    dissect_pdu_ses_react_res_err_c,
};

int                dissect_ladn_inf(dissector d, context* ctx = nullptr);
const element_meta ladn_inf = {
    0x79,
    "LADN information",
    dissect_ladn_inf,
};

int                dissect_mico_ind(dissector d, context* ctx = nullptr);
extern const element_meta mico_ind = {
    0xb0,
    "MICO indication",
    dissect_mico_ind,
};

int                dissect_nw_slicing_ind(dissector d, context* ctx = nullptr);
extern const element_meta nw_slicing_ind = {
    0x90,
    "Network slicing indication",
    dissect_nw_slicing_ind,
};

int                dissect_sal(dissector d, context* ctx = nullptr);
const element_meta sal = {
    0x27,
    "Service area list",
    dissect_sal,
};

int                dissect_t2512_gprs_timer_3(dissector d, context* ctx = nullptr);
const element_meta t3512_gprs_timer_3 = {
    0x5E,
    "T3512 value",
    dissect_t2512_gprs_timer_3,
};

int                dissect_de_reg_timer_gprs_timer2(dissector d, context* ctx = nullptr);
const element_meta de_reg_timer_gprs_timer2 = {
    0x5D,
    "Non-3GPP de-registration timer value",
    dissect_de_reg_timer_gprs_timer2,
};

int                dissect_t3502_gprs_timer_2(dissector d, context* ctx = nullptr);
const element_meta t3502_gprs_timer_2 = {
    0x16,
    "T3502 value",
    dissect_t3502_gprs_timer_2,
};

int                dissect_emerg_num_list(dissector d, context* ctx = nullptr);
const element_meta emerg_num_list = {
    0x34,
    "Emergency number list",
    dissect_emerg_num_list,
};

int                dissect_emerg_num_list_7a(dissector d, context* ctx = nullptr);
const element_meta emerg_num_list_7a = {
    0x7A,
    "Extended emergency number list",
    dissect_emerg_num_list_7a,
};

int                dissect_sor_trans_cont(dissector d, context* ctx = nullptr);
const element_meta sor_trans_cont = {
    0x73,
    "SOR transparent container",
    dissect_sor_trans_cont,
};

int                dissect_eap_message(dissector d, context* ctx = nullptr);
const element_meta eap_message = {
    0x78,
    "EAP message",
    dissect_eap_message,
};

int                dissect_nssai_inclusion_mode(dissector d, context* ctx = nullptr);
const element_meta nssai_inclusion_mode = {
    0xA0,
    "NSSAI inclusion mode",
    dissect_nssai_inclusion_mode,
};

int                dissect_operator_defined_acd(dissector d, context* ctx = nullptr);
const element_meta operator_defined_acd = {
    0x76,
    "Operator-defined access category definitions",
    dissect_operator_defined_acd,
};

int                dissect_nego_drx_param(dissector d, context* ctx = nullptr);
const element_meta nego_drx_param = {
    0x51,
    "Negotiated DRX parameters",
    dissect_nego_drx_param,
};

int dissect_reg_res(dissector d, context* ctx) { return 0; }

int dissect_guti_5gs_mobile_id(dissector d, context* ctx) { return 0; }

int dissect_plmn_list(dissector d, context* ctx) { return 0; }

int dissect_ta_id_list(dissector d, context* ctx) { return 0; }

int dissect_allowed_nssai(dissector d, context* ctx) { return 0; }

int dissect_rejected_nssai(dissector d, context* ctx) { return 0; }

int dissect_configured_nssai(dissector d, context* ctx) { return 0; }

int dissect_nw_feat_sup(dissector d, context* ctx) { return 0; }

int dissect_pdu_ses_status(dissector d, context* ctx) { return 0; }

int dissect_pdu_ses_react_res(dissector d, context* ctx) { return 0; }

int dissect_pdu_ses_react_res_err_c(dissector d, context* ctx) { return 0; }

int dissect_ladn_inf(dissector d, context* ctx) { return 0; }

int dissect_mico_ind(dissector d, context* ctx) { return 0; }

int dissect_nw_slicing_ind(dissector d, context* ctx) { return 0; }

int dissect_sal(dissector d, context* ctx) { return 0; }

int dissect_t2512_gprs_timer_3(dissector d, context* ctx) { return 0; }

int dissect_de_reg_timer_gprs_timer2(dissector d, context* ctx) { return 0; }

int dissect_t3502_gprs_timer_2(dissector d, context* ctx) { return 0; }

int dissect_emerg_num_list(dissector d, context* ctx) { return 0; }

int dissect_emerg_num_list_7a(dissector d, context* ctx) { return 0; }

int dissect_sor_trans_cont(dissector d, context* ctx) { return 0; }

int dissect_eap_message(dissector d, context* ctx) { return 0; }

int dissect_nssai_inclusion_mode(dissector d, context* ctx) { return 0; }

int dissect_operator_defined_acd(dissector d, context* ctx) { return 0; }

int dissect_nego_drx_param(dissector d, context* ctx) { return 0; }

} // namespace mm_reg_accept
