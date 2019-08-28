#include "../core.hh"
#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

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

/* 9.11.3.4     5GS mobile identity*/




} // namespace mm_reg_req

extern const val_string values_cause[];


using namespace mm;


namespace mm{


} // namespace mm

const true_false_string nas_5gs_odd_even_tfs;

namespace mm {

};



/*
 * 9.4.14a  Mobile Station Classmark 2
 * With the exception of the IEI, the contents are specified in subclause 10.5.1.6 in 3GPP
 * TS 24.008 [8]. (packet-gsm_a_common.c)
 */
/*
 * 9.4.15   NAS message container
 * Octets 3 to 253 contain the SMS message (i.e. CP DATA, CP ACK or CP ERROR)
 * as defined in subclause 7.2 of 3GPP TS 24.011 [10]
 */
int dissect_nas_msg_cont(dissector d, context* ctx) {
    /* Octets 3 to 253 contain the SMS message (i.e. CP DATA, CP ACK or CP ERROR)
     * as defined in subclause 7.2 of 3GPP TS 24.011 [10]
     */
    dissect_nas_5gs(d, ctx);
    return d.length;
}
