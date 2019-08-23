#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_reg_req {
extern const field_meta *hf_reg_req_flags;

extern const element_meta nw_slicing_ind;
extern const element_meta eps_nas_msg_cont;
extern const element_meta ue_status;
extern const element_meta last_v_tai;
extern const element_meta nksi_key_set_id;
extern const element_meta pld_cont;
extern const element_meta ladn_inf;
extern const element_meta ue_sec_cap;
extern const element_meta mm_cap;
extern const element_meta ul_data_status;
extern const element_meta s1_ue_net_cap;
extern const element_meta ue_usage_set;
extern const element_meta allow_pdu_ses_sts;
extern const element_meta aguti_mobile_id;
extern const element_meta pld_cont_type;
extern const element_meta update_type;
extern const element_meta requested_drx_param;
extern const element_meta mico_ind;
extern const element_meta mm_requested_nssai;

} // namespace mm_reg_req

/* * 8.2.6 Registration request */
int mm::registration_req(dissector d, context* ctx) {
    // using namespace em_de_mm;
    using namespace mm_reg_req;

    d.pinfo->dir = pi_dir::ul;
    // get private data

    /*   5GS registration type    5GS registration type 9.11.3.7    M    V    1/2  H0*/
    /*    ngKSI    NAS key set identifier 9.11.3.32    M    V    1/2 H1*/
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_reg_req_flags, enc::be);
    d.offset++;
    d.length--;

    /*    Mobile identity    5GS mobile identity 9.11.3.4    M    LV-E    6-n*/
    auto consumed = dissect_elem_lv_e(nullptr, &mobile_id, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    /*C-    Non-current native NAS KSI    NAS key set identifier 9.11.3.32    O    TV 1*/
    // ELEM_OPT_TV_SHORT( 0xc0, , DE_NAS_5GS_MM_NAS_KEY_SET_ID, " - native KSI");
    consumed = dissect_opt_elem_tv_short(nullptr, &nksi_key_set_id, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    /*10    5GMM capability    5GMM capability 9.11.3.1    O    TLV    3-15*/
    // ELEM_OPT_TLV(0x10, , DE_NAS_5GS_MM_5GMM_CAP, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &mm_cap, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    /*2E    UE security capability    UE security capability 9.11.3.54    O    TLV 4-10*/
    // ELEM_OPT_TLV(0x2e, , DE_NAS_5GS_MM_UE_SEC_CAP, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &ue_sec_cap, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    /*2F    Requested NSSAI    NSSAI 9.11.3.37    O    TLV    4-74*/
    // ELEM_OPT_TLV(0x2f, , DE_NAS_5GS_MM_NSSAI, " - Requested NSSAI");
    consumed = dissect_opt_elem_tlv(nullptr, &mm_requested_nssai, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    /*52    Last visited registered TAI    5GS tracking area identity 9.11.3.8    O    TV
     * 7 */
    // ELEM_OPT_TV(0x52, DE_NAS_5GS_MM_5GS_TA_ID, " - Last visited registered TAI");
    consumed = dissect_opt_elem_tv(nullptr, &last_v_tai, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    /*17    S1 UE network capability    S1 UE network capability 9.11.3.48    O    TLV
     * 4-15 */
    //    ELEM_OPT_TLV(0x17, , DE_EMM_UE_NET_CAP, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &s1_ue_net_cap, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    /*40    Uplink data status    Uplink data status 9.11.3.57    O    TLV    4-34 */
    //    ELEM_OPT_TLV(0x40, , DE_NAS_5GS_MM_UL_DATA_STATUS, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &ul_data_status, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    /*50    PDU session status    PDU session status 9.11.3.44    O    TLV    4-34 */
    //    ELEM_OPT_TLV(0x50, , DE_NAS_5GS_MM_PDU_SES_STATUS, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &pdu_ses_status, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    /*B-    MICO indication    MICO indication 9.11.3.31    O    TV    1*/
    //    ELEM_OPT_TV_SHORT(0xb0, , DE_NAS_5GS_MM_MICO_IND, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &mico_ind, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    /*2B    UE status    UE status 9.11.3.56    O    TLV    3*/
    //    ELEM_OPT_TLV(0x2b, , DE_NAS_5GS_MM_UE_STATUS, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &ue_status, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    /*77    Additional GUTI    5GS mobile identity 9.11.3.4    O    TLV-E    14 */
    // ELEM_OPT_TLV_E(0x77, , DE_NAS_5GS_MM_5GS_MOBILE_ID, " -  Additional GUTI");
    consumed = dissect_opt_elem_tlv_e(nullptr, &aguti_mobile_id, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    /*25    Allowed PDU session status    Allowed PDU session status         9.11.3.13
     * O    TLV    4 - 34 */
    //    ELEM_OPT_TLV(0x25, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_ALLOW_PDU_SES_STS, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &allow_pdu_ses_sts, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    /*18    UE's usage setting    UE's usage setting         9.11.3.55    O    TLV    3 */
    // ELEM_OPT_TLV(0x18, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_UE_USAGE_SET, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &ue_usage_set, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    /*51    Requested DRX parameters    5GS DRX parameters 9.11.3.2A    O    TLV    3 */
    /*    ELEM_OPT_TLV(0x51,DE_NAS_5GS_MM_5GS_DRX_PARAM, " - Requested DRX parameters");    */
    consumed = dissect_opt_elem_tlv(nullptr, &requested_drx_param, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    /*70    EPS NAS message container    EPS NAS message container 9.11.3.24    O    TLV-E
     * 4-n */
    // ELEM_OPT_TLV_E(0x70, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_EPS_NAS_MSG_CONT, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eps_nas_msg_cont, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    /* 74    LADN indication    LADN indication 9.11.3.29    O    TLV-E    3-811 */
    // ELEM_OPT_TLV_E(0x74, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_LADN_INF, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ladn_inf, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    /* 8-    Payload container type    Payload container type 9.11.3.40    O    TV    1 */
    // ELEM_OPT_TV_SHORT(0x80, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_PLD_CONT_TYPE, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &pld_cont_type, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    /* 7B    Payload container     Payload container 9.11.3.39    O    TLV-E    4-65538 */
    // ELEM_OPT_TLV_E(0x7B, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_PLD_CONT, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &pld_cont, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    /* 9-    Network slicing indication    Network slicing indication 9.11.3.36    O    TV
     * 1 */
    // ELEM_OPT_TV_SHORT(0x90, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_NW_SLICING_IND, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &nw_slicing_ind, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    /* 53    5GS update type    5GS update type 9.11.3.9A    O    TLV    3 */
    // ELEM_OPT_TLV(0x53, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_UPDATE_TYPE, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &update_type, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    /* 71    NAS message container    NAS message container 9.11.3.33    O    TLV-E    4-n
     */
    // ELEM_OPT_TLV_E(0x71, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_NAS_MSG_CONT, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &nas_msg_cont, d, ctx);
    d.offset -= consumed;
    d.length -= consumed;

    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);

    return d.tvb->reported_length;
}
