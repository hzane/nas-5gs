#include "../common/ber.hh"
#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace mm;
using namespace nas;

/* 8.2.7    Registration accept */
int mm::dissect_registration_accept(dissector d, context* ctx) {
    const use_context uc(ctx, "registration-accept", d, 12);

    /*      5GS registration result    9.11.3.6    M    LV 2*/
    auto consumed = dissect_lv( &registration_result, d, ctx);
    d.step(consumed);

    /*77    5G-GUTI    5GS mobile identity 9.11.3.4    O    TLV-E    14 */
    // ELEM_OPT_TLV_E(0x77, , DE_NAS_5GS_MM_5GS_MOBILE_ID, " - 5G-GUTI");
    consumed = dissect_opt_tlv_e( &guti_mobile_id, d, ctx);
    d.step(consumed);

    /*4A    Equivalent PLMNs    PLMN list     9.11.3.45    O    TLV    5-47*/
    // ELEM_OPT_TLV(0x4a, , DE_PLMN_LIST, " - Equivalent PLMNs");
    consumed = dissect_opt_tlv( &plmn_list, d, ctx);
    d.step(consumed);

    /*54    TAI list    Tracking area identity list     9.11.3.9    O    TLV    8-98*/
    // ELEM_OPT_TLV(0x54, , DE_NAS_5GS_MM_5GS_TA_ID_LIST, NULL);
    consumed = dissect_opt_tlv( &tracking_area_id_list, d, ctx);
    d.step(consumed);

    /*15    Allowed NSSAI    NSSAI     9.11.3.37    O    TLV    4-74*/
    // ELEM_OPT_TLV(0x15, , DE_NAS_5GS_MM_NSSAI, " - Allowed NSSAI");
    consumed = dissect_opt_tlv( &allowed_nssai, d, ctx);
    d.step(consumed);

    /*11    Rejected NSSAI    Rejected NSSAI     9.11.3.46    O    TLV    4-42*/
    // ELEM_OPT_TLV(0x11, , DE_NAS_5GS_MM_REJ_NSSAI, NULL);
    consumed = dissect_opt_tlv( &rejected_nssai, d, ctx);
    d.step(consumed);

    /*31    Configured NSSAI    NSSAI 9.11.3.37    O    TLV    4-146 */
    // ELEM_OPT_TLV(0x31, , DE_NAS_5GS_MM_NSSAI, " - Configured NSSAI");
    consumed = dissect_opt_tlv( &configured_nssai, d, ctx);
    d.step(consumed);

    /*21    5GS network feature support   9.11.3.5    O TLV 3-5 */
    // ELEM_OPT_TLV(0x21, , DE_NAS_5GS_MM_5GS_NW_FEAT_SUP, NULL);
    consumed = dissect_opt_tlv( &network_feature_support, d, ctx);
    d.step(consumed);

    /*50    PDU session status   9.10.3.44    O    TLV    */
    // ELEM_OPT_TLV(0x50, , DE_NAS_5GS_MM_PDU_SES_STATUS, NULL);
    consumed = dissect_opt_tlv( &pdu_session_status, d, ctx);
    d.step(consumed);

    /*26    PDU session reactivation result   9.11.3.42    O    TLV    4-32*/
    consumed = dissect_opt_tlv( &pdu_session_reactivation_result, d, ctx);
    d.step(consumed);

    /*72    PDU session reactivation result error cause 9.11.3.43  O TLV-E  5-515*/
    // ELEM_OPT_TLV_E(0x72, , DE_NAS_5GS_MM_PDU_SES_REACT_RES_ERR_C, NULL);
    consumed = dissect_opt_tlv_e( &pdu_session_reactive_result_error_cause, d, ctx);
    d.step(consumed);

    /*79    LADN information   9.11.3.30    O    TLV-E    11-1579*/
    // ELEM_OPT_TLV_E(0x79, , DE_NAS_5GS_MM_LADN_INF, NULL);
    consumed = dissect_opt_tlv_e( &ladn_information, d, ctx);
    d.step(consumed);

    /*B-    MICO indication    9.11.3.31    O    TV    1*/
    // ELEM_OPT_TV_SHORT(0xb0, , DE_NAS_5GS_MM_MICO_IND, NULL);
    consumed = dissect_opt_tv_short( &mico_indication, d, ctx);
    d.step(consumed);

    /* 9-  Network slicing indication  9.11.3.36  O  TV 1 */
    // ELEM_OPT_TV_SHORT(0x90, , DE_NAS_5GS_MM_network_slicing_indication, NULL);
    consumed = dissect_opt_tv_short( &network_slicing_indication, d, ctx);
    d.step(consumed);

    /*27    Service area list   9.11.3.49    O    TLV    6-194*/
    // ELEM_OPT_TLV(0x27, , DE_NAS_5GS_MM_SAL, NULL);
    consumed = dissect_opt_tlv( &service_area_list, d, ctx);
    d.step(consumed);

    /*5E    T3512 value    GPRS timer 3     9.11.2.25    O    TLV    3*/
    // ELEM_OPT_TLV(0x5E, , DE_GPRS_TIMER_3, " - T3512 value");
    consumed = dissect_opt_tlv( &t3512_gprs_timer_3, d, ctx);
    d.step(consumed);

    /*5D    Non-3GPP de-registration timer value  GPRS timer 2 9.11.2.4  O TLV 3*/
    // ELEM_OPT_TLV(0x5D, , DE_GPRS_TIMER_2, " - Non-3GPP de-registration timer value");
    consumed = dissect_opt_tlv( &n3g_deregistration_timer_gprs_timer2, d, ctx);
    d.step(consumed);

    /*16    T3502 value    GPRS timer 2     9.11.2.4     O    TLV    3*/
    // ELEM_OPT_TLV(0x16, , DE_GPRS_TIMER_2, " - T3502 value");
    consumed = dissect_opt_tlv( &t3502_gprs_timer_2, d, ctx);
    d.step(consumed);

    /*34  Emergency number list  9.11.3.23 O   TLV  5-50*/
    // ELEM_OPT_TLV(0x34, , DE_EMERGENCY_NUM_LIST, NULL);
    consumed = dissect_opt_tlv( &emergency_number_list, d, ctx);
    d.step(consumed);

    /*7A    Extended emergency number list  9.11.3.26  O    TLV-E    TBD*/
    // ELEM_OPT_TLV(0x7A, , DE_EMM_EXT_EMERG_NUM_LIST, NULL);
    consumed = dissect_opt_tlv_e( &ext_emergency_number_list, d, ctx);
    d.step(consumed);

    /*73    SOR transparent container   9.11.3.51    O    TLV-E 20-2048 */
    // ELEM_OPT_TLV_E(0x73, , DE_NAS_5GS_MM_SOR_TRASP_CONT, NULL);
    consumed = dissect_opt_tlv_e( &sor_transparent_container, d, ctx);
    d.step(consumed);

    /*78    EAP message  9.11.2.2    O    TLV-E    7-1503 */
    // ELEM_OPT_TLV_E(0x78, , DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_tlv_e( &eap_message, d, ctx);
    d.step(consumed);

    /* A-    NSSAI inclusion mode  9.11.3.37A    O    TV    1 */
    // ELEM_OPT_TV_SHORT(0xA0, , DE_NAS_5GS_MM_NSSAI_INC_MODE, NULL);
    consumed = dissect_opt_tv_short( &nssai_inclusion_mode, d, ctx);
    d.step(consumed);

    /* 76    Operator-defined access category definitions 9.11.3.38    O    TLV-E    3-n */
    // ELEM_OPT_TLV_E(0x76, , DE_NAS_5GS_MM_OP_DEF_ACC_CAT_DEF, NULL);
    consumed = dissect_opt_tlv_e( &operator_defined_acd, d, ctx);
    d.step(consumed);

    /* 51    Negotiated DRX parameters 9.11.3.2A    O    TLV    3 */
    // ELEM_OPT_TLV(0x51,,DE_NAS_5GS_MM_5GS_DRX_PARAM," -  Negotiated DRX parameters");
    consumed = dissect_opt_tlv( &negotiated_drx_parameter, d, ctx);
    d.step(consumed);

    // D- Non-3GPP NW policies Non - 3GPP NW provided policies 9.11.3.58 O TV 1
    consumed = dissect_opt_tv_short( &n3gpp_nw_provided_policies, d, ctx);
    d.step(consumed);

    // 60	EPS bearer context status    9.11.3.59 O TLV 4
    consumed = dissect_opt_tlv( &eps_bearer_context_status, d, ctx);
    d.step(consumed);

    // xx Negotiated extended DRX parameters Extended DRX parameters 9.11.3.60 O TLV 3
    // tbdT3447 value GPRS timer 3 9.11.2.5 O TLV 3
    // XX T3448 value GPRS timer 3 9.11.2.4 O TLV 3
    // TBD T3324 value GPRS timer 3 9.11.2.5 O TLV 3


    return uc.length;
}
namespace mm {




//  Service area list   9.11.3.49
const element_meta service_area_list = {
    0x27,
    "Service area list",
    dissect_service_area_list,
};


const element_meta t3512_gprs_timer_3 = {
    0x5E,
    "GPRS timer 3 - T3512 value",
    dissect_gprs_timer3_set,
};


const element_meta n3g_deregistration_timer_gprs_timer2 = {
    0x5D,
    "GPRS timer 2 - Non-3GPP de-registration timer value",
    dissect_gprs_timer2_set,
};


const element_meta t3502_gprs_timer_2 = {
    0x16,
    "GPRS timer 2 - T3502 value",
    dissect_gprs_timer2_set,
};


// EAP message  9.11.2.2
int dissect_eap_message(dissector d, context* ctx = nullptr);

// EAP message  9.11.2.2
const element_meta eap_message = {
    0x78,
    "EAP message",
    dissect_eap_message,
};


// NSSAI inclusion mode  9.11.3.37A
const element_meta nssai_inclusion_mode = {
    0xA0,
    "NSSAI inclusion mode",
    dissect_nssai_inclusion_mode,
};

//  Operator-defined access category definitions 9.11.3.38
int dissect_operator_defined_acd(dissector d, context* ctx );

//  Operator-defined access category definitions 9.11.3.38
extern const element_meta operator_defined_acd = {
    0x76,
    "Operator-defined access category definitions",
    dissect_operator_defined_acd,
};

// Negotiated DRX parameters 9.11.3.2A
const element_meta negotiated_drx_parameter = {
    0x51,
    "Negotiated DRX parameters",
    dissect_drx_parameter,
};

/* [14] 10.5.5.37 Non-3GPP NW provided policies */
static const tf_string tfind = {
    "Use of non-3GPP emergency numbers permitted",
    "Use of non-3GPP emergency numbers not permitted",
};

const bool_field hf_n3en_indicator = {
    "N3EN indicator",
    0x01,
    tfind.false_string,
    tfind.true_string,
};


const bool_field hf_reg_res_sms_allowed = {
    "SMS over NAS",
    0x08,
    tfind.false_string,
    tfind.true_string,
};


const octet_field hf_mobile_country_code = {
    "Mobile Country Code (MCC)",
};
const octet_field hf_mobile_network_code = {
    "Mobile Network Code (MNC)",
};



/* 9.9.3.37a Extended Emergency Number List TS24.301*/
static tf_string tfs_ext_emergency_number_list = {
    "Valid only in the PLMN from which this IE is received",
    "Valid in the country of the PLMN from which this IE is received",
};

const bcd_field hf_emergency_number_info = {
    "Emergency Number Information",
};
const uint8_field hf_emergency_number_length = {
    "Emergency Number Info length",
    0x0,
};

const bool_field hf_mountain_rescue = {
    "Mountain Rescue",
    0x10,
};
const bool_field hf_marine_guard = {
    "Marine Guard",
    0x08,
};
const bool_field hf_fire_brigade = {
    "Fire Brigade",
    0x04,
};
const bool_field hf_ambulance = {
    "Ambulance",
    0x02,
};
const bool_field hf_police = {
    "Police",
    0x01,
};
const bcd_field hf_emergency_bcd_num = {
    "Emergency BCD Number",
};


const bool_field hf_ext_emergency_number_list_validity = {
    "Extended Emergency Number List Validity",
    0x01,
    "Valid in the country of the PLMN from which this IE is received",
    "Valid only in the PLMN from which this IE is received",
};

const uint8_field hf_ext_emerge_num_len = {
    "Emergency number information length",
    0x0,
};
const bcd_field hf_emergency_number = {
    "Emergency number",
};

const uint8_field hf_sub_services_field_length = {
    "Sub-services field length",
    0x0,
};
const sms_field hf_sub_services_field = {
    "Sub-services field",
};


/* 9.11.3.51    SOR transparent container */
const tf_string tfs_nas_5gs_list_type = {
    "PLMN ID and access technology list",
    "Secured packet",
};

const tf_string tfs_sor_list_indication = {
    "List of preferred PLMN/access technology combinations is provided",
    "No list of preferred PLMN/access technology combinations is provided",
};

const tf_string tfs_nas_5gs_sor_data_type = {
    "Carries acknowledgement of successful reception of the steering of roaming "
    "information",
    "Carries steering of roaming information",
};


const bool_field hf_sor_hdr_ack = { // NOLINT
    "Acknowledgement (ACK)",
    0x08,
    &tfs_requested_not_requested,
};
const bool_field hf_sor_hdr_list_type = {
    "List type",
    0x04,
    &tfs_nas_5gs_list_type,
};

const bool_field hf_sor_hdr_list_indication = {
    "List indication",
    0x02,
    &tfs_sor_list_indication,
};

const bool_field hf_sor_hdr0_sor_data_type = {
    "SOR data type",
    0x01,
    (&tfs_nas_5gs_sor_data_type),
};

const tf_string tfs_selected_not_selected = {"Selected", "Not Selected",};

const bool_field       hf_access_tech_utran      = {
    "Access technology UTRAN",
    0x80,
    &tfs_selected_not_selected,
};
const bool_field hf_access_tech_eutran = {
    "Access technology E-UTRAN",
    0x40,
    &tfs_selected_not_selected,
};
const bool_field hf_access_tech_eutran_wb = {
    "Access technology E-UTRAN in WB-S1 mode",
    0x20,
    &tfs_selected_not_selected,
};
const bool_field hf_access_tech_eutran_nb = {
    "Access technology E-UTRAN in NB-S1 mode",
    0x10,
    &tfs_selected_not_selected,
};
const bool_field hf_access_tech_o1_b3 = {
    "Access technology NG-RAN",
    0x08,
    &tfs_selected_not_selected,
};

const bool_field hf_access_tech_o2_b7 = {
    "Access technology GSM",
    0x80,
    &tfs_selected_not_selected,
};

const bool_field hf_access_tech_o2_b6 = {
    "Access technology GSM COMPACT",
    0x40,
    &tfs_selected_not_selected,
};

const bool_field hf_access_tech_o2_b5 = {
    "Access technology CDMA2000 HRPD",
    0x20,
    &tfs_selected_not_selected,
};

const bool_field hf_access_tech_o2_b4 = {
    "Access technology CDMA2000 1xRTT",
    0x10,
    &tfs_selected_not_selected,
};

const bool_field hf_access_tech_o2_b3 = {
    "Access technology EC-GSM-IoT",
    0x08,
    &tfs_selected_not_selected,
};

const bool_field hf_acces_tech_o2_b2 = {
    "Access technology GSM ",
    0x04,
    &tfs_selected_not_selected,
};

const uint8_field hf_rfu_b2 = {
    "Reserved for Future Use(RFU)",
    0x04,
};
const uint8_field hf_rfu_b1 = {
    "Reserved for Future Use(RFU)",
    0x02,
};
const bool_field hf_rfu_b0 = {
    "Reserved for Future Use(RFU)",
    0x01,
};
const octet_field hf_sor_mac_iue = {
    "SOR-MAC-IUE",
};
const octet_field hf_sor_mac_iausf = {
    "SOR-MAC-IAUSF",
};

const uint16_field hf_counter_sor = {
    "CounterSOR",
    0x0,
};
const octet_field hf_sor_sec_pkt = {
    "Secured packet",
};

/* 9.10.2.2     EAP message*/
/* EAP message as specified in IETF RFC 3748 */
int dissect_eap_message(dissector d, context* ctx) {
    const use_context uc(ctx, "eap", d, -1);

    diag("eap message specified in rfc 3748\n");
    return d.length;
}

const uint8_field hf_mm_precedence = {
    "Precedence",
    0x0,
};
const uint8_field hf_mm_op_defined_acd_oct6 = {
    "Operator-defined access category number",
    0x1f,
};

const octet_field hf_mm_op_defined_acd_criteria = {
    "Operator-defined access category criteria",
};

/* 9.11.3.38    Operator-defined access category definitions */
int dissect_operator_defined_acd(dissector d, context* ctx) {
    const use_context uc(ctx, "operator-defined-access-category-definitions", d, 0);

    auto i = 1;
    while(d.length>0){
        auto subtree =
            d.add_item(2, formats("Operator-defined access category definition  %u", i++));
        use_tree ut(d, subtree);

        // Length of operator-defined access category definition contents oct4
        const auto length = static_cast< int >(d.uint8());
        // d.add_item(1, &hf_mm_length);
        d.step(1);

        auto sd = d.slice(length);
        /* Precedence value oct5*/
        (void) sd.add_item(1, &hf_mm_precedence);
        sd.step(1);

        /* PSAC    0 Spare    0 Spare    Operator-defined access category number  oct6*/
        (void) sd.add_item(1, &hf_mm_op_defined_acd_oct6);
        sd.step(1);

        /* Length of criteria oct7*/
        const auto clen = static_cast< int >(sd.uint8());
        sd.step(1);

        /* Criteria 8 - a-1*/
        (void) sd.add_item(clen, &hf_mm_op_defined_acd_criteria);
        sd.step(clen);

        /* 0 Spare    0 Spare    0 Spare    Standardized access category */
        if (sd.length > 0) {
            diag("operator-defined access category definitions has oct-a %d", d.length);
        }

        subtree->set_length(length + 1);
        d.step(length);
    }
    return uc.length;
}


} // namespace mm_reg_accept
