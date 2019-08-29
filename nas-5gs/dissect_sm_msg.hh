#pragma once
#include "core.hh"

/* 5GS session management messages */
namespace sm {
__declspec(selectany) extern const dissect_fnc_t no_dissect = nullptr;

int pdu_ses_est_req(dissector d, context* ctx);
int pdu_ses_est_acc(dissector d, context* ctx);
int pdu_ses_est_rej(dissector d, context* ctx);
int pdu_ses_auth_cmd(dissector d, context* ctx);
int pdu_ses_auth_comp(dissector d, context* ctx);
int pdu_ses_mod_req(dissector d, context* ctx);
int pdu_ses_mod_rej(dissector d, context* ctx);
int pdu_ses_mod_cmd(dissector d, context* ctx);
int pdu_ses_mod_comp(dissector d, context* ctx);
int pdu_ses_auth_res(dissector d, context* ctx);
int pdu_ses_mod_com_rej(dissector d, context* ctx);
int pdu_ses_rel_req(dissector d, context* ctx);
int pdu_ses_rel_rej(dissector d, context* ctx);
int pdu_ses_rel_cmd(dissector d, context* ctx);
int pdu_ses_rel_comp(dissector d, context* ctx);
int sm_status(dissector d, context* ctx);

__declspec(selectany) extern const message_meta msgs[] = {
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

int dissect_sm_cause(dissector d, context* ctx);
int dissect_ext_pco(dissector d, context* ctx);
int dissect_eap_msg(dissector d, context* ctx);
int dissect_authorized_qos_rules(dissector d, context* ctx);
int dissect_qos_rules(dissector d, context* ctx);
int dissect_mapped_eps_b_cont(dissector d, context* ctx);
int dissect_backoff_gprs_timer3(dissector d, context* ctx);
int dissect_sm_cap(dissector d, context* ctx);
int dissect_max_num_sup_kpt_flt(dissector d, context* ctx);
int dissect_ses_ambr(dissector d, context* ctx);
int dissect_rq_gprs_timer(dissector d, context* ctx);
int dissect_always_on_pdu_ses_ind(dissector d, context* ctx);

__declspec(selectany) extern const element_meta sm_cause = {
    0xff,
    "5GSM cause",
    dissect_sm_cause,
};
__declspec(selectany) extern const element_meta ext_pco = {
    0x7B,
    "Extended protocol configuration options",
    dissect_ext_pco,
};
__declspec(selectany) extern const element_meta eap_msg = {
    0x78,
    "EAP message",
    dissect_eap_msg,
};
__declspec(selectany) extern const element_meta authorized_qos_rules = {
    0x7A,
    "Authorized QoS rules",
    dissect_authorized_qos_rules,
};
__declspec(selectany) extern const element_meta mapped_eps_b_cont = {
    0x75,
    "Mapped EPS bearer contexts",
    dissect_mapped_eps_b_cont,
};
__declspec(selectany) extern const element_meta backoff_gprs_timer3 = {
    0x37,
    "GPRS timer - Back-off timer value",
    dissect_backoff_gprs_timer3,
};
__declspec(selectany) extern const element_meta sm_cap = {
    0x28,
    "5GSM capability",
    dissect_sm_cap,
};
__declspec(selectany) extern const element_meta max_num_sup_kpt_flt = {
    0x55,
    "Maximum number of suuported packet filter",
    dissect_max_num_sup_kpt_flt,
};
__declspec(selectany) extern const element_meta ses_ambr = {
    0x2A,
    "Session AMBR",
    dissect_ses_ambr,
};
__declspec(selectany) extern const element_meta rq_gprs_timer = {
    0x56,
    "GPRS timer- PDU session release time",
    dissect_rq_gprs_timer,
};
__declspec(selectany) extern const element_meta always_on_pdu_ses_ind = {
    0x80,
    "Always-on PDU session indication",
    dissect_always_on_pdu_ses_ind,
};

uint32_t get_ext_ambr_unit(uint32_t unit, const char** unit_str);

extern const value_string nas_5gs_sm_unit_for_session_ambr_values[];

__declspec(selectany) extern const field_meta hf_sm_ses_ambr_dl_unit = {
    "Unit for Session-AMBR for downlink",
    "nas_5gs.sm.unit_for_session_ambr_dl",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_sm_unit_for_session_ambr_values),
    nullptr,
    nullptr,
    0x0,
};
__declspec(selectany) extern const field_meta hf_sm_ses_ambr_ul_unit = {
    "Unit for Session-AMBR for uplink",
    "nas_5gs.sm.unit_for_session_ambr_ul",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_sm_unit_for_session_ambr_values),
    nullptr,
    nullptr,
    0x0,
};
__declspec(selectany) extern const field_meta hf_sm_ses_ambr_dl = {
    "Session-AMBR for downlink",
    "nas_5gs.sm.session_ambr_dl",
    ft::ft_uint16,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
__declspec(selectany) extern const field_meta hf_sm_ses_ambr_ul = {
    "Session-AMBR for uplink",
    "nas_5gs.sm.session_ambr_ul",
    ft::ft_uint16,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
} // namespace sm
