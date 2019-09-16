#pragma once
#include "../core.hh"

namespace sm{
int dissect_sm_congestion_reattempt(dissector d, context* ctx);
int dissect_alwayson_pdu_session_requested(dissector d, context* ctx);

int dissect_requested_qos_rules(dissector d, context* ctx);

// Selected PDU session type    PDU session type 9.11.4.11
int dissect_pdu_session_type(dissector d, context* ctx);

int dissect_pdu_address(dissector d, context* ctx);

// SM PDU DN request container 9.11.4.15
int dissect_pdu_dn_request_container(dissector d, context* ctx);

// Authorized QoS flow descriptions     QoS flow descriptions 9.11.4.12
int dissect_authorized_qos_flow_description(dissector d, context* ctx);

int dissect_qos_parameters(dissector d, int j, context* ctx);
int dissect_pdu_ses_establishment_request(dissector d, context* ctx);
int dissect_pdu_ses_establishment_accept(dissector d, context* ctx);
int dissect_pdu_ses_establishment_reject(dissector d, context* ctx);
int dissect_pdu_ses_authentication_cmd(dissector d, context* ctx);
int dissect_pdu_ses_authentication_complete(dissector d, context* ctx);
int dissect_pdu_ses_modification_request(dissector d, context* ctx);
int dissect_pdu_ses_modification_reject(dissector d, context* ctx);
int dissect_pdu_ses_modification_cmd(dissector d, context* ctx);
int dissect_pdu_ses_modification_complete(dissector d, context* ctx);
int dissect_pdu_session_authentication_result2(dissector d, context* ctx);
int dissect_pdu_ses_release_request(dissector d, context* ctx);
int dissect_pdu_ses_release_reject(dissector d, context* ctx);
int dissect_pdu_ses_release_cmd(dissector d, context* ctx);
int dissect_pdu_ses_release_complete(dissector d, context* ctx);
int dissect_sm_status(dissector d, context* ctx);

int dissect_sm_cause(dissector d, context* ctx);
int dissect_extended_protocol_configuration_options(dissector d, context* ctx);
int dissect_authorized_qos_rules(dissector d, context* ctx);
int dissect_qos_rules(dissector d, context* ctx);
int dissect_mapped_eps_bearer_ctx(dissector d, context* ctx);

int dissect_sm_capability(dissector d, context* ctx);
int dissect_max_number_supported_packet_filter(dissector d, context* ctx);
int dissect_session_ambr(dissector d, context* ctx);
int dissect_always_on_pdu_session_indication(dissector d, context* ctx);
int dissect_integrity_protection_max_data_rate(dissector d, context* ctx);
int dissect_allowed_ssc_mode(dissector d, context* ctx);

int dissect_ssc_mode(dissector d, context* ctx); //* 9.11.4.16    SSC mode

// 8.3.11	PDU session modification command reject
int dissect_pdu_session_modification_command_reject(dissector d, context* ctx);
int dissect_pdu_session_authentication_result(dissector d, context* ctx);
int dissect_reattempt_indicator(dissector d, context*ctx);
int dissect_control_plane_only_indication(dissector d, context*ctx);
} // namespace sm
