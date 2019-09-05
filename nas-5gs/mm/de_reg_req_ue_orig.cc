#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

/* * 8.2.6 Registration request */
int mm::dissect_registration_req(dissector d, context* ctx) {
    const use_context uc(ctx, "registration request", d, 6);    

    up_link(d.pinfo);
    // get private data

    /*   5GS registration type  9.11.3.7    M    V    1/2  H0*/
    // d.add_item(1, hf_reg_req_flags, enc::be);
    auto consumed = dissect_elem_v(nullptr, &registration_request_type, d, ctx);
    /*    ngKSI    NAS key set identifier 9.11.3.32    M    V    1/2 H1*/
    d.add_item(1, &hf_ngksi_nas_ksi, enc::be);
    d.step(consumed);

    /*    Mobile identity    5GS mobile identity 9.11.3.4    M    LV-E    6-n*/
    consumed = dissect_elem_lv_e(nullptr, &mobile_id, d, ctx);
    d.step(consumed);

    /*C-    Non-current native NAS KSI    NAS key set identifier 9.11.3.32    O    TV 1*/
    // ELEM_OPT_TV_SHORT( 0xc0, , DE_NAS_5GS_MM_NAS_KEY_SET_ID, " - native KSI");
    consumed = dissect_opt_elem_tv_short(nullptr, &nc_native_nas_ksi, d, ctx);
    d.step(consumed);

    /*10    5GMM capability  9.11.3.1    O    TLV    3-15*/
    consumed = dissect_opt_elem_tlv(nullptr, &mm_cap, d, ctx);
    d.step(consumed);

    /*2E    UE security capability   9.11.3.54    O    TLV 4-10*/
    // ELEM_OPT_TLV(0x2e, , DE_NAS_5GS_MM_UE_SEC_CAP, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &ue_sec_cap, d, ctx);
    d.step(consumed);

    /*2F    Requested NSSAI    NSSAI 9.11.3.37    O    TLV    4-74*/
    consumed = dissect_opt_elem_tlv(nullptr, &requested_nssai, d, ctx);
    d.step(consumed);

    /*52 Last visited registered TAI 5GS tracking area identity 9.11.3.8 O TV  7 */
    // ELEM_OPT_TV(0x52, DE_NAS_5GS_MM_5GS_TA_ID, " - Last visited registered TAI");
    consumed = dissect_opt_elem_tv(nullptr, &last_v_tai, d, ctx);
    d.step(consumed);

    /*17    S1 UE network capability  9.11.3.48    O    TLV  4-15 */
    // ELEM_OPT_TLV(0x17, , DE_EMM_UE_NET_CAP, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &s1_ue_net_cap, d, ctx);
    d.step(consumed);

    /*40    Uplink data status  9.11.3.57    O    TLV    4-34 */
    // ELEM_OPT_TLV(0x40, , DE_NAS_5GS_MM_UL_DATA_STATUS, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &ul_data_status, d, ctx);
    d.step(consumed);

    /*50    PDU session status  9.11.3.44    O    TLV    4-34 */
    // ELEM_OPT_TLV(0x50, , DE_NAS_5GS_MM_PDU_SES_STATUS, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &pdu_ses_status, d, ctx);
    d.step(consumed);

    /*B-  MICO indication 9.11.3.31    O    TV    1*/
    // ELEM_OPT_TV_SHORT(0xb0, , DE_NAS_5GS_MM_MICO_IND, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &mico_ind, d, ctx);
    d.step(consumed);

    /*2B UE status 9.11.3.56    O    TLV    3*/
    // ELEM_OPT_TLV(0x2b, , DE_NAS_5GS_MM_UE_STATUS, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &ue_status, d, ctx);
    d.step(consumed);

    /*77    Additional GUTI    5GS mobile identity 9.11.3.4    O    TLV-E    14 */
    // ELEM_OPT_TLV_E(0x77, , DE_NAS_5GS_MM_5GS_MOBILE_ID, " -  Additional GUTI");
    consumed = dissect_opt_elem_tlv_e(nullptr, &aguti_mobile_id, d, ctx);
    d.step(consumed);

    /*25    Allowed PDU session status    9.11.3.13  O    TLV    4 - 34 */
    // ELEM_OPT_TLV(0x25, , DE_NAS_5GS_MM_ALLOW_PDU_SES_STS, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &allow_pdu_ses_sts, d, ctx);
    d.step(consumed);

    /*18    UE's usage setting    9.11.3.55    O    TLV    3 */
    // ELEM_OPT_TLV(0x18, , DE_NAS_5GS_MM_UE_USAGE_SET, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &ue_usage_set, d, ctx);
    d.step(consumed);

    /* 51    Requested DRX parameters    5GS DRX parameters 9.11.3.2A    O    TLV    3 */
    /* ELEM_OPT_TLV(0x51,DE_NAS_5GS_MM_5GS_DRX_PARAM, " - Requested DRX parameters"); */
    consumed = dissect_opt_elem_tlv(nullptr, &requested_drx_param, d, ctx);
    d.step(consumed);

    /* 70    EPS NAS message container  9.11.3.24    O    TLV-E 4-n */
    // ELEM_OPT_TLV_E(0x70, , DE_NAS_5GS_MM_EPS_NAS_MSG_CONT, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eps_nas_msg_cont, d, ctx);
    d.step(consumed);

    /* 74    LADN indication  9.11.3.29    O    TLV-E    3-811 */
    // ELEM_OPT_TLV_E(0x74, , DE_NAS_5GS_MM_LADN_IND, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ladn_ind, d, ctx);
    d.step(consumed);

    /* 8-    Payload container type  9.11.3.40    O    TV    1 */
    // ELEM_OPT_TV_SHORT(0x80, , DE_NAS_5GS_MM_PLD_CONT_TYPE, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &pld_cont_type, d, ctx);
    d.step(consumed);

    /* 7B    Payload container  9.11.3.39    O    TLV-E    4-65538 */
    // ELEM_OPT_TLV_E(0x7B, , DE_NAS_5GS_MM_PLD_CONT, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &pld_cont, d, ctx);
    d.step(consumed);

    /* 9-    Network slicing indication 9.11.3.36    O    TV 1 */
    // ELEM_OPT_TV_SHORT(0x90, , DE_NAS_5GS_MM_NW_SLICING_IND, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &nw_slicing_ind, d, ctx);
    d.step(consumed);

    /* 53    5GS update type 9.11.3.9A    O    TLV    3 */
    // ELEM_OPT_TLV(0x53, , DE_NAS_5GS_MM_UPDATE_TYPE, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &update_type, d, ctx);
    d.step(consumed);

    /* Mobile station classmark 2 9.11.3.61
     * Supported codec list 9.11.3.62
     */

    /* 71    NAS message container 9.11.3.33    O    TLV-E    4-n */
    // ELEM_OPT_TLV_E(0x71, , DE_NAS_5GS_MM_NAS_MSG_CONT, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &nas_msg_cont, d, ctx);
    d.step(consumed);

    /*60	EPS bearer context status	9.11.3.59	O	TLV	4 */
    consumed = dissect_opt_elem_tlv(nullptr, &eps_bearer_ctx_status, d, ctx);
    d.step(consumed);

    /* XX	Requested extended DRX parameters 9.11.3.60	O TLV 3*/
    /* TBD	T3324 value	GPRS timer 3 9.11.2.5	O	TLV	3 */

    d.extraneous_data_check(0);

    return uc.length;
}

namespace mm_de_reg {
extern const element_meta de_reg_type;
extern const element_meta key_set_id;
} // namespace mm_de_reg_req_ue_orig

/*
 * 8.2.12 De-registration request (UE originating de-registration)
 */
int mm::dissect_reg_req_ue_orig(dissector d, context* ctx) {
    auto        len = d.length;
    use_context uc(ctx, "ue-originating-de-registration", d);

    using namespace mm_de_reg;

    /* De-registration type   9.11.3.20   M   V   1 */
    /*ELEM_MAND_V(DE_NAS_5GS_MM_DE_REG_TYPE,);*/
    auto consumed = dissect_elem_v(nullptr, &de_reg_type, d, ctx);

    /* ngKSI    NAS key set identifier 9.11.3.32    M    V    1/2 H1 */
    d.step(consumed);

    /* 5GS mobile identity  9.11.3.4    M    LV-E    6-n */
    /*ELEM_MAND_LV_E(DE_NAS_5GS_MM_5GS_MOBILE_ID,); */
    consumed = dissect_elem_lv_e(nullptr, &key_set_id, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);
    return len;
}

namespace mm {

} // namespace mm_de_reg_req_ue_orig
