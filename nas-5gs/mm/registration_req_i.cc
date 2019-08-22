#pragma once
#include "../core.hh"
#include "../dissect_mm_msg.hh"

namespace mm_reg_req {

/* * 8.2.6 Registration request */

static const val_string nas_5gs_mm_reg_req_vals[] = {
    {0x08, "Follow-On Request bit (FOR)"},
    {0x07, "5GS registration type"},
    {0x70, "NAS key set identifier"},
    {0x80, "Type of security context flag (TSC)"},
    {0, nullptr},
};
static field_meta hfm_registration_req_flags = {
    "Message type",
    "nas_5gs.sm.message_type",
    ft::ft_uint8,
    fd::base_hex,
    nas_5gs_mm_reg_req_vals,
    nullptr,
    nullptr,
    0x0,
};

extern const field_meta* hf_reg_req_flags = &hfm_registration_req_flags;

static const val_string nas_5gs_mm_registration_req_elem[] = {
    {0xc0, "Non-current native NAS KSI"},
    {0x10, "5GMM capability"},
    {0x2e, "UE security capability"},
    {0x2f, "Requested NSSAI"},
    {0x52, "Last visited registered TAI"},
    {0x17, "S1 UE network capability"},
    {0x40, "Uplink data status"},
    {0x50, "PDU session status"},
    {0xb0, "MICO indication"},
    {0x2b, "UE status"},
    {0x77, "Additional GUTI"},
    {0x25, "Allowed PDU session status"},
    {0x18, "UE's usage setting"},
    {0x51, "Requested DRX parameters"},
    {0x70, "EPS NAS message container"},
    {0x74, "LADN indication"},
    {0x80, "Payload container type"},
    {0x7B, "Payload container"},
    {0x90, "Network slicing indication"},
    {0x53, "5GS update type"},
    {0x71, "NAS message container"},
    {0, nullptr},
};

static field_meta hfm_reg_req_elem = {
    "Type",
    "elem.type",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_registration_req_elem,
    nullptr,
    nullptr,
    0x00,
};
extern const field_meta* hf_reg_req_elem = &hfm_reg_req_elem;

    /* 9.11.3.4     5GS mobile identity*/
int                dissect_mobile_id(dissector d, context* ctx = nullptr);
const element_meta mobile_id = {
    -1,
    "Mobile identity",
    dissect_mobile_id,
};

int                dissect_nksi_key_set_id(dissector d, context* ctx = nullptr);
const element_meta nksi_key_set_id = {
    0xc0,
    "Non-current native NAS KSI",
    dissect_nksi_key_set_id,
};

int                dissect_mm_cap(dissector d, context* ctx = nullptr);
const element_meta mm_cap = {
    0x10,
    "5GMM capability",
    dissect_mm_cap,
};


int                dissect_use_sec_cap(dissector d, context* ctx = nullptr);
const element_meta ue_sec_cap = {
    0x2e,
    "UE security capability",
    dissect_use_sec_cap,
};

int                dissect_requested_nssai(dissector d, context* ctx = nullptr);
const element_meta requested_nssai = {
    0x2f,
    "Requested NSSAI",
    dissect_requested_nssai,
};

int                dissect_last_v_tai(dissector d, context* ctx = nullptr);
const element_meta last_v_tai = {
    0x52,
    "Last visited registered TAI",
    dissect_last_v_tai,
};

int                dissect_s1_ue_net_cap(dissector d, context* ctx = nullptr);
const element_meta s1_ue_net_cap = {
    0x17,
    "S1 UE network capability",
    dissect_s1_ue_net_cap,
};

int                dissect_ul_data_status(dissector d, context* ctx = nullptr);
const element_meta ul_data_status = {
    0x40,
    "Uplink data status",
    dissect_ul_data_status,
};

int                dissect_pdu_ses_status(dissector d, context* ctx = nullptr);
const element_meta pdu_ses_status = {
    0x50,
    "PDU session status",
    dissect_pdu_ses_status,
};

int                dissect_mico_ind(dissector d, context* ctx = nullptr);
const element_meta mico_ind = {
    0xb0,
    "MICO indication",
    dissect_mico_ind,
};

int                dissect_ue_status(dissector d, context* ctx = nullptr);
const element_meta ue_status = {
    0x2b,
    "UE status",
    dissect_ue_status,
};

int                dissect_aguti_mobile_id(dissector d, context* ctx = nullptr);
const element_meta aguti_mobile_id = {
    0x77,
    "Additional GUTI",
    dissect_aguti_mobile_id,
};

int                dissect_pdu_ses_sts(dissector d, context* ctx = nullptr);
const element_meta allow_pdu_ses_sts = {
    0x25,
    "Allowed PDU session status",
    dissect_pdu_ses_sts,
};

int                dissect_usage_set(dissector d, context* ctx = nullptr);
const element_meta ue_usage_set = {
    0x18,
    "UE's usage setting",
    dissect_usage_set,
};

int                dissect_requested_drx_param(dissector d, context* ctx = nullptr);
const element_meta requested_drx_param = {
    0x51,
    "Requested DRX parameters",
    dissect_requested_drx_param,
};

int                dissect_eps_nas_msg_cont(dissector d, context* ctx = nullptr);
const element_meta eps_nas_msg_cont = {
    0x70,
    "EPS NAS message container",
    dissect_eps_nas_msg_cont,
};

int                dissect_ladn_inf(dissector d, context* ctx = nullptr);
const element_meta ladn_inf = {
    0x74,
    "LADN indication",
    dissect_ladn_inf,
};

int                dissect_pld_cont_type(dissector d, context* ctx = nullptr);
const element_meta pld_cont_type = {
    0x80,
    "Payload container type",
    dissect_pld_cont_type,
};

int                dissect_pld_cont(dissector d, context* ctx = nullptr);
const element_meta pld_cont = {
    0x7B,
    "Payload container",
    dissect_pld_cont,
};

int                dissect_nw_slicing_ind(dissector d, context* ctx = nullptr);
const element_meta nw_slicing_ind = {
    0x90,
    "Network slicing indication",
    dissect_nw_slicing_ind,
};

int                dissect_update_type(dissector d, context* ctx = nullptr);
const element_meta update_type = {
    0x53,
    "5GS update type",
    dissect_update_type,
};



namespace em_de_mm_reg_accept {
    extern const element_meta reg_res;
    extern const element_meta guti_5gs_mobile_id;
    extern const element_meta plmn_list;
    extern const element_meta ta_id_list;
    extern const element_meta allowed_nssai;
    extern const element_meta rejected_nssai;
    extern const element_meta configured_nssai;
    extern const element_meta nw_feat_sup;
    extern const element_meta pdu_ses_status;
    extern const element_meta pdu_ses_react_res;
    extern const element_meta pdu_ses_react_res_err_c;
    extern const element_meta ladn_inf;
    extern const element_meta mico_ind;
    extern const element_meta nw_slicing_ind;
    extern const element_meta sal;
    extern const element_meta t3512_gprs_timer_3;
    extern const element_meta de_reg_timer_gprs_timer2;
    extern const element_meta gprs_timer_2;
    extern const element_meta emerg_num_list;
    extern const element_meta emerg_num_list_7a;
    extern const element_meta sor_trans_cont;
    extern const element_meta eap_message;
    extern const element_meta nssai_inclusion_mode;
    extern const element_meta operator_defined_acd;
    extern const element_meta nego_drx_param;
} // namespace em_de_mm_reg_accept



} // namespace mm_reg_req

int mm_reg_req::dissect_mobile_id(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_nksi_key_set_id(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_mm_cap(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_use_sec_cap(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_requested_nssai(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_last_v_tai(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_s1_ue_net_cap(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_ul_data_status(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_pdu_ses_status(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_mico_ind(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_ue_status(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_aguti_mobile_id(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_pdu_ses_sts(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_usage_set(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_requested_drx_param(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_eps_nas_msg_cont(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_ladn_inf(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_pld_cont_type(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_pld_cont(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_nw_slicing_ind(dissector d, context* ctx) { return 0; }

int mm_reg_req::dissect_update_type(dissector d, context* ctx) { return 0; }

int dissect_nas_msg_cont(dissector d, context* ctx) { return 0; }
