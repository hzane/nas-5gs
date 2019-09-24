#include "../common/dissect_mm_msg.hh"

namespace mm {

/* * 8.2.6 Registration request */

static const v_string nas_5gs_mm_reg_req_vals[] = {
    {0x08, "Follow-On Request bit (FOR)"},
    {0x07, "5GS registration type"},
    {0x70, "NAS key set identifier"},
    {0x80, "Type of security context flag (TSC)"},
    {0, nullptr},
};

const v_string nas_5gs_mm_registration_req_elem[] = {
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


