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

using namespace mm;
using namespace nas;

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
    //    ELEM_OPT_TLV(0x25, , DE_NAS_5GS_MM_ALLOW_PDU_SES_STS, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &allow_pdu_ses_sts, d, ctx);
    d.step(consumed);

    /*18    UE's usage setting    UE's usage setting         9.11.3.55    O    TLV    3 */
    // ELEM_OPT_TLV(0x18, , DE_NAS_5GS_MM_UE_USAGE_SET, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &ue_usage_set, d, ctx);
    d.step(consumed);

    /*51    Requested DRX parameters    5GS DRX parameters 9.11.3.2A    O    TLV    3 */
    /* ELEM_OPT_TLV(0x51,DE_NAS_5GS_MM_5GS_DRX_PARAM, " - Requested DRX parameters");
     */
    consumed = dissect_opt_elem_tlv(nullptr, &requested_drx_param, d, ctx);
    d.step(consumed);

    /*70    EPS NAS message container    EPS NAS message container 9.11.3.24    O    TLV-E
     * 4-n */
    // ELEM_OPT_TLV_E(0x70, , DE_NAS_5GS_MM_EPS_NAS_MSG_CONT, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eps_nas_msg_cont, d, ctx);
    d.step(consumed);

    /* 74    LADN indication    LADN indication 9.11.3.29    O    TLV-E    3-811 */
    // ELEM_OPT_TLV_E(0x74, , DE_NAS_5GS_MM_LADN_INF, NULL);
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
    // ELEM_OPT_TLV(0x53, , DE_NAS_5GS_MM_UPDATE_TYPE, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &update_type, d, ctx);
    d.step(consumed);

    /* 71    NAS message container    NAS message container 9.11.3.33    O    TLV-E    4-n
     */
    // ELEM_OPT_TLV_E(0x71, , DE_NAS_5GS_MM_NAS_MSG_CONT, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &nas_msg_cont, d, ctx);
    d.step(consumed);

    // extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    d.extraneous_data_check(0);

    return d.tvb->length;
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

/* 9-  Network slicing indication  Network slicing indication 9.11.3.36  O  TV 1 */

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

int mm_reg_req::dissect_nksi_key_set_id(dissector d, context* ctx) {
    return dissect_mobile_id(d, ctx);
}


const field_meta hf_lpp_cap_b2 = {
    "LTE Positioning Protocol (LPP) capability",
    "nas_5gs.mm.lpp_cap_b2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_requested_not_requested),
    nullptr,
    0x04,
};

const field_meta hf_ho_attach_b1 = {
    "HO attach",
    "nas_5gs.mm.ho_attach_b1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_supported_not_supported),
    nullptr,
    0x02,
};
const field_meta hf_s1_mode_b0 = {
    "S1 mode",
    "nas_5gs.mm.s1_mode_b0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_requested_not_requested),
    nullptr,
    0x01,
};
/* 9.11.3.1     5GMM capability*/
int mm_reg_req::dissect_mm_cap(dissector d, context* ctx) {
    static const field_meta* flags[] = {
        &hf_spare_b7,
        &hf_spare_b6,
        &hf_spare_b5,
        &hf_spare_b4,
        &hf_spare_b3,
        &hf_lpp_cap_b2,
        &hf_ho_attach_b1,
        &hf_s1_mode_b0,
        nullptr,
    };
    d.add_bits(flags);
    d.step(1);
    d.extraneous_data_check(0);
    return 1;
}

const field_meta hf_nas_5gs_mm_5g_ea0 = {
    "5G-EA0",
    "nas_5gs.mm.5g_ea0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x80,
};
const field_meta hf_nas_5gs_mm_5g_ea1 = {
    "128-5G-EA1",
    "nas_5gs.mm.128_5g_ea1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x40,
};
const field_meta hf_nas_5gs_mm_5g_ea2 = {
    "128-5G-EA2",
    "nas_5gs.mm.128_5g_ea2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x20,
};
const field_meta hf_nas_5gs_mm_5g_ea3 = {
    "128-5G-EA3",
    "nas_5gs.mm.128_5g_ea3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x10,
};
const field_meta hf_nas_5gs_mm_5g_ea4 = {
    "5G-EA4",
    "nas_5gs.mm.5g_ea4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x08,
};
const field_meta hf_nas_5gs_mm_5g_ea5 = {
    "5G-EA5",
    "nas_5gs.mm.5g_ea5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x04,
};
const field_meta hf_nas_5gs_mm_5g_ea6 = {
    "5G-EA6",
    "nas_5gs.mm.5g_ea6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x02,
};
const field_meta hf_nas_5gs_mm_5g_ea7 = {
    "5G-EA7",
    "nas_5gs.mm.5g_ea7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x01,
};

const field_meta hf_nas_5gs_mm_5g_ia0 = {
    "5G-IA0",
    "nas_5gs.mm.ia0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x80,
};
const field_meta hf_nas_5gs_mm_5g_ia1 = {
    "128-5G-IA1",
    "nas_5gs.mm.5g_128_ia1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x40,
};
const field_meta hf_nas_5gs_mm_5g_ia2 = {
    "128-5G-IA2",
    "nas_5gs.mm.5g_128_ia2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x20,
};
const field_meta hf_nas_5gs_mm_5g_ia3 = {
    "128-5G-IA3",
    "nas_5gs.mm.5g_128_ia4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x10,
};
const field_meta hf_nas_5gs_mm_5g_ia4 = {
    "5G-IA4",
    "nas_5gs.mm.5g_128_ia4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x08,
};
const field_meta hf_nas_5gs_mm_5g_ia5 = {
    "5G-IA5",
    "nas_5gs.mm.5g_ia5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x04,
};
const field_meta hf_nas_5gs_mm_5g_ia6 = {
    "5G-IA6",
    "nas_5gs.mm.5g_ia6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x02,
};
const field_meta hf_nas_5gs_mm_5g_ia7 = {
    "5G-IA7",
    "nas_5gs.mm.5g_ia7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x01,
};

const field_meta hf_nas_5gs_mm_eea0 = {
    "EEA0",
    "nas_5gs.mm.eea0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x80,
};
const field_meta hf_nas_5gs_mm_eea1 = {
    "128-EEA1",
    "nas_5gs.mm.128eea1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x40,
};
const field_meta hf_nas_5gs_mm_eea2 = {
    "128-EEA2",
    "nas_5gs.mm.128eea2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x20,
};
const field_meta hf_nas_5gs_mm_eea3 = {
    "128-EEA3",
    "nas_5gs.mm.eea3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x10,
};
const field_meta hf_nas_5gs_mm_eea4 = {
    "EEA4",
    "nas_5gs.mm.eea4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x08,
};
const field_meta hf_nas_5gs_mm_eea5 = {
    "EEA5",
    "nas_5gs.mm.eea5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x04,
};
const field_meta hf_nas_5gs_mm_eea6 = {
    "EEA6",
    "nas_5gs.mm.eea6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x02,
};
const field_meta hf_nas_5gs_mm_eea7 = {
    "EEA7",
    "nas_5gs.mm.eea7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x01,
};

const field_meta hf_nas_5gs_mm_eia0 = {
    "EIA0",
    "nas_5gs.mm.eia0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x80,
};
const field_meta hf_nas_5gs_mm_eia1 = {
    "128-EIA1",
    "nas_5gs.mm.128eia1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x40,
};
const field_meta hf_nas_5gs_mm_eia2 = {
    "128-EIA2",
    "nas_5gs.mm.128eia2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x20,
};
const field_meta hf_nas_5gs_mm_eia3 = {
    "128-EIA3",
    "nas_5gs.mm.eia3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x10,
};
const field_meta hf_nas_5gs_mm_eia4 = {
    "EIA4",
    "nas_5gs.mm.eia4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x08,
};
const field_meta hf_nas_5gs_mm_eia5 = {
    "EIA5",
    "nas_5gs.mm.eia5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x04,
};
const field_meta hf_nas_5gs_mm_eia6 = {
    "EIA6",
    "nas_5gs.mm.eia6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x02,
};
const field_meta hf_nas_5gs_mm_eia7 = {
    "EIA7",
    "nas_5gs.mm.eia7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x01,
};

/* 9.11.3.54    UE security capability*/
int mm_reg_req::dissect_use_sec_cap(dissector d, context* ctx) {
    static const field_meta* oct3_flags[] = {
        &hf_nas_5gs_mm_5g_ea0,
        &hf_nas_5gs_mm_5g_ea1,
        &hf_nas_5gs_mm_5g_ea2,
        &hf_nas_5gs_mm_5g_ea3,
        &hf_nas_5gs_mm_5g_ea4,
        &hf_nas_5gs_mm_5g_ea5,
        &hf_nas_5gs_mm_5g_ea6,
        &hf_nas_5gs_mm_5g_ea7,
        nullptr,
    };

    static const field_meta* oct4_flags[] = {
        &hf_nas_5gs_mm_5g_ia0,
        &hf_nas_5gs_mm_5g_ia1,
        &hf_nas_5gs_mm_5g_ia2,
        &hf_nas_5gs_mm_5g_ia3,
        &hf_nas_5gs_mm_5g_ia4,
        &hf_nas_5gs_mm_5g_ia5,
        &hf_nas_5gs_mm_5g_ia6,
        &hf_nas_5gs_mm_5g_ia7,
        nullptr,
    };

    static const field_meta* oct5_flags[] = {
        &hf_nas_5gs_mm_eea0,
        &hf_nas_5gs_mm_eea1,
        &hf_nas_5gs_mm_eea2,
        &hf_nas_5gs_mm_eea3,
        &hf_nas_5gs_mm_eea4,
        &hf_nas_5gs_mm_eea5,
        &hf_nas_5gs_mm_eea6,
        &hf_nas_5gs_mm_eea7,
        nullptr,
    };

    static const field_meta* oct6_flags[] = {
        &hf_nas_5gs_mm_eia0,
        &hf_nas_5gs_mm_eia1,
        &hf_nas_5gs_mm_eia2,
        &hf_nas_5gs_mm_eia3,
        &hf_nas_5gs_mm_eia4,
        &hf_nas_5gs_mm_eia5,
        &hf_nas_5gs_mm_eia6,
        &hf_nas_5gs_mm_eia7,
        nullptr,
    };

    /* 5G-EA0    128-5G-EA1    128-5G-EA2    128-5G-EA3    5G-EA4    5G-EA5    5G-EA6
     * 5G-EA7    octet 3 */
    d.add_bits(oct3_flags);
    d.step(1);

    /* 5G-IA0    128-5G-IA1    128-5G-IA2    128-5G-IA3    5G-IA4    5G-IA5    5G-IA6
     * 5G-IA7 octet 4 */
    d.add_bits(oct4_flags);
    d.step(1);

    if (d.length<-0) {
        return 2;
    }

    /* EEA0    128-EEA1    128-EEA2    128-EEA3    EEA4    EEA5    EEA6    EEA7 octet 5 */
    d.add_bits( oct5_flags);
    d.step(1);

    /* EIA0    128-EIA1    128-EIA2    128-EIA3    EIA4    EIA5    EIA6    EIA7 octet 6 */
    d.add_bits(oct6_flags);
    d.step(1);

    return 4;
}

//* 9.11.3.8     5GS tracking area identity
int mm_reg_req::dissect_last_v_tai(dissector d, context* ctx) {
    /* MCC digit 2    MCC digit 1 Octet 2*/
    /* MNC digit 3    MCC digit 3 Octet 3*/
    /* MNC digit 2    MNC digit 1 Octet 4*/
    /* TAC Octet 5 - 7 */
   auto consumed =  dissect_e212_mcc_mnc(d, ctx);
   d.step(3);
   return 3;
}

// S1 UE network capability 9.11.3.48
static const true_false_string nas_eps_emm_ucs2_supp_flg_value = {
    "The UE has no preference between the use of the default alphabet and the use of "
    "UCS2",
    "The UE has a preference for the default alphabet",
};

const field_meta hf_nas_eps_emm_eea0 = {
    "EEA0",
    "nas_eps.emm.eea0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x80,
};
const field_meta hf_nas_eps_emm_128eea1 = {
    "128-EEA1",
    "nas_eps.emm.128eea1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x40,
};
const field_meta hf_nas_eps_emm_128eea2 = {
    "128-EEA2",
    "nas_eps.emm.128eea2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x20,
};
const field_meta hf_nas_eps_emm_eea3 = {
    "128-EEA3",
    "nas_eps.emm.eea3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x10,
};
const field_meta hf_nas_eps_emm_eea4 = {
    "EEA4",
    "nas_eps.emm.eea4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x08,
};
const field_meta hf_nas_eps_emm_eea5 = {
    "EEA5",
    "nas_eps.emm.eea5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x04,
};
const field_meta hf_nas_eps_emm_eea6 = {
    "EEA6",
    "nas_eps.emm.eea6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x02,
};
const field_meta hf_nas_eps_emm_eea7 = {
    "EEA7",
    "nas_eps.emm.eea7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x01,
};

const field_meta hf_nas_eps_emm_eia0 = {
    "EIA0",
    "nas_eps.emm.eia0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x80,
};
const field_meta hf_nas_eps_emm_128eia1 = {
    "128-EIA1",
    "nas_eps.emm.128eia1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x40,
};
const field_meta hf_nas_eps_emm_128eia2 = {
    "128-EIA2",
    "nas_eps.emm.128eia2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x20,
};
const field_meta hf_nas_eps_emm_eia3 = {
    "128-EIA3",
    "nas_eps.emm.eia3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x10,
};
const field_meta hf_nas_eps_emm_eia4 = {
    "EIA4",
    "nas_eps.emm.eia4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x08,
};
const field_meta hf_nas_eps_emm_eia5 = {
    "EIA5",
    "nas_eps.emm.eia5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x04,
};
const field_meta hf_nas_eps_emm_eia6 = {
    "EIA6",
    "nas_eps.emm.eia6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x02,
};
const field_meta hf_nas_eps_emm_eia7 = {
    "EIA7",
    "nas_eps.emm.eia7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x01,
};

const field_meta hf_nas_eps_emm_uea0 = {
    "UEA0",
    "nas_eps.emm.uea0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x80,
};
const field_meta hf_nas_eps_emm_uea1 = {
    "UEA1",
    "nas_eps.emm.uea1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x40,
};
const field_meta hf_nas_eps_emm_uea2 = {
    "UEA2",
    "nas_eps.emm.uea2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x20,
};
const field_meta hf_nas_eps_emm_uea3 = {
    "UEA3",
    "nas_eps.emm.uea3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x10,
};
const field_meta hf_nas_eps_emm_uea4 = {
    "UEA4",
    "nas_eps.emm.uea4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x08,
};
const field_meta hf_nas_eps_emm_uea5 = {
    "UEA5",
    "nas_eps.emm.uea5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x04,
};
const field_meta hf_nas_eps_emm_uea6 = {
    "UEA6",
    "nas_eps.emm.uea6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x02,
};
const field_meta hf_nas_eps_emm_uea7 = {
    "UEA7",
    "nas_eps.emm.uea7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x01,
};

const field_meta hf_nas_eps_emm_ucs2_supp = {
    "UCS2 support (UCS2)",
    "nas_eps.emm.emm_ucs2_supp",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&nas_eps_emm_ucs2_supp_flg_value,nullptr,
    0x80,
};
const field_meta hf_nas_eps_emm_uia1 = {
    "UMTS integrity algorithm UIA1",
    "nas_eps.emm.uia1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x40,
};
const field_meta hf_nas_eps_emm_uia2 = {
    "UMTS integrity algorithm UIA2",
    "nas_eps.emm.uia2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x20,
};
const field_meta hf_nas_eps_emm_uia3 = {
    "UMTS integrity algorithm UIA3",
    "nas_eps.emm.uia3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x10,
};
const field_meta hf_nas_eps_emm_uia4 = {
    "UMTS integrity algorithm UIA4",
    "nas_eps.emm.uia4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x08,
};
const field_meta hf_nas_eps_emm_uia5 = {
    "UMTS integrity algorithm UIA5",
    "nas_eps.emm.uia5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x04,
};
const field_meta hf_nas_eps_emm_uia6 = {
    "UMTS integrity algorithm UIA6",
    "nas_eps.emm.uia6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x02,
};
const field_meta hf_nas_eps_emm_uia7 = {
    "UMTS integrity algorithm UIA7",
    "nas_eps.emm.uia7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x01,
};

const field_meta hf_nas_eps_emm_prose_dd_cap = {
    "ProSe direct discovery",
    "nas_eps.emm.prose_dd_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x80,
};
const field_meta hf_nas_eps_emm_prose_cap = {
    "ProSe",
    "nas_eps.emm.prose_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x40,
};
const field_meta hf_nas_eps_emm_h245_ash_cap = {
    "H.245 After SRVCC Handover",
    "nas_eps.emm.h245_ash_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x20,
};
const field_meta hf_nas_eps_emm_acc_csfb_cap = {
    "Access class control for CSFB",
    "nas_eps.emm.acc_csfb_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x10,
};
const field_meta hf_nas_eps_emm_lpp_cap = {
    "LTE Positioning Protocol",
    "nas_eps.emm.lpp_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x08,
};
const field_meta hf_nas_eps_emm_lcs_cap = {
    "Location services (LCS) notification mechanisms",
    "nas_eps.emm.lcs_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x04,
};
const field_meta hf_nas_eps_emm_1xsrvcc_cap = {
    "SRVCC from E-UTRAN to cdma2000 1xCS",
    "nas_eps.emm.1xsrvcc_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x02,
};
const field_meta hf_nas_eps_emm_nf_cap = {
    "Notification procedure",
    "nas_eps.emm.nf_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x01,
};

const field_meta hf_nas_eps_emm_epco_cap = {
    "Extended protocol configuration options",
    "nas_eps.emm.epco_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x80,
};
const field_meta hf_nas_eps_emm_hc_cp_ciot_cap = {
    "Header compression for control plane CIoT EPS optimization",
    "nas_eps.emm.hc_cp_ciot_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x40,
};
const field_meta hf_nas_eps_emm_er_wo_pdn_cap = {
    "EMM-REGISTERED w/o PDN connectivity",
    "nas_eps.emm.er_wo_pdn_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x20,
};
const field_meta hf_nas_eps_emm_s1u_data_cap = {
    "S1-U data transfer",
    "nas_eps.emm.s1u_data_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x10,
};
const field_meta hf_nas_eps_emm_up_ciot_cap = {
    "User plane CIoT EPS optimization",
    "nas_eps.emm.up_ciot_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x08,
};
const field_meta hf_nas_eps_emm_cp_ciot_cap = {
    "Control plane CIoT EPS optimization",
    "nas_eps.emm.cp_ciot_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x04,
};
const field_meta hf_nas_eps_emm_prose_relay_cap = {
    "ProSe UE-to-network relay",
    "nas_eps.emm.prose_relay_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x02,
};
const field_meta hf_nas_eps_emm_prose_dc_cap = {
    "ProSe direct communication",
    "nas_eps.emm.prose_dc_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x01,
};

const field_meta hf_nas_eps_15_bearers_cap = {
    "Signalling for a maximum number of 15 EPS bearer contexts",
    "nas_eps.emm.15_bearers_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x80,
};
const field_meta hf_nas_eps_sgc_cap = {
    "Service gap control",
    "nas_eps.emm.sgc_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x40,
};
const field_meta hf_nas_eps_n1mode_cap = {
    "N1 mode",
    "nas_eps.emm.n1mode_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x20,
};
const field_meta hf_nas_eps_dcnr_cap = {
    "Dual connectivity with NR",
    "nas_eps.emm.dcnr_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x10,
};
const field_meta hf_nas_eps_cp_backoff_cap = {
    "Control plane data backoff",
    "nas_eps.emm.cp_backoff_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x08,
};
const field_meta hf_nas_eps_restrict_ec_cap = {
    "Restriction on use of enhanced coverage",
    "nas_eps.emm.restrict_ec_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x04,
};
const field_meta hf_nas_eps_v2x_pc5_cap = {
    "V2X communication over PC5",
    "nas_eps.emm.v2x_pc5_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x02,
};
const field_meta hf_nas_eps_multiple_drb_cap = {
    "Multiple DRB",
    "nas_eps.emm.multiple_drb_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
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
int mm_reg_req::dissect_s1_ue_net_cap(dissector d, context* ctx) {
    static const field_meta* oct3_flags[] = {
        &hf_nas_eps_emm_eea0,
        &hf_nas_eps_emm_128eea1,
        &hf_nas_eps_emm_128eea2,
        &hf_nas_eps_emm_eea3,
        &hf_nas_eps_emm_eea4,
        &hf_nas_eps_emm_eea5,
        &hf_nas_eps_emm_eea6,
        &hf_nas_eps_emm_eea7,
        nullptr,
    };

    static const field_meta* oct4_flags[] = {
        &hf_nas_eps_emm_eia0,
        &hf_nas_eps_emm_128eia1,
        &hf_nas_eps_emm_128eia2,
        &hf_nas_eps_emm_eia3,
        &hf_nas_eps_emm_eia4,
        &hf_nas_eps_emm_eia5,
        &hf_nas_eps_emm_eia6,
        &hf_nas_eps_emm_eia7,
        nullptr,
    };

    static const field_meta* oct5_flags[] = {
        &hf_nas_eps_emm_uea0,
        &hf_nas_eps_emm_uea1,
        &hf_nas_eps_emm_uea2,
        &hf_nas_eps_emm_uea3,
        &hf_nas_eps_emm_uea4,
        &hf_nas_eps_emm_uea5,
        &hf_nas_eps_emm_uea6,
        &hf_nas_eps_emm_uea7,
        nullptr,
    };

    static const field_meta* oct6_flags[] = {
        &hf_nas_eps_emm_ucs2_supp,
        &hf_nas_eps_emm_uia1,
        &hf_nas_eps_emm_uia2,
        &hf_nas_eps_emm_uia3,
        &hf_nas_eps_emm_uia4,
        &hf_nas_eps_emm_uia5,
        &hf_nas_eps_emm_uia6,
        &hf_nas_eps_emm_uia7,
        nullptr,
    };

    static const field_meta* oct7_flags[] = {
        &hf_nas_eps_emm_prose_dd_cap,
        &hf_nas_eps_emm_prose_cap,
        &hf_nas_eps_emm_h245_ash_cap,
        &hf_nas_eps_emm_acc_csfb_cap,
        &hf_nas_eps_emm_lpp_cap,
        &hf_nas_eps_emm_lcs_cap,
        &hf_nas_eps_emm_1xsrvcc_cap,
        &hf_nas_eps_emm_nf_cap,
        nullptr,
    };

    static const field_meta* oct8_flags[] = {
        &hf_nas_eps_emm_epco_cap,
        &hf_nas_eps_emm_hc_cp_ciot_cap,
        &hf_nas_eps_emm_er_wo_pdn_cap,
        &hf_nas_eps_emm_s1u_data_cap,
        &hf_nas_eps_emm_up_ciot_cap,
        &hf_nas_eps_emm_cp_ciot_cap,
        &hf_nas_eps_emm_prose_relay_cap,
        &hf_nas_eps_emm_prose_dc_cap,
        nullptr,
    };

    static const field_meta* oct9_flags[] = {
        &hf_nas_eps_15_bearers_cap,
        &hf_nas_eps_sgc_cap,
        &hf_nas_eps_n1mode_cap,
        &hf_nas_eps_dcnr_cap,
        &hf_nas_eps_cp_backoff_cap,
        &hf_nas_eps_restrict_ec_cap,
        &hf_nas_eps_v2x_pc5_cap,
        &hf_nas_eps_multiple_drb_cap,
        nullptr,
    };
    auto len = d.length;

    /* EPS encryption algorithms supported (octet 3) */
    /* EEA0    128-EEA1    128-EEA2    128-EEA3    EEA4    EEA5    EEA6    EEA7 */
    d.add_bits(oct3_flags);
    d.step(1);

    /* EPS integrity algorithms supported (octet 4) */
    /* EIA0    128-EIA1    128-EIA2    128-EIA3    EIA4    EIA5    EIA6    EIA7 */
    d.add_bits(oct4_flags);
    d.step(1);

    /* Following octets are optional */
    if(d.length<=0) return 2;

    /* UMTS encryption algorithms supported (octet 5)
     * UEA0    UEA1    UEA2    UEA3    UEA4    UEA5    UEA6    UEA7 */
    d.add_bits(oct5_flags);
    d.step(1);

    if (d.length <= 0) return 3;

    /* Octet 6 */
    /* UCS2    UIA1    UIA2    UIA3    UIA4    UIA5    UIA6    UIA7 */
    d.add_bits(oct6_flags);
    d.step(1);

    if (d.length <= 0) return 4;

    /* Octet 7
     * ProSe-dd ProSe    H.245-ASH    ACC-CSFB    LPP    LCS    1xSR VCC    NF
     */
    d.add_bits(oct7_flags);
    d.step(1);

    if (d.length <= 0) return len;

    /* Octet 8
     * ePCO    HC-CP CIoT    ERw/oPDN    S1-U data    UP CIoT    CP CIoT    Prose-relay
     * ProSe-dc
     */
    d.add_bits(oct8_flags );
    d.step(1);

    if (d.length <= 0) return len;

    /* Octet 9
     * 0 Spare    SGC    N1mode    DCNR    CP backoff    RestrictEC    V2X PC5 multipleDRB
     */
    // hf_nas_eps_spare_bits
    d.add_bits(oct9_flags);
    d.step(1);

    while (d.length >= 0) {
        d.add_item(1, &hf_nas_eps_spare_bits, enc::be);
        d.step(1);
    }
    return len;
}
/*
 * 9.11.3.57    Uplink data status
 */

static true_false_string tfs_nas_5gs_ul_data_sts_psi = {
    "uplink data are pending",
    "no uplink data are pending",
};
const field_meta hf_nas_5gs_ul_data_sts_psi_7_b7 = {
    "PSI(7)",
    "nas_5gs.ul_data_sts_psi_7_b7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x80,
};
const field_meta hf_nas_5gs_ul_data_sts_psi_6_b6 = {
    "PSI(6)",
    "nas_5gs.ul_data_sts_psi_6_b6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x40,
};
const field_meta hf_nas_5gs_ul_data_sts_psi_5_b5 = {
    "PSI(5)",
    "nas_5gs.ul_data_sts_psi_5_b5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x20,
};
const field_meta hf_nas_5gs_ul_data_sts_psi_4_b4 = {
    "PSI(4)",
    "nas_5gs.ul_data_sts_psi_4_b4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x10,
};
const field_meta hf_nas_5gs_ul_data_sts_psi_3_b3 = {
    "PSI(3)",
    "nas_5gs.ul_data_sts_psi_3_b3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x08,
};
const field_meta hf_nas_5gs_ul_data_sts_psi_2_b2 = {
    "PSI(2)",
    "nas_5gs.ul_data_sts_psi_2_b2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x04,
};
const field_meta hf_nas_5gs_ul_data_sts_psi_1_b1 = {
    "PSI(1)",
    "nas_5gs.ul_data_sts_psi_1_b1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x02,
};
const field_meta hf_nas_5gs_ul_data_sts_psi_0_b0 = {
    "Spare",
    "nas_5gs.ul_data_sts_psi_0_b0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x01,
};

const field_meta hf_nas_5gs_ul_data_sts_psi_15_b7 = {
    "PSI(15)",
    "nas_5gs.ul_data_sts_psi_15_b7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x80,
};
const field_meta hf_nas_5gs_ul_data_sts_psi_14_b6 = {
    "PSI(14)",
    "nas_5gs.ul_data_sts_psi_14_b6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x40,
};
const field_meta hf_nas_5gs_ul_data_sts_psi_13_b5 = {
    "PSI(13)",
    "nas_5gs.ul_data_sts_psi_13_b5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x20,
};
const field_meta hf_nas_5gs_ul_data_sts_psi_12_b4 = {
    "PSI(12)",
    "nas_5gs.ul_data_sts_psi_12_b4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x10,
};
const field_meta hf_nas_5gs_ul_data_sts_psi_11_b3 = {
    "PSI(11)",
    "nas_5gs.ul_data_sts_psi_11_b3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x08,
};
const field_meta hf_nas_5gs_ul_data_sts_psi_10_b2 = {
    "PSI(10)",
    "nas_5gs.ul_data_sts_psi_10_b2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x04,
};
const field_meta hf_nas_5gs_ul_data_sts_psi_9_b1 = {
    "PSI(9)",
    "nas_5gs.ul_data_sts_psi_9_b1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x02,
};
const field_meta hf_nas_5gs_ul_data_sts_psi_8_b0 = {
    "PSI(8)",
    "nas_5gs.ul_data_sts_psi_8_b0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x01,
};

/*40    Uplink data status    Uplink data status 9.11.3.57    O    TLV    4-34 */
int mm_reg_req::dissect_ul_data_status(dissector d, context* ctx) {
    static const field_meta* psi_0_7_flags[] = {
        &hf_nas_5gs_ul_data_sts_psi_7_b7,
        &hf_nas_5gs_ul_data_sts_psi_6_b6,
        &hf_nas_5gs_ul_data_sts_psi_5_b5,
        &hf_nas_5gs_ul_data_sts_psi_4_b4,
        &hf_nas_5gs_ul_data_sts_psi_3_b3,
        &hf_nas_5gs_ul_data_sts_psi_2_b2,
        &hf_nas_5gs_ul_data_sts_psi_1_b1,
        &hf_nas_5gs_ul_data_sts_psi_0_b0,
        nullptr,
    };

    static const field_meta* psi_8_15_flags[] = {
        &hf_nas_5gs_ul_data_sts_psi_15_b7,
        &hf_nas_5gs_ul_data_sts_psi_14_b6,
        &hf_nas_5gs_ul_data_sts_psi_13_b5,
        &hf_nas_5gs_ul_data_sts_psi_12_b4,
        &hf_nas_5gs_ul_data_sts_psi_11_b3,
        &hf_nas_5gs_ul_data_sts_psi_10_b2,
        &hf_nas_5gs_ul_data_sts_psi_9_b1,
        &hf_nas_5gs_ul_data_sts_psi_8_b0,
        nullptr,
    };
    auto len = d.length;

    d.add_bits(psi_0_7_flags);
    d.step(1);

    d.add_bits(psi_8_15_flags);
    d.step(1);

    d.extraneous_data_check(0);

    return 2;
}

/* 6D   UE status UE status 9.9.3.54 O TLV 3 */
/*
 *    9.11.3.56    UE status
 */

static true_false_string tfs_nas_5gs_mm_n1_mod = {
    "UE is in 5GMM-REGISTERED state",
    "UE is not in 5GMM-REGISTERED state",
};

static true_false_string tfs_nas_5gs_mm_s1_mod = {
    "UE is in EMM-REGISTERED state",
    "UE is not in EMM-REGISTERED state",
};
const field_meta hf_nas_5gs_spare_b6 = {
    "Spare",
    "nas_5gs.spare_b6",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x40,
};
const field_meta hf_nas_5gs_spare_b5 = {
    "Spare",
    "nas_5gs.spare_b5",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x20,
};
const field_meta hf_nas_5gs_spare_b4 = {
    "Spare",
    "nas_5gs.spare_b4",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x10,
};
#if 0
const field_meta hf_nas_5gs_mm_n1_mode_reg_b1 = {
    "N1 mode reg",
    "nas_5gs.mm.n1_mode_reg_b1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_mm_n1_mod,
    nullptr,
    0x02,
};
const field_meta hf_mm_s1_mode_reg_b0 = {
    "S1 mode reg",
    "nas_5gs.mm.s1_mode_reg_b0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_mm_s1_mod,
    nullptr,
    0x01,
};
#endif

int mm_reg_req::dissect_ue_status(dissector d, context* ctx) {
    static const field_meta* flags[] = {
        &hf_nas_5gs_spare_b7,
        &hf_nas_5gs_spare_b6,
        &hf_nas_5gs_spare_b5,
        &hf_nas_5gs_spare_b4,
        &hf_nas_5gs_spare_b3,
        &hf_nas_5gs_spare_b2,
        &hf_nas_5gs_mm_n1_mode_reg_b1,
        &hf_mm_s1_mode_reg_b0,
        nullptr,
    };
    /* 0     0     0     0     0     0     0 Spare    S1  mode reg */
    d.add_bits(flags);
    return 1;
}

int mm_reg_req::dissect_aguti_mobile_id(dissector d, context* ctx) {
    return mm::dissect_mobile_id(d, ctx);
}

int mm_reg_req::dissect_pdu_ses_sts(dissector d, context* ctx) {
    return mm::dissect_pdu_ses_status(d, ctx);
}

// UE's usage setting    UE's usage setting         9.11.3.55
/*
 * 9.11.3.55    UE's usage setting
 */
static true_false_string tfs_nas_5gs_mm_ue_usage_setting = {
    "Data centric",
    "Voice centric",
};
const field_meta hf_nas_5gs_spare_b1 = {
    "Spare",
    "nas_5gs.spare_b1",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x02,
};
const field_meta hf_nas_5gs_mm_ue_usage_setting = {
    "UE's usage setting",
    "nas_5gs.mm.ue_usage_setting",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_mm_ue_usage_setting,
    nullptr,
    0x01,
};
int mm_reg_req::dissect_usage_set(dissector d, context* ctx) {
    static const field_meta* flags[] = {
        &hf_nas_5gs_spare_b3,
        &hf_nas_5gs_spare_b2,
        &hf_nas_5gs_spare_b1,
        &hf_nas_5gs_mm_ue_usage_setting,
        nullptr,
    };
    d.add_bits(flags);
    return 1;
}

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
    nas_5gs_mm_drx_vals,
    nullptr,
    nullptr,
    0x0f,
};
/* 9.11.3.2A    5GS DRX parameters*/
int mm_reg_req::dissect_requested_drx_param(dissector d, context* ctx) {
    d.add_item(1, &hf_drx_param, enc::be);
    return 0;
}

/*
 *   9.11.3.24    EPS NAS message container
 */
int mm_reg_req::dissect_eps_nas_msg_cont(dissector d, context* ctx) {
    diag("no eps dissector\n");
    return d.length;
}

int mm_reg_req::dissect_ladn_inf(dissector d, context* ctx) {
    return mm::dissect_ladn_inf(d, ctx);
}

int mm_reg_req::dissect_pld_cont_type(dissector d, context* ctx) {
    auto oct = d.tvb->uint8(d.offset);
    d.set_private("payload-content-type", oct);

    d.add_item(1, &mm::hf_pld_cont_type, enc::be);
    return 1;
}

int mm_reg_req::dissect_pld_cont(dissector d, context* ctx) {
    return mm::dissect_pld_cont(d, ctx);
}

/*
 * 9.11.3.9A    5GS update type
 */

const true_false_string tfs_nas5gs_sms_requested = {
    "SMS over NAS supported",
    "SMS over NAS not supported",
};
const true_false_string tfs_needed_not_needed = {"Needed", "Not Needed"};
const field_meta hf_ng_ran_rcu = {
    "NG-RAN Radio Capability Update (NG-RAN-RCU)",
    "nas_5gs.mm.ng_ran_rcu",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_needed_not_needed,
    nullptr,
    0x02,
};

int mm_reg_req::dissect_update_type(dissector d, context* ctx) {
    static const field_meta* flags[] = {
        &hf_nas_5gs_spare_b3,
        &hf_nas_5gs_spare_b2,
        &hf_ng_ran_rcu,
        &hf_sms_requested,
        nullptr,
    };
    d.add_bits(flags);
    return 1;
}

int mm_reg_req::dissect_mico_ind(dissector d, context* ctx) {
    return mm::dissect_mico_ind(d, ctx);
}

/* 9.11.3.37    NSSAI*/
int mm_reg_req::dissect_requested_nssai(dissector d, context* ctx) {
    auto len = d.length;
    auto i = 1;
    while(d.length>0){
        auto subtree = d.tree->add_subtree(d.pinfo, d.tvb, d.offset, 2, "S-NSSAI %u", i);
        use_tree ut(d, subtree);

        auto length = (int) d.tvb->uint8(d.offset);
        d.add_item(1, &hf_mm_length, enc::be);
        d.step(1);

        auto consumed = dissect_s_nssai(d.slice(length), ctx);
        d.step(consumed);
        subtree->set_length(length + 1);
        ++i;
    }
    return len;
}
