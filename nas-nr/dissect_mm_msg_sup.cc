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


extern const true_false_string mm::tfs_mm_tsc = {
    "Mapped security context (for KSIASME)",
    "Native security context (for KSIAMF)",
};

const field_meta mm::hf_tsc = {
    "Type of security context flag (TSC)",
    "nas.nr.mm.tsc",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_mm_tsc,
    nullptr,
    0x08,
};


const field_meta mm::hf_tsc_h1 = {
    "Type of security context flag (TSC)",
    "nas.nr.mm.tsc.h1",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_mm_tsc,
    nullptr,
    0x80,
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

const field_meta mm::hf_nas_key_set_id_h1 = {
    "NAS key set identifier",
    "nas.nr.mm.nas_key_set_id.h1",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x70,
};

const field_meta mm::hf_mm_sst = {
    "Slice/service type (SST)",
    "nas.nr.mm.sst",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta hfm_mm_sd = { // NOLINT
    "Slice differentiator (SD)",
    "nas.nr.mm.mm_sd",
    ft::ft_uint24,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta hfm_mm_mapped_conf_sst = { // NOLINT
    "Mapped configured SST",
    "nas.nr.mm.mapped_conf_sst",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta hfm_mm_mapped_conf_ssd = { // NOLINT
    "Mapped configured SD",
    "nas.nr.mm.mapped_conf_ssd",
    ft::ft_uint24,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};


const true_false_string mm_switch_off_tfs = {
    "Switch off",
    "Normal de-registration",
};
const field_meta hfm_mm_switch_off = { // NOLINT
    "Switch off",
    "nas.nr.mm.switch_off",
    ft::ft_boolean,
    8,
    nullptr,
    &mm_switch_off_tfs,
    nullptr,
    0x08,
};

const true_false_string mm_re_reg_req_tfs = {
    "re-registration required",
    "re-registration not required",
};
const field_meta hfm_mm_re_reg_req = { // NOLINT
    "Re-registration required",
    "nas.nr.mm.re_reg_req",
    ft::ft_boolean,
    8,
    nullptr,
    &mm_re_reg_req_tfs,
    nullptr,
    0x04,
};


const field_meta mm::hfm_mm_conf_upd_ind_ack_b0 = {
    "Acknowledgement",
    "nas.nr.mm.conf_upd_ind.ack",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_requested_not_requested,
    nullptr,
    0x01,
};

const field_meta mm::hfm_nas_5gs_mm_conf_upd_ind_red_b1 = {
    "Registration",
    "nas.nr.mm.conf_upd_ind.red",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_requested_not_requested,
    nullptr,
    0x02,
};

extern const val_string mm::mm_type_of_enc_algo_vals[] = {
    {0x0, "5G-EA0 (null ciphering algorithm)"},
    {0x1, "128-5G-EA1"},
    {0x2, "128-5G-EA2"},
    {0x3, "128-5G-EA3"},
    {0x4, "5G-EA4"},
    {0x5, "5G-EA5"},
    {0x6, "5G-EA6"},
    {0x7, "5G-EA7"},
    {0, nullptr},
};
const field_meta mm::hfm_mm_nas_sec_algo_enc = {
    "Type of ciphering algorithm",
    "nas.nr.mm.nas_sec_algo_enc",
    ft::ft_uint8,
    fd::base_dec,
    mm_type_of_enc_algo_vals,
    nullptr,
    nullptr,
    0xf0,
};


const field_meta mm::hfm_mm_s1_mode_b0 = {
    "S1 mode",
    "nas.nr.mm.s1_mode_b0",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_requested_not_requested,
    nullptr,
    0x01,
};

const field_meta mm::hfm_mm_ho_attach_b1 = {
    "HO attach",
    "nas.nr.mm.ho_attach_b1",
    ft::ft_boolean,
    8,
    nullptr,
    &nas::tfs_supported_not_supported,
    nullptr,
    0x02,
};

const field_meta mm::hfm_mm_lpp_cap_b2 = {
    "LTE Positioning Protocol (LPP) capability",
    "nas.nr.mm.lpp_cap_b2",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_requested_not_requested,
    nullptr,
    0x04,
};


const field_meta mm::hfm_mm_odd_even = {
    "Odd/even indication",
    "nas.nr.mm.odd_even",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_odd_even,
    nullptr,
    0x08,
};
#if 0
const field_meta mm::hfm_mm_length = {
    "Length",
    "nas.nr.mm.length",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
#endif

const field_meta mm::hfm_mm_abba = {
    "ABBA Contents",
    "nas.nr.mm.abba_contents",
    ft::ft_uint16,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x00,
};
const field_meta mm::hfm_mm_pld_cont = {
    "Payload container",
    "nas.nr.mm.pld_cont",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

/* *     9.11.3.47    Request type */
const val_string mm::mm_req_type_vals[] = {
    {0x01, "Initial request"},
    {0x02, "Existing PDU session"},
    {0x03, "Initial emergency request"},
    {0x04, "Existing emergency PDU session"},
    {0x05, "Modification request"},
    {0x07, "Reserved"},
    {0, nullptr},
};
const field_meta mm::hfm_mm_req_type = {
    "Request type",
    "nas.nr.mm.req_typ",
    ft::ft_uint8,
    fd::base_dec,
    mm_req_type_vals,
    nullptr,
    nullptr,
    0x0f,
};


const field_meta mm::hfm_mm_5g_ea0 = {
    "5G-EA0",
    "nas.nr.mm.5g_ea0",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x80,
};

const field_meta mm::hfm_mm_128_5g_ea1 = {
    "128-5G-EA1",
    "nas.nr.mm.128_5g_ea1",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x40,
};

const field_meta mm::hfm_mm_128_5g_ea2 = {
    "128-5G-EA2",
    "nas.nr.mm.128_5g_ea2",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x20,
};

const field_meta mm::hfm_mm_128_5g_ea3 = {
    "128-5G-EA3",
    "nas.nr.mm.128_5g_ea3",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x10,
};

const field_meta mm::hfm_mm_5g_ea4 = {
    "5G-EA4",
    "nas.nr.mm.5g_ea4",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x08,
};

const field_meta mm::hfm_mm_5g_ea5 = {
    "5G-EA5",
    "nas.nr.mm.5g_ea5",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x04,
};

const field_meta mm::hfm_mm_5g_ea6 = {
    "5G-EA6",
    "nas.nr.mm.5g_ea6",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x02,
};

const field_meta mm::hfm_mm_5g_ea7 = {
    "5G-EA7",
    "nas.nr.mm.5g_ea7",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x01,
};

const field_meta mm::hfm_mm_5g_ia0 = {
    "5G-IA0",
    "nas.nr.mm.ia0",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x80,
};

const field_meta mm::hfm_mm_5g_128_ia1 = {
    "128-5G-IA1",
    "nas.nr.mm.5g_128_ia1",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x40,
};

const field_meta mm::hfm_mm_5g_128_ia2 = {
    "128-5G-IA2",
    "nas.nr.mm.5g_128_ia2",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x20,
};

const field_meta mm::hfm_mm_5g_128_ia3 = {
    "128-5G-IA3",
    "nas.nr.mm.5g_128_ia4",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x10,
};

const field_meta mm::hfm_mm_5g_ia4 = {
    "5G-IA4",
    "nas.nr.mm.5g_128_ia4",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x08,
};

const field_meta mm::hfm_nas_5gs_mm_5g_ia5 = {
    "5G-IA5",
    "nas.nr.mm.5g_ia5",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x04,
};

const field_meta mm::hfm_nas_5gs_mm_5g_ia6 = {
    "5G-IA6",
    "nas.nr.mm.5g_ia6",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x02,
};

const field_meta mm::hfm_nas_5gs_mm_5g_ia7 = {
    "5G-IA7",
    "nas.nr.mm.5g_ia7",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x01,
};

const field_meta mm::hfm_nas_5gs_mm_eea0 = {
    "EEA0",
    "nas.nr.mm.eea0",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x80,
};

const field_meta mm::hfm_nas_5gs_mm_128eea1 = {
    "128-EEA1",
    "nas.nr.mm.128eea1",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x40,

};

const field_meta mm::hfm_nas_5gs_mm_128eea2 = {
    "128-EEA2",
    "nas.nr.mm.128eea2",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x20,
};

const field_meta mm::hfm_nas_5gs_mm_eea3 = {
    "128-EEA3",
    "nas.nr.mm.eea3",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x10,

};

const field_meta mm::hfm_nas_5gs_mm_eea4 = {
    "EEA4",
    "nas.nr.mm.eea4",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x08,
};

const field_meta mm::hfm_nas_5gs_mm_eea5 = {
    "EEA5",
    "nas.nr.mm.eea5",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x04,

};
const field_meta mm::hfm_nas_5gs_mm_eea6 = {
    "EEA6",
    "nas.nr.mm.eea6",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x02,

};
const field_meta mm::hfm_nas_5gs_mm_eea7 = {
    "EEA7",
    "nas.nr.mm.eea7",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x01,

};
const field_meta mm::hfm_nas_5gs_mm_eia0 = {
    "EIA0",
    "nas.nr.mm.eia0",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x80,

};
const field_meta mm::hfm_nas_5gs_mm_128eia1 = {
    "128-EIA1",
    "nas.nr.mm.128eia1",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x40,

};
const field_meta mm::hfm_nas_5gs_mm_128eia2 = {
    "128-EIA2",
    "nas.nr.mm.128eia2",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x20,
};
const field_meta mm::hfm_nas_5gs_mm_eia3 = {
    "128-EIA3",
    "nas.nr.mm.eia3",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x10,

};
const field_meta mm::hfm_nas_5gs_mm_eia4 = {
    "EIA4",
    "nas.nr.mm.eia4",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x08,

};
const field_meta mm::hfm_nas_5gs_mm_eia5 = {
    "EIA5",
    "nas.nr.mm.eia5",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x04,

};
const field_meta mm::hfm_nas_5gs_mm_eia6 = {
    "EIA6",
    "nas.nr.mm.eia6",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x02,

};
const field_meta mm::hfm_nas_5gs_mm_eia7 = {
    "EIA7",
    "nas.nr.mm.eia7",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x01,
};



/* *    9.11.3.48    S1 UE network capability */

/* See subclause 9.9.3.34 in 3GPP TS 24.301 */

/* *   9.11.3.48A    S1 UE security capability */

/*See subclause 9.9.3.36 in 3GPP TS 24.301 */

/* *     9.11.3.49    Service area list */

const true_false_string mm::tfs_sal_al_t = {
    "TAIs in the list are in the non-allowed area",
    "TAIs in the list are in the allowed area",
};

const field_meta mm::hf_mm_sal_al_t = {
    "Allowed type",
    "nas.nr.mm.sal_al_t",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_sal_al_t,
    nullptr,
    0x80,

};

extern const val_string mm::mm_sal_t_li_values[] = {
    {0x00, "list of TACs belonging to one PLMN, with non-consecutive TAC values"},
    {0x01, "list of TACs belonging to one PLMN, with consecutive TAC values"},
    {0x02, "list of TAIs belonging to different PLMNs"},
    {0x03, "All TAIs belonging to the PLMN are in the allowed area"},
    {0, nullptr},
};

const field_meta mm::hf_mm_sal_t_li      = {
    "Type of list",
    "nas.nr.mm.sal_t_li",
    ft::ft_uint8,
    fd::base_dec,
    mm_sal_t_li_values,
    nullptr,
    nullptr,
    0x60,
};
#if 0
const field_meta mm::hf_proc_trans_id = {
    "Procedure transaction identity",
    "nas.nr.proc_trans_id",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
#endif
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
    {0x47,
     "Deregistration request (UE terminated)",
     dissect_dereg_req_ue_term,
     nullptr},
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
#if 0
extern const field_meta mm::hf_nas_5gs_spare_b7 = {
    "Spare",
    "nas.nr.spare_b7",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x80,
};
extern const field_meta mm::hf_nas_5gs_spare_b3 = {
    "Spare",
    "nas.nr.spare_b3",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x04,
};
extern const field_meta mm::hf_nas_5gs_spare_b2 = {
    "Spare",
    "nas.nr.spare_b2",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x02,
};
#endif

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
#if 0
extern const field_meta mm::hf_mm_length = {
    "Length",
    "nas.nr.mm.length",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
#endif

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


/*
 * 9.9.3.21 NAS key set identifier
 */
/*
 * Type of security context flag (TSC) (octet 1)
 */
extern const true_false_string mm::tfs_eps_tsc = {
    "Mapped security context (for KSIsgsn)",
    "Native security context (for KSIasme)",
};
extern const field_meta mm::hfm_nas_eps_tsc = {
    "Type of security context flag (TSC)",
    "nas_eps.emm.tsc",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_eps_tsc,
    nullptr,
    0x08,
};
const field_meta* mm::hf_nas_eps_tsc = &hfm_nas_eps_tsc;


extern const field_meta mm::hfm_nas_eps_nas_ksi = { // NOLINT
    "NAS key set identifier",
    "nas_eps.emm.nas_key_set_id",
    ft::ft_uint8,
    fd::base_dec,
    nas_eps_emm_nas_ksi_values,
    nullptr,
    nullptr,
    0x00,
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

const field_meta mm::hf_mapped_conf_sst = {
    "Mapped configured SST",
    "nas.nr.mm.mapped_conf_sst",
    ft::ft_uint8,
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

const true_false_string mm::tfs_follow_on_req = {
    "Follow-on request pending",
    "No follow-on request pending",
};

const field_meta mm::hf_follow_on_req = {
    "Follow-On Request bit (FOR)",
    "nas.nr.mm.for",
    ft::ft_boolean,
    fd::sep_dot,
    nullptr,
    &tfs_follow_on_req,
    nullptr,
    0x08,
};
