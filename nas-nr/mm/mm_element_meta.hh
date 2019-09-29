#pragma once
#include <common/gsm.hh>

#include "../common/core.hh"

extern const element_meta nrmm_capability;
extern const element_meta nrmm_cause;
extern const element_meta network_feature_support ;
extern const element_meta network_slicing_indication;
extern const element_meta eps_nas_message_container;
extern const element_meta ue_status;
extern const element_meta last_visited_tai;
extern const element_meta nc_native_nas_ksi;
extern const element_meta payload_container;
extern const element_meta ladn_indication;
extern const element_meta ue_security_capability;
extern const element_meta s1_ue_network_capability;
extern const element_meta ue_usage_setting;
extern const element_meta allowed_pdu_session_status;
extern const element_meta aguti_mobile_id;
extern const element_meta payload_container_type;
extern const element_meta update_type;
extern const element_meta requested_drx_parameter;
extern const element_meta mico_indication;
extern const element_meta requested_nssai;
extern const element_meta guti_mobile_id;
extern const element_meta ladn_information;
extern const element_meta service_area_list;
extern const element_meta t3512_gprs_timer_3;
extern const element_meta n3g_deregistration_timer_gprs_timer2;
extern const element_meta t3502_gprs_timer_2;
extern const element_meta emergency_number_list;
extern const element_meta ext_emergency_number_list;
extern const element_meta sor_transparent_container;
extern const element_meta eap_message;
extern const element_meta nssai_inclusion_mode;
extern const element_meta operator_defined_acd;
extern const element_meta negotiated_drx_parameter;
extern const element_meta n3gpp_nw_provided_policies;
extern const element_meta registration_result;
extern const element_meta authentication_failure_parameter;
extern const element_meta authentication_parameter_rand;
extern const element_meta authentication_parameter_autn;
extern const element_meta authentication_response_parameter;
extern const element_meta configure_update_indication;
extern const element_meta daylight_saving_time;
extern const element_meta full_name_network;
extern const element_meta short_name_network;
extern const element_meta local_timezone;
extern const element_meta timezone_time;
extern const element_meta operator_defined_access_category_defs;
extern const element_meta sms_indication;
extern const element_meta configured_nssai ;
extern const element_meta mobile_id;
extern const element_meta t3346_gprs_timer2;
extern const element_meta pdu_session_id;
extern const element_meta backoff_gprs_timer3;
extern const element_meta plmn_list;
extern const element_meta selected_security_algo;
extern const element_meta replayed_ue_security_capability;
extern const element_meta imeisv_request;
extern const element_meta selected_eps_security_algo;
extern const element_meta additional_security_info;
extern const element_meta replayed_s1_ue_security_capability;
extern const element_meta pdu_session_reactivation_result;
extern const element_meta pdu_session_reactive_result_error_cause;
extern const element_meta s_tmsi;
extern const element_meta uplink_data_status;
extern const element_meta old_pdu_session_id;
extern const element_meta request_type;
extern const element_meta nas_ksi;
extern const element_meta nas_msg_container;
extern const element_meta abba;
extern const element_meta eps_bearer_context_status;
extern const element_meta allowed_nssai;
extern const element_meta tracking_area_id_list;
extern const element_meta rejected_nssai;
extern const element_meta pdu_session_status;
extern const element_meta imeisv_mobile_id;

// Uplink data status  9.11.3.57
inline const element_meta uplink_data_status = {
    0x40,
    "Uplink data status",
    mm::dissect_uplink_data_status,
};

// See subclause 10.5.3.8 in 3GPP TS 24.008 [12].
inline const element_meta local_timezone = {
    0x46,
    "Local time zone",
    mm::dissect_timezone_set,

};

// 9.11.3.53
inline const element_meta timezone_time = {
    0x47,
    "Time zone and time - Universal time and local time zone",
    mm::dissect_timezone_time_set,
};

// SOR transparent container   9.11.3.51
inline const element_meta sor_transparent_container = {
    0x73,
    "SOR transparent container",
    mm::dissect_sor_transparent_container,
};

inline const element_meta s_tmsi = {
    0xff,
    "5GS mobile identity - 5G-S-TMSI",
    mm::dissect_mobile_id,
};

inline const element_meta imeisv_mobile_id = {
    0x77,
    "5G mobile identity - IMEISV",
    mm::dissect_mobile_id,
};

inline const element_meta selected_security_algo = {
    0xff,
    "Selected NAS security algorithms",
    mm::dissect_security_algo,
};
inline const element_meta replayed_ue_security_capability = {
    0xff,
    "UE security capability - Replayed UE security capabilities",
    mm::dissect_replayed_ue_security_capability,
};
inline const element_meta imeisv_request = {
    0xE0,
    "IMEISV request",
    mm::dissect_imeisv_request,
};

inline const element_meta additional_security_info = {
    0x36,
    "Additional 5G security information",
    mm::dissect_additional_security_info,
};

inline const element_meta replayed_s1_ue_security_capability = {
    0x19,
    "S1 UE security capability - Replayed S1 UE security capabilities",
    mm::dissect_reported_s1_ue_security_capability,
};

// Request type  9.11.3.47
inline const element_meta request_type = {
    0x80,
    "Request type",
    mm::dissect_request_type,
};

//  9.11.3.46    Rejected NSSAI
inline const element_meta rejected_nssai = {
    0x11,
    "Rejected NSSAI",
    mm::dissect_rejected_nssai,
};

// EAP message  9.11.2.2
inline const element_meta eap_message = {
    0x78,
    "EAP message",
    cmn::dissect_eap_message,
};

// NSSAI inclusion mode  9.11.3.37A
inline const element_meta nssai_inclusion_mode = {
    0xA0,
    "NSSAI inclusion mode",
    mm::dissect_nssai_inclusion_mode,
};

inline const element_meta plmn_list = {
    0x4a,
    "Equivalent PLMNs",
    mm::dissect_plmn_list,
};

inline const element_meta pdu_session_reactive_result_error_cause = {
    0x72,
    "PDU session reactivation result error cause",
    mm::dissect_pdu_session_reactive_result_error_cause,
};

// PDU session ID 2 9.11.3.41
inline const element_meta pdu_session_id = {
    0x12,
    "PDU session identity 2 - PDU session ID",
    mm::dissect_pdu_session_id_set,
};

// PDU session identity 2 9.11.3.41
inline const element_meta old_pdu_session_id = {
    0x59,
    "PDU session identity 2 - Old PDU session ID",
    mm::dissect_pdu_session_id_set,
};

// Payload container  9.11.3.39
inline const element_meta payload_container = {
    0x7B,
    "Payload container",
    mm::dissect_payload_container,
};

// Payload container type   9.11.3.40
inline const element_meta payload_container_type = {
    0x80,
    "Payload container type",
    mm::dissect_payload_container_type,
};

inline const element_meta operator_defined_access_category_defs = {
    0x76,
    "Operator-defined access category definitions",
    mm::dissect_operator_defined_access_category_definitions,
};

// Configured NSSAI    NSSAI 9.11.3.37
inline const element_meta configured_nssai = {
    0x31,
    "Configured NSSAI",
    mm::dissect_configured_nssai,
};

// Non-3GPP NW policies Non-3GPP NW provided policies 9.11.3.58
inline const element_meta n3gpp_nw_provided_policies = {
    0xd0,
    "Non-3GPP NW provided policies",
    mm::dissect_n3gpp_nw_provided_policies,
};

// Network slicing indication  9.11.3.36
inline const element_meta network_slicing_indication = {
    0x90,
    "Network slicing indication",
    mm::dissect_network_slicing_indicationication,
};

// See subclause 10.5.3.5a in 3GPP TS 24.008 [12].
inline const element_meta full_name_network = {
    0x43,
    "Network name - Full Name",
    mm::dissect_full_name_network,

};

// See subclause 10.5.3.5a in 3GPP TS 24.008 [12].
inline const element_meta short_name_network = {
    0x45,
    "Network Name - Short Name",
    mm::dissect_short_name_network,
};

inline const element_meta mico_indication = {
    0xb0,
    "MICO indication",
    mm::dissect_mico_ind,
};

// LADN information   9.11.3.30
inline const element_meta ladn_information = {
    0x79,
    "LADN information",
    mm::dissect_ladn_information,
};

inline const element_meta ext_emergency_number_list = {
    0x7A,
    "Extended emergency number list",
    mm::dissect_extended_emergency_number_list,
};

inline const element_meta selected_eps_security_algo = {
    0x57,
    "EPS NAS security algorithms - Selected EPS NAS security algorithms",
    mm::dissect_selected_eps_security_algo,
};

inline const element_meta emergency_number_list = {
    0x34,
    "Emergency number list",
    mm::dissect_emergency_number_list,
};

// Back-off timer value    GPRS timer 3 9.11.2.5
inline const element_meta backoff_gprs_timer3 = {
    0x37,
    "GPRS timer 3 - Back-off timer",
    cmn::dissect_gprs_timer3_set,
};

inline const element_meta t3346_gprs_timer2 = {
    0x5f,
    "GPRS timer 2 - T3346 value",
    cmn::dissect_gprs_timer2_set,
};

// 9.11.3.19
inline const element_meta daylight_saving_time = {
    0x49,
    "Network daylight saving time",
    mm::dissect_daylight_saving_time,

};

inline const element_meta configure_update_indication = {
    0xD0,
    "Configuration update indication",
    mm::dissect_configuration_update_indication,
};

inline const element_meta sms_indication = {
    0xF0,
    "SMS indication",
    mm::dissect_sms_indication,

};

// 9.11.3.17
inline const element_meta authentication_response_parameter = {
    0x2d,
    "Authentication response parameter",
    mm::dissect_authentication_response_parameter,
};

inline const element_meta authentication_parameter_rand = {
    0x21,
    "Authentication parameter RAND - 5G authentication challenge",
    mm::dissect_authentication_parameter_rand,
};

inline const element_meta authentication_parameter_autn = {
    0x20,
    "Authentication parameter AUTN - 5G authentication challenge",
    mm::dissect_authentication_parameter_autn,
};

inline const element_meta authentication_failure_parameter = {
    0x30,
    "Authentication failure parameter",
    mm::dissect_authentication_failure_parameter,
};

// Allowed PDU session status
inline const element_meta allowed_pdu_session_status = {
    0x25,
    "Allowed PDU session status",
    mm::dissect_allowed_pdu_session_status,
};

inline const element_meta abba = {
    0x38,
    "ABBA",
    mm::dissect_abba_set,
};

// 9.11.3.9A 5GS update type
inline const element_meta update_type = {
    0x53,
    "5GS update type",
    mm::dissect_update_type,
};

inline const element_meta nc_native_nas_ksi = {
    0xc0,
    "NAS key set identifier - Non-current native NAS KSI",
    mm::dissect_nas_ksi,
};

inline const element_meta ue_security_capability = {
    0x2e,
    "UE security capability",
    mm::dissect_ue_security_capability,
};

/*2F    Requested NSSAI    NSSAI 9.11.3.37    O    TLV    4-74*/
inline const element_meta requested_nssai = {
    0x2f,
    "NSSAI - Requested",
    mm::dissect_requested_nssai,
};

inline const element_meta last_visited_tai = {
    0x52,
    "5GS tracking area identity - Last visited registered TAI",
    mm::dissect_last_visited_tai,
};

inline const element_meta s1_ue_network_capability = {
    0x17,
    "S1 UE network capability",
    mm::dissect_s1_ue_net_capability,
};

inline const element_meta ue_status = {
    0x2b,
    "UE status",
    mm::dissect_ue_status,
};

inline const element_meta aguti_mobile_id = {
    0x77,
    "5GS mobile identity - Additional GUTI",
    mm::dissect_mobile_id,
};

// UE's usage setting         9.11.3.55
inline const element_meta ue_usage_setting = {
    0x18,
    "UE's usage setting",
    mm::dissect_usage_setting,
};

inline const element_meta requested_drx_parameter = {
    0x51,
    "5GS DRX parameters - Requested",
    mm::dissect_drx_parameter,
};

inline const element_meta eps_nas_message_container = {
    0x70,
    "EPS NAS message container",
    mm::dissect_eps_nas_msg_container,
};

inline const element_meta ladn_indication = {
    0x74,
    "LADN indication",
    mm::dissect_ladn_indication,
};

inline const element_meta registration_result = {
    0xff,
    "5GS registration result",
    mm::dissect_registration_result,
};

// 5GS network feature support   9.11.3.5
inline const element_meta network_feature_support = {
    0x21,
    "5GS network feature support",
    mm::dissect_network_feature_support,
};

inline const element_meta guti_mobile_id = {
    0x77,
    "5GS mobile identity - 5G-GUTI",
    mm::dissect_mobile_id,
};

// 9.11.3.2	5GMM cause
inline const element_meta nrmm_cause = {
    0x58,
    "5GMM cause",
    mm::dissect_nrmm_cause,
};

/*10    5GMM capability  9.11.3.1    O    TLV    3-15*/
inline const element_meta nrmm_capability = {
    0x10,
    "5GMM capability",
    mm::dissect_mm_capability,
};

// 5GS mobile identity  9.11.3.4
inline const element_meta mobile_id = {
    0x77,
    "5GS mobile identity",
    mm::dissect_mobile_id,
};


// Allowed NSSAI    NSSAI     9.11.3.37
extern const element_meta allowed_nssai = {
    0x15,
    "Allowed NSSAI",
    mm::dissect_allowed_nssai,
};

// 9.11.3.9
extern const element_meta tracking_area_id_list = {
    0x54,
    "5GS tracking area identity list - TAI list",
    mm::dissect_tracking_area_id_list,
};

// PDU session reactivation result   9.11.3.42
extern const element_meta pdu_session_reactivation_result = {
    0x26,
    "PDU session reactivation result",
    mm::dissect_pdu_session_reactive_result,
};

/* 9.11.3.44    PDU session status */
extern const element_meta pdu_session_status = {
    0x50,
    "PDU session status",
    mm::dissect_pdu_session_status,
};



// NAS message container 9.11.3.33
extern const element_meta nas_msg_container = {
    0x71,
    "NAS message container",
    mm::dissect_nas_message_container,
};

// EPS bearer context status	9.11.3.59
extern const element_meta eps_bearer_context_status = {
    0x60,
    "EPS bearer context status",
    mm::dissect_eps_bearer_context_status,
};

// NAS key set identifier 9.11.3.32
extern const element_meta nas_ksi = {
    0xff,
    "NAS key set identifier - ngKSI",
    mm::dissect_nas_ksi,
};