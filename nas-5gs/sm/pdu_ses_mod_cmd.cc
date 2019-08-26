#include "../dissect_nas_5gs.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"

namespace sm_pdu_ses_mod {
extern const element_meta authorized_qos_flow_des;
}

/*
 * 8.3.9 PDU session modification command
 */
int sm::pdu_ses_mod_cmd(dissector d, context* ctx) {
    use_context uc(ctx, "pdu-session-modification-command");

    using namespace sm_pdu_ses_mod;
    /* Direction: network to UE */
    d.pinfo->dir = pi_dir::dl;

    /*59    5GSM cause    5GSM cause 9.11.4.2    O    TV    2*/
    // ELEM_OPT_TV(0x59, NAS_5GS_PDU_TYPE_SM, DE_NAS_5GS_SM_5GSM_CAUSE, NULL);
    auto consumed = dissect_opt_elem_tv(nullptr, &sm_cause, d, ctx);
    d.step(consumed);

    /*2A    Session AMBR    Session-AMBR     9.11.4.14    O    TLV    8*/
    // ELEM_OPT_TLV(0x2A, NAS_5GS_PDU_TYPE_SM, DE_NAS_5GS_SM_SESSION_AMBR, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &ses_ambr, d, ctx);
    d.step(consumed);

    /*56    RQ timer value    GPRS timer     9.11.4.3    O    TV    2*/
    // ELEM_OPT_TV(0x56, GSM_A_PDU_TYPE_GM, DE_GPRS_TIMER, " - PDU session release time");
    consumed = dissect_opt_elem_tv(nullptr, &rq_gprs_timer, d, ctx);
    d.step(consumed);

    /* 8-   Always-on PDU session indication    Always-on PDU session indication 9.11.4.3
     * O    TV    1 */
    // ELEM_OPT_TV_SHORT(  0x80, , DE_NAS_5GS_SM_ALWAYS_ON_PDU_SES_IND, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &always_on_pdu_ses_ind, d, ctx);
    d.step(consumed);

    /*7A    Authorized QoS rules    QoS rules     9.11.4.6    O    TLV-E    3-65538*/
    // ELEM_OPT_TLV_E(  0x7A, , DE_NAS_5GS_SM_QOS_RULES, " - Authorized QoS rules");
    consumed = dissect_opt_elem_tlv_e(nullptr, &authorized_qos_rules, d, ctx);
    d.step(consumed);

    /*75    Mapped EPS bearer contexts     Mapped EPS  bearer contexts     9.11.4.5    O
     * TLV-E    7-65538*/
    // ELEM_OPT_TLV_E(0x75, NAS_5GS_PDU_TYPE_SM, DE_NAS_5GS_SM_MAPPED_EPS_B_CONT, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &mapped_eps_b_cont, d, ctx);
    d.step(consumed);

    /*79    Authorized QoS flow descriptions     QoS flow descriptions     9.11.4.12    O
     * TLV-E    6-65538*/
    // ELEM_OPT_TLV_E(  0x79, , DE_NAS_5GS_SM_QOS_FLOW_DES, " - Authorized");
    consumed = dissect_opt_elem_tlv_e(nullptr, &authorized_qos_flow_des, d, ctx);
    d.step(consumed);

    /*7B    Extended protocol configuration options    Extended protocol configuration
     * options     9.11.4.2    O    TLV-E    4-65538*/
    // ELEM_OPT_TLV_E(0x7B, NAS_PDU_TYPE_ESM, DE_ESM_EXT_PCO, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);

    // extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    d.extraneous_data_check(0);

    return d.tvb->reported_length;
}
namespace sm_pdu_ses_mod {
int dissect_authorized_qos_flow_des(dissector d, context* ctx);

extern const element_meta authorized_qos_flow_des = {
    0x79,
    "Authorized QoS flow descriptions",
    dissect_authorized_qos_flow_des,
};
int dissect_always_on_pdu_ses_req(dissector d, context* ctx) { return 0; }
int dissect_int_prot_max_data_rate(dissector d, context* ctx) { return 0; }
int dissect_requested_qos_rules(dissector d, context* ctx) { return 0; }
int dissect_authorized_qos_flow_des(dissector d, context* ctx) { return 0; }
} // namespace sm_pdu_ses_mod
