#include "../dissect_mm_msg.hh"

namespace mm {

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
    "nas.nr.sm.message_type",
    ft::ft_uint8,
    fd::base_hex,
    nas_5gs_mm_reg_req_vals,
    nullptr,
    nullptr,
    0x0F,
};

true_false_string nas_5gs_for_tfs = {
    "Follow-on request pending",
    "No follow-on request pending",
};
const field_meta hf_mm_for = {
    "Follow-On Request bit (FOR)",
    "nas.nr.mm.for",
    ft::ft_boolean,
    fd::base_dec,
    nullptr, (&nas_5gs_for_tfs),nullptr,
    0x08,
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

} // namespace


