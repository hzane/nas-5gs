#pragma once
#include "../core.hh"

namespace mm {
int dissect_auth_fail_param(dissector d, context* ctx);
int dissect_auth_parameter_rand(dissector d, context* ctx);
int dissect_auth_parameter_autn(dissector d, context* ctx);
int dissect_auth_resp_param(dissector d, context* ctx);
int dissect_deregistration_type(dissector d, context* ctx);
int dissect_config_update_ind(dissector d, context* ctx);
int dissect_service_area_list(dissector d, context* ctx);
int dissect_timezone_time_set(dissector d, context* ctx);
int dissect_daylight_saving_time(dissector d, context* ctx);
int dissect_mico_ind(dissector d, context* ctx);
int dissect_full_name_network(dissector d, context* ctx);
int dissect_short_name_network(dissector d, context* ctx);
int dissect_timezone_set(dissector d, context* ctx);
int dissect_operator_defined_access_category_definitions(dissector d, context* ctx);
int dissect_sms_indication(dissector d, context* ctx);
int dissect_security_algo(dissector d, context* ctx);
int dissect_replayed_ue_sec_cap(dissector d, context* ctx);
int dissect_imeisv_req(dissector d, context* ctx);
int dissect_selected_eps_security_algo(dissector d, context* ctx);
int dissect_additional_security_info(dissector d, context* ctx);
int dissect_reported_s1_ue_sec_cap(dissector d, context* ctx);
int dissect_service_type(dissector d, context* ctx);
int dissect_uplink_data_status(dissector d, context* ctx);
int dissect_allowed_pdu_ses_status(dissector d, context* ctx);
int dissect_pdu_session_id(dissector d, context* ctx);
int dissect_payload_container_type(dissector d, context* ctx); // 9.11.3.40
int dissect_payload_container(dissector d, context* ctx);      // 9.11.3.39
int dissect_request_type(dissector d, context* ctx);

int dissect_last_v_tai(dissector d, context* ctx); //  9.11.3.8
int dissect_s1_ue_net_capability(dissector d, context* ctx);

int dissect_ue_status(dissector d, context* ctx ); // 9.11.3.56

// 9.11.3.55
int dissect_usage_setting(dissector d, context* ctx );

// 9.11.3.24
int dissect_eps_nas_msg_container(dissector d, context* ctx );

// 9.11.3.29
int dissect_ladn_indication(dissector d, context* ctx );

// 9.11.3.9A 5GS update type
int dissect_update_type(dissector d, context* ctx );

/* 9.11.3.54    UE security capability*/
int dissect_ue_security_capability(dissector d, context* ctx);

int dissect_n3gpp_nw_provided_policies(dissector d, context* ctx);

int dissect_pdu_session_reactive_result_error_cause(dissector d, context*);

int dissect_sor_trans_cont(dissector d, context* ctx);

int dissect_access_type(dissector d, context*);/*  9.11.3.11    Access type */

int dissect_registration_req(dissector d, context* ctx);
int dissect_registration_accept(dissector d, context* ctx);
int dissect_registration_complete(dissector d, context* ctx);
int dissect_registration_rej(dissector d, context* ctx);
int dissect_deregistration_req_ue_orig(dissector d, context* ctx);
int dissect_deregistration_req_ue_term(dissector d, context* ctx);
int dissect_service_request(dissector d, context* ctx);
int dissect_service_reject(dissector d, context* ctx);
int dissect_service_accept(dissector d, context* ctx);

int dissect_config_update_cmd(dissector d, context* ctx);
int dissect_config_update_cmpl(dissector d, context* ctx);
int authentication_request(dissector d, context* ctx);
int authentication_resp(dissector d, context* ctx);
int authentication_reject(dissector d, context* ctx);
int authentication_failure(dissector d, context* ctx);
int authentication_result(dissector d, context* ctx);
int dissect_identity_request(dissector d, context* ctx);
int dissect_identity_resp(dissector d, context* ctx);
int dissect_security_mode_cmd(dissector d, context* ctx);
int dissect_security_mode_cmpl(dissector d, context* ctx);
int dissect_security_mode_reject(dissector d, context* ctx);

int dissect_mm_status(dissector d, context* ctx);
int dissect_notification(dissector d, context* ctx);
int dissect_notification_resp(dissector d, context* ctx);
int dissect_ul_nas_transp(dissector d, context* ctx);
int dissect_dl_nas_transp(dissector d, context* ctx);

int dissect_allowed_nssai(dissector d, context* ctx);
int dissect_tracking_area_id_list(dissector d, context* ctx);

//  9.11.3.46    Rejected NSSAI
int dissect_rejected_nssai(dissector d, context* ctx);

int dissect_configured_nssai(dissector d, context* ctx);

int dissect_pdu_session_reactive_result(dissector d, context* ctx );

int dissect_pdu_session_status(dissector d, context* ctx); /* 9.11.3.44*/
int dissect_mm_cause(dissector d, context* ctx);                 // 5GMM cause   9.11.3.2
int dissect_drx_param(dissector d, context* ctx);

int dissect_ladn_information(dissector d, context* ctx); /*  9.11.3.30    LADN information */
int dissect_mobile_id(dissector d, context* ctx);

//  9.11.3.36    Network slicing indication
int dissect_nw_slicing_ind(dissector d, context* ctx);
int dissect_nas_ksi(dissector d, context* ctx);
int dissect_nas_msg_container(dissector d, context* ctx = nullptr);

int dissect_abba_set(dissector d, context* ctx);
int dissect_requested_nssai(dissector d, context* ctx);
int dissect_eps_bearer_context_status(dissector d, context* ctx);

int dissect_mobile_id_noid(dissector d, context* ctx);    // 0, no identity
int dissect_mobile_id_suci(dissector d, context* ctx);    // 1, SUCI
int dissect_mobile_id_5gguti(dissector d, context* ctx);  // 2, 5G-GUTI
int dissect_mobile_id_imei(dissector d, context* ctx);    // 3, IMEI
int dissect_mobile_id_5gstmsi(dissector d, context* ctx); // 4, 5G-S-TMSI
int dissect_mobile_id_imeisv(dissector d, context* ctx);  // 5, IMEISV
int dissect_mobile_id_mac(dissector d, context* ctx);     // 6, MAC address
int dissect_identity_type(dissector d, context* ctx);
int dissect_nw_feature_support(dissector d, context* ctx);
/*  5GS registration result    9.11.3.6    M    LV 2 */
int dissect_registration_result(dissector d, context* ctx = nullptr);

int dissect_registration_request_type(dissector d, context* ctx);
//  5GMM capability  9.11.3.1
int dissect_mm_capability(dissector d, context* ctx);

int dissect_updp(dissector d, context* ctx);
int dissect_security_protected_5gs_nas_msg(dissector d, context* ctx);

int dissect_emergency_num_list(dissector d, context* ctx);

// Extended emergency number list  9.11.3.26
int dissect_ext_emerge_num_list(dissector d, context* ctx );
int dissect_nssai_inclusion_mode(dissector d, context* ctx);
int dissect_optional_ie(dissector d, context* ctx);
int dissect_pld_container_entry(dissector d, context* ctx);

/*4A    Equivalent PLMNs    PLMN list     9.11.3.45    O    TLV    5-47*/
int dissect_plmn_list(dissector d, context* ctx );

int dissect_ue_parameters_update_transparent_container(dissector d, context* ctx);
int dissect_deregistration_accept_ue_orig(dissector d, context* ctx);
int dissect_deregistration_accept_ue_term(dissector d, context* ctx);
} // namespace mm
