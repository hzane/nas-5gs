#include "../core.hh"
#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"
#include "registration_req.hh"

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
    0x0F,
};

// 9.11.3.7	5GS registration type
const value_string nas_5gs_registration_type_values[] = {
    {0x1, "initial registration"},
    {0x2, "mobility registration updating"},
    {0x3, "periodic registration updating"},
    {0x4, "emergency registration"},
    {0x7, "reserved"},
    {0, nullptr},
};

true_false_string nas_5gs_for_tfs = {
    "Follow-on request pending",
    "No follow-on request pending",
};
const field_meta hf_mm_for = {
    "Follow-On Request bit (FOR)",
    "nas_5gs.mm.for",
    ft::ft_boolean,
    fd::base_dec,
    nullptr, (&nas_5gs_for_tfs),nullptr,
    0x08,
};
const field_meta hf_mm_reg_type = {
    "5GS registration type",
    "nas_5gs.mm.5gs_reg_type",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_registration_type_values),
    nullptr,
    nullptr,
    0x07,
};

const field_meta* hf_reg_req_flags = &hfm_registration_req_flags;

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

} // namespace mm_reg_req

// only spare half octet
const field_meta mm_reg_req::hf_ngksi_nas_ksi = {
    "NAS key set identifier - ngKSI",
    "nas_5gs.mm.ngksi",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0xF0,
};
const element_meta mm_reg_req::registration_request = {
    0xff,
    "5GS registration type",
    dissect_reg_req_type,
};
