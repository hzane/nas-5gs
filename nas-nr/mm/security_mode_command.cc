#include "../common/ber.hh"
#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace nas;
using namespace mm;

/* 8.2.25 Security mode command  */
int mm::dissect_security_mode_command(dissector d, context* ctx) {
    const use_context uc(ctx, "security-mode-cmd", d, 0);

    /* Direction: network to UE */
    down_link(d.packet);

    /*Selected NAS security algorithms NAS security algorithms 9.11.3.34 M V 1  */
    dissect_v(nullptr, &selected_security_algo, d, ctx);
    d.step(1);

    /*ngKSI     NAS key set identifier 9.11.3.32    M    V    1/2  */
    dissect_v(nullptr, &nas_ksi, d, ctx);

    /* Spare half octet    Spare half octet     9.5    M    V    1/2 */
    d.step(1);

    /* Replayed UE security capabilities    UE security capability   9.11.3.54  M  LV
     * 3-5*/
    // ELEM_MAND_LV(,DE_NAS_5GS_MM_UE_SEC_CAP," - Replayed UE security capabilities",);
    auto consumed = dissect_lv(nullptr, &replayed_ue_security_capability, d, ctx);
    d.step(consumed);

    /*E-    IMEISV request    IMEISV request     9.11.3.28    O    TV    1*/
    consumed = dissect_opt_tv_short(nullptr, &imeisv_request, d, ctx);
    d.step(consumed);

    /*57 Selected EPS NAS security algorithms EPS NAS security algorithms 9.11.3.25  O TV
     * 2 */
    // ELEM_OPT_TV(0x57, , DE_EMM_NAS_SEC_ALGS, " - Selected EPS NAS security
    // algorithms");
    consumed = dissect_opt_tv(nullptr, &selected_eps_security_algo, d, ctx);
    d.step(consumed);

    /*36    Additional 5G security information  9.11.3.12    O    TLV    3 */
    // ELEM_OPT_TLV(0x36, , DE_NAS_5GS_MM_ADD_5G_SEC_INF, NULL);
    consumed = dissect_opt_tlv(nullptr, &additional_security_info, d, ctx);
    d.step(consumed);

    /*78    EAP message  9.11.2.2    O    TLV-E    7*/
    consumed = dissect_opt_tlv_e(nullptr, &cmn::eap_message, d, ctx);
    d.step(consumed);

    /*38  ABBA 9.11.3.10    O    TLV    4-n */
    // ELEM_OPT_TLV(0x38, , DE_NAS_5GS_MM_ABBA, NULL);
    consumed = dissect_opt_tlv(nullptr, &abba, d, ctx);
    d.step(consumed);

    /*19 Replayed S1 UE security capabilities    S1 UE security capability 9.11.3.48A
     * O    TLV    4-7 */
    // ELEM_OPT_TLV(0x19, DE_EMM_UE_SEC_CAP, " - Replayed S1 UE security capabilities");
    consumed = dissect_opt_tlv(nullptr, &replayed_s1_ue_security_capability, d, ctx);
    d.step(consumed);

    return uc.length;
}

namespace mm {
extern const element_meta selected_security_algo = {
    0xff,
    "Selected NAS security algorithms",
    dissect_security_algo,
    nullptr,
};
extern const element_meta replayed_ue_security_capability = {
    0xff,
    "UE security capability - Replayed UE security capabilities",
    dissect_replayed_ue_security_capability,
    nullptr,
};
extern const element_meta imeisv_request = {
    0xE0,
    "IMEISV request",
    dissect_imeisv_request,
    nullptr,
};

extern const element_meta additional_security_info = {
    0x36,
    "Additional 5G security information",
    dissect_additional_security_info,
    nullptr,
};

extern const element_meta replayed_s1_ue_security_capability = {
    0x19,
    "S1 UE security capability - Replayed S1 UE security capabilities",
    dissect_reported_s1_ue_security_capability,
    nullptr,
};

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

const field_meta hf_security_ciphering_algo = {
    "Type of ciphering algorithm",
    "nas.nr.mm.security.algorithm.type",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_type_of_enc_algo_vals,
    nullptr,
    nullptr,
    0xf0,
};

const field_meta hf_mm_128_5g_ea1 = {
    "128-5G-EA1",
    "nas.nr.mm.128.5g-ea1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x40,
};
const field_meta hf_mm_128_5g_ea2 = {
    "128-5G-EA2",
    "nas.nr.mm.128-5g.ea2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x20,
};
const field_meta hf_mm_128_5g_ea3 = {
    "128-5G-EA3",
    "nas.nr.mm.128.5g-ea3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x10,
};
const field_meta hf_mm_5g_ea4 = {
    "5G-EA4",
    "nas.nr.mm.5g.ea4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x08,
};
const field_meta hf_mm_5g_ea5 = {
    "5G-EA5",
    "nas.nr.mm.5g.ea5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x04,
};
const field_meta hf_mm_5g_ea6 = {
    "5G-EA6",
    "nas.nr.mm.5g.ea6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x02,
};
const field_meta hf_mm_5g_ea7 = {
    "5G-EA7",
    "nas.nr.mm.5g.ea7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x01,
};

const field_meta hf_mm_5g_ia0 = {
    "5G-IA0",
    "nas.nr.mm.ia0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x80,
};
const field_meta hf_mm_128_5g_ia1 = {
    "128-5G-IA1",
    "nas.nr.mm.5g-128.ia1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x40,
};
const field_meta hf_mm_128_5g_ia2 = {
    "128-5G-IA2",
    "nas.nr.mm.5g.128.ia2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x20,
};
const field_meta hf_mm_128_5g_ia3 = {
    "128-5G-IA3",
    "nas.nr.mm.5g.128.ia4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x10,
};
const field_meta hf_mm_5g_ia4 = {
    "5G-IA4",
    "nas.nr.mm.5g.128.ia4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x08,
};
const field_meta hf_mm_5g_ia5 = {
    "5G-IA5",
    "nas.nr.mm.5g.ia5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x04,
};
const field_meta hf_mm_5g_ia6 = {
    "5G-IA6",
    "nas.nr.mm.5g.ia6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x02,
};
const field_meta hf_mm_5g_ia7 = {
    "5G-IA7",
    "nas.nr.mm.5g.ia7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x01,
};

const field_meta hf_mm_eea0 = {
    "EEA0",
    "nas.nr.mm.eea0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x80,
};
const field_meta hf_mm_128eea1 = {
    "128-EEA1",
    "nas.nr.mm.128eea1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x40,
};
const field_meta hf_mm_128eea2 = {
    "128-EEA2",
    "nas.nr.mm.128eea2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x20,
};
const field_meta hf_mm_eea3 = {
    "128-EEA3",
    "nas.nr.mm.eea3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x10,
};
const field_meta hf_mm_eea4 = {
    "EEA4",
    "nas.nr.mm.eea4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x08,
};
const field_meta hf_mm_eea5 = {
    "EEA5",
    "nas.nr.mm.eea5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x04,
};
const field_meta hf_mm_eea6 = {
    "EEA6",
    "nas.nr.mm.eea6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x02,
};
const field_meta hf_mm_eea7 = {
    "EEA7",
    "nas.nr.mm.eea7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x01,
};

const field_meta hf_mm_eia0 = {
    "EIA0",
    "nas.nr.mm.eia0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x80,
};
const field_meta hf_mm_128eia1 = {
    "128-EIA1",
    "nas.nr.mm.128eia1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x40,
};
const field_meta hf_mm_128eia2 = {
    "128-EIA2",
    "nas.nr.mm.128eia2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x20,
};
const field_meta hf_mm_eia3 = {
    "128-EIA3",
    "nas.nr.mm.eia3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x10,
};
const field_meta hf_mm_eia4 = {
    "EIA4",
    "nas.nr.mm.eia4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x08,
};
const field_meta hf_mm_eia5 = {
    "EIA5",
    "nas.nr.mm.eia5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x04,
};
const field_meta hf_mm_eia6 = {
    "EIA6",
    "nas.nr.mm.eia6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x02,
};
const field_meta hf_mm_eia7 = {
    "EIA7",
    "nas.nr.mm.eia7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x01,
};
#if 0
const field_meta hf_spare_b3 = {
    "Spare",
    "nas.nr.spare_b3",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x08,
};
const field_meta hf_spare_b2 = {
    "Spare",
    "nas.nr.spare",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x04,
};
#endif
const field_meta hf_retransmission_of_initial_nas_request = {
    "Retransmission of initial NAS message request(RINMR)",
    "nas.nr.mm.retransmission",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_requested_not_requested,
    nullptr,
    0x02,
};
const true_false_string tfs_required_not_required = {
    "Required",
    "Not required",
};

const field_meta hf_horizontal_derivation_parameter = {
    "Horizontal derivation parameter (HDP)",
    "nas.nr.mm.hdp",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_required_not_required,
    nullptr,
    0x01,
};

const field_meta hf_emm_eea5 = {
    "EEA5",
    "nas.emm.eea5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x04,
};
const field_meta hf_emm_eea6 = {
    "EEA6",
    "nas.emm.eea6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x02,
};
const field_meta hf_emm_eea7 = {
    "EEA7",
    "nas.emm.eea7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x01,
};

const field_meta hf_emm_eia0 = {
    "EIA0",
    "nas.emm.eia0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x80,
};
const field_meta hf_emm_128eia1 = {
    "128-EIA1",
    "nas.emm.128eia1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x40,
};
const field_meta hf_emm_128eia2 = {
    "128-EIA2",
    "nas.emm.128eia2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x20,
};
const field_meta hf_emm_eia3 = {
    "128-EIA3",
    "nas.emm.eia3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x10,
};
const field_meta hf_emm_eia4 = {
    "EIA4",
    "nas.emm.eia4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x08,
};
const field_meta hf_emm_eia5 = {
    "EIA5",
    "nas.emm.eia5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x04,
};
const field_meta hf_emm_eia6 = {
    "EIA6",
    "nas.emm.eia6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x02,
};
const field_meta hf_emm_eia7 = {
    "EIA7",
    "nas.emm.eia7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x01,
};

const field_meta hf_emm_uea0 = {
    "UEA0",
    "nas.emm.uea0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x80,
};
const field_meta hf_emm_uea1 = {
    "UEA1",
    "nas.emm.uea1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x40,
};
const field_meta hf_emm_uea2 = {
    "UEA2",
    "nas.emm.uea2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x20,
};
const field_meta hf_emm_uea3 = {
    "UEA3",
    "nas.emm.uea3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x10,
};
const field_meta hf_emm_uea4 = {
    "UEA4",
    "nas.emm.uea4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x08,
};
const field_meta hf_emm_uea5 = {
    "UEA5",
    "nas.emm.uea5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x04,
};
const field_meta hf_emm_uea6 = {
    "UEA6",
    "nas.emm.uea6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x02,
};
const field_meta hf_emm_uea7 = {
    "UEA7",
    "nas.emm.uea7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x01,
};

const field_meta hf_emm_uia1 = {
    "UMTS integrity algorithm UIA1",
    "nas.emm.uia1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x40,
};
const field_meta hf_emm_uia2 = {
    "UMTS integrity algorithm UIA2",
    "nas.emm.uia2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x20,
};
const field_meta hf_emm_uia3 = {
    "UMTS integrity algorithm UIA3",
    "nas.emm.uia3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x10,
};
const field_meta hf_emm_uia4 = {
    "UMTS integrity algorithm UIA4",
    "nas.emm.uia4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x08,
};
const field_meta hf_emm_uia5 = {
    "UMTS integrity algorithm UIA5",
    "nas.emm.uia5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x04,
};
const field_meta hf_emm_uia6 = {
    "UMTS integrity algorithm UIA6",
    "nas.emm.uia6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x02,
};
const field_meta hf_emm_uia7 = {
    "UMTS integrity algorithm UIA7",
    "nas.emm.uia7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x01,
};

const field_meta hf_emm_gea1 = {
    "GPRS encryption algorithm GEA1",
    "nas.emm.gea1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x40,
};
const field_meta hf_emm_gea2 = {
    "GPRS encryption algorithm GEA2",
    "nas.emm.gea2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x20,
};
const field_meta hf_emm_gea3 = {
    "GPRS encryption algorithm GEA3",
    "nas.emm.gea3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x10,
};
const field_meta hf_emm_gea4 = {
    "GPRS encryption algorithm GEA4",
    "nas.emm.gea4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x08,
};
const field_meta hf_emm_gea5 = {
    "GPRS encryption algorithm GEA5",
    "nas.emm.gea5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x04,
};
const field_meta hf_emm_gea6 = {
    "GPRS encryption algorithm GEA6",
    "nas.emm.gea6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x02,
};
const field_meta hf_emm_gea7 = {
    "GPRS encryption algorithm GEA7",
    "nas.emm.gea7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x01,
};

} // namespace mm
