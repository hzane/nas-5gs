#include "../dissect_sm_msg.hh"
#include "../ber.hh"
#include "../common.hh"
#include "../packet_info.hh"

using namespace cmn;
using namespace nas;
using namespace sm;

/* 8.3.2 PDU session establishment accept */
int sm::dissect_pdu_session_establishment_accept(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-establishment-accept", d, -1);

    /* Direction: network to UE */
    down_link(d.pinfo);

    /* Selected PDU session type    PDU session type 9.11.4.11    M    V    1/2 H0*/
    dissect_pdu_session_type(d, ctx);

    /* Selected SSC mode    SSC mode 9.11.4.16    M    V    1/2 H1*/
    (void) d.add_item(1, &hfm_selected_ssc_mode, enc::be);
    d.step(1);

    /* Authorized QoS rules QoS rules 9.11.4.13 M LV-E 2-65537  DE_NAS_5GS_SM_QOS_RULES*/
    // ELEM_MAND_LV_E(,DE_NAS_5GS_SM_QOS_RULES, " - Authorized QoS rules",);
    auto consumed = dissect_lv_e(nullptr, &authorized_qos_rules, d, ctx);
    d.step(consumed);

    /* Session-AMBR 9.11.4.14    M    LV    7 */
    consumed = dissect_lv(nullptr, &session_ambr, d, ctx);
    d.step(consumed);

    /*59 5GSM cause 9.11.4.2    O    TV    2*/
    consumed = dissect_opt_tv(nullptr, &sm_cause, d, ctx);
    d.step(consumed);

    /*29  PDU address 9.11.4.10    O    TLV    7 */
    consumed = dissect_opt_tlv(nullptr, &pdu_address, d, ctx);
    d.step(consumed);

    /*56    RQ timer value    GPRS timer 9.11.2.3    O    TV    2*/
    // ELEM_OPT_TV(0x56, , DE_GPRS_TIMER, " - RQ timer value");
    consumed = dissect_opt_tv(nullptr, &rq_gprs_timer, d, ctx);
    d.step(consumed);

    /* 22 S-NSSAI 9.11.2.8    O    TLV    3-6*/
    consumed = dissect_opt_tlv(nullptr, &s_nssai, d, ctx);
    d.step(consumed);

    /* 8-    Always-on PDU session indication   9.11.4.3  O    TV    1 */
    consumed = dissect_opt_tv_short(nullptr, &alwayson_pdu_ses_ind, d, ctx);
    d.step(consumed);

    /* 75    Mapped EPS bearer contexts  9.11.4.8    O  TLV-E    7-65538 */
    consumed = dissect_opt_tlv_e(nullptr, &mapped_eps_bearer_ctx, d, ctx);
    d.step(consumed);

    /*78    EAP message    EAP message 9.11.2.2    O    TLV-E    7-1503*/
    consumed = dissect_opt_tlv_e(nullptr, &eap_message, d, ctx);
    d.step(consumed);

    /*79 Authorized QoS flow descriptions    QoS flow descriptions 9.11.4.12    O
     * TLV-E    6-65538 */
    // ELEM_OPT_TLV_E( 0x79, , DE_NAS_5GS_SM_QOS_FLOW_DES, " - Authorized");
    consumed = dissect_opt_tlv_e(nullptr, &authorized_qos_flow_desc, d, ctx);
    d.step(consumed);

    /*7B  Extended protocol configuration options 9.11.4.6    O    TLV-E    4-65538*/
    // ELEM_OPT_TLV_E(0x7B, , DE_ESM_EXT_PCO, NULL);
    consumed = dissect_opt_tlv_e(nullptr, &extended_pco, d, ctx);
    d.step(consumed);

    /* 25 DNN 9.11.2.1A    O    TLV    3-102 */
    // ELEM_OPT_TLV(0x25, , DE_NAS_5GS_CMN_DNN, NULL);
    consumed = dissect_opt_tlv(nullptr, &dnn, d, ctx);
    d.step(consumed);

    /*xx	5GSM network feature support 9.11.4.18	O	TLV	3-15
     * consumed = dissect_opt_tlv(nullptr, &sm_nw_feature_support, d, ctx);
     * d.step(consumed);
    xx	Session-TMBR	Session-TMBR 9.11.4.19	O	TLV	8
     consumed = dissect_opt_tlv(nullptr, &session_tmbr, d, ctx);
     d.step(consumed);
    TBD	Serving PLMN rate control 9.11.4.20	O	TLV	4
     consumed = dissect_opt_tlv(nullptr, &serving_plmn_rate_control, d, ctx);
     d.step(consumed);
    XX	ATSSS container 9.11.4.22	O	TLV-E	3-65538
     consumed = dissect_opt_tlv_e(nullptr, &atsss_container, d, ctx);
     d.step(consumed);
    XX	Control plane only indication 9.11.4.23	O	TV	1
     consumed = dissect_opt_tv_short(nullptr, &control_plane_only_indication, d, ctx);
     d.step(consumed);
    */
   // no data length check

    return uc.length;
}

struct pdu_session_type_t {};
struct qos_rules_t {};
struct ambr_t {};
struct sm_cause_t {};
struct pdu_address_t {};
struct s_nssai_t{};
struct pdu_session_indication_t {};
struct mapped_eps_bearer_contexts_t {};

struct pdu_session_establishment_accept_t {
    pdu_session_type_t type;
    qos_rules_t        authorized_qos_rules;
    ambr_t             session_ambr;
    sm_cause_t         cause;
    pdu_address_t      address;
    timer_t            rq_timer;
    s_nssai_t          s_nssai;
    pdu_session_indication_t alwayson_pdu_session_indication;
    mapped_eps_bearer_contexts_t mapped_eps_bearer_contexts;
    payload_t                    eap_message;

};
