#include "dissect_mm_msg.hh"

using namespace mm;
using namespace nas;

const true_false_string mm::tfs_sms_requested = {
    "SMS over NAS supported",
    "SMS over NAS not supported",
};
const field_meta mm::hf_sms_requested = {
    "SMS requested",
    "nas.nr.mm.sms_requested",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_sms_requested,
    nullptr,
    0x01,
};


extern const true_false_string mm::tfs_security_context_types = {
    "Mapped security context (for KSIASME)",
    "Native security context (for KSIAMF)",
};

const field_meta mm::hf_tsc = {
    "Type of security context flag (TSC)",
    "nas.nr.mm.tsc",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_security_context_types,
    nullptr,
    0x08,
};


const field_meta mm::hf_sal_num_e = {
    "Number of elements",
    "nas.nr.mm.sal_num_e",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x1f,
};

/* *     9.11.3.47    Request type */
const val_string mm::request_type_values[] = {
    {0x01, "Initial request"},
    {0x02, "Existing PDU session"},
    {0x03, "Initial emergency request"},
    {0x04, "Existing emergency PDU session"},
    {0x05, "Modification request"},
    {0x07, "Reserved"},
    {0, nullptr},
};

/* *    9.11.3.48    S1 UE network capability */
/* See subclause 9.9.3.34 in 3GPP TS 24.301 */

/* *   9.11.3.48A    S1 UE security capability */
/*See subclause 9.9.3.36 in 3GPP TS 24.301 */

/* *     9.11.3.49    Service area list */

extern const val_string mm::tac_list_values[] = {
    {0x00, "list of TACs belonging to one PLMN, with non-consecutive TAC values"},
    {0x01, "list of TACs belonging to one PLMN, with consecutive TAC values"},
    {0x02, "list of TAIs belonging to different PLMNs"},
    {0x03, "All TAIs belonging to the PLMN are in the allowed area"},
    {0, nullptr},
};

const field_meta mm::hf_element = {
    "Message Elements",
    "nas.nr.message_elements",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

extern const message_meta mm::msgs[] = {
    {0x41, "Registration request", dissect_registration_req, nullptr},
    {0x42, "Registration accept", dissect_registration_accept, nullptr},
    {0x43, "Registration complete", dissect_registration_complete, nullptr},
    {0x44, "Registration reject", dissect_registration_rej, nullptr},
    {0x45, "Deregistration request (UE originating)", dissect_dereg_req_ue_orig, nullptr},
    {0x46, "Deregistration accept (UE originating)", nullptr, nullptr},
    {
        0x47,
        "Deregistration request (UE terminated)",
        dissect_dereg_req_ue_term,
        nullptr,
    },
    {0x48, "Deregistration accept (UE terminated)", nullptr, nullptr},

    {0x49, "Not used in current version", no_dissect, nullptr},
    {0x4a, "Not used in current version", no_dissect, nullptr},
    {0x4b, "Not used in current version", no_dissect, nullptr},

    {0x4c, "Service request", dissect_service_request, nullptr},
    {0x4d, "Service reject", dissect_service_reject, nullptr},
    {0x4e, "Service accept", dissect_service_accept, nullptr},

    {0x4f, "Not used in current version", no_dissect, nullptr},
    {0x50, "Not used in current version", no_dissect, nullptr},
    {0x51, "Not used in current version", no_dissect, nullptr},
    {0x52, "Not used in current version", no_dissect, nullptr},
    {0x53, "Not used in current version", no_dissect, nullptr},

    {0x54, "Configuration update command", dissect_config_update_cmd, nullptr},
    {0x55, "Configuration update complete", dissect_config_update_cmpl, nullptr},
    {0x56, "Authentication request", authentication_request, nullptr},
    {0x57, "Authentication response", authentication_resp, nullptr},
    {0x58, "Authentication reject", authentication_reject, nullptr},
    {0x59, "Authentication failure", authentication_failure, nullptr},

    {0x5a, "Authentication result", authentication_result, nullptr},
    {0x5b, "Identity request", dissect_identity_request, nullptr},
    {0x5c, "Identity response", dissect_identity_resp, nullptr},
    {0x5d, "Security mode command", dissect_security_mode_cmd, nullptr},
    {0x5e, "Security mode complete", dissect_security_mode_cmpl, nullptr},
    {0x5f, "Security mode reject", dissect_security_mode_reject, nullptr},

    {0x60, "Not used in current version", no_dissect, nullptr},
    {0x61, "Not used in current version", no_dissect, nullptr},
    {0x62, "Not used in current version", no_dissect, nullptr},
    {0x63, "Not used in current version", no_dissect, nullptr},
    {0x64, "5GMM status", dissect_mm_status, nullptr},
    {0x65, "Notification", dissect_notification, nullptr},
    {0x66, "Notification response", dissect_notification_resp, nullptr},
    {0x67, "UL NAS transport", dissect_ul_nas_transp, nullptr},
    {0x68, "DL NAS transport", dissect_dl_nas_transp, nullptr},
    {0, nullptr, nullptr, nullptr},
};

// Allowed NSSAI    NSSAI     9.11.3.37
extern const element_meta mm::allowed_nssai = {
    0x15,
    "Allowed NSSAI",
    dissect_allowed_nssai,
    nullptr,
};

// 9.11.3.9
extern const element_meta mm::tracking_area_id_list = {
    0x54,
    "5GS tracking area identity list - TAI list",
    dissect_tracking_area_id_list,
    nullptr,
};

// PDU session reactivation result   9.11.3.42
extern const element_meta mm::pdu_ses_react_res = {
    0x26,
    "PDU session reactivation result",
    dissect_pdu_session_reactive_result,
    nullptr,
};

/* 9.11.3.44    PDU session status */
extern const element_meta mm::pdu_ses_status = {
    0x50,
    "PDU session status",
    dissect_pdu_session_status,
    nullptr,
};

extern const field_meta mm::hfm_nas_eps_nas_ksi = { // NOLINT
    "NAS key set identifier",
    "nas_eps.emm.nas_key_set_id",
    ft::ft_uint8,
    fd::base_dec,
    nas_ksi_values,
    nullptr,
    nullptr,
    0x07,
};
const field_meta* mm::hf_nas_eps_nas_ksi = &hfm_nas_eps_nas_ksi;

// NAS message container 9.11.3.33
extern const element_meta mm::nas_msg_container = {
    0x71,
    "NAS message container",
    dissect_nas_msg_container,
    nullptr,
};

// EPS bearer context status	9.11.3.59
extern const element_meta mm::eps_bearer_ctx_status = {
    0x60,
    "EPS bearer context status",
    dissect_eps_bearer_context_status,
    nullptr,
};

const field_meta mm::hf_sd = {
    "Slice differentiator (SD)",
    "nas.nr.mm.mm_sd",
    ft::ft_uint24,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta mm::hf_sst = {
    "Slice/service type (SST)",
    "nas.nr.mm.sst",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const true_false_string mm::tfs_follow_on_request = {
    "Follow-on request pending",
    "No follow-on request pending",
};

const field_meta mm::hf_follow_on_req = {
    "Follow-On Request bit (FOR)",
    "nas.nr.mm.for",
    ft::ft_boolean,
    fd::sep_dot,
    nullptr,
    &tfs_follow_on_request,
    nullptr,
    0x08,
};
