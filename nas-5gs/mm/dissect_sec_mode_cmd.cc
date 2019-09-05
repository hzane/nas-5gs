#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

using namespace nas;
using namespace mm;

/* 8.2.25 Security mode command  */
int mm::dissect_sec_mode_cmd(dissector d, context* ctx) {
    const use_context uc(ctx, "security-mode-cmd", d, 0);
    
    /* Direction: network to UE */
    down_link(d.pinfo);    

    /*Selected NAS security algorithms NAS security algorithms 9.11.3.34 M V 1  */
    // ELEM_MAND_V(,DE_NAS_5GS_MM_NAS_SEC_ALGO, );
    auto consumed = dissect_elem_v(nullptr, &sec_algo, d, ctx);
    d.step(consumed);

    /* Spare half octet    Spare half octet     9.5    M    V    1/2 */
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_spare_half_octet, enc::be);

    /*ngKSI     NAS key set identifier 9.11.3.32    M    V    1/2  */
    // ELEM_MAND_V(DE_NAS_5GS_MM_NAS_KEY_SET_ID, " - ngKSI", );
    consumed = dissect_elem_v(nullptr, &nas_ksi, d, ctx);
    d.step(consumed);

    /* Replayed UE security capabilities    UE security capability   9.11.3.54  M  LV   3-5*/
    // ELEM_MAND_LV(,DE_NAS_5GS_MM_UE_SEC_CAP," - Replayed UE security capabilities",);
    consumed = dissect_elem_v(nullptr, &replayed_ue_sec_cap, d, ctx);
    d.step(consumed);

    /*E-    IMEISV request    IMEISV request     9.11.3.28    O    TV    1*/
    // ELEM_OPT_TV_SHORT(0xE0, , DE_EMM_IMEISV_REQ, NULL);
    consumed = dissect_elem_tv_short(nullptr, &imeisv_req, d, ctx);
    d.step(consumed);

    /*57 Selected EPS NAS security algorithms EPS NAS security algorithms 9.11.3.25  O TV 2 */
    // ELEM_OPT_TV(0x57, , DE_EMM_NAS_SEC_ALGS, " - Selected EPS NAS security algorithms");
    consumed = dissect_opt_elem_tv(nullptr, &selected_eps_sec_algo, d, ctx);
    d.step(consumed);

    /*36    Additional 5G security information  9.11.3.12    O    TLV    3 */
    // ELEM_OPT_TLV(0x36, , DE_NAS_5GS_MM_ADD_5G_SEC_INF, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &a_sec_info, d, ctx);
    d.step(consumed);

    /*78    EAP message  9.11.2.2    O    TLV-E    7*/
    consumed = dissect_opt_elem_tlv_e(nullptr, &eap_msg, d, ctx);
    d.step(consumed);

    /*38  ABBA 9.11.3.10    O    TLV    4-n */
    // ELEM_OPT_TLV(0x38, , DE_NAS_5GS_MM_ABBA, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &abba, d, ctx);
    d.step(consumed);

    /*19 Replayed S1 UE security capabilities    S1 UE security capability 9.11.3.48A
     * O    TLV    4-7 */
    // ELEM_OPT_TLV(0x19, DE_EMM_UE_SEC_CAP, " - Replayed S1 UE security capabilities");
    consumed = dissect_opt_elem_tlv(nullptr, &reported_s1_ue_sec_cap, d, ctx);
    d.step(consumed);
    
    return uc.length;
}

int mm::dissect_sec_algo(dissector d, context* ctx) {
    const use_context uc(ctx, "sec-algo", d, -1);

    static const field_meta* flags[] = {
        &hf_sec_algo_enc,
        &hf_sec_algo_ip,
        nullptr,
    };
    d.add_bits(flags);
    return 1;
}

namespace mm {
extern const element_meta sec_algo = {
    0xff,
    "Selected NAS security algorithms",
    dissect_sec_algo,
    nullptr,
};
extern const element_meta replayed_ue_sec_cap = {
    0xff,
    "UE security capability - Replayed UE security capabilities",
    dissect_replayed_ue_sec_cap,
    nullptr,
};
extern const element_meta imeisv_req = {
    0xE0,
    "IMEISV request",
    dissect_imeisv_req,
    nullptr,
};
extern const element_meta selected_eps_sec_algo = {
    0x57,
    "EPS NAS security algorigthms - Selected EPS NAS security algorithms",
    dissect_selected_eps_sec_algo,
    nullptr,
};
extern const element_meta a_sec_info = {
    0x36,
    "Additional 5G security information",
    dissect_a_sec_info,
    nullptr,
};

extern const element_meta reported_s1_ue_sec_cap = {
    0x19,
    "S1 UE security capability - Replayed S1 UE security capabilities",
    dissect_reported_s1_ue_sec_cap,
    nullptr,
};


/* 9.11.3.34    NAS security algorithms */
const value_string nas_5gs_mm_type_of_ip_algo_vals[] = {
    {0x0, "5G-IA0 (null integrity protection algorithm)"},
    {0x1, "128-5G-IA1"},
    {0x2, "128-5G-IA2"},
    {0x3, "128-5G-IA3"},
    {0x4, "5G-IA4"},
    {0x5, "5G-IA5"},
    {0x6, "5G-IA6"},
    {0x7, "5G-IA7"},
    {0, nullptr},};

const value_string nas_5gs_mm_type_of_enc_algo_vals[] = {
    {0x0, "5G-EA0 (null ciphering algorithm)"},
    {0x1, "128-5G-EA1"},
    {0x2, "128-5G-EA2"},
    {0x3, "128-5G-EA3"},
    {0x4, "5G-EA4"},
    {0x5, "5G-EA5"},
    {0x6, "5G-EA6"},
    {0x7, "5G-EA7"},
    {0, nullptr},
};

const field_meta hf_sec_algo_enc = {
    "Type of ciphering algorithm",
    "nas_5gs.mm.nas_sec_algo_enc",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_type_of_enc_algo_vals,
    nullptr,
    nullptr,
    0xf0,
};
const field_meta hf_sec_algo_ip = {
    "Type of integrity protection algorithm",
    "nas_5gs.mm.nas_sec_algo_ip",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_type_of_ip_algo_vals,
    nullptr,
    nullptr,
    0x0f,
};

const field_meta hf_mm_5g_ea0 = {
    "5G-EA0",
    "nas_5gs.mm.5g_ea0",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x80,
};
const field_meta hf_mm_128_5g_ea1 = {
    "128-5G-EA1",
    "nas_5gs.mm.128_5g_ea1",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x40,
};
const field_meta hf_mm_128_5g_ea2 = {
    "128-5G-EA2",
    "nas_5gs.mm.128_5g_ea2",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x20,
};
const field_meta hf_mm_128_5g_ea3 = {
    "128-5G-EA3",
    "nas_5gs.mm.128_5g_ea3",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x10,
};
const field_meta hf_mm_5g_ea4 = {
    "5G-EA4",
    "nas_5gs.mm.5g_ea4",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x08,
};
const field_meta hf_mm_5g_ea5 = {
    "5G-EA5",
    "nas_5gs.mm.5g_ea5",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x04,
};
const field_meta hf_mm_5g_ea6 = {
    "5G-EA6",
    "nas_5gs.mm.5g_ea6",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x02,
};
const field_meta hf_mm_5g_ea7 = {
    "5G-EA7",
    "nas_5gs.mm.5g_ea7",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x01,
};

const field_meta hf_mm_5g_ia0 = {
    "5G-IA0",
    "nas_5gs.mm.ia0",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x80,
};
const field_meta hf_mm_128_5g_ia1 = {
    "128-5G-IA1",
    "nas_5gs.mm.5g_128_ia1",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x40,
};
const field_meta hf_mm_128_5g_ia2 = {
    "128-5G-IA2",
    "nas_5gs.mm.5g_128_ia2",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x20,
};
const field_meta hf_mm_128_5g_ia3 = {
    "128-5G-IA3",
    "nas_5gs.mm.5g_128_ia4",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x10,
};
const field_meta hf_mm_5g_ia4 = {
    "5G-IA4",
    "nas_5gs.mm.5g_128_ia4",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x08,
};
const field_meta hf_mm_5g_ia5 = {
    "5G-IA5",
    "nas_5gs.mm.5g_ia5",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x04,
};
const field_meta hf_mm_5g_ia6 = {
    "5G-IA6",
    "nas_5gs.mm.5g_ia6",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x02,
};
const field_meta hf_mm_5g_ia7 = {
    "5G-IA7",
    "nas_5gs.mm.5g_ia7",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x01,
};

const field_meta hf_mm_eea0 = {
    "EEA0",
    "nas_5gs.mm.eea0",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x80,
};
const field_meta hf_mm_128eea1 = {
    "128-EEA1",
    "nas_5gs.mm.128eea1",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x40,
};
const field_meta hf_mm_128eea2 = {
    "128-EEA2",
    "nas_5gs.mm.128eea2",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x20,
};
const field_meta hf_mm_eea3 = {
    "128-EEA3",
    "nas_5gs.mm.eea3",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x10,
};
const field_meta hf_mm_eea4 = {
    "EEA4",
    "nas_5gs.mm.eea4",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x08,
};
const field_meta hf_mm_eea5 = {
    "EEA5",
    "nas_5gs.mm.eea5",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x04,
};
const field_meta hf_mm_eea6 = {
    "EEA6",
    "nas_5gs.mm.eea6",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x02,
};
const field_meta hf_mm_eea7 = {
    "EEA7",
    "nas_5gs.mm.eea7",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x01,
};

const field_meta hf_mm_eia0 = {
    "EIA0",
    "nas_5gs.mm.eia0",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x80,
};
const field_meta hf_mm_128eia1 = {
    "128-EIA1",
    "nas_5gs.mm.128eia1",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x40,
};
const field_meta hf_mm_128eia2 = {
    "128-EIA2",
    "nas_5gs.mm.128eia2",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x20,
};
const field_meta hf_mm_eia3 = {
    "128-EIA3",
    "nas_5gs.mm.eia3",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x10,
};
const field_meta hf_mm_eia4 = {
    "EIA4",
    "nas_5gs.mm.eia4",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x08,
};
const field_meta hf_mm_eia5 = {
    "EIA5",
    "nas_5gs.mm.eia5",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x04,
};
const field_meta hf_mm_eia6 = {
    "EIA6",
    "nas_5gs.mm.eia6",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x02,
};
const field_meta hf_mm_eia7 = {
    "EIA7",
    "nas_5gs.mm.eia7",
    ft::ft_boolean,
    fd::base_dec
    ,nullptr,&tfs_supported_not_supported,nullptr,
    0x01,
};
const field_meta hf_spare_b3 = {
    "Spare",
    "nas_5gs.spare_b3",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x08,
};
const field_meta hf_spare_b2 = {
    "Spare",
    "nas_5gs.spare_b2",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x04,
};
const field_meta hf_mm_rinmr = {
    "Retransmission of initial NAS message request(RINMR)",
    "nas_5gs.mm.rinmr",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_requested_not_requested,nullptr,
    0x02,
};
const true_false_string tfs_required_not_required = {"Required", "Not required"};
const field_meta hf_mm_hdp = {
    "Horizontal derivation parameter (HDP)",
    "nas_5gs.mm.hdp",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_required_not_required,
    nullptr,
    0x01,
};

const field_meta hf_emm_eea0 = {
    "EEA0",
    "nas_eps.emm.eea0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x80,
};
const field_meta hf_emm_128eea1 = {
    "128-EEA1",
    "nas_eps.emm.128eea1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x40,
};
const field_meta hf_emm_128eea2 = {
    "128-EEA2",
    "nas_eps.emm.128eea2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x20,
};
const field_meta hf_emm_eea3 = {
    "128-EEA3",
    "nas_eps.emm.eea3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x10,
};
const field_meta hf_emm_eea4 = {
    "EEA4",
    "nas_eps.emm.eea4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x08,
};
const field_meta hf_emm_eea5 = {
    "EEA5",
    "nas_eps.emm.eea5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x04,
};
const field_meta hf_emm_eea6 = {
    "EEA6",
    "nas_eps.emm.eea6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x02,
};
const field_meta hf_emm_eea7 = {
    "EEA7",
    "nas_eps.emm.eea7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x01,
};

const field_meta hf_emm_eia0 = {
    "EIA0",
    "nas_eps.emm.eia0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x80,
};
const field_meta hf_emm_128eia1 = {
    "128-EIA1",
    "nas_eps.emm.128eia1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x40,
};
const field_meta hf_emm_128eia2 = {
    "128-EIA2",
    "nas_eps.emm.128eia2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x20,
};
const field_meta hf_emm_eia3 = {
    "128-EIA3",
    "nas_eps.emm.eia3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x10,
};
const field_meta hf_emm_eia4 = {
    "EIA4",
    "nas_eps.emm.eia4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x08,
};
const field_meta hf_emm_eia5 = {
    "EIA5",
    "nas_eps.emm.eia5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x04,
};
const field_meta hf_emm_eia6 = {
    "EIA6",
    "nas_eps.emm.eia6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x02,
};
const field_meta hf_emm_eia7 = {
    "EIA7",
    "nas_eps.emm.eia7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x01,
};

const field_meta hf_emm_uea0 = {
    "UEA0",
    "nas_eps.emm.uea0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x80,
};
const field_meta hf_emm_uea1 = {
    "UEA1",
    "nas_eps.emm.uea1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x40,
};
const field_meta hf_emm_uea2 = {
    "UEA2",
    "nas_eps.emm.uea2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x20,
};
const field_meta hf_emm_uea3 = {
    "UEA3",
    "nas_eps.emm.uea3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x10,
};
const field_meta hf_emm_uea4 = {
    "UEA4",
    "nas_eps.emm.uea4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x08,
};
const field_meta hf_emm_uea5 = {
    "UEA5",
    "nas_eps.emm.uea5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x04,
};
const field_meta hf_emm_uea6 = {
    "UEA6",
    "nas_eps.emm.uea6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x02,
};
const field_meta hf_emm_uea7 = {
    "UEA7",
    "nas_eps.emm.uea7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x01,
};

const field_meta hf_spare_b7 = {
    "Spare",
    "nas_eps.spare.b7",
    ft::ft_uint8,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x80,
};
const field_meta hf_emm_uia1 = {
    "UMTS integrity algorithm UIA1",
    "nas_eps.emm.uia1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x40,
};
const field_meta hf_emm_uia2 = {
    "UMTS integrity algorithm UIA2",
    "nas_eps.emm.uia2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x20,
};
const field_meta hf_emm_uia3 = {
    "UMTS integrity algorithm UIA3",
    "nas_eps.emm.uia3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x10,
};
const field_meta hf_emm_uia4 = {
    "UMTS integrity algorithm UIA4",
    "nas_eps.emm.uia4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x08,
};
const field_meta hf_emm_uia5 = {
    "UMTS integrity algorithm UIA5",
    "nas_eps.emm.uia5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x04,
};
const field_meta hf_emm_uia6 = {
    "UMTS integrity algorithm UIA6",
    "nas_eps.emm.uia6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x02,
};
const field_meta hf_emm_uia7 = {
    "UMTS integrity algorithm UIA7",
    "nas_eps.emm.uia7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x01,
};

const field_meta hf_emm_gea1 = {
    "GPRS encryption algorithm GEA1",
    "nas_eps.emm.gea1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x40,
};
const field_meta hf_emm_gea2 = {
    "GPRS encryption algorithm GEA2",
    "nas_eps.emm.gea2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x20,
};
const field_meta hf_emm_gea3 = {
    "GPRS encryption algorithm GEA3",
    "nas_eps.emm.gea3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x10,
};
const field_meta hf_emm_gea4 = {
    "GPRS encryption algorithm GEA4",
    "nas_eps.emm.gea4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x08,
};
const field_meta hf_emm_gea5 = {
    "GPRS encryption algorithm GEA5",
    "nas_eps.emm.gea5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x04,
};
const field_meta hf_emm_gea6 = {
    "GPRS encryption algorithm GEA6",
    "nas_eps.emm.gea6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x02,
};
const field_meta hf_emm_gea7 = {
    "GPRS encryption algorithm GEA7",
    "nas_eps.emm.gea7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_supported_not_supported,nullptr,
    0x01,
};

} // namespace mm
