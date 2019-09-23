#pragma once
#include "../common/core.hh"

namespace sm{
int dissect_sm_congestion_reattempt(dissector d, context* ctx);
int dissect_alwayson_pdu_session_requested(dissector d, context* ctx);

int dissect_requested_qos_rules(dissector d, context* ctx);

int dissect_authorized_qos_flow_description(dissector d, context* ctx); // 9.11.4.12
int dissect_qos_parameters(dissector d, int j, context* ctx);

int dissect_pdu_dn_request_container(dissector d, context* ctx); // 9.11.4.15
int dissect_pdu_session_type(dissector d, context* ctx);         // 9.11.4.11
int dissect_pdu_address(dissector d, context* ctx);
int dissect_pdu_session_establishment_request(dissector d, context* ctx);
int dissect_pdu_session_establishment_accept(dissector d, context* ctx);
int dissect_pdu_session_establishment_reject(dissector d, context* ctx);
int dissect_pdu_session_authentication_command(dissector d, context* ctx);
int dissect_pdu_session_authentication_complete(dissector d, context* ctx);
int dissect_pdu_session_modification_request(dissector d, context* ctx);
int dissect_pdu_session_modification_reject(dissector d, context* ctx);
int dissect_pdu_session_modification_command(dissector d, context* ctx);
int dissect_pdu_session_modification_complete(dissector d, context* ctx);
int dissect_pdu_session_authentication_result2(dissector d, context* ctx);
int dissect_pdu_session_release_request(dissector d, context* ctx);
int dissect_pdu_session_release_reject(dissector d, context* ctx);
int dissect_pdu_session_release_command(dissector d, context* ctx);
int dissect_pdu_session_release_complete(dissector d, context* ctx);
int dissect_pdu_session_modification_command_reject(dissector d, context* ctx); // 8.3.11
int dissect_pdu_session_authentication_result(dissector d, context* ctx);

int dissect_nrsm_cause(dissector d, context* ctx);
int dissect_extended_protocol_configuration_options(dissector d, context* ctx);
int dissect_authorized_qos_rules(dissector d, context* ctx);
int dissect_qos_rules(dissector d, context* ctx);
int dissect_mapped_eps_bearer_contexts(dissector d, context* ctx);
int dissect_nrsm_capability(dissector d, context* ctx);
int dissect_max_number_supported_packet_filter(dissector d, context* ctx);
int dissect_session_ambr(dissector d, context* ctx);
int dissect_always_on_pdu_session_indication(dissector d, context* ctx);
int dissect_integrity_protection_max_data_rate(dissector d, context* ctx);
int dissect_allowed_ssc_mode(dissector d, context* ctx);
int dissect_ssc_mode(dissector d, context* ctx); //* 9.11.4.16    SSC mode
int dissect_reattempt_indicator(dissector d, context*ctx);
int dissect_control_plane_only_indication(dissector d, context*ctx);
int dissect_sm_status(dissector d, context* ctx);
} // namespace sm
