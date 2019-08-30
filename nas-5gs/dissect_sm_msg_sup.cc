#include "dissect_sm_msg.hh"

// using namespace nas;

extern const message_meta sm::msgs[] = {
    {0xc1, "PDU session establishment request", pdu_ses_est_req},
    {0xc2, "PDU session establishment accept", pdu_ses_est_acc},
    {0xc3, "PDU session establishment reject", pdu_ses_est_rej},

    {0xc4, "Not used in current version", no_dissect},
    {0xc5, "PDU session authentication command", pdu_ses_auth_cmd},

    {0xc6, "PDU session authentication complete", pdu_ses_auth_comp},
    {0xc7, "PDU session authentication result", no_dissect},
    {0xc8, "Not used in current version", no_dissect},

    {0xc9, "PDU session modification request", pdu_ses_mod_req},
    {0xca, "PDU session modification reject", pdu_ses_mod_rej},
    {0xcb, "PDU session modification command", pdu_ses_mod_cmd},
    {0xcc, "PDU session modification complete", pdu_ses_mod_comp},
    {0xcd, "PDU session modification command reject", pdu_ses_mod_com_rej},

    {0xce, "Not used in current version", no_dissect},
    {0xcf, "Not used in current version", no_dissect},
    {0xd0, "Not used in current version", no_dissect},

    {0xd1, "PDU session release request", pdu_ses_rel_req},
    {0xd2, "PDU session release reject", pdu_ses_rel_rej},
    {0xd3, "PDU session release command", pdu_ses_rel_cmd},
    {0xd4, "PDU session release complete", pdu_ses_rel_comp},

    {0xd5, "Not used in current version", no_dissect},

    {0xd6, "5GSM status", sm_status},
    {0, nullptr, nullptr},
};

const element_meta sm::sm_cause = {
    0xff,
    "5GSM cause",
    dissect_sm_cause,
};
const element_meta sm::ext_pco = {
    0x7B,
    "Extended protocol configuration options",
    dissect_ext_pco,
};
const element_meta sm::eap_msg = {
    0x78,
    "EAP message",
    dissect_eap_msg,
};
const element_meta sm::authorized_qos_rules = {
    0x7A,
    "Authorized QoS rules",
    dissect_authorized_qos_rules,
};
const element_meta sm::mapped_eps_b_cont = {
    0x75,
    "Mapped EPS bearer contexts",
    dissect_mapped_eps_b_cont,
};
const element_meta sm::backoff_gprs_timer3 = {
    0x37,
    "GPRS timer - Back-off timer value",
    dissect_backoff_gprs_timer3,
};
const element_meta sm::sm_cap = {
    0x28,
    "5GSM capability",
    dissect_sm_cap,
};
const element_meta sm::max_num_sup_kpt_flt = {
    0x55,
    "Maximum number of suuported packet filter",
    dissect_max_num_sup_kpt_flt,
};
const element_meta sm::ses_ambr = {
    0x2A,
    "Session AMBR",
    dissect_ses_ambr,
};
const element_meta sm::rq_gprs_timer = {
    0x56,
    "GPRS timer- PDU session release time",
    dissect_rq_gprs_timer,
};
const element_meta sm::always_on_pdu_ses_ind = {
    0x80,
    "Always-on PDU session indication",
    dissect_always_on_pdu_ses_ind,
};

const field_meta sm::hf_sm_ses_ambr_dl_unit = {
    "Unit for Session-AMBR for downlink",
    "nas_5gs.sm.unit_for_session_ambr_dl",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_sm_unit_for_session_ambr_values),
    nullptr,
    nullptr,
    0x0,
};
const field_meta sm::hf_sm_ses_ambr_ul_unit = {
    "Unit for Session-AMBR for uplink",
    "nas_5gs.sm.unit_for_session_ambr_ul",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_sm_unit_for_session_ambr_values),
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
};
