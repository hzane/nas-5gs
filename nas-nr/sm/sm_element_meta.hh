#pragma once
#include "../common/core.hh"
#include "sm_dissects.hh"

extern const element_meta nrsm_cause;
extern const element_meta extended_pco;
extern const element_meta authorized_qos_rules;
extern const element_meta mapped_eps_bearer_context;
extern const element_meta backoff_gprs_timer3;
extern const element_meta nrsm_capability;
extern const element_meta max_supported_packet_filters;
extern const element_meta session_ambr;
extern const element_meta rq_gprs_timer;
extern const element_meta alwayson_pdu_session_indication;
extern const element_meta allowed_ssc_mode;
extern const element_meta congestion_reattempt;
extern const element_meta alwayson_pdu_session_requested;
extern const element_meta pdu_session_type;
extern const element_meta selected_pdu_session_type;
extern const element_meta pdu_address;
extern const element_meta integrity_protection_max_data_rate;
extern const element_meta ssc_mode;
extern const element_meta sm_pdu_dn_request_container;
extern const element_meta requested_qos_rules;
extern const element_meta authorized_qos_flow_desc; // Authorized QoS flow descriptions QoS
extern const element_meta requested_qos_flow_desc;  // Requested QoS flow descriptions QoS
extern const element_meta control_plane_only_indication;

// SM PDU DN request container 9.11.4.15
inline const element_meta sm_pdu_dn_request_container = {
    0x39u,
    "PDU DN request container",
    sm::dissect_pdu_dn_request_container,
};

// Session-AMBR 9.11.4.14
inline const element_meta session_ambr = {
    0x2A,
    "Session AMBR",
    sm::dissect_session_ambr,
};

inline const element_meta serving_plmn_rate_control = {
    0xffu,
    "Serving PLMN rate control",
    sm::dissect_serving_plmn_rate_control,
};

inline const element_meta ssc_mode = {
    0xa0,
    "SSC mode",
    sm::dissect_ssc_mode,
};

inline const element_meta qos_rules = {
    0xffu,
    "Qos rules",
    sm::dissect_qos_rules,
};

inline const element_meta requested_qos_rules = {
    0x7A,
    "QoS rules - Requested QoS rules",
    sm::dissect_requested_qos_rules,

};

// Requested QoS flow descriptions     QoS flow descriptions 9.11.4.12
inline const element_meta requested_qos_flow_desc = {
    0x79,
    "QoS flow descriptions - Requested",
    sm::dissect_authorized_qos_flow_description,
};

// Authorized QoS flow descriptions     QoS flow descriptions 9.11.4.12
inline const element_meta authorized_qos_flow_desc = {
    0x79,
    "QoS flow descriptions - Authorized",
    sm::dissect_authorized_qos_flow_description,
};

// Selected PDU session type    PDU session type 9.11.4.11
inline const element_meta selected_pdu_session_type = {
    0x90,
    "Selected PDU session type",
    sm::dissect_pdu_session_type,
};

// PDU session type    PDU session type 9.11.4.11
inline const element_meta pdu_session_type = {
    0x90,
    "PDU session type",
    sm::dissect_pdu_session_type,
};

inline const element_meta allowed_ssc_mode = {
    0xf0,
    "Allowed SSC mode",
    sm::dissect_allowed_ssc_mode,
};

// PDU address 9.11.4.10
inline const element_meta pdu_address = {
    0x29,
    "PDU address",
    sm::dissect_pdu_address,
};

// Maximum number of supported packet filter 9.11.4.9
inline const element_meta max_supported_packet_filters = {
    0x55,
    "Maximum number of supported packet filter",
    sm::dissect_max_number_supported_packet_filter,
};

// Mapped EPS  bearer contexts     9.11.4.5
inline const element_meta mapped_eps_bearer_context = {
    0x75,
    "Mapped EPS bearer contexts",
    sm::dissect_mapped_eps_bearer_contexts,
};

// Integrity protection maximum data rate   9.11.4.7
inline const element_meta integrity_protection_max_data_rate = {
    0x13,
    "Integrity protection maximum data rate",
    sm::dissect_integrity_protection_max_data_rate,

};

// Extended protocol configuration options  9.11.4.6
inline const element_meta extended_pco = {
    0x7B,
    "Extended protocol configuration options",
    sm::dissect_extended_protocol_configuration_options,
};

// XX Control plane only indication 9.11.4.23	O	TV	1
const element_meta control_plane_only_indication = {
    0xffu,
    "Control plane only indication",
    sm::dissect_control_plane_only_indication,
};

//  Always-on PDU session requested  9.11.4.4
inline const element_meta alwayson_pdu_session_requested = {
    0xB0,
    "Always-on PDU session requested",
    sm::dissect_alwayson_pdu_session_requested,
};

// Always-on PDU session indication 9.11.4.3
inline const element_meta alwayson_pdu_session_indication = {
    0x80,
    "Always-on PDU session indication",
    sm::dissect_always_on_pdu_session_indication,
};

// 5GSM congestion re-attempt indicator 9.11.4.21
inline const element_meta congestion_reattempt = {
    0x61u,
    "5GSM congestion re-attempt indicator",
    sm::dissect_sm_congestion_reattempt,
};

// 5GSM cause 9.11.4.2
inline const element_meta nrsm_cause = {
    0x59,
    "5GSM cause",
    sm::dissect_nrsm_cause,
};

// 5GSM capability 9.11.4.1
inline const element_meta nrsm_capability = {
    0x28,
    "5GSM capability",
    sm::dissect_nrsm_capability,
};

// Authorized QoS rules QoS rules 9.11.4.13
const element_meta authorized_qos_rules = {
    0x7A,
    "QoS rules - Authorized QoS rules",
    sm::dissect_authorized_qos_rules,
};