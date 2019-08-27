#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_reg_req {
extern const field_meta* hf_reg_req_flags;

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
extern const element_meta requested_nssai;

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
    d.step(1);

    /*    Mobile identity    5GS mobile identity 9.11.3.4    M    LV-E    6-n*/
    auto consumed = dissect_elem_lv_e(nullptr, &mobile_id, d, ctx);
    d.step(consumed);

    /*C-    Non-current native NAS KSI    NAS key set identifier 9.11.3.32    O    TV 1*/
    // ELEM_OPT_TV_SHORT( 0xc0, , DE_NAS_5GS_MM_NAS_KEY_SET_ID, " - native KSI");
    consumed = dissect_opt_elem_tv_short(nullptr, &nksi_key_set_id, d, ctx);
    d.step(consumed);

    /*10    5GMM capability    5GMM capability 9.11.3.1    O    TLV    3-15*/
    // ELEM_OPT_TLV(0x10, , DE_NAS_5GS_MM_5GMM_CAP, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &mm_cap, d, ctx);
    d.step(consumed);

    /*2E    UE security capability    UE security capability 9.11.3.54    O    TLV 4-10*/
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

    /*17    S1 UE network capability    S1 UE network capability 9.11.3.48    O    TLV
     * 4-15 */
    //    ELEM_OPT_TLV(0x17, , DE_EMM_UE_NET_CAP, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &s1_ue_net_cap, d, ctx);
    d.step(consumed);

    /*40    Uplink data status    Uplink data status 9.11.3.57    O    TLV    4-34 */
    //    ELEM_OPT_TLV(0x40, , DE_NAS_5GS_MM_UL_DATA_STATUS, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &ul_data_status, d, ctx);
    d.step(consumed);

    /*50    PDU session status    PDU session status 9.11.3.44    O    TLV    4-34 */
    //    ELEM_OPT_TLV(0x50, , DE_NAS_5GS_MM_PDU_SES_STATUS, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &pdu_ses_status, d, ctx);
    d.step(consumed);

    /*B-    MICO indication    MICO indication 9.11.3.31    O    TV    1*/
    //    ELEM_OPT_TV_SHORT(0xb0, , DE_NAS_5GS_MM_MICO_IND, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &mico_ind, d, ctx);
    d.step(consumed);

    /*2B    UE status    UE status 9.11.3.56    O    TLV    3*/
    //    ELEM_OPT_TLV(0x2b, , DE_NAS_5GS_MM_UE_STATUS, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &ue_status, d, ctx);
    d.step(consumed);

    /*77    Additional GUTI    5GS mobile identity 9.11.3.4    O    TLV-E    14 */
    // ELEM_OPT_TLV_E(0x77, , DE_NAS_5GS_MM_5GS_MOBILE_ID, " -  Additional GUTI");
    consumed = dissect_opt_elem_tlv_e(nullptr, &aguti_mobile_id, d, ctx);
    d.step(consumed);

    /*25    Allowed PDU session status    Allowed PDU session status         9.11.3.13
     * O    TLV    4 - 34 */
    //    ELEM_OPT_TLV(0x25, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_ALLOW_PDU_SES_STS, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &allow_pdu_ses_sts, d, ctx);
    d.step(consumed);

    /*18    UE's usage setting    UE's usage setting         9.11.3.55    O    TLV    3 */
    // ELEM_OPT_TLV(0x18, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_UE_USAGE_SET, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &ue_usage_set, d, ctx);
    d.step(consumed);

    /*51    Requested DRX parameters    5GS DRX parameters 9.11.3.2A    O    TLV    3 */
    /*    ELEM_OPT_TLV(0x51,DE_NAS_5GS_MM_5GS_DRX_PARAM, " - Requested DRX parameters");
     */
    consumed = dissect_opt_elem_tlv(nullptr, &requested_drx_param, d, ctx);
    d.step(consumed);

    /*70    EPS NAS message container    EPS NAS message container 9.11.3.24    O    TLV-E
     * 4-n */
    // ELEM_OPT_TLV_E(0x70, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_EPS_NAS_MSG_CONT, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eps_nas_msg_cont, d, ctx);
    d.step(consumed);

    /* 74    LADN indication    LADN indication 9.11.3.29    O    TLV-E    3-811 */
    // ELEM_OPT_TLV_E(0x74, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_LADN_INF, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ladn_inf, d, ctx);
    d.step(consumed);

    /* 8-    Payload container type    Payload container type 9.11.3.40    O    TV    1 */
    // ELEM_OPT_TV_SHORT(0x80, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_PLD_CONT_TYPE, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &pld_cont_type, d, ctx);
    d.step(consumed);

    /* 7B    Payload container     Payload container 9.11.3.39    O    TLV-E    4-65538 */
    // ELEM_OPT_TLV_E(0x7B, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_PLD_CONT, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &pld_cont, d, ctx);
    d.step(consumed);

    /* 9-    Network slicing indication    Network slicing indication 9.11.3.36    O    TV
     * 1 */
    // ELEM_OPT_TV_SHORT(0x90, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_NW_SLICING_IND, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &nw_slicing_ind, d, ctx);
    d.step(consumed);

    /* 53    5GS update type    5GS update type 9.11.3.9A    O    TLV    3 */
    // ELEM_OPT_TLV(0x53, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_UPDATE_TYPE, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &update_type, d, ctx);
    d.step(consumed);

    /* 71    NAS message container    NAS message container 9.11.3.33    O    TLV-E    4-n
     */
    // ELEM_OPT_TLV_E(0x71, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_NAS_MSG_CONT, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &nas_msg_cont, d, ctx);
    d.step(consumed);

    // extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    d.extraneous_data_check(0);

    return d.tvb->reported_length;
}

namespace mm_reg_req{
int                       dissect_mico_ind(dissector d, context* ctx = nullptr);
extern const element_meta mico_ind = {
    0xb0,
    "MICO indication",
    dissect_mico_ind,
};
/*2F    Requested NSSAI    NSSAI 9.11.3.37    O    TLV    4-74*/
int                dissect_requested_nssai(dissector d, context* ctx = nullptr);
const element_meta requested_nssai = {
    0x2f,
    "Requested NSSAI",
    dissect_requested_nssai,
};

int                dissect_pld_cont(dissector d, context* ctx = nullptr);
const element_meta pld_cont = {
    0x7B,
    "Payload container",
    dissect_pld_cont,
};

int                dissect_nw_slicing_ind(dissector d, context* ctx = nullptr);
const element_meta nw_slicing_ind = {
    0x90,
    "Network slicing indication",
    dissect_nw_slicing_ind,
};

int                dissect_update_type(dissector d, context* ctx = nullptr);
const element_meta update_type = {
    0x53,
    "5GS update type",
    dissect_update_type,
};


int                dissect_nksi_key_set_id(dissector d, context* ctx = nullptr);
const element_meta nksi_key_set_id = {
    0xc0,
    "Non-current native NAS KSI",
    dissect_nksi_key_set_id,
};

int                dissect_mm_cap(dissector d, context* ctx = nullptr);
const element_meta mm_cap = {
    0x10,
    "5GMM capability",
    dissect_mm_cap,
};

int                dissect_use_sec_cap(dissector d, context* ctx = nullptr);
const element_meta ue_sec_cap = {
    0x2e,
    "UE security capability",
    dissect_use_sec_cap,
};

int                dissect_last_v_tai(dissector d, context* ctx = nullptr);
const element_meta last_v_tai = {
    0x52,
    "Last visited registered TAI",
    dissect_last_v_tai,
};

int                dissect_s1_ue_net_cap(dissector d, context* ctx = nullptr);
const element_meta s1_ue_net_cap = {
    0x17,
    "S1 UE network capability",
    dissect_s1_ue_net_cap,
};

int                dissect_ul_data_status(dissector d, context* ctx = nullptr);
const element_meta ul_data_status = {
    0x40,
    "Uplink data status",
    dissect_ul_data_status,
};

int                dissect_ue_status(dissector d, context* ctx = nullptr);
const element_meta ue_status = {
    0x2b,
    "UE status",
    dissect_ue_status,
};

int                dissect_aguti_mobile_id(dissector d, context* ctx = nullptr);
const element_meta aguti_mobile_id = {
    0x77,
    "Additional GUTI",
    dissect_aguti_mobile_id,
};

int                dissect_pdu_ses_sts(dissector d, context* ctx = nullptr);
const element_meta allow_pdu_ses_sts = {
    0x25,
    "Allowed PDU session status",
    dissect_pdu_ses_sts,
};

int                dissect_usage_set(dissector d, context* ctx = nullptr);
const element_meta ue_usage_set = {
    0x18,
    "UE's usage setting",
    dissect_usage_set,
};

int                dissect_requested_drx_param(dissector d, context* ctx = nullptr);
const element_meta requested_drx_param = {
    0x51,
    "Requested DRX parameters",
    dissect_requested_drx_param,
};

int                dissect_eps_nas_msg_cont(dissector d, context* ctx = nullptr);
const element_meta eps_nas_msg_cont = {
    0x70,
    "EPS NAS message container",
    dissect_eps_nas_msg_cont,
};

int dissect_ladn_inf(dissector d, context* ctx = nullptr);
__declspec(selectany) const element_meta ladn_inf = {
    0x74,
    "LADN indication",
    dissect_ladn_inf,
};

int                dissect_pld_cont_type(dissector d, context* ctx = nullptr);
const element_meta pld_cont_type = {
    0x80,
    "Payload container type",
    dissect_pld_cont_type,
};

} // namespace mm_reg_req

int mm_reg_req::dissect_nksi_key_set_id(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_mm_cap(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_use_sec_cap(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_last_v_tai(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_s1_ue_net_cap(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_ul_data_status(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_ue_status(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_aguti_mobile_id(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_pdu_ses_sts(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_usage_set(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_requested_drx_param(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_eps_nas_msg_cont(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_ladn_inf(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_pld_cont_type(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_pld_cont(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_nw_slicing_ind(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_update_type(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_mico_ind(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_requested_nssai(dissector d, context* ctx) { return 0; }
