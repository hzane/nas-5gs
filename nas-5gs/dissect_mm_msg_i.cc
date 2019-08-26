#include "dissect_mm_msg.hh"

extern const true_false_string nas_5gs_for_tfs = {
    "Follow-on request pending",
    "No follow-on request pending",
};

static field_meta hfm_nas_5gs_mm_for = {
    "Follow-On Request bit (FOR)",
    "nas_5gs.mm.for",
    ft::ft_boolean,
    fd::sep_dot,
    nullptr,
    &nas_5gs_for_tfs,
    nullptr,
    0x08,
};

const field_meta* hf_nas_5gs_mm_for = &hfm_nas_5gs_mm_for;

/* * 9.11.3.9A    5GS update type*/

static true_false_string tfs_nas5gs_sms_requested = {
    "SMS over NAS supported",
    "SMS over NAS not supported",
};
static field_meta hfm_nas_5gs_mm_sms_requested = {
    "SMS requested",
    "nas_5gs.mm.sms_requested",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_nas5gs_sms_requested,
    nullptr,
    0x01,
};

/* 9.11.3.7    5GS registration type */

static const val_string nas_5gs_registration_type_values[] = {
    {0x1, "initial registration"},
    {0x2, "mobility registration updating"},
    {0x3, "periodic registration updating"},
    {0x4, "emergency registration"},
    {0x7, "reserved"},
    {0, nullptr},
};
static field_meta hfm_nas_5gs_mm_5gs_reg_type = {
    "5GS registration type",
    "nas_5gs.mm.5gs_reg_type",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_registration_type_values,
    nullptr,
    nullptr,
    0x07,
};
const field_meta* hf_nas_5gs_mm_5gs_reg_type = &hfm_nas_5gs_mm_5gs_reg_type;

static const true_false_string nas_5gs_mm_tsc_tfs = {
    "Mapped security context (for KSIASME)",
    "Native security context (for KSIAMF)",
};

static field_meta hfm_nas_5gs_mm_tsc = {
    "Type of security context flag (TSC)",
    "nas_5gs.mm.tsc",
    ft::ft_boolean,
    8,
    nullptr,
    &nas_5gs_mm_tsc_tfs,
    nullptr,
    0x08,
};

static field_meta hfm_nas_5gs_mm_nas_key_set_id = {
    "NAS key set identifier",
    "nas_5gs.mm.nas_key_set_id",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x07,
};

static field_meta hfm_nas_5gs_mm_tsc_h1 = {
    "Type of security context flag (TSC)",
    "nas_5gs.mm.tsc.h1",
    ft::ft_boolean,
    8,
    nullptr,
    &nas_5gs_mm_tsc_tfs,
    nullptr,
    0x80,
};
const field_meta* hf_nas_5gs_mm_tsc_h1 = &hfm_nas_5gs_mm_tsc_h1;

static field_meta hfm_nas_5gs_mm_nas_key_set_id_h1 = {
    "NAS key set identifier",
    "nas_5gs.mm.nas_key_set_id.h1",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x70,
};
const field_meta* hf_nas_5gs_mm_nas_key_set_id_h1 =
    &hfm_nas_5gs_mm_nas_key_set_id_h1;

/* * 9.11.3.2 5GMM cause */

extern const val_string nas_5gs_mm_cause_vals[] = {
    {0x03, "Illegal UE"},
    {0x05, "PEI not accepted"},
    {0x06, "Illegal ME"},
    {0x07, "5GS services not allowed"},
    {0x09, "UE identity cannot be derived by the network"},
    {0x0a, "Implicitly deregistered"},
    {0x0b, "PLMN not allowed"},
    {0x0c, "Tracking area not allowed"},
    {0x0d, "Roaming not allowed in this tracking area"},
    {0x0f, "No suitable cells in tracking area"},
    {0x14, "MAC failure"},
    {0x15, "Synch failure"},
    {0x16, "Congestion"},
    {0x17, "UE security capabilities mismatch"},
    {0x18, "Security mode rejected, unspecified"},
    {0x1a, "Non-5G authentication unacceptable"},
    {0x1b, "N1 mode not allowed"},
    {0x1c, "Restricted service area"},
    {0x2b, "LADN not available"},
    {0x41, "Maximum number of PDU sessions reached"},
    {0x43, "Insufficient resources for specific slice and DNN"},
    {0x45, "Insufficient resources for specific slice"},
    {0x47, "ngKSI already in use"},
    {0x48, "Non-3GPP access to 5GCN not allowed"},
    {0x49, "Serving network not authorized"},
    {0x5a, "Payload was not forwarded"},
    {0x5b, "DNN not supported or not subscribed in the slice"},
    {0x5c, "Insufficient user-plane resources for the PDU session"},
    {0x5f, "Semantically incorrect message"},
    {0x60, "Invalid mandatory information"},
    {0x61, "Message type non-existent or not implemented"},
    {0x62, "Message type not compatible with the protocol state"},
    {0x63, "Information element non-existent or not implemented"},
    {0x64, "Conditional IE error"},
    {0x65, "Message not compatible with the protocol state"},
    {0x6f, "Protocol error, unspecified"},
    {0, nullptr},
};
const val_string* nas_5gs_mm_cause_values = nas_5gs_mm_cause_vals;

const field_meta hfm_nas_5gs_mm_5gmm_cause = {
    "5GMM cause",
    "nas_5gs.mm.5gmm_cause",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_cause_vals,
    nullptr,
    nullptr,
    0x0,
};

/* *   9.11.3.40    Payload container type */

static const val_string nas_5gs_mm_pld_cont_type_vals[] = {
    {0x01, "N1 SM information"},
    {0x02, "SMS"},
    {0x03, "LTE Positioning Protocol (LPP) message container"},
    {0x04, "SOR transparent container"},
    {0x05, "UE policy container"},
    {0x06, "UE parameters update transparent container"},
    {0x0f, "Multiple payloads"},
    {0, nullptr},
};
static field_meta hfm_nas_5gs_mm_pld_cont_type = {
    "Payload container type",
    "nas_5gs.mm.pld_cont_type",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_pld_cont_type_vals,
    nullptr,
    nullptr,
    0x0f,
};

static field_meta hfm_nas_5gs_mm_sst = {
    "Slice/service type (SST)",
    "nas_5gs.mm.sst",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

static field_meta hfm_nas_5gs_mm_sd = {
    "Slice differentiator (SD)",
    "nas_5gs.mm.mm_sd",
    ft::ft_uint24,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

static field_meta hfm_nas_5gs_mm_mapped_conf_sst = {
    "Mapped configured SST",
    "nas_5gs.mm.mapped_conf_sst",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

static field_meta hfm_nas_5gs_mm_mapped_conf_ssd = {
    "Mapped configured SD",
    "nas_5gs.mm.mapped_conf_ssd",
    ft::ft_uint24,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

/* *   9.11.3.19    Daylight saving time */

/* See subclause 10.5.3.12 in 3GPP TS 24.008 */

/* *   9.11.3.20    De-registration type */

static const true_false_string nas_5gs_mm_switch_off_tfs = {
    "Switch off",
    "Normal de-registration",
};
static field_meta hfm_nas_5gs_mm_switch_off = {
    "Switch off",
    "nas_5gs.mm.switch_off",
    ft::ft_boolean,
    8,
    nullptr,
    &nas_5gs_mm_switch_off_tfs,
    nullptr,
    0x08,
};

static const true_false_string nas_5gs_mm_re_reg_req_tfs = {
    "re-registration required",
    "re-registration not required",
};
static field_meta hfm_nas_5gs_mm_re_reg_req = {
    "Re-registration required",
    "nas_5gs.mm.re_reg_req",
    ft::ft_boolean,
    8,
    nullptr,
    &nas_5gs_mm_re_reg_req_tfs,
    nullptr,
    0x04,
};

static const val_string nas_5gs_mm_acc_type_vals[] = {
    {0x1, "3GPP access"},
    {0x2, "Non-3GPP access"},
    {0x3, "3GPP access and non-3GPP access"},
    {0, nullptr},
};
static field_meta hfm_nas_5gs_mm_acc_type = {
    "Access type",
    "nas_5gs.mm.acc_type",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_acc_type_vals,
    nullptr,
    nullptr,
    0x03,
};

/* *   9.11.3.31    MICO indication */

static const true_false_string tfs_nas_5gs_raai = {
    "all PLMN registration area allocated",
    "all PLMN registration area not allocated",
};

static field_meta hfm_nas_5gs_mm_raai_b0 = {
    "Registration Area Allocation Indication (RAAI)",
    "nas_5gs.mm.raai_b0",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_nas_5gs_raai,
    nullptr,
    0x01,
};

__declspec(selectany) extern const true_false_string tfs_requested_not_requested = {
    "Requested",
    "Not Requested",
};
static field_meta hfm_nas_5gs_mm_conf_upd_ind_ack_b0 = {
    "Acknowledgement",
    "nas_5gs.mm.conf_upd_ind.ack",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_requested_not_requested,
    nullptr,
    0x01,
};

static field_meta hfm_nas_5gs_mm_conf_upd_ind_red_b1 = {
    "Registration",
    "nas_5gs.mm.conf_upd_ind.red",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_requested_not_requested,
    nullptr,
    0x02,
};

static const val_string nas_5gs_mm_type_of_enc_algo_vals[] = {
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
static field_meta hfm_nas_5gs_mm_nas_sec_algo_enc = {
    "Type of ciphering algorithm",
    "nas_5gs.mm.nas_sec_algo_enc",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_type_of_enc_algo_vals,
    nullptr,
    nullptr,
    0xf0,
};

/* *   9.11.3.34    NAS security algorithms */

static const val_string nas_5gs_mm_type_of_ip_algo_vals[] = {
    {0x0, "5G-IA0 (null integrity protection algorithm)"},
    {0x1, "128-5G-IA1"},
    {0x2, "128-5G-IA2"},
    {0x3, "128-5G-IA3"},
    {0x4, "5G-IA4"},
    {0x5, "5G-IA5"},
    {0x6, "5G-IA6"},
    {0x7, "5G-IA7"},
    {0, nullptr},
};
static field_meta hfm_nas_5gs_mm_nas_sec_algo_ip = {
    "Type of integrity protection algorithm",
    "nas_5gs.mm.nas_sec_algo_ip",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_type_of_ip_algo_vals,
    nullptr,
    nullptr,
    0x0f,
};

static field_meta hfm_nas_5gs_mm_s1_mode_b0 = {
    "S1 mode",
    "nas_5gs.mm.s1_mode_b0",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_requested_not_requested,
    nullptr,
    0x01,
};

__declspec(selectany) extern const true_false_string tfs_supported_not_supported = {
    "Supported",
    "Not supported",
};
static field_meta hfm_nas_5gs_mm_ho_attach_b1 = {
    "HO attach",
    "nas_5gs.mm.ho_attach_b1",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x02,
};

static field_meta hfm_nas_5gs_mm_lpp_cap_b2 = {
    "LTE Positioning Protocol (LPP) capability",
    "nas_5gs.mm.lpp_cap_b2",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_requested_not_requested,
    nullptr,
    0x04,
};

/* * 9.11.3.4    5GS mobile identity */

static const val_string nas_5gs_mm_type_id_vals[] = {
    {0x0, "No identity"},
    {0x1, "SUCI"},
    {0x2, "5G-GUTI"},
    {0x3, "IMEI"},
    {0x4, "5G-S-TMSI"},
    {0x5, "IMEISV"},
    {0, nullptr},
};
static field_meta hfm_nas_5gs_mm_type_id = {
    "Type of identity",
    "nas_5gs.mm.type_id",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_type_id_vals,
    nullptr,
    nullptr,
    0x07,
};

const true_false_string nas_5gs_odd_even_tfs = {
    "Odd number of identity digits",
    "Even number of identity digits",
};
const field_meta hfm_nas_5gs_mm_odd_even = {
    "Odd/even indication",
    "nas_5gs.mm.odd_even",
    ft::ft_boolean,
    8,
    nullptr,
    &nas_5gs_odd_even_tfs,
    nullptr,
    0x08,
};

const field_meta hfm_nas_5gs_mm_length = {
    "Length",
    "nas_5gs.mm.length",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta hfm_nas_5gs_mm_abba = {
    "ABBA Contents",
    "nas_5gs.mm.abba_contents",
    ft::ft_uint16,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x00,
};
const field_meta hfm_nas_5gs_mm_pld_cont = {
    "Payload container",
    "nas_5gs.mm.pld_cont",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

/* *     9.11.3.47    Request type */

const val_string nas_5gs_mm_req_type_vals[] = {
    {0x01, "Initial request"},
    {0x02, "Existing PDU session"},
    {0x03, "Initial emergency request"},
    {0x04, "Existing emergency PDU session"},
    {0x05, "Modification request"},
    {0x07, "Reserved"},
    {0, nullptr},
};
const field_meta hfm_nas_5gs_mm_req_type = {
    "Request type",
    "nas_5gs.mm.req_typ",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_req_type_vals,
    nullptr,
    nullptr,
    0x0f,
};

/* *     9.11.3.50    Service type */

/* Used inline as H1 (Upper nibble)*/
const val_string nas_5gs_mm_serv_type_vals[] = {
    {0x00, "Signalling"},
    {0x01, "Data"},
    {0x02, "Mobile terminated services"},
    {0x03, "Emergency services"},
    {0x04, "Emergency services fallback"},
    {0x05, "High priority access"},
    {0, nullptr},
};
const field_meta hfm_nas_5gs_mm_serv_type = {
    "Service type",
    "nas_5gs.mm.serv_type",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_serv_type_vals,
    nullptr,
    nullptr,
    0x70,
};

const field_meta hfm_nas_5gs_mm_5g_ea0 = {
    "5G-EA0",
    "nas_5gs.mm.5g_ea0",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x80,
};

const field_meta hfm_nas_5gs_mm_128_5g_ea1 = {
    "128-5G-EA1",
    "nas_5gs.mm.128_5g_ea1",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x40,
};

const field_meta hfm_nas_5gs_mm_128_5g_ea2 = {
    "128-5G-EA2",
    "nas_5gs.mm.128_5g_ea2",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x20,
};

const field_meta hfm_nas_5gs_mm_128_5g_ea3 = {
    "128-5G-EA3",
    "nas_5gs.mm.128_5g_ea3",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x10,
};

const field_meta hfm_nas_5gs_mm_5g_ea4 = {
    "5G-EA4",
    "nas_5gs.mm.5g_ea4",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x08,
};

const field_meta hfm_nas_5gs_mm_5g_ea5 = {
    "5G-EA5",
    "nas_5gs.mm.5g_ea5",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x04,
};

const field_meta hfm_nas_5gs_mm_5g_ea6 = {
    "5G-EA6",
    "nas_5gs.mm.5g_ea6",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x02,
};

const field_meta hfm_nas_5gs_mm_5g_ea7 = {
    "5G-EA7",
    "nas_5gs.mm.5g_ea7",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x01,
};

const field_meta hfm_nas_5gs_mm_5g_ia0 = {
    "5G-IA0",
    "nas_5gs.mm.ia0",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x80,
};

const field_meta hfm_nas_5gs_mm_5g_128_ia1 = {
    "128-5G-IA1",
    "nas_5gs.mm.5g_128_ia1",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x40,
};

const field_meta hfm_nas_5gs_mm_5g_128_ia2 = {
    "128-5G-IA2",
    "nas_5gs.mm.5g_128_ia2",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x20,
};

const field_meta hfm_nas_5gs_mm_5g_128_ia3 = {
    "128-5G-IA3",
    "nas_5gs.mm.5g_128_ia4",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x10,
};

const field_meta hfm_nas_5gs_mm_5g_ia4 = {
    "5G-IA4",
    "nas_5gs.mm.5g_128_ia4",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x08,
};

const field_meta hfm_nas_5gs_mm_5g_ia5 = {
    "5G-IA5",
    "nas_5gs.mm.5g_ia5",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x04,
};

const field_meta hfm_nas_5gs_mm_5g_ia6 = {
    "5G-IA6",
    "nas_5gs.mm.5g_ia6",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x02,
};

const field_meta hfm_nas_5gs_mm_5g_ia7 = {
    "5G-IA7",
    "nas_5gs.mm.5g_ia7",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x01,
};

const field_meta hfm_nas_5gs_mm_eea0 = {
    "EEA0",
    "nas_5gs.mm.eea0",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x80,
};

const field_meta hfm_nas_5gs_mm_128eea1 = {
    "128-EEA1",
    "nas_5gs.mm.128eea1",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x40,

};

const field_meta hfm_nas_5gs_mm_128eea2 = {
    "128-EEA2",
    "nas_5gs.mm.128eea2",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x20,
};

const field_meta hfm_nas_5gs_mm_eea3 = {
    "128-EEA3",
    "nas_5gs.mm.eea3",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x10,

};

const field_meta hfm_nas_5gs_mm_eea4 = {
    "EEA4",
    "nas_5gs.mm.eea4",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x08,
};

const field_meta hfm_nas_5gs_mm_eea5 = {
    "EEA5",
    "nas_5gs.mm.eea5",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x04,

};
const field_meta hfm_nas_5gs_mm_eea6 = {
    "EEA6",
    "nas_5gs.mm.eea6",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x02,

};
const field_meta hfm_nas_5gs_mm_eea7 = {
    "EEA7",
    "nas_5gs.mm.eea7",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x01,

};
const field_meta hfm_nas_5gs_mm_eia0 = {
    "EIA0",
    "nas_5gs.mm.eia0",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x80,

};
const field_meta hfm_nas_5gs_mm_128eia1 = {
    "128-EIA1",
    "nas_5gs.mm.128eia1",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x40,

};
const field_meta hfm_nas_5gs_mm_128eia2 = {
    "128-EIA2",
    "nas_5gs.mm.128eia2",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x20,
};
const field_meta hfm_nas_5gs_mm_eia3 = {
    "128-EIA3",
    "nas_5gs.mm.eia3",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x10,

};
const field_meta hfm_nas_5gs_mm_eia4 = {
    "EIA4",
    "nas_5gs.mm.eia4",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x08,

};
const field_meta hfm_nas_5gs_mm_eia5 = {
    "EIA5",
    "nas_5gs.mm.eia5",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x04,

};
const field_meta hfm_nas_5gs_mm_eia6 = {
    "EIA6",
    "nas_5gs.mm.eia6",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x02,

};
const field_meta hfm_nas_5gs_mm_eia7 = {
    "EIA7",
    "nas_5gs.mm.eia7",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_supported_not_supported,
    nullptr,
    0x01,
};

/* *    9.11.3.56    UE status */

const true_false_string tfs_nas_5gs_mm_n1_mod = {
    "UE is in 5GMM-REGISTERED state",
    "UE is not in 5GMM-REGISTERED state",
};
const field_meta hfm_nas_5gs_mm_n1_mode_reg_b1 = {
    "N1 mode reg",
    "nas_5gs.mm.n1_mode_reg_b1",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_nas_5gs_mm_n1_mod,
    nullptr,
    0x02,

};

const true_false_string tfs_nas_5gs_mm_s1_mod = {
    "UE is in EMM-REGISTERED state",
    "UE is not in EMM-REGISTERED state",
};
const field_meta hfm_nas_5gs_mm_s1_mode_reg_b0 = {
    "S1 mode reg",
    "nas_5gs.mm.s1_mode_reg_b0",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_nas_5gs_mm_s1_mod,
    nullptr,
    0x01,

};

/* *    9.11.3.48    S1 UE network capability */

/* See subclause 9.9.3.34 in 3GPP TS 24.301 */

/* *   9.11.3.48A    S1 UE security capability */

/*See subclause 9.9.3.36 in 3GPP TS 24.301 */

/* *     9.11.3.49    Service area list */

const true_false_string tfs_nas_5gs_sal_al_t = {
    "TAIs in the list are in the non-allowed area",
    "TAIs in the list are in the allowed area",
};
const field_meta hfm_nas_5gs_mm_sal_al_t = {
    "Allowed type",
    "nas_5gs.mm.sal_al_t",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_nas_5gs_sal_al_t,
    nullptr,
    0x80,

};

const val_string nas_5gs_mm_sal_t_li_values[] = {
    {0x00, "list of TACs belonging to one PLMN, with non-consecutive TAC values"},
    {0x01, "list of TACs belonging to one PLMN, with consecutive TAC values"},
    {0x02, "list of TAIs belonging to different PLMNs"},
    {0x03, "All TAIs belonging to the PLMN are in the allowed area"},
    {0, nullptr},
};
const field_meta hfm_nas_5gs_mm_sal_t_li = {
    "Type of list",
    "nas_5gs.mm.sal_t_li",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_sal_t_li_values,
    nullptr,
    nullptr,
    0x60,
};
const field_meta hfm_nas_5gs_mm_sal_num_e = {
    "Number of elements",
    "nas_5gs.mm.sal_num_e",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x1f,

};

