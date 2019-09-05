#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

/* 9.11.3.7    5GS registration type */

extern const val_string mm::values_registration_type[] = {
    {0x1, "initial registration"},
    {0x2, "mobility registration updating"},
    {0x3, "periodic registration updating"},
    {0x4, "emergency registration"},
    {0x7, "reserved"},
    {0, nullptr},
};
const field_meta mm::hf_5gs_reg_type = {
    "5GS registration type",
    "nas_5gs.mm.5gs_reg_type",
    ft::ft_uint8,
    fd::base_dec,
    values_registration_type,
    nullptr,
    nullptr,
    0x07,
};

const element_meta mm::registration_request_type = {
    0xff,
    "5GS registration type",
    dissect_reg_req_type,
    nullptr,
};

// only spare half octet
const field_meta mm::hf_ngksi_nas_ksi = {
    "NAS key set identifier - ngKSI",
    "nas_5gs.mm.ngksi",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0xF0,
};

const element_meta mm::nc_native_nas_ksi = {
    0xc0,
    "Non-current native NAS KSI",
    mm::dissect_nas_ksi,
    nullptr,
};

const element_meta mm::ue_sec_cap = {
    0x2e,
    "UE security capability",
    dissect_use_sec_cap,
    nullptr,
};

/*2F    Requested NSSAI    NSSAI 9.11.3.37    O    TLV    4-74*/
const element_meta mm::requested_nssai = {
    0x2f,
    "Requested NSSAI",
    mm::dissect_requested_nssai,
    nullptr,
};

const element_meta mm::last_v_tai = {
    0x52,
    "5GS tracking area identity - Last visited registered TAI",
    dissect_last_v_tai,
    nullptr,
};

// int dissect_s1_ue_net_cap(dissector d, context* ctx);

const element_meta mm::s1_ue_net_cap = {
    0x17,
    "S1 UE network capability",
    dissect_s1_ue_net_cap,
    nullptr,
};


const element_meta mm::ul_data_status = {
    0x40,
    "Uplink data status",
    dissect_ul_data_status,
    nullptr,
};


const element_meta mm::ue_status = {
    0x2b,
    "UE status",
    dissect_ue_status,
    nullptr,
};


const element_meta mm::aguti_mobile_id = {
    0x77,
    "5GS mobile identity - Additional GUTI",
    dissect_aguti_mobile_id,
    nullptr,
};


const element_meta mm::allow_pdu_ses_sts = {
    0x25,
    "Allowed PDU session status",
    dissect_pdu_ses_sts,
    nullptr,
};


const element_meta mm::ue_usage_set = {
    0x18,
    "UE's usage setting",
    dissect_usage_set,
    nullptr,
};


const element_meta mm::requested_drx_param = {
    0x51,
    "5GS DRX parameters - Requested",
    dissect_requested_drx_param,
    nullptr,
};

const element_meta mm::eps_nas_msg_cont = {
    0x70,
    "EPS NAS message container",
    dissect_eps_nas_msg_cont,
    nullptr,
};


const element_meta mm::ladn_ind = {
    0x74,
    "LADN indication",
    dissect_ladn_ind,
    nullptr,
};




