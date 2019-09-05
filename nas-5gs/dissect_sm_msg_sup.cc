#include "dissect_sm_msg.hh"
#include "gsm.hh"
#include "common/common.hh"
#include "dissect_nas5g.hh"

using namespace cmn;
using namespace sm;

extern const message_meta sm::msgs[] = {
    {0xc1, "PDU session establishment request", dissect_pdu_ses_est_req, nullptr},
    {0xc2, "PDU session establishment accept", dissect_pdu_ses_est_acc, nullptr},
    {0xc3, "PDU session establishment reject", dissect_pdu_ses_est_rej, nullptr},

    {0xc4, "Not used in current version", no_dissect, nullptr},
    {0xc5, "PDU session authentication command", dissect_pdu_ses_auth_cmd, nullptr},

    {0xc6, "PDU session authentication complete", dissect_pdu_ses_auth_comp, nullptr},
    {0xc7, "PDU session authentication result", no_dissect, nullptr},
    {0xc8, "Not used in current version", no_dissect, nullptr},

    {0xc9, "PDU session modification request", dissect_pdu_ses_mod_req, nullptr},
    {0xca, "PDU session modification reject", dissect_pdu_ses_mod_rej, nullptr},
    {0xcb, "PDU session modification command", dissect_pdu_ses_mod_cmd, nullptr},
    {0xcc, "PDU session modification complete", dissect_pdu_ses_mod_comp, nullptr},
    {0xcd, "PDU session modification command reject", dissect_pdu_ses_mod_com_rej, nullptr},

    {0xce, "Not used in current version", no_dissect, nullptr},
    {0xcf, "Not used in current version", no_dissect, nullptr},
    {0xd0, "Not used in current version", no_dissect, nullptr},

    {0xd1, "PDU session release request", dissect_pdu_ses_rel_req, nullptr},
    {0xd2, "PDU session release reject", dissect_pdu_ses_rel_rej, nullptr},
    {0xd3, "PDU session release command", dissect_pdu_ses_rel_cmd, nullptr},
    {0xd4, "PDU session release complete", dissect_pdu_ses_rel_comp, nullptr},

    {0xd5, "Not used in current version", no_dissect, nullptr},

    {0xd6, "5GSM status", dissect_sm_status, nullptr},
    {0, nullptr, nullptr, nullptr},
};

// 5GSM cause 9.11.4.2
const element_meta sm::sm_cause = {
    0x59,
    "5GSM cause",
    dissect_sm_cause,
    nullptr,
};

// Extended protocol configuration options  9.11.4.6
const element_meta sm::ext_pco = {
    0x7B,
    "Extended protocol configuration options",
    dissect_ext_pco,
    nullptr,
};

// EAP message 9.11.2.2
const element_meta sm::eap_msg = {
    0x78,
    "EAP message",
    cmn::dissect_eap_msg,
    nullptr,
};

// Authorized QoS rules QoS rules 9.11.4.13
const element_meta sm::authorized_qos_rules = {
    0x7A,
    "Authorized QoS rules",
    dissect_authorized_qos_rules,
    nullptr,
};

// Mapped EPS  bearer contexts     9.11.4.5
const element_meta sm::mapped_eps_b_cont = {
    0x75,
    "Mapped EPS bearer contexts",
    dissect_mapped_eps_b_cont,
    nullptr,
};

// Back-off timer value    GPRS timer 3 9.11.2.25
const element_meta sm::backoff_gprs_timer3 = {
    0x37,
    "GPRS timer 3 - Back-off timer value",
    dissect_gprs_timer3,
    nullptr,
};

// 5GSM capability 9.11.4.1
const element_meta sm::sm_cap = {
    0x28,
    "5GSM capability",
    dissect_sm_cap,
    nullptr,
};

// Maximum number of suuported packet filter 9.11.4.9
const element_meta sm::max_num_sup_kpt_flt = {
    0x55,
    "Maximum number of suuported packet filter",
    dissect_max_num_sup_kpt_flt,
    nullptr,
};

// Session-AMBR 9.11.4.14
const element_meta sm::ses_ambr = {
    0x2A,
    "Session AMBR",
    dissect_ses_ambr,
    nullptr,
};

// RQ timer value    GPRS timer 9.11.2.3
const element_meta sm::rq_gprs_timer = {
    0x56,
    "GPRS timer- PDU session release time",
    dissect_gprs_timer,
    nullptr,
};

// Always-on PDU session indication 9.11.4.3
const element_meta sm::always_on_pdu_ses_ind = {
    0x80,
    "Always-on PDU session indication",
    dissect_always_on_pdu_ses_ind,
    nullptr,
};

//  *      9.11.4.14    Session-AMBR
extern const value_string sm::sm_unit_for_session_ambr_values[] = {
    {0x00, "value is not used"},
    {0x01, "value is incremented in multiples of 1 Kbps"},
    {0x02, "value is incremented in multiples of 4 Kbps"},
    {0x03, "value is incremented in multiples of 16 Kbps"},
    {0x04, "value is incremented in multiples of 64 Kbps"},
    {0x05, "value is incremented in multiples of 256 kbps"},
    {0x06, "value is incremented in multiples of 1 Mbps"},
    {0x07, "value is incremented in multiples of 4 Mbps"},
    {0x08, "value is incremented in multiples of 16 Mbps"},
    {0x09, "value is incremented in multiples of 64 Mbps"},
    {0x0a, "value is incremented in multiples of 256 Mbps"},
    {0x0b, "value is incremented in multiples of 1 Gbps"},
    {0x0c, "value is incremented in multiples of 4 Gbps"},
    {0x0d, "value is incremented in multiples of 16 Gbps"},
    {0x0e, "value is incremented in multiples of 64 Gbps"},
    {0x0f, "value is incremented in multiples of 256 Gbps"},
    {0x10, "value is incremented in multiples of 1 Tbps"},
    {0x11, "value is incremented in multiples of 4 Tbps"},
    {0x12, "value is incremented in multiples of 16 Tbps"},
    {0x13, "value is incremented in multiples of 64 Tbps"},
    {0x14, "value is incremented in multiples of 256 Tbps"},
    {0x15, "value is incremented in multiples of 1 Pbps"},
    {0x16, "value is incremented in multiples of 4 Pbps"},
    {0x17, "value is incremented in multiples of 16 Pbps"},
    {0x18, "value is incremented in multiples of 64 Pbps"},
    {0x19, "value is incremented in multiples of 256 Pbps"},
    {0, nullptr},
};

const field_meta sm::hf_sm_ses_ambr_dl_unit = {
    "Unit for Session-AMBR for downlink",
    "nas_5gs.sm.unit_for_session_ambr_dl",
    ft::ft_uint8,
    fd::base_dec,
    sm_unit_for_session_ambr_values,
    nullptr,
    nullptr,
    0x0,
};
const field_meta sm::hf_sm_ses_ambr_ul_unit = {
    "Unit for Session-AMBR for uplink",
    "nas_5gs.sm.unit_for_session_ambr_ul",
    ft::ft_uint8,
    fd::base_dec,
    (sm_unit_for_session_ambr_values),
    nullptr,
    nullptr,
    0x0,
};
const field_meta sm::hf_sm_ses_ambr_dl = {
    "Session-AMBR for downlink",
    "nas_5gs.sm.session_ambr_dl",
    ft::ft_uint16,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta sm::hf_sm_ses_ambr_ul = {
    "Session-AMBR for uplink",
    "nas_5gs.sm.session_ambr_ul",
    ft::ft_uint16,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const true_false_string sm::tfs_allowed_not_allowed = {
    "Allowed",
    "Not Allowed",
};

const element_meta sm::allowed_ssc_mode = {
    0xf0,
    "Allowed SSC mode",
    dissect_allowed_ssc_mode,
    nullptr,
};

/* * 9.11.4.2    5GSM cause */
extern const value_string sm::sm_cause_values[] = {
    {0x1a, "Insufficient resources"},
    {0x1b, "Missing or unknown DNN"},
    {0x1c, "Unknown PDU session type"},
    {0x1d, "User authentication or authorization failed"},
    {0x1f, "Request rejected, unspecified"},
    {0x22, "Service option temporarily out of order"},
    {0x23, "PTI already in use"},
    {0x24, "Regular deactivation"},
    {0x27, "Reactivation requested"},
    {0x2b, "Invalid PDU session identity"},
    {0x2c, "Semantic errors in packet filter(s)"},
    {0x2d, "Syntactical error in packet filter(s)"},
    {0x2e, "Out of LADN service area"},
    {0x2f, "PTI mismatch"},
    {0x32, "PDU session type Ipv4 only allowed"},
    {0x33, "PDU session type Ipv6 only allowed"},
    {0x36, "PDU session does not exist"},
    {0x43, "Insufficient resources for specific slice and DNN"},
    {0x44, "Not supported SSC mode"},
    {0x45, "Insufficient resources for specific slice"},
    {0x46, "Missing or unknown DNN in a slice"},
    {0x51, "Invalid PTI value"},
    {0x52, "Maximum data rate per UE for user-plane integrity protection is too low"},
    {0x53, "Semantic error in the QoS operation"},
    {0x54, "Syntactical error in the QoS operation"},
    {0x55, "Invalid mapped EPS bearer identity"},
    {0x5f, "Semantically incorrect message"},
    {0x60, "Invalid mandatory information"},
    {0x61, "Message type non - existent or not implemented"},
    {0x62, "Message type not compatible with the protocol state"},
    {0x63, "Information element non - existent or not implemented"},
    {0x64, "Conditional IE error"},
    {0x65, "Message not compatible with the protocol state"},
    {0x6f, "Protocol error, unspecified"},
    {0, nullptr},
};
const field_meta sm::hf_sm_cause = {
    "5GSM cause",
    "nas_5gs.sm.5gsm_cause",
    ft::ft_uint8,
    fd::base_dec,
    (sm_cause_values),
    nullptr,
    nullptr,
    0x0,
};


extern const value_string sm::rule_operation_code_values[] = {
    {0x0, "Reserved"},
    {0x1, "Create new QoS rule"},
    {0x2, "Delete existing QoS rule"},
    {0x3, "Modify existing QoS rule and add packet filters"},
    {0x4, "Modify existing QoS rule and replace packet filters"},
    {0x5, "Modify existing QoS rule and delete packet filters"},
    {0x6, "Modify existing QoS rule without modifying packet filters"},
    {0x7, "Reserved"},
    {0, nullptr},
};

extern const value_string sm::sm_pf_type_values[] = {
    {0x01, "Match-all type"},
    {0x10, "IPv4 remote address type"},
    {0x11, "IPv4 local address type"},
    {0x21, "IPv6 remote address/prefix length type"},
    {0x23, "IPv6 local address/prefix length type"},
    {0x30, "Protocol identifier/Next header type"},
    {0x40, "Single local port type"},
    {0x41, "Local port range type"},
    {0x50, "Single remote port type"},
    {0x51, "Remote port range type"},
    {0x60, "Security parameter index type"},
    {0x70, "Type of service/Traffic class type"},
    {0x80, "Flow label type"},
    {0x81, "Destination MAC address type"},
    {0x82, "Source MAC address type"},
    {0x83, "802.1Q C-TAG VID type"},
    {0x84, "802.1Q S-TAG VID type"},
    {0x85, "802.1Q C-TAG PCP/DEI type"},
    {0x86, "802.1Q S-TAG PCP/DEI type"},
    {0x87, "Ethertype type"},
    {0, nullptr},
};

extern const value_string sm::sm_pkt_flt_dir_values[] = {
    {0x00, "Reserved"},
    {0x01, "Downlink only"},
    {0x02, "Uplink only"},
    {0x03, "Bidirectional"},
    {0, nullptr},
};

extern const value_string sm::rule_param_cont[] = {
    {0x0, "Reserved"},
    {0x01, "5QI 1"},
    {0x02, "5QI 2"},
    {0x03, "5QI 3"},
    {0x04, "5QI 4"},
    {0x05, "5QI 5"},
    {0x06, "5QI 6"},
    {0x07, "5QI 7"},
    {0x08, "5QI 8"},
    {0x09, "5QI 9"},
    {0, nullptr},
};

const field_meta sm::hf_sm_dqr = {
    "DQR",
    "nas_5gs.sm.dqr",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_sm_dqr),
    nullptr,
    0x10,
};
const field_meta sm::hf_sm_rop = {
    "Rule operation code",
    "nas_5gs.sm.rop",
    ft::ft_uint8,
    fd::base_dec,
    (rule_operation_code_values),
    nullptr,
    nullptr,
    0xe0,
};
const field_meta sm::hf_sm_nof_pkt_filters = {
    "Number of packet filters",
    "nas_5gs.sm.nof_pkt_filters",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0f,
};

const field_meta sm::hf_sm_qos_rule_id = {
    "QoS rule identifier",
    "nas_5gs.sm.qos_rule_id",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta sm::hf_sm_length = {
    "Length",
    "nas_5gs.sm.length",
    ft::ft_uint16,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta sm::hf_sm_pkt_flt_id = {
    "Packet filter identifier",
    "nas_5gs.sm.pkt_flt_id",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0f,
};
const field_meta sm::hf_sm_pkt_flt_dir = {
    "Packet filter direction",
    "nas_5gs.sm.pkt_flt_dir",
    ft::ft_uint8,
    fd::base_dec,
    (sm_pkt_flt_dir_values),
    nullptr,
    nullptr,
    0x30,
};
const field_meta sm::hf_sm_pf_len = {
    "Length",
    "nas_5gs.sm.pf_len",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta sm::hf_sm_pf_type = {
    "Packet filter component type",
    "nas_5gs.sm.pf_type",
    ft::ft_uint8,
    fd::base_dec,
    (sm_pf_type_values),
    nullptr,
    nullptr,
    0x0,
};

const field_meta sm::hf_pdu_addr_ipv4 = {
    "PDU address information",
    "nas_5gs.sm.pdu_addr_inf_ipv4",
    ft::ft_uint32, // FT_IPv4,
    fd::ipv4,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta sm::hf_sm_qos_rule_precedence = {
    "QoS rule precedence",
    "nas_5gs.sm.qos_rule_precedence",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

/*
 *     9.11.4.8 Mapped EPS bearer contexts
 */
extern const value_string sm::sm_mapd_eps_b_cont_opt_code_values[] = {
    {0x0, "Reserved"},
    {0x01, "Create new EPS bearer"},
    {0x02, "Delete existing EPS bearer"},
    {0x03, "Modify existing EPS bearer"},
    {0, nullptr},
};

extern const value_string sm::sm_mapd_eps_b_cont_deb_values[] = {
    {0x0, "the EPS bearer is not the default EPS bearer."},
    {0x01, "the EPS bearer is the default EPS bearer"},
    {0, nullptr},
};

extern const value_string sm::sm_mapd_eps_b_cont_e_values[] = {
    {0x0, "parameters list is not included"},
    {0x01, "parameters list is included"},
    {0, nullptr},
};

extern const value_string sm::sm_mapd_eps_b_cont_E_Modify_values[] = {
    {0x0, "previously provided parameters list extension"},
    {0x01, "previously provided parameters list replacement"},
    {0, nullptr},
};

extern const value_string sm::sm_mapd_eps_b_cont_param_id_values[] = {
    {0x01, "Mapped EPS QoS parameters"},
    {0x02, "Mapped extended EPS QoS parameters"},
    {0x03, "Traffic flow template"},
    {0x04, "APN-AMBR"},
    {0x05, "extended APN-AMBR"},
    {0, nullptr},
};

const field_meta sm::hf_sm_mapd_eps_b_cont_opt_code = {
    "Operation code",
    "nas_5gs.sm.mapd_eps_b_cont_opt_code",
    ft::ft_uint8,
    fd::base_dec,
    sm_mapd_eps_b_cont_opt_code_values,
    nullptr,
    nullptr,
    0xc0,
};
const field_meta sm::hf_sm_mapd_eps_b_cont_deb = {
    "DEB bit",
    "nas_5gs.sm.mapd_eps_b_cont_DEB",
    ft::ft_uint8,
    fd::base_dec,
    sm_mapd_eps_b_cont_deb_values,
    nullptr,
    nullptr,
    0x20,
};
const field_meta sm::hf_sm_mapd_eps_b_cont_e = {
    "E bit",
    "nas_5gs.sm.mapd_eps_b_cont_E",
    ft::ft_uint8,
    fd::base_dec,
    sm_mapd_eps_b_cont_e_values,
    nullptr,
    nullptr,
    0x10,
};
const field_meta sm::hf_sm_mapd_eps_b_cont_num_eps_parms = {
    "Number of EPS parameters",
    "nas_5gs.sm.mapd_eps_b_cont_num_eps_parms",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0f,
};
const field_meta sm::hf_sm_mapd_eps_b_cont_e_mod = {
    "E bit",
    "nas_5gs.sm.mapd_eps_b_cont_E_mod",
    ft::ft_uint8,
    fd::base_dec,
    sm_mapd_eps_b_cont_E_Modify_values,
    nullptr,
    nullptr,
    0x10,
};

const field_meta sm::hf_sm_mapd_eps_b_cont_id = {
    "EPS bearer identity",
    "nas_5gs.sm.mapd_eps_b_cont_id",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0xf0,
};
const field_meta sm::hf_sm_mapd_eps_b_cont_num_eps_param_id = {
    "EPS parameter identity",
    "nas_5gs.sm.mapd_eps_b_cont_param_id",
    ft::ft_uint8,
    fd::base_dec,
    sm_mapd_eps_b_cont_param_id_values,
    nullptr,
    nullptr,
    0x0,
};
const field_meta sm::hf_sm_mapd_eps_b_cont_eps_param_cont = {
    "EPS parameter contents",
    "nas_5gs.sm.mapd_eps_b_cont_eps_param_cont",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta sm::hf_sm_rqos_b0 = {
    "Reflective QoS(RqoS)",
    "nas_5gs.sm.rqos",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &nas::tfs_supported_not_supported,
    nullptr,
    0x01,
};

// * 9.11.4.7 Integrity protection maximum data rate
extern const value_string sm::sm_int_prot_max_data_rate_values[] = {
    {0x0, "64 kbps"},
    {0xff, "Full data rate"},
    {0, nullptr},
};

const field_meta sm::hf_sm_int_prot_max_data_rate_ul = {
    "Integrity protection maximum data rate for uplink",
    "nas_5gs.sm.int_prot_max_data_rate_ul",
    ft::ft_uint8,
    fd::base_dec,
    (sm_int_prot_max_data_rate_values),
    nullptr,
    nullptr,
    0x0,
};
const field_meta sm::hf_sm_int_prot_max_data_rate_dl = {
    "Integrity protection maximum data rate for downlink",
    "nas_5gs.sm.int_prot_max_data_rate_dl",
    ft::ft_uint8,
    fd::base_dec,
    (sm_int_prot_max_data_rate_values),
    nullptr,
    nullptr,
    0x0,
};

const field_meta sm::hf_sm_all_ssc_mode_b2 = {
    "SSC mode 3",
    "nas_5gs.sm.all_ssc_mode_b2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &sm::tfs_allowed_not_allowed,
    nullptr,
    0x04,
};
const field_meta sm::hf_sm_all_ssc_mode_b1 = {
    "SSC mode 2",
    "nas_5gs.sm.all_ssc_mode_b1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &sm::tfs_allowed_not_allowed,
    nullptr,
    0x02,
};
const field_meta sm::hf_sm_all_ssc_mode_b0 = {
    "SSC mode 1",
    "nas_5gs.sm.all_ssc_mode_b0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &sm::tfs_allowed_not_allowed,
    nullptr,
    0x01,
};

/*
 *      9.11.4.16    SSC mode
 */

extern const value_string sm::sc_mode_values[] = {
    {0x1, "SSC mode 1"},
    {0x2, "SSC mode 2"},
    {0x3, "SSC mode 3"},
    {0, nullptr},
};

const field_meta sm::hf_sm_sc_mode = {
    "SSC mode",
    "nas_5gs.sm.sc_mode",
    ft::ft_uint8,
    fd::base_dec,
    (sc_mode_values),
    nullptr,
    nullptr,
    0x0f,
};
