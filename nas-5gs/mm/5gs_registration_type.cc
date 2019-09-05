#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

/* 9.11.3.7    5GS registration type */

extern const val_string mm::values_registration_type[] = {
    {0x1, "initial registration"},
    {0x2, "mobility registration updating"},
    {0x3, "periodic registration updating"},
    {0x4, "emergency registration"},
    {0x7, "reserved"},
    {0, nullptr},
};
const field_meta mm::hf_5gs_reg_type = {
    "5GS registration type",
    "nas_5gs.mm.5gs_reg_type",
    ft::ft_uint8,
    fd::base_dec,
    values_registration_type,
    nullptr,
    nullptr,
    0x07,
};

const element_meta mm::registration_request_type = {
    0xff,
    "5GS registration type",
    dissect_reg_req_type,
    nullptr,
};

// only spare half octet
const field_meta mm::hf_ngksi_nas_ksi = {
    "NAS key set identifier - ngKSI",
    "nas_5gs.mm.ngksi",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0xF0,
};

// 9.11.3.32
int dissect_nksi_key_set_id(dissector d, context* ctx) {
    return mm::dissect_nas_ksi(d, ctx);
}

const element_meta mm::nksi_key_set_id = {
    0xc0,
    "Non-current native NAS KSI",
    mm::dissect_nas_ksi,
    nullptr,
};
// 9.11.3.54
int dissect_use_sec_cap(dissector d, context* ctx = nullptr);

const element_meta mm::ue_sec_cap = {
    0x2e,
    "UE security capability",
    dissect_use_sec_cap,
    nullptr,
};

/*2F    Requested NSSAI    NSSAI 9.11.3.37    O    TLV    4-74*/
const element_meta mm::requested_nssai = {
    0x2f,
    "Requested NSSAI",
    mm::dissect_requested_nssai,
    nullptr,
};

const element_meta mm::last_v_tai = {
    0x52,
    "Last visited registered TAI",
    dissect_last_v_tai,
    nullptr,
};

// int dissect_s1_ue_net_cap(dissector d, context* ctx);

const element_meta mm::s1_ue_net_cap = {
    0x17,
    "S1 UE network capability",
    dissect_s1_ue_net_cap,
    nullptr,
};


const element_meta mm::ul_data_status = {
    0x40,
    "Uplink data status",
    dissect_ul_data_status,
    nullptr,
};


const element_meta mm::ue_status = {
    0x2b,
    "UE status",
    dissect_ue_status,
    nullptr,
};


const element_meta mm::aguti_mobile_id = {
    0x77,
    "Additional GUTI",
    dissect_aguti_mobile_id,
    nullptr,
};


const element_meta mm::allow_pdu_ses_sts = {
    0x25,
    "Allowed PDU session status",
    dissect_pdu_ses_sts,
    nullptr,
};


const element_meta mm::ue_usage_set = {
    0x18,
    "UE's usage setting",
    dissect_usage_set,
    nullptr,
};


const element_meta mm::requested_drx_param = {
    0x51,
    "Requested DRX parameters",
    dissect_requested_drx_param,
    nullptr,
};

const element_meta mm::eps_nas_msg_cont = {
    0x70,
    "EPS NAS message container",
    dissect_eps_nas_msg_cont,
    nullptr,
};


const element_meta mm::ladn_ind = {
    0x74,
    "LADN indication",
    dissect_ladn_ind,
    nullptr,
};




// 9.11.3.9A 5GS update type
const element_meta mm::update_type = {
    0x53,
    "5GS update type",
    dissect_update_type,
    nullptr,
};



/* * 8.2.6 Registration request */
int mm::registration_req(dissector d, context* ctx) {
    auto len = d.length;

    d.pinfo->dir = pi_dir::ul;
    // get private data

    /*   5GS registration type  9.11.3.7    M    V    1/2  H0*/
    // d.add_item(1, hf_reg_req_flags, enc::be);
    auto consumed = dissect_elem_v(nullptr, &registration_request_type, d, ctx);
    d.add_item(1, &hf_ngksi_nas_ksi, enc::be);
    /*    ngKSI    NAS key set identifier 9.11.3.32    M    V    1/2 H1*/
    d.step(consumed);

    /*    Mobile identity    5GS mobile identity 9.11.3.4    M    LV-E    6-n*/
    consumed = dissect_elem_lv_e(nullptr, &mobile_id, d, ctx);
    d.step(consumed);

    /*C-    Non-current native NAS KSI    NAS key set identifier 9.11.3.32    O    TV 1*/
    // ELEM_OPT_TV_SHORT( 0xc0, , DE_NAS_5GS_MM_NAS_KEY_SET_ID, " - native KSI");
    consumed = dissect_opt_elem_tv_short(nullptr, &nksi_key_set_id, d, ctx);
    d.step(consumed);

    /*10    5GMM capability  9.11.3.1    O    TLV    3-15*/
    // ELEM_OPT_TLV(0x10, , DE_NAS_5GS_MM_5GMM_CAP, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &mm_cap, d, ctx);
    d.step(consumed);

    /*2E    UE security capability   9.11.3.54    O    TLV 4-10*/
    // ELEM_OPT_TLV(0x2e, , DE_NAS_5GS_MM_UE_SEC_CAP, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &ue_sec_cap, d, ctx);
    d.step(consumed);

    /*2F    Requested NSSAI    NSSAI 9.11.3.37    O    TLV    4-74*/
    // ELEM_OPT_TLV(0x2f, , DE_NAS_5GS_MM_NSSAI, " - Requested NSSAI");
    consumed = dissect_opt_elem_tlv(nullptr, &requested_nssai, d, ctx);
    d.step(consumed);

    /*52    Last visited registered TAI    5GS tracking area identity 9.11.3.8    O    TV
     * 7 */
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

    /*B-    MICO indication    MICO indication 9.11.3.31    O    TV    1*/
    // ELEM_OPT_TV_SHORT(0xb0, , DE_NAS_5GS_MM_MICO_IND, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &mico_ind, d, ctx);
    d.step(consumed);

    /*2B    UE status    UE status 9.11.3.56    O    TLV    3*/
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

    /* XX	Requested extended DRX parameters	Extended DRX parameters 9.11.3.60	O	TLV
     * 3*/
    /* TBD	T3324 value	GPRS timer 3 9.11.2.5	O	TLV	3 */

    d.extraneous_data_check(0);

    return len;
}
