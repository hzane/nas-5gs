#include "dissect_mm_msg.hh"
#include "ts24007.hh"

#include "mm_registration_req.hh"


/*
 * 8.2.6 Registration request
 */
int mm::nas_5gs_mm_registration_req(packet_info* pinfo,
                                    proto_node*  tree,
                                    tvbuff*      buf,
                                    int          offset,
                                    int          len,
                                    context*     ctx) {
    using namespace em_de_mm;
    pinfo->dir = pi_dir::ul;
    // get private data

    /*   5GS registration type    5GS registration type 9.11.3.7    M    V    1/2  H0*/
    /*    ngKSI    NAS key set identifier 9.11.3.32    M    V    1/2 H1*/
    tree->add_item(pinfo, buf, offset, 1, hf_registration_req_flags, enc::be);    
    offset++;
    len--;

    /*    Mobile identity    5GS mobile identity 9.11.3.4    M    LV-E    6-n*/
    auto consumed = dissect_elem_lv_e(nullptr, &mobile_id, tree, pinfo, buf, offset, len);
    offset -= consumed;
    len -= consumed;

    /*C-    Non-current native NAS KSI    NAS key set identifier 9.11.3.32    O    TV 1*/
    //ELEM_OPT_TV_SHORT(
        //0xc0, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_NAS_KEY_SET_ID, " - native KSI");
    dissect_opt_elem_tv_short(
        hf_mm_registration_req_elem, &nksi_key_set_id, tree, pinfo, buf, offset, len);
    

    /*10    5GMM capability    5GMM capability 9.11.3.1    O    TLV    3-15*/
    // ELEM_OPT_TLV(0x10, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_5GMM_CAP, NULL);
    dissect_opt_elem_tlv(
        hf_mm_registration_req_elem, &mm_cap, tree, pinfo, buf, offset, len);

    /*2E    UE security capability    UE security capability 9.11.3.54    O    TLV 4-10*/
    // ELEM_OPT_TLV(0x2e, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_UE_SEC_CAP, NULL);
    dissect_opt_elem_tlv(
        hf_mm_registration_req_elem, &ue_sec_cap, tree, pinfo, buf, offset, len);

    /*2F    Requested NSSAI    NSSAI 9.11.3.37    O    TLV    4-74*/
    // ELEM_OPT_TLV(0x2f, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_NSSAI, " - Requested NSSAI");
    dissect_opt_elem_tlv(
        hf_mm_registration_req_elem, &mm_requested_nssai, tree, pinfo, buf, offset, len);

    /*52    Last visited registered TAI    5GS tracking area identity 9.11.3.8    O    TV
     * 7 */
    //ELEM_OPT_TV(0x52,
      //          NAS_5GS_PDU_TYPE_MM,
        //        DE_NAS_5GS_MM_5GS_TA_ID,
          //      " - Last visited registered TAI");
    dissect_opt_elem_tv(
        hf_mm_registration_req_elem, &last_v_tai, tree, pinfo, buf, offset, len);

    /*17    S1 UE network capability    S1 UE network capability 9.11.3.48    O    TLV
     * 4-15 */
//    ELEM_OPT_TLV(0x17, NAS_PDU_TYPE_EMM, DE_EMM_UE_NET_CAP, NULL);
    dissect_opt_elem_tlv(
        hf_mm_registration_req_elem, &s1_ue_net_cap, tree, pinfo, buf, offset, len);

    /*40    Uplink data status    Uplink data status 9.11.3.57    O    TLV    4-34 */
//    ELEM_OPT_TLV(0x40, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_UL_DATA_STATUS, NULL);
    dissect_opt_elem_tlv(
        hf_mm_registration_req_elem, &ul_data_status, tree, pinfo, buf, offset, len);

    /*50    PDU session status    PDU session status 9.11.3.44    O    TLV    4-34 */
//    ELEM_OPT_TLV(0x50, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_PDU_SES_STATUS, NULL);
    dissect_opt_elem_tlv(
        hf_mm_registration_req_elem, &pdu_ses_status, tree, pinfo, buf, offset, len);

    /*B-    MICO indication    MICO indication 9.11.3.31    O    TV    1*/
//    ELEM_OPT_TV_SHORT(0xb0, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_MICO_IND, NULL);
    dissect_opt_elem_tv_short(
        hf_mm_registration_req_elem, &mico_ind, tree, pinfo, buf, offset, len);

    /*2B    UE status    UE status 9.11.3.56    O    TLV    3*/
//    ELEM_OPT_TLV(0x2b, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_UE_STATUS, NULL);
    dissect_opt_elem_tlv(
        hf_mm_registration_req_elem, &ue_status, tree, pinfo, buf, offset, len);

    /*77    Additional GUTI    5GS mobile identity 9.11.3.4    O    TLV-E    14 */
    //ELEM_OPT_TLV_E(
//        0x77, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_5GS_MOBILE_ID, " -  Additional GUTI");
    dissect_opt_elem_tlv_e(
        hf_mm_registration_req_elem, &aguti_mobile_id, tree, pinfo, buf, offset, len);

    /*25    Allowed PDU session status    Allowed PDU session status         9.11.3.13
     * O    TLV    4 - 34 */
//    ELEM_OPT_TLV(0x25, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_ALLOW_PDU_SES_STS, NULL);
    dissect_opt_elem_tlv(
        hf_mm_registration_req_elem, &allow_pdu_ses_sts, tree, pinfo, buf, offset, len);

    /*18    UE's usage setting    UE's usage setting         9.11.3.55    O    TLV    3 */
    //ELEM_OPT_TLV(0x18, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_UE_USAGE_SET, NULL);
    dissect_opt_elem_tlv(
        hf_mm_registration_req_elem, &ue_usage_set, tree, pinfo, buf, offset, len);

    /*51    Requested DRX parameters    5GS DRX parameters 9.11.3.2A    O    TLV    3 */
/*    ELEM_OPT_TLV(0x51,
                 NAS_5GS_PDU_TYPE_MM,
                 DE_NAS_5GS_MM_5GS_DRX_PARAM,
                 " - Requested DRX parameters");
*/
    dissect_opt_elem_tlv(
        hf_mm_registration_req_elem, &requested_drx_param, tree, pinfo, buf, offset, len);

    /*70    EPS NAS message container    EPS NAS message container 9.11.3.24    O    TLV-E
     * 4-n */
    //ELEM_OPT_TLV_E(0x70, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_EPS_NAS_MSG_CONT, NULL);
    dissect_opt_elem_tlv_e(
        hf_mm_registration_req_elem, &eps_nas_msg_cont, tree, pinfo, buf, offset, len);

    /* 74    LADN indication    LADN indication 9.11.3.29    O    TLV-E    3-811 */
    // ELEM_OPT_TLV_E(0x74, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_LADN_INF, NULL);
    dissect_opt_elem_tlv_e(
        hf_mm_registration_req_elem, &ladn_inf, tree, pinfo, buf, offset, len);

    /* 8-    Payload container type    Payload container type 9.11.3.40    O    TV    1 */
    // ELEM_OPT_TV_SHORT(0x80, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_PLD_CONT_TYPE, NULL);
    dissect_opt_elem_tv_short(
        hf_mm_registration_req_elem, &pld_cont_type, tree, pinfo, buf, offset, len);

    /* 7B    Payload container     Payload container 9.11.3.39    O    TLV-E    4-65538 */
    // ELEM_OPT_TLV_E(0x7B, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_PLD_CONT, NULL);
    dissect_opt_elem_tlv_e(
        hf_mm_registration_req_elem, &pld_cont, tree, pinfo, buf, offset, len);

    /* 9-    Network slicing indication    Network slicing indication 9.11.3.36    O    TV
     * 1 */
    // ELEM_OPT_TV_SHORT(0x90, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_NW_SLICING_IND, NULL);
    dissect_opt_elem_tv_short(
        hf_mm_registration_req_elem, &nw_slicing_ind, tree, pinfo, buf, offset, len);

    /* 53    5GS update type    5GS update type 9.11.3.9A    O    TLV    3 */
    // ELEM_OPT_TLV(0x53, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_UPDATE_TYPE, NULL);
    dissect_opt_elem_tlv(
        hf_mm_registration_req_elem, &update_type, tree, pinfo, buf, offset, len);

    /* 71    NAS message container    NAS message container 9.11.3.33    O    TLV-E    4-n
     */
    // ELEM_OPT_TLV_E(0x71, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_NAS_MSG_CONT, NULL);
    dissect_opt_elem_tlv_e(
        hf_mm_registration_req_elem, &nas_msg_cont, tree, pinfo, buf, offset, len);

    extraneous_data_check(pinfo, tree, buf, offset, len, 0);
    // EXTRANEOUS_DATA_CHECK(curr_len, 0, pinfo, &ei_nas_5gs_extraneous_data);

    return 0;
}

int mm::nas_5gs_mm_registration_accept(packet_info* pinfo,
                                       proto_node*  tree,
                                       tvbuff*      buf,
                                       int          offset,
                                       int          len,
                                       context*     ctx) {
    using namespace em_de_mm_reg_accept;

    /*      5GS registration result    5GS registration result     9.11.3.6    M    LV 2*/
    dissect_elem_lv(nullptr, &reg_res, tree, pinfo, buf, offset, len);

    /*77    5G-GUTI    5GS mobile identity 9.11.3.4    O    TLV-E    14 */    
    // ELEM_OPT_TLV_E(0x77, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_5GS_MOBILE_ID, " - 5G-GUTI");
    dissect_opt_elem_tlv_e(
        nullptr, &guti_5gs_mobile_id, tree, pinfo, buf, offset, len);

    /*4A    Equivalent PLMNs    PLMN list     9.11.3.33    O    TLV    5-47*/
    // ELEM_OPT_TLV(0x4a, GSM_A_PDU_TYPE_COMMON, DE_PLMN_LIST, " - Equivalent PLMNs");
    dissect_opt_elem_tlv(nullptr, &plmn_list, tree, pinfo, buf, offset, len);

    /*54    TAI list    Tracking area identity list     9.11.3.9    O    TLV    8-98*/
    // ELEM_OPT_TLV(0x54, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_5GS_TA_ID_LIST, NULL);
    dissect_opt_elem_tlv(
        nullptr, &ta_id_list, tree, pinfo, buf, offset, len);


    /*15    Allowed NSSAI    NSSAI     9.11.3.28    O    TLV    4-74*/
    // ELEM_OPT_TLV(0x15, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_NSSAI, " - Allowed NSSAI");
    dissect_opt_elem_tlv(
        nullptr, &allowed_nssai, tree, pinfo, buf, offset, len);

    /*11    Rejected NSSAI    Rejected NSSAI     9.11.3.35    O    TLV    4-42*/
    // ELEM_OPT_TLV(0x11, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_REJ_NSSAI, NULL);
    dissect_opt_elem_tlv(
        nullptr, &rejected_nssai, tree, pinfo, buf, offset, len);

    /*31    Configured NSSAI    NSSAI 9.11.3.34    O    TLV    4-146 */
    // ELEM_OPT_TLV(0x31, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_NSSAI, " - Configured NSSAI");
    dissect_opt_elem_tlv(
        nullptr, &configured_nssai, tree, pinfo, buf, offset, len);

    /*21    5GS network feature support    5GS network feature support 9.11.3.5    O TLV
     * 3-5 */
    // ELEM_OPT_TLV(0x21, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_5GS_NW_FEAT_SUP, NULL);
    dissect_opt_elem_tlv(
        nullptr, &nw_feat_sup, tree, pinfo, buf, offset, len);

    /*50    PDU session status    PDU session status     9.10.2.2    O    TLV    4*/
    // ELEM_OPT_TLV(0x50, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_PDU_SES_STATUS, NULL);
    dissect_opt_elem_tlv(
        nullptr, &pdu_ses_status, tree, pinfo, buf, offset, len);

    /*26    PDU session reactivation result    PDU session reactivation
     * result     9.11.3.32    O    TLV    4-32*/
    // ELEM_OPT_TLV(0x26, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_PDU_SES_REACT_RES, NULL);
    dissect_opt_elem_tlv(
        nullptr, &pdu_ses_react_res, tree, pinfo, buf, offset, len);

    /*72    PDU session reactivation result error cause PDU session reactivation result
     * error cause 9.11.3.40  O TLV-E  5-515*/
    //ELEM_OPT_TLV_E(
        //0x72, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_PDU_SES_REACT_RES_ERR_C, NULL);
    dissect_opt_elem_tlv_e(
        nullptr, &pdu_ses_react_res_err_c, tree, pinfo, buf, offset, len);

    /*79    LADN information    LADN information     9.11.3.19    O    TLV-E    11-1579*/
    // ELEM_OPT_TLV_E(0x79, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_LADN_INF, NULL);
    dissect_opt_elem_tlv_e(
        nullptr, &ladn_inf, tree, pinfo, buf, offset, len);

    /*B-    MICO indication    MICO indication     9.11.3.21    O    TV    1*/
    // ELEM_OPT_TV_SHORT(0xb0, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_MICO_IND, NULL);
    dissect_opt_elem_tv_short(
        nullptr, &mico_ind, tree, pinfo, buf, offset, len);

    /* 9-    Network slicing indication    Network slicing indication 9.11.3.36    O    TV
     * 1 */
    // ELEM_OPT_TV_SHORT(0x90, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_NW_SLICING_IND, NULL);
    dissect_opt_elem_tv_short(
        nullptr, &nw_slicing_ind, tree, pinfo, buf, offset, len);

    /*27    Service area list    Service area list     9.11.3.47    O    TLV    6-194*/
    // ELEM_OPT_TLV(0x27, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_SAL, NULL);
    dissect_opt_elem_tlv(
        nullptr, &sal, tree, pinfo, buf, offset, len);

    /*5E    T3512 value    GPRS timer 3     9.11.3.21    O    TLV    3*/
    // ELEM_OPT_TLV(0x5E, GSM_A_PDU_TYPE_GM, DE_GPRS_TIMER_3, " - T3512 value");
    dissect_opt_elem_tlv(
        nullptr, &t3512_gprs_timer_3, tree, pinfo, buf, offset, len);

    /*5D    Non-3GPP de-registration timer value    GPRS timer 2     9.11.3.20    O    TLV
     * 3*/
    //ELEM_OPT_TLV(0x5D,
                 //GSM_A_PDU_TYPE_GM,
                 //DE_GPRS_TIMER_2,
                 //" - Non-3GPP de-registration timer value");
    dissect_opt_elem_tlv(
        nullptr, &de_reg_timer_gprs_timer2, tree, pinfo, buf, offset, len);

    /*16    T3502 value    GPRS timer 2     9.10.2.4     O    TLV    3*/
    // ELEM_OPT_TLV(0x16, GSM_A_PDU_TYPE_GM, DE_GPRS_TIMER_2, " - T3502 value");
    dissect_opt_elem_tlv(
        nullptr, &gprs_timer_2, tree, pinfo, buf, offset, len);

    /*34    Emergency number list    Emergency number list     9.11.3.17    O    TLV
     * 5-50*/
    // ELEM_OPT_TLV(0x34, GSM_A_PDU_TYPE_DTAP, DE_EMERGENCY_NUM_LIST, NULL);
    dissect_opt_elem_tlv(
        nullptr, &emerg_num_list, tree, pinfo, buf, offset, len);

    /*7A    Extended emergency number list    Extended emergency number list 9.11.3.24
     * O    TLV    TBD*/
    // ELEM_OPT_TLV(0x7A, NAS_PDU_TYPE_EMM, DE_EMM_EXT_EMERG_NUM_LIST, NULL);
    dissect_opt_elem_tlv(
        nullptr, &emerg_num_list_7a, tree, pinfo, buf, offset, len);

    /*73    SOR transparent container    SOR transparent container 9.11.3.51    O    TLV-E
     * 20-2048 */
    // ELEM_OPT_TLV_E(0x73, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_SOR_TRASP_CONT, NULL);
    dissect_opt_elem_tlv_e(
        nullptr, &sor_trans_cont, tree, pinfo, buf, offset, len);

    /*78    EAP message    EAP message 9.10.2.2    O    TLV-E    7-1503 */
    // ELEM_OPT_TLV_E(0x78, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    dissect_opt_elem_tlv_e(
        nullptr, &eap_message, tree, pinfo, buf, offset, len);

    /* A-    NSSAI inclusion mode    NSSAI inclusion mode 9.11.3.37A    O    TV    1 */
    // ELEM_OPT_TV_SHORT(0xA0, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_NSSAI_INC_MODE, NULL);
    dissect_opt_elem_tv_short(
        nullptr, &nssai_inclusion_mode, tree, pinfo, buf, offset, len);

    /* 76    Operator-defined access category definitions    Operator-defined access
     * category definitions 9.11.3.38    O    TLV-E    3-TBD */
    // ELEM_OPT_TLV_E(0x76, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_OP_DEF_ACC_CAT_DEF, NULL);
    dissect_opt_elem_tlv_e(
        nullptr, &operator_defined_acd, tree, pinfo, buf, offset, len);

    /* 51    Negotiated DRX parameters    5GS DRX parameters 9.11.3.2A    O    TLV    3 */
    //ELEM_OPT_TLV(0x51,
                 //NAS_5GS_PDU_TYPE_MM,
                 //DE_NAS_5GS_MM_5GS_DRX_PARAM,
                 //" -  Negotiated DRX parameters");
    dissect_opt_elem_tlv(
        nullptr, &nego_drx_param, tree, pinfo, buf, offset, len);

    extraneous_data_check(pinfo, tree, buf, offset, len, 0);
    // EXTRANEOUS_DATA_CHECK(curr_len, 0, pinfo, &ei_nas_5gs_extraneous_data);
    return 0;
}

/*
 * 8.2.8 Registration complete
 */
int mm::nas_5gs_mm_registration_complete(packet_info* pinfo,
                                         proto_node*  tree,
                                         tvbuff*      buf,
                                         int          offset,
                                         int          len,
                                         context*     ctx) {
    /* 73    SOR transparent container    SOR transparent container 9.11.3.51    O TLV-E
     * 20-2048 */
    extraneous_data_check(pinfo, tree, buf, offset, len, 0);
    return 0;
}

int mm::nas_5gs_mm_registration_rej(packet_info* pinfo,
                                    proto_node*  tree,
                                    tvbuff*      buf,
                                    int          offset,
                                    int          len,
                                    context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_de_reg_req_ue_orig(packet_info* pinfo,
                                      proto_node*  tree,
                                      tvbuff*      buf,
                                      int          offset,
                                      int          len,
                                      context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_de_registration_req_ue_term(packet_info* pinfo,
                                               proto_node*  tree,
                                               tvbuff*      buf,
                                               int          offset,
                                               int          len,
                                               context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_service_req(packet_info* pinfo,
                               proto_node*  tree,
                               tvbuff*      buf,
                               int          offset,
                               int          len,
                               context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_service_rej(packet_info* pinfo,
                               proto_node*  tree,
                               tvbuff*      buf,
                               int          offset,
                               int          len,
                               context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_service_acc(packet_info* pinfo,
                               proto_node*  tree,
                               tvbuff*      buf,
                               int          offset,
                               int          len,
                               context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_conf_upd_cmd(packet_info* pinfo,
                                proto_node*  tree,
                                tvbuff*      buf,
                                int          offset,
                                int          len,
                                context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_conf_update_comp(packet_info* pinfo,
                                    proto_node*  tree,
                                    tvbuff*      buf,
                                    int          offset,
                                    int          len,
                                    context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_authentication_req(packet_info* pinfo,
                                      proto_node*  tree,
                                      tvbuff*      buf,
                                      int          offset,
                                      int          len,
                                      context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_authentication_resp(packet_info* pinfo,
                                       proto_node*  tree,
                                       tvbuff*      buf,
                                       int          offset,
                                       int          len,
                                       context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_authentication_rej(packet_info* pinfo,
                                      proto_node*  tree,
                                      tvbuff*      buf,
                                      int          offset,
                                      int          len,
                                      context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_authentication_failure(packet_info* pinfo,
                                          proto_node*  tree,
                                          tvbuff*      buf,
                                          int          offset,
                                          int          len,
                                          context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_authentication_result(packet_info* pinfo,
                                         proto_node*  tree,
                                         tvbuff*      buf,
                                         int          offset,
                                         int          len,
                                         context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_id_req(packet_info* pinfo,
                          proto_node*  tree,
                          tvbuff*      buf,
                          int          offset,
                          int          len,
                          context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_id_resp(packet_info* pinfo,
                           proto_node*  tree,
                           tvbuff*      buf,
                           int          offset,
                           int          len,
                           context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_sec_mode_cmd(packet_info* pinfo,
                                proto_node*  tree,
                                tvbuff*      buf,
                                int          offset,
                                int          len,
                                context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_sec_mode_comp(packet_info* pinfo,
                                 proto_node*  tree,
                                 tvbuff*      buf,
                                 int          offset,
                                 int          len,
                                 context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_sec_mode_rej(packet_info* pinfo,
                                proto_node*  tree,
                                tvbuff*      buf,
                                int          offset,
                                int          len,
                                context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_5gmm_status(packet_info* pinfo,
                               proto_node*  tree,
                               tvbuff*      buf,
                               int          offset,
                               int          len,
                               context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_notification(packet_info* pinfo,
                                proto_node*  tree,
                                tvbuff*      buf,
                                int          offset,
                                int          len,
                                context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_notification_resp(packet_info* pinfo,
                                     proto_node*  tree,
                                     tvbuff*      buf,
                                     int          offset,
                                     int          len,
                                     context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_ul_nas_transp(packet_info* pinfo,
                                 proto_node*  tree,
                                 tvbuff*      buf,
                                 int          offset,
                                 int          len,
                                 context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_dl_nas_transp(packet_info* pinfo,
                                 proto_node*  tree,
                                 tvbuff*      buf,
                                 int          offset,
                                 int          len,
                                 context*     ctx) {
    return 0;
}
