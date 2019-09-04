#include "../dissect_nas5g.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"
#include "pdu_ses.hh"

namespace sm_pdu_ses_mod {
// extern const element_meta always_on_pdu_ses_req;
extern const element_meta int_prot_max_data_rate;
extern const element_meta requested_qos_rules;
extern const element_meta authorized_qos_flow_des; // Requested QoS flow descriptions QoS
                                                   // flow descriptions 9.11.4.12
} // namespace sm_pdu_ses_mod

using namespace nas;
using namespace sm;
using namespace pdu_ses;

/* 8.3.7 PDU session modification request */
int sm::pdu_ses_mod_req(dissector d, context* ctx) {
    auto        len = d.length;
    use_context uc(ctx, "pdu-session-modification-request", d);

    using namespace sm_pdu_ses_mod;

    /* Direction: UE to network */
    d.pinfo->dir = pi_dir::ul;

    /* 28 5GSM capability 9.11.4.1    O    TLV    3-15 */
    // ELEM_OPT_TLV(0x28, , DE_NAS_5GS_SM_5GSM_CAP, NULL);
    auto consumed = dissect_opt_elem_tlv(nullptr, &sm_cap, d, ctx);
    d.step(consumed);

    /* 59 5GSM cause 9.11.4.2    O    TV    2 */
    // ELEM_OPT_TLV(0x59, , DE_NAS_5GS_SM_5GSM_CAUSE, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &sm_cause, d, ctx);
    d.step(consumed);

    /*55    Maximum number of suuported packet filter 9.11.4.9    O    TV    3*/
    // ELEM_OPT_TV(0x55, , DE_NAS_5GS_SM_MAX_NUM_SUP_PKT_FLT, NULL);
    consumed = dissect_opt_elem_tv(nullptr, &max_num_sup_kpt_flt, d, ctx);
    d.step(consumed);

    /* B-    Always-on PDU session requested  9.11.4.4 O    TV    1 */
    // ELEM_OPT_TV_SHORT(0xB0, , DE_NAS_5GS_SM_ALWAYS_ON_PDU_SES_REQ, );
    consumed = dissect_opt_elem_tv_short(nullptr, &always_on_pdu_ses_req, d, ctx);
    d.step(consumed);

    /* 13    Integrity protection maximum data rate   9.11.4.7    O    TV    3 */
    // ELEM_OPT_TV(0x13, , DE_NAS_5GS_SM_INT_PROT_MAX_DATA_RTE, NULL);
    consumed = dissect_opt_elem_tv(nullptr, &int_prot_max_data_rate, d, ctx);
    d.step(consumed);

    /*7A    Requested QoS rules    QoS rules 9.11.4.13    O    TLV-E    3-65538 */
    // ELEM_OPT_TLV_E(0x7A, , DE_NAS_5GS_SM_QOS_RULES, " - Requested QoS rules");
    consumed = dissect_opt_elem_tlv_e(nullptr, &requested_qos_rules, d, ctx);
    d.step(consumed);

    /* 79    Requested QoS flow descriptions    QoS flow descriptions 9.11.4.12    O
     * TLV-E    5-65538 */
    // ELEM_OPT_TLV_E(  0x79, , DE_NAS_5GS_SM_QOS_FLOW_DES, " - Authorized");
    consumed = dissect_opt_elem_tlv_e(nullptr, &authorized_qos_flow_des, d, ctx);
    d.step(consumed);

    /* 75  Mapped EPS bearer contexts 9.11.4.8    O TLV-E    7-65538 */
    // ELEM_OPT_TLV_E(0x75, , DE_NAS_5GS_SM_MAPPED_EPS_B_CONT, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &mapped_eps_b_cont, d, ctx);
    d.step(consumed);

    /* 7B Extended protocol configuration options  9.11.4.6 O TLV-E    4-65538*/
    // ELEM_OPT_TLV_E(0x7B, , DE_ESM_EXT_PCO, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);

    return len;
}

namespace sm_pdu_ses_mod {
int dissect_requested_qos_rules(dissector d, context* ctx);

// Integrity protection maximum data rate   9.11.4.7
extern const element_meta int_prot_max_data_rate = {
    0x13,
    "Integrity protection maximum data rate",
    dissect_int_prot_max_data_rate,
    nullptr,

};

extern const element_meta requested_qos_rules = {
    0x7A,
    "Requested QoS rules",
    dissect_requested_qos_rules,
    nullptr,

};

} // namespace sm_pdu_ses_mod
