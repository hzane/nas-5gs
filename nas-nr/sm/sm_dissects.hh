#pragma once
#include "../core.hh"

namespace sm{
int dissect_sm_congestion_reattempt(dissector d, context* ctx);
int dissect_always_on_pdu_ses_req(dissector d, context* ctx);

int dissect_requested_qos_rules(dissector d, context* ctx);

// Selected PDU session type    PDU session type 9.11.4.11
int dissect_pdu_session_type(dissector d, context* ctx);

int dissect_pdu_address(dissector d, context* ctx);

// SM PDU DN request container 9.11.4.15
int dissect_pdu_dn_req_cont(dissector d, context* ctx);

// Authorized QoS flow descriptions     QoS flow descriptions 9.11.4.12
int dissect_authorized_qos_flow_des(dissector d, context* ctx);

int dissect_qos_param(dissector d, int j, context* ctx);
int dissect_pdu_ses_establishment_req(dissector d, context* ctx);
int dissect_pdu_ses_establishment_accept(dissector d, context* ctx);
int dissect_pdu_ses_establishment_rej(dissector d, context* ctx);
int dissect_pdu_ses_authentication_cmd(dissector d, context* ctx);
int dissect_pdu_ses_authentication_cmpl(dissector d, context* ctx);
int dissect_pdu_ses_modification_req(dissector d, context* ctx);
int dissect_pdu_ses_modification_rej(dissector d, context* ctx);
int dissect_pdu_ses_modification_cmd(dissector d, context* ctx);
int dissect_pdu_ses_modification_cmpl(dissector d, context* ctx);
int dissect_pdu_session_authentication_result2(dissector d, context* ctx);
int dissect_pdu_ses_release_req(dissector d, context* ctx);
int dissect_pdu_ses_release_rej(dissector d, context* ctx);
int dissect_pdu_ses_release_cmd(dissector d, context* ctx);
int dissect_pdu_ses_release_cmpl(dissector d, context* ctx);
int dissect_sm_status(dissector d, context* ctx);

int dissect_sm_cause(dissector d, context* ctx);
int dissect_ext_pco(dissector d, context* ctx);
int dissect_authorized_qos_rules(dissector d, context* ctx);
int dissect_qos_rules(dissector d, context* ctx);
int dissect_mapped_eps_bearer_ctx(dissector d, context* ctx);

int dissect_sm_cap(dissector d, context* ctx);
int dissect_max_num_sup_kpt_flt(dissector d, context* ctx);
int dissect_session_ambr(dissector d, context* ctx);
int dissect_always_on_pdu_ses_ind(dissector d, context* ctx);
int dissect_int_prot_max_data_rate(dissector d, context* ctx);
int dissect_allowed_ssc_mode(dissector d, context* ctx);

int dissect_ssc_mode(dissector d, context* ctx); //* 9.11.4.16    SSC mode

// 8.3.11	PDU session modification command reject
int dissect_pdu_session_modification_command_reject(dissector d, context* ctx);
int dissect_pdu_session_authentication_result(dissector d, context* ctx);
} // namespace sm
