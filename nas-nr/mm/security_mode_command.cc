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
    dissect_v( &selected_security_algo, d, ctx);
    d.step(1);

    /*ngKSI     NAS key set identifier 9.11.3.32    M    V    1/2  */
    dissect_v( &nas_ksi, d, ctx);

    /* Spare half octet    Spare half octet     9.5    M    V    1/2 */
    d.step(1);

    /* Replayed UE security capabilities    UE security capability   9.11.3.54  M  LV
     * 3-5*/
    // ELEM_MAND_LV(,DE_NAS_5GS_MM_UE_SEC_CAP," - Replayed UE security capabilities",);
    auto consumed = dissect_lv( &replayed_ue_security_capability, d, ctx);
    d.step(consumed);

    /*E-    IMEISV request    IMEISV request     9.11.3.28    O    TV    1*/
    consumed = dissect_opt_tv_short( &imeisv_request, d, ctx);
    d.step(consumed);

    /*57 Selected EPS NAS security algorithms EPS NAS security algorithms 9.11.3.25  O TV
     * 2 */
    // ELEM_OPT_TV(0x57, , DE_EMM_NAS_SEC_ALGS, " - Selected EPS NAS security
    // algorithms");
    consumed = dissect_opt_tv( &selected_eps_security_algo, d, ctx);
    d.step(consumed);

    /*36    Additional 5G security information  9.11.3.12    O    TLV    3 */
    // ELEM_OPT_TLV(0x36, , DE_NAS_5GS_MM_ADD_5G_SEC_INF, NULL);
    consumed = dissect_opt_tlv( &additional_security_info, d, ctx);
    d.step(consumed);

    /*78    EAP message  9.11.2.2    O    TLV-E    7*/
    consumed = dissect_opt_tlv_e( &cmn::eap_message, d, ctx);
    d.step(consumed);

    /*38  ABBA 9.11.3.10    O    TLV    4-n */
    // ELEM_OPT_TLV(0x38, , DE_NAS_5GS_MM_ABBA, NULL);
    consumed = dissect_opt_tlv( &abba, d, ctx);
    d.step(consumed);

    /*19 Replayed S1 UE security capabilities    S1 UE security capability 9.11.3.48A
     * O    TLV    4-7 */
    // ELEM_OPT_TLV(0x19, DE_EMM_UE_SEC_CAP, " - Replayed S1 UE security capabilities");
    consumed = dissect_opt_tlv( &replayed_s1_ue_security_capability, d, ctx);
    d.step(consumed);

    return uc.length;
}

namespace mm {
extern const element_meta selected_security_algo = {
    0xff,
    "Selected NAS security algorithms",
    dissect_security_algo,
};
extern const element_meta replayed_ue_security_capability = {
    0xff,
    "UE security capability - Replayed UE security capabilities",
    dissect_replayed_ue_security_capability,
};
extern const element_meta imeisv_request = {
    0xE0,
    "IMEISV request",
    dissect_imeisv_request,
};

extern const element_meta additional_security_info = {
    0x36,
    "Additional 5G security information",
    dissect_additional_security_info,
};

extern const element_meta replayed_s1_ue_security_capability = {
    0x19,
    "S1 UE security capability - Replayed S1 UE security capabilities",
    dissect_reported_s1_ue_security_capability,
};

const tag_field hf_security_ciphering_algo = {
    "Type of ciphering algorithm",
    0xf0,
    (const v_string[]){
        {0x0, "5G-EA0 (null ciphering algorithm)"},
        {0x1, "128-5G-EA1"},
        {0x2, "128-5G-EA2"},
        {0x3, "128-5G-EA3"},
        {0x4, "5G-EA4"},
        {0x5, "5G-EA5"},
        {0x6, "5G-EA6"},
        {0x7, "5G-EA7"},
        {0, nullptr},
    },
};

static const char* s = tfs_supported_not_supported.true_string;
static const char* ns = tfs_supported_not_supported.false_string;

const bool_field hf_mm_128_5g_ea1 = {
    "128-5G-EA1",
    0x40,ns,s
};
const bool_field hf_mm_128_5g_ea2 = {
    "128-5G-EA2",
    0x20,ns,s
};
const bool_field hf_mm_128_5g_ea3 = {
    "128-5G-EA3",
    0x10,ns,s
};
const bool_field hf_mm_5g_ea4 = {
    "5G-EA4",
    0x08,ns,s
};
const bool_field hf_mm_5g_ea5 = {
    "5G-EA5",
    0x04,ns,s
};
const bool_field hf_mm_5g_ea6 = {
    "5G-EA6",
    0x02,ns,s
};
const bool_field hf_mm_5g_ea7 = {
    "5G-EA7",
    0x01,ns,s
};

const bool_field hf_mm_5g_ia0 = {
    "5G-IA0",
    0x80,ns,s
};
const bool_field hf_mm_128_5g_ia1 = {
    "128-5G-IA1",
    0x40,ns,s
};
const bool_field hf_mm_128_5g_ia2 = {
    "128-5G-IA2",
    0x20,ns,s
};
const bool_field hf_mm_128_5g_ia3 = {
    "128-5G-IA3",
    0x10,ns,s
};
const bool_field hf_mm_5g_ia4 = {
    "5G-IA4",
    0x08,ns,s
};
const bool_field hf_mm_5g_ia5 = {
    "5G-IA5",
    0x04,ns,s
};
const bool_field hf_mm_5g_ia6 = {
    "5G-IA6",
    0x02,ns,s
};
const bool_field hf_mm_5g_ia7 = {
    "5G-IA7",
    0x01,ns,s
};

const bool_field hf_mm_eea0 = {
    "EEA0",
    0x80,ns,s
};
const bool_field hf_mm_128eea1 = {
    "128-EEA1",
    0x40,ns,s
};
const bool_field hf_mm_128eea2 = {
    "128-EEA2",
    0x20,ns,s
};
const bool_field hf_mm_eea3 = {
    "128-EEA3",
    0x10,ns,s
};
const bool_field hf_mm_eea4 = {
    "EEA4",
    0x08,ns,s
};
const bool_field hf_mm_eea5 = {
    "EEA5",
    0x04,ns,s
};
const bool_field hf_mm_eea6 = {
    "EEA6",
    0x02,ns,s
};
const bool_field hf_mm_eea7 = {
    "EEA7",
    0x01,ns,s
};

const bool_field hf_mm_eia0 = {
    "EIA0",
    0x80,ns,s
};
const bool_field hf_mm_128eia1 = {
    "128-EIA1",
    0x40,ns,s
};
const bool_field hf_mm_128eia2 = {
    "128-EIA2",
    0x20,ns,s
};
const bool_field hf_mm_eia3 = {
    "128-EIA3",
    0x10,ns,s
};
const bool_field hf_mm_eia4 = {
    "EIA4",
    0x08,ns,s
};
const bool_field hf_mm_eia5 = {
    "EIA5",
    0x04,ns,s
};
const bool_field hf_mm_eia6 = {
    "EIA6",
    0x02,ns,s
};
const bool_field hf_mm_eia7 = {
    "EIA7",
    0x01,ns,s
};

const bool_field hf_retransmission_of_initial_nas_request = {
    "Retransmission of initial NAS message request(RINMR)",
    0x02,
    "Not Requested",
    "Requested",
};

const bool_field hf_horizontal_derivation_parameter = {
    "Horizontal derivation parameter (HDP)",
    0x01,
    "Not required",
    "Required",
    };

const bool_field hf_emm_eea5 = {
    "EEA5",
    0x04,ns,s
};
const bool_field hf_emm_eea6 = {
    "EEA6",
    0x02,ns,s
};
const bool_field hf_emm_eea7 = {
    "EEA7",
    0x01,ns,s
};

const bool_field hf_emm_eia0 = {
    "EIA0",
    0x80,ns,s
};
const bool_field hf_emm_128eia1 = {
    "128-EIA1",
    0x40,ns,s
};
const bool_field hf_emm_128eia2 = {
    "128-EIA2",
    0x20,ns,s
};
const bool_field hf_emm_eia3 = {
    "128-EIA3",
    0x10,ns,s
};
const bool_field hf_emm_eia4 = {
    "EIA4",
    0x08,ns,s
};
const bool_field hf_emm_eia5 = {
    "EIA5",
    0x04,ns,s
};
const bool_field hf_emm_eia6 = {
    "EIA6",
    0x02,ns,s
};
const bool_field hf_emm_eia7 = {
    "EIA7",
    0x01,ns,s
};

const bool_field hf_emm_uea0 = {
    "UEA0",
    0x80,ns,s
};
const bool_field hf_emm_uea1 = {
    "UEA1",
    0x40,ns,s
};
const bool_field hf_emm_uea2 = {
    "UEA2",
    0x20,ns,s
};
const bool_field hf_emm_uea3 = {
    "UEA3",
    0x10,ns,s
};
const bool_field hf_emm_uea4 = {
    "UEA4",
    0x08,ns,s
};
const bool_field hf_emm_uea5 = {
    "UEA5",
    0x04,ns,s
};
const bool_field hf_emm_uea6 = {
    "UEA6",
    0x02,ns,s
};
const bool_field hf_emm_uea7 = {
    "UEA7",
    0x01,ns,s
};

const bool_field hf_emm_uia1 = {
    "UMTS integrity algorithm UIA1",
    0x40,ns,s
};
const bool_field hf_emm_uia2 = {
    "UMTS integrity algorithm UIA2",
    0x20,ns,s
};
const bool_field hf_emm_uia3 = {
    "UMTS integrity algorithm UIA3",
    0x10,ns,s
};
const bool_field hf_emm_uia4 = {
    "UMTS integrity algorithm UIA4",
    0x08,ns,s
};
const bool_field hf_emm_uia5 = {
    "UMTS integrity algorithm UIA5",
    0x04,ns,s
};
const bool_field hf_emm_uia6 = {
    "UMTS integrity algorithm UIA6",
    0x02,ns,s
};
const bool_field hf_emm_uia7 = {
    "UMTS integrity algorithm UIA7",
    0x01,ns,s
};

const bool_field hf_emm_gea1 = {
    "GPRS encryption algorithm GEA1",
    0x40,ns,s
};
const bool_field hf_emm_gea2 = {
    "GPRS encryption algorithm GEA2",
    0x20,ns,s
};
const bool_field hf_emm_gea3 = {
    "GPRS encryption algorithm GEA3",
    0x10,ns,s
};
const bool_field hf_emm_gea4 = {
    "GPRS encryption algorithm GEA4",
    0x08,ns,s
};
const bool_field hf_emm_gea5 = {
    "GPRS encryption algorithm GEA5",
    0x04,ns,s
};
const bool_field hf_emm_gea6 = {
    "GPRS encryption algorithm GEA6",
    0x02,    ns,s

};
const bool_field hf_emm_gea7 = {
    "GPRS encryption algorithm GEA7",
    0x01,
    ns,s
};

} // namespace mm
