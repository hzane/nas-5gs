#include "../core.hh"

namespace sm{
int dissect_sm_congestion_reattempt(dissector d, context* ctx);
int dissect_always_on_pdu_ses_req(dissector d, context* ctx);
int dissect_pdu_ses_type(dissector d, context* ctx);
int dissect_pdu_address(dissector d, context* ctx);
int dissect_authorized_qos_flow_des(dissector d, context* ctx);
int dissect_requested_qos_rules(dissector d, context* ctx);
} // namespace sm
