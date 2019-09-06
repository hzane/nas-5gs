#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

using namespace cmn;
using namespace mm;
using namespace nas;

/* 8.2.7    Registration accept */
int mm::dissect_registration_accept(dissector d, context* ctx) {    
    const use_context uc(ctx, "registration-accept", d, 12);
    // network to UE
    down_link(d.pinfo);

    /*      5GS registration result    9.11.3.6    M    LV 2*/
    auto consumed = dissect_elem_lv(nullptr, &reg_res, d, ctx);
    d.step(consumed);

    /*77    5G-GUTI    5GS mobile identity 9.11.3.4    O    TLV-E    14 */
    // ELEM_OPT_TLV_E(0x77, , DE_NAS_5GS_MM_5GS_MOBILE_ID, " - 5G-GUTI");
    consumed = dissect_opt_elem_tlv_e(nullptr, &guti_5gs_mobile_id, d, ctx);
    d.step(consumed);

    /*4A    Equivalent PLMNs    PLMN list     9.11.3.45    O    TLV    5-47*/
    // ELEM_OPT_TLV(0x4a, , DE_PLMN_LIST, " - Equivalent PLMNs");
    consumed = dissect_opt_elem_tlv(nullptr, &plmn_list, d, ctx);
    d.step(consumed);

    /*54    TAI list    Tracking area identity list     9.11.3.9    O    TLV    8-98*/
    // ELEM_OPT_TLV(0x54, , DE_NAS_5GS_MM_5GS_TA_ID_LIST, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &ta_id_list, d, ctx);
    d.step(consumed);

    /*15    Allowed NSSAI    NSSAI     9.11.3.37    O    TLV    4-74*/
    // ELEM_OPT_TLV(0x15, , DE_NAS_5GS_MM_NSSAI, " - Allowed NSSAI");
    consumed = dissect_opt_elem_tlv(nullptr, &allowed_nssai, d, ctx);
    d.step(consumed);

    /*11    Rejected NSSAI    Rejected NSSAI     9.11.3.46    O    TLV    4-42*/
    // ELEM_OPT_TLV(0x11, , DE_NAS_5GS_MM_REJ_NSSAI, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &rej_nssai, d, ctx);
    d.step(consumed);

    /*31    Configured NSSAI    NSSAI 9.11.3.37    O    TLV    4-146 */
    // ELEM_OPT_TLV(0x31, , DE_NAS_5GS_MM_NSSAI, " - Configured NSSAI");
    consumed = dissect_opt_elem_tlv(nullptr, &configured_nssai, d, ctx);
    d.step(consumed);

    /*21    5GS network feature support   9.11.3.5    O TLV 3-5 */
    // ELEM_OPT_TLV(0x21, , DE_NAS_5GS_MM_5GS_NW_FEAT_SUP, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &nw_feat_sup, d, ctx);
    d.step(consumed);

    /*50    PDU session status   9.10.3.44    O    TLV    */
    // ELEM_OPT_TLV(0x50, , DE_NAS_5GS_MM_PDU_SES_STATUS, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &pdu_ses_status, d, ctx);
    d.step(consumed);

    /*26    PDU session reactivation result   9.11.3.42    O    TLV    4-32*/
    // ELEM_OPT_TLV(0x26, , DE_NAS_5GS_MM_PDU_SES_REACT_RES, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &pdu_ses_react_res, d, ctx);
    d.step(consumed);

    /*72    PDU session reactivation result error cause 9.11.3.43  O TLV-E  5-515*/
    // ELEM_OPT_TLV_E(0x72, , DE_NAS_5GS_MM_PDU_SES_REACT_RES_ERR_C, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &pdu_ses_react_res_err_c, d, ctx);
    d.step(consumed);

    /*79    LADN information   9.11.3.30    O    TLV-E    11-1579*/
    // ELEM_OPT_TLV_E(0x79, , DE_NAS_5GS_MM_LADN_INF, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ladn_inf, d, ctx);
    d.step(consumed);

    /*B-    MICO indication    9.11.3.31    O    TV    1*/
    // ELEM_OPT_TV_SHORT(0xb0, , DE_NAS_5GS_MM_MICO_IND, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &mico_ind, d, ctx);
    d.step(consumed);

    /* 9-  Network slicing indication  9.11.3.36  O  TV 1 */
    // ELEM_OPT_TV_SHORT(0x90, , DE_NAS_5GS_MM_NW_SLICING_IND, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &nw_slicing_ind, d, ctx);
    d.step(consumed);

    /*27    Service area list   9.11.3.49    O    TLV    6-194*/
    // ELEM_OPT_TLV(0x27, , DE_NAS_5GS_MM_SAL, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &sal, d, ctx);
    d.step(consumed);

    /*5E    T3512 value    GPRS timer 3     9.11.2.25    O    TLV    3*/
    // ELEM_OPT_TLV(0x5E, , DE_GPRS_TIMER_3, " - T3512 value");
    consumed = dissect_opt_elem_tlv(nullptr, &t3512_gprs_timer_3, d, ctx);
    d.step(consumed);

    /*5D    Non-3GPP de-registration timer value  GPRS timer 2 9.11.2.4  O TLV 3*/
    // ELEM_OPT_TLV(0x5D, , DE_GPRS_TIMER_2, " - Non-3GPP de-registration timer value");
    consumed = dissect_opt_elem_tlv(nullptr, &de_reg_timer_gprs_timer2, d, ctx);
    d.step(consumed);

    /*16    T3502 value    GPRS timer 2     9.11.2.4     O    TLV    3*/
    // ELEM_OPT_TLV(0x16, , DE_GPRS_TIMER_2, " - T3502 value");
    consumed = dissect_opt_elem_tlv(nullptr, &t3502_gprs_timer_2, d, ctx);
    d.step(consumed);

    /*34  Emergency number list  9.11.3.23 O   TLV  5-50*/
    // ELEM_OPT_TLV(0x34, , DE_EMERGENCY_NUM_LIST, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &emerg_num_list, d, ctx);
    d.step(consumed);

    /*7A    Extended emergency number list  9.11.3.26  O    TLVE    TBD*/
    // ELEM_OPT_TLV(0x7A, , DE_EMM_EXT_EMERG_NUM_LIST, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &emerg_num_list_7a, d, ctx);
    d.step(consumed);

    /*73    SOR transparent container   9.11.3.51    O    TLV-E 20-2048 */
    // ELEM_OPT_TLV_E(0x73, , DE_NAS_5GS_MM_SOR_TRASP_CONT, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &sor_trans_cont, d, ctx);
    d.step(consumed);

    /*78    EAP message  9.11.2.2    O    TLV-E    7-1503 */
    // ELEM_OPT_TLV_E(0x78, , DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eap_message, d, ctx);
    d.step(consumed);

    /* A-    NSSAI inclusion mode  9.11.3.37A    O    TV    1 */
    // ELEM_OPT_TV_SHORT(0xA0, , DE_NAS_5GS_MM_NSSAI_INC_MODE, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &nssai_inclusion_mode, d, ctx);
    d.step(consumed);

    /* 76    Operator-defined access category definitions 9.11.3.38    O    TLV-E    3-TBD */
    // ELEM_OPT_TLV_E(0x76, , DE_NAS_5GS_MM_OP_DEF_ACC_CAT_DEF, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &operator_defined_acd, d, ctx);
    d.step(consumed);

    /* 51    Negotiated DRX parameters 9.11.3.2A    O    TLV    3 */
    // ELEM_OPT_TLV(0x51,,DE_NAS_5GS_MM_5GS_DRX_PARAM," -  Negotiated DRX parameters");
    consumed = dissect_opt_elem_tlv(nullptr, &nego_drx_param, d, ctx);
    d.step(consumed);

    // D - Non - 3GPP NW policies Non - 3GPP NW provided policies 9.11.3.58 O TV 1
    consumed = dissect_opt_elem_tv_short(nullptr, &n3gpp_nw_provided_policies, d, ctx);
    d.step(consumed);

    // 60	EPS bearer context status    9.11.3.59 O TLV 4
    consumed = dissect_opt_elem_tlv(nullptr, &eps_bearer_ctx_status, d, ctx);
    d.step(consumed);

    // xx Negotiated extended DRX parameters Extended DRX parameters 9.11.3.60 O TLV 3
    // tbdT3447 value GPRS timer 3 9.11.2.5 O TLV 3
    // XX T3448 value GPRS timer 3 9.11.2.4 O TLV 3
    // TBD T3324 value GPRS timer 3 9.11.2.5 O TLV 3
   

    return uc.length;
}
namespace mm {

const element_meta guti_5gs_mobile_id = {
    0x77,
    "5GS mobile identity - 5G-GUTI",
    dissect_mobile_id,
    nullptr,
};

/*4A    Equivalent PLMNs    PLMN list     9.11.3.45    O    TLV    5-47*/
int dissect_plmn_list(dissector d, context* ctx = nullptr);

const element_meta plmn_list = {
    0x4a,
    "Equivalent PLMNs",
    dissect_plmn_list,
    nullptr,
};


/* 9.11.3.43    PDU session reactivation result error cause */
int dissect_pdu_ses_react_res_err_c(dissector d, context* ctx = nullptr);

const element_meta pdu_ses_react_res_err_c = {
    0x72,
    "PDU session reactivation result error cause",
    dissect_pdu_ses_react_res_err_c,
    nullptr,
};


//  Service area list   9.11.3.49
const element_meta sal = {
    0x27,
    "Service area list",
    dissect_sal,
    nullptr,
};

// T3512 value    GPRS timer 3     9.11.2.25
int dissect_t3512_gprs_timer_3(dissector d, context* ctx = nullptr);

const element_meta t3512_gprs_timer_3 = {
    0x5E,
    "GPRS timer 3 - T3512 value",
    dissect_t3512_gprs_timer_3,
    nullptr,
};

// Non-3GPP de-registration timer value  GPRS timer 2 9.11.2.4
int dissect_de_reg_timer_gprs_timer2(dissector d, context* ctx = nullptr);

const element_meta de_reg_timer_gprs_timer2 = {
    0x5D,
    "GPRS timer 2 - Non-3GPP de-registration timer value",
    dissect_de_reg_timer_gprs_timer2,
    nullptr,
};

// T3502 value    GPRS timer 2     9.11.2.4
int dissect_t3502_gprs_timer_2(dissector d, context* ctx = nullptr);

const element_meta t3502_gprs_timer_2 = {
    0x16,
    "GPRS timer 2 - T3502 value",
    dissect_t3502_gprs_timer_2,
    nullptr,
};

// Emergency number list  9.11.3.23
int dissect_emerg_num_list(dissector d, context* ctx = nullptr);

const element_meta emerg_num_list = {
    0x34,
    "Emergency number list",
    dissect_emerg_num_list,
    nullptr,
};

// Extended emergency number list  9.11.3.26
int dissect_emerg_num_list_7a(dissector d, context* ctx = nullptr);

const element_meta emerg_num_list_7a = {
    0x7A,
    "Extended emergency number list",
    dissect_emerg_num_list_7a,
    nullptr,
};


// EAP message  9.11.2.2
int dissect_eap_message(dissector d, context* ctx = nullptr);

// EAP message  9.11.2.2
const element_meta eap_message = {
    0x78,
    "EAP message",
    dissect_eap_message,
    nullptr,
};

// NSSAI inclusion mode  9.11.3.37A
int dissect_nssai_inclusion_mode(dissector d, context* ctx = nullptr);

// NSSAI inclusion mode  9.11.3.37A
const element_meta nssai_inclusion_mode = {
    0xA0,
    "NSSAI inclusion mode",
    dissect_nssai_inclusion_mode,
    nullptr,
};

//  Operator-defined access category definitions 9.11.3.38
int dissect_operator_defined_acd(dissector d, context* ctx = nullptr);

//  Operator-defined access category definitions 9.11.3.38
const element_meta mm::operator_defined_acd = {
    0x76,
    "Operator-defined access category definitions",
    dissect_operator_defined_acd,
    nullptr,
};

// Negotiated DRX parameters 9.11.3.2A
const element_meta nego_drx_param = {
    0x51,
    "Negotiated DRX parameters",
    dissect_drx_param,
    nullptr,
};

/* [14] 10.5.5.37 Non-3GPP NW provided policies */
const true_false_string gsm_a_gm_n3en_ind_value = {
    "Use of non-3GPP emergency numbers permitted",
    "Use of non-3GPP emergency numbers not permitted",
};

const field_meta hf_gsm_a_n3en_ind = {
    "N3EN indicator",
    "gsm_a.gm.gmm.n3en_ind",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &gsm_a_gm_n3en_ind_value,
    nullptr,
    0x01,
};


// Non - 3GPP NW policies Non - 3GPP NW provided policies 9.11.3.58
const element_meta mm::n3gpp_nw_provided_policies = {
    0xd0,
    "",
    dissect_n3gpp_nw_provided_policies,
    nullptr,
};

const field_meta hf_reg_res_sms_allowed = {
    "SMS over NAS",
    "nas_5gs.mm.reg_res.sms_all",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_allowed_not_allowed,
    nullptr,
    0x08,
};


// 5G-GUTI    5GS mobile identity 9.11.3.4
int dissect_guti_5gs_mobile_id(dissector d, context* ctx) {
    return dissect_mobile_id(d, ctx);
}

const field_meta hf_mobile_country_code = {
    "Mobile Country Code (MCC)",
    "gsm_a.mobile_country_code",
    ft::ft_bytes,
    fd::mcc,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta hf_mobile_network_code = {
    "Mobile Network Code (MNC)",
    "gsm_a.mobile_network_code",
    ft::ft_bytes,
    fd::mnc,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

/*  [3] 10.5.1.13 PLMN list GSM-A */
/*4A    Equivalent PLMNs    PLMN list     9.11.3.45    O    TLV    5-47*/
int dissect_plmn_list(dissector d, context* ctx) {
    const auto start = d.offset;
    auto num = 1;

    while(d.length>=3){
        auto     subtree = d.add_item(3, "PLMN[%u]", num);
        use_tree ut(d, subtree);

        d.add_item(3, &hf_mobile_country_code, enc::na);
        d.add_item(3, &hf_mobile_network_code, enc::na);

        d.step(3);
        num++;
    }
    return d.offset - start;
}


// T3512 value    GPRS timer 3     9.11.2.25
int dissect_t3512_gprs_timer_3(dissector d, context* ctx) {
    return dissect_gprs_timer3(d, ctx);
}

// Non-3GPP de-registration timer value  GPRS timer 2 9.11.2.4
int dissect_de_reg_timer_gprs_timer2(dissector d, context* ctx) {
    return dissect_gprs_timer2(d, ctx);
}

// T3502 value    GPRS timer 2     9.11.2.4
int dissect_t3502_gprs_timer_2(dissector d, context* ctx) {
    return dissect_gprs_timer2(d, ctx);
}

/* 9.9.3.37a Extended Emergency Number List TS24.301*/
static true_false_string tfs_eenlv_value = {
    "Valid only in the PLMN from which this IE is received",
    "Valid in the country of the PLMN from which this IE is received",
};

const field_meta hf_gsma_eni = {
    "Emergency Number Information",
    "gsm_a.dtap.emergency_number_information",
    ft::ft_uint32,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x0,
};
const field_meta hf_gsma_eni_length = {
    "Emergency Number Info length",
    "gsm_a.dtap.emerg_num_info_length",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta hf_gsma_svc_cat_b4 = {
    "Mountain Rescue",
    "gsm_a.dtap.serv_cat_b5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x10,
};
const field_meta hf_gsma_svc_cat_b3 = {
    "Marine Guard",
    "gsm_a.dtap.serv_cat_b4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x08,
};
const field_meta hf_gsma_svc_cat_b2 = {
    "Fire Brigade",
    "gsm_a.dtap.serv_cat_b3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x04,
};
const field_meta hf_gsma_svc_cat_b1 = {
    "Ambulance",
    "gsm_a.dtap.serv_cat_b2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x02,
};
const field_meta hf_gsma_svc_cat_b0 = {
    "Police",
    "gsm_a.dtap.serv_cat_b1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x01,
};
const field_meta hf_gsma_emergency_bcd_num = {
    "Emergency BCD Number",
    "gsm_a.dtap.emergency_bcd_num",
    ft::ft_bytes,
    fd::bcd,
    nullptr,
    nullptr,
    nullptr,
    0,
};
// Emergency number list  9.11.3.23
int dissect_emerg_num_list(dissector d, context* ctx) {
    // See subclause 10.5.3.13 in 3GPP TS 24.008 [12].
    static const field_meta* flags[] = {
        &hf_gsma_svc_cat_b0,
        &hf_gsma_svc_cat_b1,
        &hf_gsma_svc_cat_b2,
        &hf_gsma_svc_cat_b3,
        &hf_gsma_svc_cat_b4,
        nullptr,
    };
    const auto len = d.length;

    while(d.length>0){
        /* Length of 1st Emergency Number information note 1) octet 3
         * NOTE 1: The length contains the number of octets used to encode the
         * Emergency Service Category Value and the Number digits.
         */
        auto elen = d.uint8();
        auto subtree = d.add_item(elen+1, &hf_gsma_eni, enc::be);
        use_tree ut(d, subtree);

        d.add_item(1, &hf_gsma_eni_length, enc::be);
        d.step(1);

        /* 0 0 0 Emergency Service Category Value (see Table 10.5.135d/3GPP TS 24.008
         * Table 10.5.135d/3GPP TS 24.008: Service Category information element
         */
        d.add_bits(flags);
        d.step(1);
        --elen;
        d.add_item(elen, &hf_gsma_emergency_bcd_num, enc::be);

        d.step(elen);
    }
    return len;
}

const field_meta hf_ext_emerge_num_list_eenlv = {
    "Extended Emergency Number List Validity",
    "nas_eps.emm.ext_emerg_num_list.eenlv",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_eenlv_value,
    nullptr,
    0x01,
};
const field_meta hf_ext_emerge_num_len = {
    "Emergency number information length",
    "nas_eps.emm.ext_emerg_num_list.emerg_num.len",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta hf_emerge_num = {
    "Emergency number",
    "nas_eps.emm.ext_emerg_num_list.emerg_num",
    ft::ft_bytes,
    fd::bcd,
    nullptr,nullptr,nullptr,
    0x0,
};

const field_meta hf_ext_emerge_sub_serv_field_len = {
    "Sub-services field length",
    "nas_eps.emm.ext_emerg_num_list.sub_serv_field.len",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta hf_emm_emerg_num_list_sub_svc_field = {
    "Sub-services field",
    "nas_eps.emm.ext_emerg_num_list.sub_serv_field",
    ft::ft_bytes,
    fd::bits7,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
// Extended emergency number list  9.11.3.26
int dissect_emerg_num_list_7a(dissector d, context* ctx) {
    // See subclause 9.9.3.37A in 3GPP TS 24.301 [15].

    auto len = d.length;
    d.add_item(1, &hf_ext_emerge_num_list_eenlv, enc::be);
    d.step(1);

    auto i = 1;
    while (d.length > 0) {
        const auto     start   = d.offset;
        auto     subtree = d.add_item(-1, "Extended emergency number #%u", i++);
        use_tree ut(d, subtree);

        auto length = static_cast< int >(d.uint8());
        d.add_item(1, &hf_ext_emerge_num_len, enc::be);
        d.step(1);

        if (length>0){
            d.add_item(length, &hf_emerge_num, enc::be);
            d.step(length);
        }

        length = d.uint8();
        d.add_item(1, &hf_ext_emerge_sub_serv_field_len, enc::be);
        d.step(1);

        if (length>0){
            d.add_item(length, &hf_emm_emerg_num_list_sub_svc_field, enc::be);
            // auto nchars = (len << 3) / 7;
            // auto str = ts_23_038_7bits_string(d.safe_ptr(), 0, nchars);
            d.step(length);
        }
        subtree->set_length(d.offset - start);
    }
    return len;
}

/* 9.11.3.51    SOR transparent container */
const true_false_string tfs_nas_5gs_list_type = {
    "PLMN ID and access technology list",
    "Secured packet",
};

const true_false_string tfs_nas_5gs_list_ind = {
    "List of preferred PLMN/access technology combinations is provided",
    "No list of preferred PLMN/access technology combinations is provided",
};

const true_false_string tfs_nas_5gs_sor_data_type = {
    "Carries acknowledgement of successful reception of the steering of roaming "
    "information",
    "Carries steering of roaming information",
};


const field_meta hf_sor_hdr0_ack = {
    "Acknowledgement (ACK)",
    "nas_5gs.sor_hdr0.ack",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_requested_not_requested,
    nullptr,
    0x08,
};
const field_meta hf_sor_hdr0_list_type = {
    "List type",
    "nas_5gs.sor_hdr0.list_type",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_list_type),
    nullptr,
    0x04,
};
const field_meta hf_sor_hdr0_list_ind = {
    "List indication",
    "nas_5gs.sor_hdr0.list_ind",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_list_ind),
    nullptr,
    0x02,
};
const field_meta hf_sor_hdr0_sor_data_type = {
    "SOR data type",
    "nas_5gs.sor.sor_data_type",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_sor_data_type),
    nullptr,
    0x01,
};
const true_false_string tfs_selected_not_selected = {"Selected", "Not Selected"};
const field_meta hf_acces_tech_o1_b7 = {
    "Access technology UTRAN",
    "nas_5gs.cces_tech_o1_b7.utran",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_selected_not_selected),
    nullptr,
    0x80,
};
const field_meta hf_acces_tech_o1_b6 = {
    "Access technology E-UTRAN",
    "nas_5gs.cces_tech_o1_b6.e_utran",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_selected_not_selected),
    nullptr,
    0x40,
};
const field_meta hf_acces_tech_o1_b5 = {
    "Access technology E-UTRAN in WB-S1 mode",
    "nas_5gs.cces_tech_o1_b5.e_utran_in_wb_s1_mode",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_selected_not_selected),
    nullptr,
    0x20,
};
const field_meta hf_acces_tech_o1_b4 = {
    "Access technology E-UTRAN in NB-S1 mode",
    "nas_5gs.cces_tech_o1_b4.e_utran_in_nb_s1_mode",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_selected_not_selected),
    nullptr,
    0x10,
};
const field_meta hf_acces_tech_o1_b3 = {
    "Access technology NG-RAN",
    "nas_5gs.cces_tech_o1_b3.ng_ran",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_selected_not_selected),
    nullptr,
    0x08,
};

const field_meta hf_acces_tech_o2_b7 = {
    "Access technology GSM",
    "nas_5gs.cces_tech_o2_b7.gsm",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_selected_not_selected),
    nullptr,
    0x80,
};
const field_meta hf_acces_tech_o2_b6 = {
    "Access technology GSM COMPACT",
    "nas_5gs.cces_tech_o2_b6.gsm_compact",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_selected_not_selected),
    nullptr,
    0x40,
};
const field_meta hf_acces_tech_o2_b5 = {
    "Access technology CDMA2000 HRPD",
    "nas_5gs.cces_tech_o2_b5.cdma2000_hrpd",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_selected_not_selected),
    nullptr,
    0x20,
};
const field_meta hf_acces_tech_o2_b4 = {
    "Access technology CDMA2000 1xRTT",
    "nas_5gs.cces_tech_o2_b4.cdma2000_1x_rtt",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_selected_not_selected),
    nullptr,
    0x10,
};
const field_meta hf_acces_tech_o2_b3 = {
    "Access technology EC-GSM-IoT",
    "nas_5gs.cces_tech_o2_b3.ec_gsm_iot",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_selected_not_selected),
    nullptr,
    0x08,
};
const field_meta hf_acces_tech_o2_b2 = {
    "Access technology GSM ",
    " nas_5gs.cces_tech_o2_b2.gsm ",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_selected_not_selected),
    nullptr,
    0x04,
};

const field_meta hf_rfu_b2 = {
    "Reserved for Future Use(RFU)",
    "nas_5gs.rfu.b2",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x04,
};
const field_meta hf_rfu_b1 = {
    "Reserved for Future Use(RFU)",
    "nas_5gs.rfu.b1",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x02,
};
const field_meta hf_rfu_b0 = {
    "Reserved for Future Use(RFU)",
    "nas_5gs.rfu.b0",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x01,
};
const field_meta hf_sor_mac_iue = {
    "SOR-MAC-IUE",
    "nas_5gs.mm.sor_mac_iue",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta hf_sor_mac_iausf = {
    "SOR-MAC-IAUSF",
    "nas_5gs.mm.sor_mac_iausf",
    ft::ft_bytes,
    fd::base_none,
    nullptr,nullptr,nullptr,
    0x0,
};

const field_meta hf_counter_sor = {
    "CounterSOR",
    "nas_5gs.mm.counter_sor",
    ft::ft_uint16,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x0,
};
const field_meta hf_sor_sec_pkt = {
    "Secured packet",
    "nas_5gs.mm.sor_sec_pkt",
    ft::ft_bytes,
    fd::base_none,
    nullptr,nullptr,nullptr,
    0x0,
};


/* 9.10.2.2     EAP message*/
/* EAP message as specified in IETF RFC 3748 */
int dissect_eap_message(dissector d, context* ctx) {
    diag("eap message specified in rfc 3748\n");
    return d.length;
}

/* 9.11.3.37A   NSSAI inclusion mode */
static const value_string nas_5gs_mm_nssai_inc_mode_vals[] = {
    {0x00, "A"},
    {0x01, "B"},
    {0x02, "C"},
    {0x03, "D"},
    {0, nullptr},
};
const field_meta hf_nssai_inc_mode = {
    "NSSAI inclusion mode",
    "nas_5gs.mm.nssai_inc_mode",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_nssai_inc_mode_vals,
    nullptr,
    nullptr,
    0x03,
};

// 9.11.3.37A NSSAI inclusion mode page.381
// a type 1 information element
int dissect_nssai_inclusion_mode(dissector d, context* ctx) {
    static const field_meta* flags[] = {
        &hf_spare_b3,
        &hf_spare_b2,
        &hf_nssai_inc_mode,
        nullptr,
    };
    d.add_bits(flags);
    return 1;
}

const field_meta hf_mm_precedence = {
    "Precedence",
    "nas_5gs.mm.precedence",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta hf_mm_op_defined_acd_oct6 = {
    "Operator-defined access category number",
    "nas_5gs.mm.opd_acc_cat",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x1f,
};
const true_false_string tfs_mm_opd_acc_psac = {
    "Standardized access category field is included",
    "Standardized access category field is not included",
};

const field_meta hf_mm_op_defined_acd_psac = { // NOLINT
    "Presence of standardized access category (PSAC)",
    "nas_5gs.mm.opd_acc_psac",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    &tfs_mm_opd_acc_psac,
    nullptr,
    0x80,
};
const field_meta hf_mm_op_defined_acd_criteria = {};

/* 9.11.3.38    Operator-defined access category definitions */
int dissect_operator_defined_acd(dissector d, context* ctx) {
    auto len = d.length;
    auto i = 1;
    while(d.length>0){
        auto subtree =
            d.add_item(2, "Operator-defined access category definition  %u", i);
        use_tree ut(d, subtree);

        // Length of operator-defined access category definition contents oct4
        const auto length = static_cast< int >(d.uint8());
        d.add_item(1, &hf_mm_length, enc::be);
        d.step(1);

        auto sd = d.slice(length);
        /* Precedence value oct5*/
        sd.add_item(1, &hf_mm_precedence, enc::be);
        sd.step(1);

        /* PSAC    0 Spare    0 Spare    Operator-defined access category number  oct6*/
        sd.add_item(1, &hf_mm_op_defined_acd_oct6, enc::be);
        sd.step(1);

        /* Length of criteria oct7*/
        const auto clen = static_cast< int >(sd.uint8());
        sd.step(1);

        /* Criteria 8 - a-1*/
        sd.add_item(clen, &hf_mm_op_defined_acd_criteria, enc::be);
        sd.step(clen);

        /* 0 Spare    0 Spare    0 Spare    Standardized access category */
        if (sd.length > 0) {
            diag("operator-defined access category definitions has oct-a %d", d.length);
        }
        subtree->set_length(len + 1); // len+2?

        d.step(len);
        ++i;
    }
    return len;
}


} // namespace mm_reg_accept
