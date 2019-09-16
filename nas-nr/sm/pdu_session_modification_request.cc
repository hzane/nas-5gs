#include "../dissect_sm_msg.hh"
#include "../ber.hh"
#include "../packet_info.hh"

using namespace nas;
using namespace sm;

/* 8.3.7 PDU session modification request */
int sm::dissect_pdu_ses_modification_request(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-modification-request", d, 0);

    /* Direction: UE to network */
    up_link(d.pinfo);    

    /* 28 5GSM capability 9.11.4.1    O    TLV    3-15 */
    auto consumed = dissect_opt_tlv(nullptr, &sm_capability, d, ctx);
    d.step(consumed);

    /* 59 5GSM cause 9.11.4.2    O    TV    2 */
    consumed = dissect_opt_tv(nullptr, &sm_cause, d, ctx);
    d.step(consumed);

    /*55    Maximum number of supported packet filter 9.11.4.9    O    TV    3*/
    consumed = dissect_opt_tv(nullptr, &max_of_supported_pkt_filter, d, ctx);
    d.step(consumed);

    /* B-    Always-on PDU session requested  9.11.4.4 O    TV    1 */
    consumed = dissect_opt_tv_short(nullptr, &alwayson_pdu_session_requested, d, ctx);
    d.step(consumed);

    /* 13    Integrity protection maximum data rate   9.11.4.7    O    TV    3 */
    consumed = dissect_opt_tv(nullptr, &integrity_protection_max_data_rate, d, ctx);
    d.step(consumed);

    /*7A    Requested QoS rules    QoS rules 9.11.4.13    O    TLV-E    3-65538 */
    // ELEM_OPT_TLV_E(0x7A, , DE_NAS_5GS_SM_QOS_RULES, " - Requested QoS rules");
    consumed = dissect_opt_tlv_e(nullptr, &requested_qos_rules, d, ctx);
    d.step(consumed);

    /* 79    Requested QoS flow descriptions    QoS flow descriptions 9.11.4.12    O
     * TLV-E    5-65538 */
    // ELEM_OPT_TLV_E(  0x79, , DE_NAS_5GS_SM_QOS_FLOW_DES, " - Requested");
    consumed = dissect_opt_tlv_e(nullptr, &requested_qos_flow_des, d, ctx);
    d.step(consumed);

    /* 75  Mapped EPS bearer contexts 9.11.4.8    O TLV-E    7-65538 */
    // ELEM_OPT_TLV_E(0x75, , DE_NAS_5GS_SM_MAPPED_EPS_B_CONT, NULL);
    consumed = dissect_opt_tlv_e(nullptr, &mapped_eps_bearer_ctx, d, ctx);
    d.step(consumed);

    /* 7B Extended protocol configuration options  9.11.4.6 O TLV-E    4-65538*/
    consumed = dissect_opt_tlv_e(nullptr, &extended_pco, d, ctx);
    d.step(consumed);

    // It is possible for UEs compliant with earlier versions of this specification
    // to send the Mapped EPS bearer contexts IE with IEI of value "7F" for this message.
    return uc.length;
}

