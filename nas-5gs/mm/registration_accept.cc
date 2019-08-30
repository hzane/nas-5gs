#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_reg_accept {
extern const element_meta plmn_list;
extern const element_meta eap_message;
extern const element_meta nego_drx_param;
extern const element_meta t3512_gprs_timer_3;
extern const element_meta ladn_inf;
extern const element_meta mico_ind;
extern const element_meta nssai_inclusion_mode;
extern const element_meta t3502_gprs_timer_2;
extern const element_meta emerg_num_list;
extern const element_meta nw_slicing_ind;
extern const element_meta nw_feat_sup;
extern const element_meta de_reg_timer_gprs_timer2;
extern const element_meta sal;
extern const element_meta pdu_ses_react_res_err_c;

extern const element_meta emerg_num_list_7a;
extern const element_meta operator_defined_acd;
extern const element_meta guti_5gs_mobile_id;
extern const element_meta reg_res;
extern const element_meta sor_trans_cont;
} // namespace mm_reg_accept

using namespace mm;
using namespace nas;

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
    // ELEM_OPT_TLV(0x4a, , DE_PLMN_LIST, " - Equivalent PLMNs");
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
    consumed = dissect_opt_elem_tlv(nullptr, &rej_nssai, d, ctx);
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
    // ELEM_OPT_TLV_E(0x72, , DE_NAS_5GS_MM_PDU_SES_REACT_RES_ERR_C, NULL);
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

    /* 9-  Network slicing indication  Network slicing indication 9.11.3.36  O  TV 1 */
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

    /*34  Emergency number list  Emergency number list  9.11.3.17 O   TLV
     * 5-50*/
    // ELEM_OPT_TLV(0x34, , DE_EMERGENCY_NUM_LIST, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &emerg_num_list, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*7A    Extended emergency number list    Extended emergency number list 9.11.3.24
     * O    TLV    TBD*/
    // ELEM_OPT_TLV(0x7A, , DE_EMM_EXT_EMERG_NUM_LIST, NULL);
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
    // ELEM_OPT_TLV_E(0x78, , DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eap_message, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /* A-    NSSAI inclusion mode    NSSAI inclusion mode 9.11.3.37A    O    TV    1 */
    // ELEM_OPT_TV_SHORT(0xA0, , DE_NAS_5GS_MM_NSSAI_INC_MODE, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &nssai_inclusion_mode, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /* 76    Operator-defined access category definitions    Operator-defined access
     * category definitions 9.11.3.38    O    TLV-E    3-TBD */
    // ELEM_OPT_TLV_E(0x76, , DE_NAS_5GS_MM_OP_DEF_ACC_CAT_DEF, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &operator_defined_acd, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /* 51    Negotiated DRX parameters    5GS DRX parameters 9.11.3.2A    O    TLV    3 */
    // ELEM_OPT_TLV(0x51,,DE_NAS_5GS_MM_5GS_DRX_PARAM," -  Negotiated DRX parameters");
    consumed = dissect_opt_elem_tlv(nullptr, &nego_drx_param, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    d.extraneous_data_check(0);

    return d.tvb->length;
}
namespace mm_reg_accept {

/*
 * 9.11.3.6    5GS registration result
 */
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



int                dissect_nw_feat_sup(dissector d, context* ctx = nullptr);
const element_meta nw_feat_sup = {
    0x21,
    "5GS network feature support",
    dissect_nw_feat_sup,
};


/*
 *   9.11.3.43    PDU session reactivation result error cause
 */
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

extern const element_meta nw_slicing_ind = {
    0x90,
    "Network slicing indication",
    dissect_nw_slicing_ind,
};


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

/*
 * 9.11.3.6    5GS registration result
 */

static const value_string nas_5gs_mm_reg_res_values[] = {
    {0x1, "3GPP access"},
    {0x2, "Non-3GPP access"},
    {0x3, "3GPP access and non-3GPP access"},
    {0, nullptr},};
const field_meta hf_reg_res_res = {
    "5GS registration result",
    "nas_5gs.mm.reg_res.res",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_reg_res_values,
    nullptr,
    nullptr,
    0x07,
};
// 9.11.3.6    5GS registration result
int dissect_reg_res(dissector d, context* ctx) {
    /* 0 Spare 0 Spare 0 Spare 0 Spare SMS allowed 5GS registration result value */
    d.add_item(1, &hf_reg_res_sms_allowed, enc::be);
    d.add_item(1, &hf_reg_res_res, enc::be);
    return 1;
}

int dissect_guti_5gs_mobile_id(dissector d, context* ctx) {
    return dissect_mobile_id(d, ctx);
}

/*  0   1   2   3   4   5   6   7   8   9   a   b   c   d   e   f */
const char dgt_tbcd[] =
    {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '?', 'B', 'C', '*', '#', '?'};

/*
 * Decode the MCC/MNC from 3 octets in 'octs'
 */
void mcc_mnc_aux(const uint8_t* octs, char* mcc, char* mnc) {
    if ((octs[0] & 0x0f) <= 9) {
        mcc[0] = dgt_tbcd[octs[0] & 0x0f];
    } else {
        mcc[0] = (octs[0] & 0x0f) + 55;
    }

    if (((octs[0] & 0xf0) >> 4) <= 9) {
        mcc[1] = dgt_tbcd[(octs[0] & 0xf0) >> 4];
    } else {
        mcc[1] = ((octs[0] & 0xf0) >> 4) + 55;
    }

    if ((octs[1] & 0x0f) <= 9) {
        mcc[2] = dgt_tbcd[octs[1] & 0x0f];
    } else {
        mcc[2] = (octs[1] & 0x0f) + 55;
    }

    mcc[3] = '\0';

    if (((octs[1] & 0xf0) >> 4) <= 9) {
        mnc[2] = dgt_tbcd[(octs[1] & 0xf0) >> 4];
    } else {
        mnc[2] = ((octs[1] & 0xf0) >> 4) + 55;
    }

    if ((octs[2] & 0x0f) <= 9) {
        mnc[0] = dgt_tbcd[octs[2] & 0x0f];
    } else {
        mnc[0] = (octs[2] & 0x0f) + 55;
    }

    if (((octs[2] & 0xf0) >> 4) <= 9) {
        mnc[1] = dgt_tbcd[(octs[2] & 0xf0) >> 4];
    } else {
        mnc[1] = ((octs[2] & 0xf0) >> 4) + 55;
    }

    if (mnc[1] == 'F') {
        /*
         * only a 1 digit MNC (very old)
         */
        mnc[1] = '\0';
    } else if (mnc[2] == 'F') {
        /*
         * only a 2 digit MNC
         */
        mnc[2] = '\0';
    } else {
        mnc[3] = '\0';
    }
}

const field_meta hf_mobile_country_code = {
    "Mobile Country Code (MCC)",
    "gsm_a.mobile_country_code",
    ft::ft_bytes,
    fd::base_string,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta hf_mobile_network_code = {
    "Mobile Network Code (MNC)",
    "gsm_a.mobile_network_code",
    ft::ft_bytes,
    fd::base_string,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
/*
 * [3] 10.5.1.13 PLMN list GSM-A
 */
int dissect_plmn_list(dissector d, context* ctx) {
    auto start = d.offset;
    auto num = 0;
    char mcc[4] = {0};
    char mnc[4] = {0};
    while(d.length>=3){
        mcc_mnc_aux(d.safe_ptr(), mcc, mnc);
        auto subtree = d.tree->add_subtree(d.pinfo, d.tvb, d.offset, 3, "PLMN[%u]", num + 1);
        use_tree ut(d, subtree);
        auto item = d.add_item(3, &hf_mobile_country_code, enc::na);
        item->set_string(string((const char*)mcc));

        item = d.add_item(3, &hf_mobile_network_code, enc::na);
        item->set_string(string((const char*) mnc));
        d.step(3);
        num++;
    }
    return d.offset - start;
}

const value_string nas_5gs_nw_feat_sup_emf_values[] = {
    {0x0, "Emergency services fallback not supported"},
    {0x1, "Emergency services fallback supported in NR connected to 5GCN only"},
    {0x2, "Emergency services fallback supported in E-UTRA connected to 5GCN only"},
    {0x3,
     "mergency services fallback supported in NR connected to 5GCN and E-UTRA connected "
     "to 5GCN"},
    {0, nullptr},
};

const true_false_string tfs_nas_5gs_nw_feat_sup_mpsi = {
    "Access identity 1 valid in RPLMN or equivalent PLMN",
    "Access identity 1 not valid in RPLMN or equivalent PLMN",
};
const field_meta hf_nw_feat_sup_mpsi_b7 = {
    "MPS indicator (MPSI)",
    "nas_5gs.nw_feat_sup.mpsi",
    ft::ft_boolean,
    fd::base_dec,
    nullptr, &tfs_nas_5gs_nw_feat_sup_mpsi,nullptr,
    0x80,
};

const true_false_string tfs_supported_not_supported = {"Supported", "Not supported"};

/*
 * 9.11.3.5    5GS network feature support
 */
const field_meta hf_nw_feat_sup_ims_iwk_n26_b6 = {
    "Interworking without N26",
    "nas_5gs.nw_feat_sup.iwk_n26",
    ft::ft_boolean,
    fd::base_dec,
    nullptr, &tfs_supported_not_supported, nullptr,
    0x40,
};
const field_meta hf_nw_feat_sup_ims_emf_b5b4 = {
    "Emergency service fallback indicator (EMF)",
    "nas_5gs.nw_feat_sup.emf",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_nw_feat_sup_emf_values, nullptr, nullptr,
    0x30,
};

const value_string nas_5gs_nw_feat_sup_emc_values[] = {
    {0x0, "Emergency services not supported"},
    {0x1, "Emergency services supported in NR connected to 5GCN only"},
    {0x2, "Emergency services supported in E-UTRA connected to 5GCN only"},
    {0x3,
     "Emergency services supported in NR connected to 5GCN and E-UTRA connected to 5GCN"},
    {0, nullptr},
};
const field_meta hf_nw_feat_sup_ims_emc_b3b2 = {
    "Emergency service support indicator (EMC)",
    "nas_5gs.nw_feat_sup.emc",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_nw_feat_sup_emc_values, nullptr, nullptr,
    0x0c,
};

const value_string nas_5gs_nw_feat_sup_ims_vops_values[] = {
    {0x0, "IMS voice over PS session not supported"},
    {0x1, "IMS voice over PS session supported over 3GPP access"},
    {0x2, "IMS voice over PS session supported over non - 3GPP access"},
    {0x3, "Reserved"},
    {0, nullptr},
};
const field_meta hf_nw_feat_sup_ims_vops_b1b0 = {
    "IMS voice over PS session indicator (IMS VoPS)",
    "nas_5gs.nw_feat_sup.vops",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_nw_feat_sup_ims_vops_values,nullptr,nullptr,
    0x03,
};

/* 9.11.3.5     5GS network feature support*/
int dissect_nw_feat_sup(dissector d, context* ctx) {
    static const field_meta* flags[] = {&hf_nw_feat_sup_mpsi_b7,
                                 &hf_nw_feat_sup_ims_iwk_n26_b6,
                                 &hf_nw_feat_sup_ims_emf_b5b4,
                                 &hf_nw_feat_sup_ims_emc_b3b2,
                                 &hf_nw_feat_sup_ims_vops_b1b0,
        nullptr,
    };
    /* MPSI    IWK N26    EMF    EMC    IMS VoPS    octet 3*/
    d.add_bits(flags);
    return 1;
}

/*
 *   9.11.3.43    PDU session reactivation result error cause
 */
int dissect_pdu_ses_react_res_err_c(dissector d, context* ctx) {
    auto len = d.length;
    /*Partial service area list*/
    while(d.length>0){
        d.add_item(1, hf_pdu_sess_id, enc::be);
        d.step(1);
        d.add_item(1, &hf_mm_cause, enc::be);
        d.step(1);
    }
    return len;
}

/*
 *   9.11.3.30    LADN information
 */
int dissect_ladn_inf(dissector d, context* ctx) { return mm::dissect_ladn_inf(d, ctx); }

int dissect_mico_ind(dissector d, context* ctx) { return mm::dissect_mico_ind(d, ctx); }




int dissect_t2512_gprs_timer_3(dissector d, context* ctx) {
    diag("no dissector, %s\n", ctx->path().c_str());
    return d.length;
}

int dissect_de_reg_timer_gprs_timer2(dissector d, context* ctx) {
    diag("no dissector, %s\n", ctx->path().c_str());
    return d.length;
}

int dissect_t3502_gprs_timer_2(dissector d, context* ctx) {
    diag("no dissector, %s\n", ctx->path().c_str());
    return d.length;
}

int dissect_emerg_num_list(dissector d, context* ctx) {
    diag("no dissector, %s\n", ctx->path().c_str());
    return d.length;
}

/* 9.9.3.37a Extended Emergency Number List */
static true_false_string tfs_eenlv_value = {
    "Valid only in the PLMN from which this IE is received",
    "Valid in the country of the PLMN from which this IE is received",
};
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
    fd::base_string,
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

int dissect_emerg_num_list_7a(dissector d, context* ctx) {
    auto len = d.length;
    d.add_item(1, &hf_ext_emerge_num_list_eenlv, enc::be);
    d.step(1);

    auto i = 0;
    while(d.length>0){
        auto start = d.offset;
        auto subtree = d.tree->add_subtree(
            d.pinfo, d.tvb, d.offset, -1, "Extended emergency number #%u", i++);
        use_tree ut(d, subtree);

        auto len = (int) d.tvb->uint8(d.offset);
        d.add_item(1, &hf_ext_emerge_num_len, enc::be);
        d.step(1);
        if (len>0){
            // TODO: implement
            auto item = d.add_item(len, &hf_emerge_num, enc::be);
            // item->set_string(string());
            d.step(len);
        }
        len = d.tvb->uint8(d.offset);
        d.add_item(1, &hf_ext_emerge_sub_serv_field_len, enc::be);
        d.step(1);
        if (len>0){
            auto nchars = (len << 3) / 7;
            auto str = ts_23_038_7bits_string(d.safe_ptr(), 0, nchars);
            d.step(len);
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
    (&tfs_requested_not_requested),
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

int              dissect_sor_trans_cont(dissector d, context* ctx) {
    auto len = d.length;
    /* Layout differs depending on SOR data type*/
    static const field_meta* flags_dt0[] = {
        &hf_spare_b7,
        &hf_spare_b6,
        &hf_spare_b5,
        &hf_spare_b4,
        &hf_sor_hdr0_ack,
        &hf_sor_hdr0_list_type,
        &hf_sor_hdr0_list_ind,
        &hf_sor_hdr0_sor_data_type,
        nullptr,
    };

    static const field_meta* flags_dt1[] = {
        &hf_spare_b7,
        &hf_spare_b6,
        &hf_spare_b5,
        &hf_spare_b4,
        &hf_spare_b3,
        &hf_spare_b2,
        &hf_spare_b1,
        &hf_sor_hdr0_sor_data_type,
        nullptr,
    };
    /* 3GPP TS 31.102 [22] subclause 4.2.5 */
    static const field_meta* flags_acces_tech_1[] = {
        &hf_acces_tech_o1_b7,
        &hf_acces_tech_o1_b6,
        &hf_acces_tech_o1_b5,
        &hf_acces_tech_o1_b4,
        &hf_acces_tech_o1_b3,
        &hf_rfu_b2,
        &hf_rfu_b1,
        &hf_rfu_b0,
        nullptr,
    };

    static const field_meta* flags_acces_tech_2[] = {
        &hf_acces_tech_o2_b7,
        &hf_acces_tech_o2_b6,
        &hf_acces_tech_o2_b5,
        &hf_acces_tech_o2_b4,
        &hf_acces_tech_o2_b3,
        &hf_acces_tech_o2_b2,
        &hf_rfu_b1,
        &hf_rfu_b0,
        nullptr,
    };
    auto i = 1;
    auto oct = d.tvb->uint8(d.offset);
    auto data_type = oct &0x01;

    if (data_type == 0){
        /* SOR header    octet 4*/
        d.add_bits(flags_dt0);
        d.step(1);

        auto list_type = (oct & 0x4) >> 2;
        /* SOR-MAC-IAUSF    octet 5-20 */
        d.add_item(16, &hf_sor_mac_iausf, enc::na);
        d.step(16);

        /* CounterSOR    octet 21-22 */
        d.add_item(2, &hf_counter_sor, enc::be);
        d.step(2);

        if (list_type == 0) {
            /* Secured packet    octet 23* - 2048* */
            d.add_item(d.length, &hf_sor_sec_pkt, enc::na);
            d.step(d.length);
        } else {
            /* PLMN ID and access technology list    octet 23*-102* */
            while (d.length > 0) {
                auto subtree =
                    d.tree->add_subtree(d.pinfo, d.tvb, d.offset, -1, "List item %u", i);
                use_tree ut(d, subtree);
                /* The PLMN ID and access technology list consists of PLMN ID and access
                 * technology identifier and are coded as specified in 3GPP TS 31.102 [22]
                 * subclause 4.2.5 PLMN Contents:
                 * - Mobile Country Code (MCC) followed by the Mobile Network Code (MNC).
                 * Coding:
                 * - according to TS 24.008 [9].
                 */
                /* PLMN ID 1    octet 23*- 25* */
                auto consumed = dissect_e212_mcc_mnc(d, ctx);
                d.step(consumed);

                /* access technology identifier 1    octet 26*- 27* */
                d.add_bits(flags_acces_tech_1);
                d.step(1);

                d.add_bits(flags_acces_tech_2);
                d.step(1);

                i++;
            }
        }
    }else{
        /* SOR header    octet 4*/
        d.add_bits(flags_dt1);
        d.step(1);
        /* SOR-MAC-IUE    octet 5 - 20*/
        d.add_item(16, &hf_sor_mac_iue, enc::na);
        d.step(16);
    }
    d.extraneous_data_check(0);
    return len;
}

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

/* 9.11.3.38    Operator-defined access category definitions */
int dissect_operator_defined_acd(dissector d, context* ctx) {
    auto len = d.length;
    auto i = 1;
    while(d.length>0){
        auto subtree =
            d.tree->add_subtree(d.pinfo,
                                d.tvb,
                                d.offset,
                                2,
                                "Operator-defined access category definition  %u",
                                i);
        use_tree ut(d, subtree);
        auto len = (int) d.tvb->uint8(d.offset);
        d.add_item(1, &hf_mm_length, enc::be);
        d.step(1);

        /* Precedence value */
        d.add_item(1, &hf_mm_precedence, enc::be);
        d.step(1);

        /* PSAC    0 Spare    0 Spare    Operator-defined access category number */
        /* Length of criteria */
        /* Criteria */
        /* 0 Spare    0 Spare    0 Spare    Standardized access category */
        d.step(len);
        subtree->set_length(len + 1); // len+2?

        ++i;
    }
    return len;
}

/* 9.11.3.2A    5GS DRX parameters*/
static const value_string nas_5gs_mm_drx_vals[] = {
    {0x0, "DRX value not specified"},
    {0x1, "DRX cycle parameter T = 32"},
    {0x2, "DRX cycle parameter T = 64"},
    {0x3, "DRX cycle parameter T = 128"},
    {0x4, "DRX cycle parameter T = 256"},
    {0, nullptr},
};
const field_meta hf_drx_param = {
    "DRX value",
    "nas_5gs.mm.drx_value",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_mm_drx_vals),nullptr,nullptr,
    0x0f,
};
int dissect_nego_drx_param(dissector d, context* ctx) {
    d.add_item(1, &hf_drx_param, enc::be);
    return 1;
}

} // namespace mm_reg_accept
