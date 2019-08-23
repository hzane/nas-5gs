#include "../dissect_nas_5gs.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"

namespace sm_pdu_ses_est{
extern const field_meta* hf_sel_sc_mode;

extern const element_meta pdu_ses_type;
extern const element_meta pdu_address;
extern const element_meta s_nssai;
extern const element_meta dnn;
}
/*
 * 8.3.2 PDU session establishment accept
 */
int sm::pdu_ses_est_acc(dissector d, context* ctx) {
    use_context uc(ctx, "pdu-session-establishment-accept");

    using namespace sm_pdu_ses_est;
    /* Direction: network to UE */
    d.pinfo->dir = pi_dir::dl;

    // proto_tree_add_item(tree, hf_nas_5gs_sm_sel_sc_mode, tvb, offset, 1,
    // ENC_BIG_ENDIAN);
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_sel_sc_mode, enc::be);
    /*Selected PDU session type    PDU session type 9.11.4.5    M    V    1/2 H0*/
    // ELEM_MAND_V( DE_NAS_5GS_SM_PDU_SESSION_TYPE,);
    auto consumed = dissect_elem_v(nullptr, &pdu_ses_type, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*Selected SSC mode    SSC mode 9.11.4.9    M    V    1/2 H1*/

    /*Authorized QoS rules    QoS rules 9.11.4.6    M    LV-E    2-65537
     * DE_NAS_5GS_SM_QOS_RULES*/
    // ELEM_MAND_LV_E(NAS_5GS_PDU_TYPE_SM,DE_NAS_5GS_SM_QOS_RULES, " - Authorized QoS rules",);
    consumed = dissect_elem_lv_e(nullptr, &authorized_qos_rules, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*Session AMBR    Session-AMBR 9.11.4.14    M    LV    7 */
    // ELEM_MAND_LV(NAS_5GS_PDU_TYPE_SM, DE_NAS_5GS_SM_SESSION_AMBR);
    consumed = dissect_elem_lv(nullptr, &ses_ambr, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*59    5GSM cause    5GSM cause 9.11.4.2    O    TV    2*/
    // ELEM_OPT_TV(0x59, NAS_5GS_PDU_TYPE_SM, DE_NAS_5GS_SM_5GSM_CAUSE, NULL);
    consumed = dissect_opt_elem_tv(nullptr, &sm_cause, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*29    PDU address    PDU address 9.11.4.4    O    TLV    7 */
    // ELEM_OPT_TLV(0x29, NAS_5GS_PDU_TYPE_SM, DE_NAS_5GS_SM_PDU_ADDRESS, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &pdu_address, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*56    RQ timer value    GPRS timer 9.10.2.3    O    TV    2*/
    // ELEM_OPT_TV(0x56, GSM_A_PDU_TYPE_GM, DE_GPRS_TIMER, " - RQ timer value");
    consumed = dissect_opt_elem_tv(nullptr, &rq_gprs_timer, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*22    S-NSSAI    S-NSSAI 9.11.3.37    O    TLV    3-6*/
    // ELEM_OPT_TLV(0x22, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_S_NSSAI, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &s_nssai, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /* 8-    Always-on PDU session indication    Always-on PDU session indication 9.11.4.3
     * O    TV    1 */
    // ELEM_OPT_TV_SHORT(w 0x80, , DE_NAS_5GS_SM_ALWAYS_ON_PDU_SES_IND, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &always_on_pdu_ses_ind, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /* 75    Mapped EPS bearer contexts    Mapped EPS bearer contexts 9.11.4.9    O
     * TLV-E    7-65538 */
    // ELEM_OPT_TLV_E(0x75, NAS_5GS_PDU_TYPE_SM, DE_NAS_5GS_SM_MAPPED_EPS_B_CONT, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &mapped_eps_b_cont, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*78    EAP message    EAP message 9.11.3.14    O    TLV-E    7-1503*/
    // ELEM_OPT_TLV_E(0x78, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eap_msg, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*79    Authorized QoS flow descriptions    QoS flow descriptions 9.11.4.12    O
     * TLV-E    6-65538 */
    // ELEM_OPT_TLV_E( 0x79, , DE_NAS_5GS_SM_QOS_FLOW_DES, " - Authorized");
    consumed = dissect_opt_elem_tlv_e(nullptr, &authorized_qos_rules, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*7B    Extended protocol configuration options    Extended protocol configuration
     * options 9.11.4.2    O    TLV-E    4-65538*/
    // ELEM_OPT_TLV_E(0x7B, NAS_PDU_TYPE_ESM, DE_ESM_EXT_PCO, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /* 25    DNN    DNN 9.11.2.1A    O    TLV    3-102 */
    // ELEM_OPT_TLV(0x25, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_DNN, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &dnn, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);

    return d.tvb->reported_length;
}

namespace sm_pdu_ses_est {
/*
 *      9.11.4.16    SSC mode
 */
static const val_string nas_5gs_sc_mode_values[] = {
    {0x1, "SSC mode 1"},
    {0x2, "SSC mode 2"},
    {0x3, "SSC mode 3"},
    {0, nullptr},
};
extern const field_meta hfm_sel_sc_mode = {
    "Selected SSC mode",
    "nas_5gs.sm.sel_sc_mode",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_sc_mode_values,
    nullptr,
    nullptr,
    0xf0,
};
const field_meta* hf_sel_sc_mode = &hfm_sel_sc_mode;

int dissect_pdu_ses_type(dissector d, context* ctx);
int dissect_pdu_address(dissector d, context* ctx);
int dissect_s_nssai(dissector d, context* ctx);
int dissect_dnn(dissector d, context* ctx);

extern const element_meta pdu_ses_type = {
    0xff,
    "Selected PDU session type",
    dissect_pdu_ses_type,
};
extern const element_meta pdu_address = {
    0x29,
    "PDU address",
    dissect_pdu_address,
};
extern const element_meta s_nssai = {
    0x22,
    "S-NSSAI",
    dissect_s_nssai,
};
extern const element_meta dnn = {
    0x25,
    "DNN",
    dissect_dnn,
};
} // namespace sm_pdu_ses_est_acc
