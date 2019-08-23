#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_sec_mode_cmd{
extern const element_meta sec_algo;
extern const element_meta replayed_ue_sec_cap;
extern const element_meta imeisv_req;
extern const element_meta selected_eps_sec_algo;
extern const element_meta a_sec_info;
extern const element_meta abba;
extern const element_meta reported_s1_ue_sec_cap;
}
/*
 * 8.2.25 Security mode command
 */
int mm::sec_mode_cmd(dissector d, context* ctx) {
    using namespace mm_sec_mode_cmd;
    /* Direction: network to UE */
    d.pinfo->dir = pi_dir::dl;

    /*Selected NAS security algorithms    NAS security algorithms     9.11.3.34    M    V
     * 1  */
    // ELEM_MAND_V(,DE_NAS_5GS_MM_NAS_SEC_ALGO, );
    auto consumed = dissect_elem_v(nullptr, &sec_algo, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*ngKSI     NAS key set identifier 9.11.3.32    M    V    1/2  */
    /* Spare half octet    Spare half octet     9.5    M    V    1/2 */

    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_spare_half_octet, enc::be);

    // ELEM_MAND_V(DE_NAS_5GS_MM_NAS_KEY_SET_ID, " - ngKSI", );
    consumed = dissect_elem_v(nullptr, &nksi, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*Replayed UE security capabilities    UE security capability     9.11.3.54    M    LV
     * 3-5*/
    // ELEM_MAND_LV(,DE_NAS_5GS_MM_UE_SEC_CAP," - Replayed UE security capabilities",);
    consumed = dissect_elem_v(nullptr, &replayed_ue_sec_cap, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*E-    IMEISV request    IMEISV request     9.11.3.28    O    TV    1*/
    // ELEM_OPT_TV_SHORT(0xE0, NAS_PDU_TYPE_EMM, DE_EMM_IMEISV_REQ, NULL);
    consumed = dissect_elem_tv_short(nullptr, &imeisv_req, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*57    Selected EPS NAS security algorithms    EPS NAS security algorithms 9.11.3.25
     * O    TV    2 */
    // ELEM_OPT_TV(0x57, , DE_EMM_NAS_SEC_ALGS, " - Selected EPS NAS security algorithms");
    consumed = dissect_opt_elem_tv(nullptr, &selected_eps_sec_algo, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*36    Additional 5G security information    Additional 5G security
     * information 9.11.3.12    O    TLV    3 */
    // ELEM_OPT_TLV(0x36, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_ADD_5G_SEC_INF, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &a_sec_info, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*78    EAP message    EAP message     9.10.2.2    O    TLV-E    7*/
    // ELEM_OPT_TLV_E(0x78, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eap_msg, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*38    ABBA    ABBA 9.11.3.10    O    TLV    4-n */
    // ELEM_OPT_TLV(0x38, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_ABBA, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &abba, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*19    Replayed S1 UE security capabilities    S1 UE security capability 9.11.3.48A
     * O    TLV    4-7 */
    // ELEM_OPT_TLV(0x19, DE_EMM_UE_SEC_CAP, " - Replayed S1 UE security capabilities");
    consumed = dissect_opt_elem_tlv(nullptr, &reported_s1_ue_sec_cap, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    return d.tvb->reported_length;
}

namespace mm_sec_mode_cmd {
int dissect_sec_algo(dissector d, context* ctx);
int dissect_replayed_ue_sec_cap(dissector d, context* ctx);
int dissect_imeisv_req(dissector d, context* ctx);
int dissect_selected_eps_sec_algo(dissector d, context* ctx);
int dissect_a_sec_info(dissector d, context* ctx);
int dissect_abba(dissector d, context* ctx);
int dissect_reported_s1_ue_sec_cap(dissector d, context* ctx);

extern const element_meta sec_algo = {
    0xff,
    "Selected NAS security algorithms",
    dissect_sec_algo,
};
extern const element_meta replayed_ue_sec_cap = {
    0xff,
    "Replayed UE security capabilities",
    dissect_replayed_ue_sec_cap,
};
extern const element_meta imeisv_req = {
    0xE0,
    "IMEISV request",
    dissect_imeisv_req,
};
extern const element_meta selected_eps_sec_algo = {
    0x57,
    "Selected EPS NAS security algorithms",
    dissect_selected_eps_sec_algo,
};
extern const element_meta a_sec_info            = {
    0x36,
    "Additional 5G security information",
    dissect_a_sec_info,
};
extern const element_meta abba                  = {
    0x38,
    "ABBA",
    dissect_abba,
};
extern const element_meta reported_s1_ue_sec_cap = {
    0x19,
    "Replayed S1 UE security capabilities",
    dissect_reported_s1_ue_sec_cap,
};
}
