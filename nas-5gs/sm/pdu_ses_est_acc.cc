#include "../dissect_nas5g.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"
#include "../common/common.hh"

namespace sm {
extern const field_meta* hf_sel_sc_mode;

extern const element_meta pdu_ses_type;
extern const element_meta pdu_address;
} // namespace sm_pdu_ses_est

using namespace cmn;
using namespace nas;
using namespace sm;

/* 8.3.2 PDU session establishment accept */
int sm::pdu_ses_est_acc(dissector d, context* ctx) {
    use_context uc(ctx, "pdu-session-establishment-accept", d);
    auto        len = d.length;

    /* Direction: network to UE */
    down_link(d.pinfo);

    /* Selected PDU session type    PDU session type 9.11.4.11    M    V    1/2 H0*/
    // ELEM_MAND_V( DE_NAS_5GS_SM_PDU_SESSION_TYPE,);
    dissect_elem_v(nullptr, &pdu_ses_type, d, ctx);

    /* Selected SSC mode    SSC mode 9.11.4.16    M    V    1/2 H1*/
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_sel_sc_mode, enc::be);
    d.step(1);

    /* Authorized QoS rules QoS rules 9.11.4.13 M LV-E 2-65537  DE_NAS_5GS_SM_QOS_RULES*/
    // ELEM_MAND_LV_E(,DE_NAS_5GS_SM_QOS_RULES, " - Authorized QoS rules",);
    auto consumed = dissect_elem_lv_e(nullptr, &authorized_qos_rules, d, ctx);
    d.step(consumed);

    /* Session-AMBR 9.11.4.14    M    LV    7 */
    // ELEM_MAND_LV(, DE_NAS_5GS_SM_SESSION_AMBR);
    consumed = dissect_elem_lv(nullptr, &ses_ambr, d, ctx);
    d.step(consumed);

    /*59 5GSM cause 9.11.4.2    O    TV    2*/
    // ELEM_OPT_TV(0x59, , DE_NAS_5GS_SM_5GSM_CAUSE, NULL);
    consumed = dissect_opt_elem_tv(nullptr, &sm_cause, d, ctx);
    d.step(consumed);

    /*29  PDU address 9.11.4.10    O    TLV    7 */
    // ELEM_OPT_TLV(0x29, , DE_NAS_5GS_SM_PDU_ADDRESS, );
    consumed = dissect_opt_elem_tlv(nullptr, &pdu_address, d, ctx);
    d.step(consumed);

    /*56    RQ timer value    GPRS timer 9.11.2.3    O    TV    2*/
    // ELEM_OPT_TV(0x56, , DE_GPRS_TIMER, " - RQ timer value");
    consumed = dissect_opt_elem_tv(nullptr, &rq_gprs_timer, d, ctx);
    d.step(consumed);

    /* 22 S-NSSAI 9.11.2.8    O    TLV    3-6*/
    // ELEM_OPT_TLV(0x22, , DE_NAS_5GS_CMN_S_NSSAI, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &s_nssai, d, ctx);
    d.step(consumed);

    /* 8-    Always-on PDU session indication   9.11.4.3  O    TV    1 */
    // ELEM_OPT_TV_SHORT(w 0x80, , DE_NAS_5GS_SM_ALWAYS_ON_PDU_SES_IND, );
    consumed = dissect_opt_elem_tv_short(nullptr, &always_on_pdu_ses_ind, d, ctx);
    d.step(consumed);

    /* 75    Mapped EPS bearer contexts  9.11.4.8    O  TLV-E    7-65538 */
    // ELEM_OPT_TLV_E(0x75, , DE_NAS_5GS_SM_MAPPED_EPS_B_CONT, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &mapped_eps_b_cont, d, ctx);
    d.step(consumed);

    /*78    EAP message    EAP message 9.11.2.2    O    TLV-E    7-1503*/
    // ELEM_OPT_TLV_E(0x78, , DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eap_msg, d, ctx);
    d.step(consumed);

    /*79 Authorized QoS flow descriptions    QoS flow descriptions 9.11.4.12    O
     * TLV-E    6-65538 */
    // ELEM_OPT_TLV_E( 0x79, , DE_NAS_5GS_SM_QOS_FLOW_DES, " - Authorized");
    consumed = dissect_opt_elem_tlv_e(nullptr, &authorized_qos_rules, d, ctx);
    d.step(consumed);

    /*7B  Extended protocol configuration options 9.11.4.6    O    TLV-E    4-65538*/
    // ELEM_OPT_TLV_E(0x7B, , DE_ESM_EXT_PCO, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);

    /* 25 DNN 9.11.2.1A    O    TLV    3-102 */
    // ELEM_OPT_TLV(0x25, , DE_NAS_5GS_CMN_DNN, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &dnn, d, ctx);
    d.step(consumed);

    /*xx	5GSM network feature support 9.11.4.18	O	TLV	3-15
    xx	Session-TMBR	Session-TMBR 9.11.4.19	O	TLV	8
    TBD	Serving PLMN rate control 9.11.4.20	O	TLV	4
    XX	ATSSS container 9.11.4.22	O	TLV-E	3-65538
    XX	Control plane only indication 9.11.4.23	O	TV	1
    */
   // no data length check

    return len;
}

namespace sm_pdu_ses_est {





} // namespace sm_pdu_ses_est
