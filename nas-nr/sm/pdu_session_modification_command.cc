#include "../common/ber.hh"
#include "../common/dissect_nas5g.hh"
#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"
#include "common/packet.hh"

using namespace nas;
using namespace sm;

/* 8.3.9 PDU session modification command */
int sm::dissect_pdu_session_modification_command(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-modification-command", d, 8);

    /* Direction: network to UE */
    down_link(d.pinfo);

    /* 59 5GSM cause 9.11.4.2    O    TV    2*/
    // ELEM_OPT_TV(0x59, , DE_NAS_5GS_SM_5Gnrsm_cause, NULL);
    auto consumed = dissect_opt_tv(nullptr, &nrsm_cause, d, ctx);
    d.step(consumed);

    /* 2A Session-AMBR     9.11.4.14    O    TLV    8*/
    consumed = dissect_opt_tlv(nullptr, &session_ambr, d, ctx);
    d.step(consumed);

    /*56    RQ timer value    GPRS timer     9.11.2.3    O    TV    2*/
    // ELEM_OPT_TV(0x56, , DE_GPRS_TIMER, " - PDU session release time");
    consumed = dissect_opt_tv(nullptr, &rq_gprs_timer, d, ctx);
    d.step(consumed);

    /* 8-  Always-on PDU session indication 9.11.4.3  O    TV    1 */
    consumed = dissect_opt_tv_short(nullptr, &alwayson_pdu_session_indication, d, ctx);
    d.step(consumed);

    /*7A    Authorized QoS rules    QoS rules     9.11.4.13    O    TLV-E    3-65538*/
    // ELEM_OPT_TLV_E(  0x7A, , DE_NAS_5GS_SM_QOS_RULES, " - Authorized QoS rules");
    consumed = dissect_opt_tlv_e(nullptr, &authorized_qos_rules, d, ctx);
    d.step(consumed);

    /*75 Mapped EPS  bearer contexts     9.11.4.5    O TLV-E    7-65538*/
    consumed = dissect_opt_tlv_e(nullptr, &mapped_eps_bearer_context, d, ctx);
    d.step(consumed);

    /*79 Authorized QoS flow descriptions     QoS flow descriptions 9.11.4.12 O TLV-E 6-65538*/
    // ELEM_OPT_TLV_E(  0x79, , DE_NAS_5GS_SM_QOS_FLOW_DES, " - Authorized");
    consumed = dissect_opt_tlv_e(nullptr, &authorized_qos_flow_desc, d, ctx);
    d.step(consumed);

    /*7B    Extended protocol configuration options  9.11.4.6    O    TLV-E    4-65538*/
    consumed = dissect_opt_tlv_e(nullptr, &extended_pco, d, ctx);
    d.step(consumed);

    /*xx Session-TMBR    9.11.4.19	O	TLV	8    */


    return uc.length;
}
namespace sm {

const value_string nas_5gs_rule_param_cont[] = {
    {0x0, "Reserved"},
    {0x01, "5QI 1"},
    {0x02, "5QI 2"},
    {0x03, "5QI 3"},
    {0x04, "5QI 4"},
    {0x05, "5QI 5"},
    {0x06, "5QI 6"},
    {0x07, "5QI 7"},
    {0x08, "5QI 8"},
    {0x09, "5QI 9"},
    {0, nullptr},
};

int dissect_requested_qos_rules(dissector d, context* ctx) {
    return dissect_qos_rules(d, ctx);
}

const field_meta hf_qos_flow_ebit = {
    "E bit",
    "nas.nr.sm.qos.flow.ebit",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x40,
};
const field_meta hf_sm_parameters_number = {
    "Number of parameters",
    "nas.nr.sm.number.parameters",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x3f,
};

static const value_string nas_5gs_sm_param_id_values[] = {
    {0x01, "5QI"},
    {0x02, "GFBR uplink"},
    {0x03, "GFBR downlink"},
    {0x04, "MFBR uplink"},
    {0x05, "MFBR downlink"},
    {0x06, "Averaging window"},
    {0x07, "EPS bearer identity"},
    {0, nullptr},
};
const field_meta hf_sm_parameter_identifier = {
    "Parameter identifier",
    "nas.nr.sm.param_id",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_sm_param_id_values,
    nullptr,
    nullptr,
    0x0,
};
#if 0
const field_meta hf_sm_param_len = {
    "Length",
    "nas.nr.sm.param_len",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
#endif

const field_meta hf_sm_parameters_content = {
    "Parameters content",
    "nas.nr.sm.parameter.content",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_rule_param_cont,
    nullptr,
    nullptr,
    0x0,
};
const field_meta hf_averaging_window = {
    "Average Window",
    "nas.nr.sm.qos.param",
    ft::ft_uint16,
    fd::base_bin,
    nullptr,
    nullptr,
    nullptr,
    0,
};
const field_meta hf_eps_bearer_identity = {
    "EPS bearer identity",
    "nas.nr.sm.qos.eps.bearid",
    ft::ft_uint8,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0,
};


}
