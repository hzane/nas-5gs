#include "../core.hh"

namespace sm{
int dissect_sm_congestion_reattempt(dissector d, context* ctx);
int dissect_always_on_pdu_ses_req(dissector d, context* ctx);
int dissect_pdu_ses_type(dissector d, context* ctx);
int dissect_pdu_address(dissector d, context* ctx);
int dissect_authorized_qos_flow_des(dissector d, context* ctx);
int dissect_requested_qos_rules(dissector d, context* ctx);

// Selected PDU session type    PDU session type 9.11.4.11
int dissect_pdu_ses_type(dissector d, context* ctx);

int dissect_pdu_address(dissector d, context* ctx);

// SM PDU DN request container 9.11.4.15
int dissect_pdu_dn_req_cont(dissector d, context* ctx);

// Authorized QoS flow descriptions     QoS flow descriptions 9.11.4.12
int dissect_authorized_qos_flow_des(dissector d, context* ctx);

int dissect_qos_param(dissector d, int j, context* ctx);
} // namespace sm
