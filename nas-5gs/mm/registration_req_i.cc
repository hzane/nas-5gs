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
/*
 * 9.9.3.21 NAS key set identifier
 */
/*
 * Type of security context flag (TSC) (octet 1)
 */
static const true_false_string nas_eps_tsc_value = {
    "Mapped security context (for KSIsgsn)",
    "Native security context (for KSIasme)",
};
const field_meta hfm_nas_eps_tsc = {
    "Type of security context flag (TSC)",
    "nas_eps.emm.tsc",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &nas_eps_tsc_value,
    nullptr,
    0x0,
};
const field_meta* hf_nas_eps_tsc = &hfm_nas_eps_tsc;

/* NAS key set identifier (octet 1) Bits 3  2   1 */

static const val_string nas_eps_emm_NAS_key_set_identifier_vals[] = {
    {0, ""},
    {1, ""},
    {2, ""},
    {3, ""},
    {4, ""},
    {5, ""},
    {6, ""},
    {7, "No key is available"},
    {0, nullptr},
};
const field_meta hfm_nas_eps_nas_ksi = {
    "NAS key set identifier",
    "nas_eps.emm.nas_key_set_id",
    ft::ft_uint8,
    fd::base_dec,
    nas_eps_emm_NAS_key_set_identifier_vals,
    nullptr,
    nullptr,
    0x00,
};
const field_meta* hf_nas_eps_nas_ksi = &hfm_nas_eps_nas_ksi;

} // namespace mm

// nas key set id nas-key-set-id
int dissect_nas_ksi(dissector d, context* ctx) {
    auto v = d.tvb->get_uint8(d.offset);

    /* Type of security context flag (TSC) (octet 1)    V   1/2   */
    auto tsc  = (v & 0x10) >> 4;
    auto item = d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_nas_eps_tsc, enc::none);
    item->set_uint(tsc, enc::be, nullptr);

    auto nas_ksi = (v & 0xe0) >> 5;
    item = d.add_item(1, hf_nas_eps_nas_ksi, enc::none);
    item->set_uint(nas_ksi, enc::be, nullptr);

    return 1;
}

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
    // TODO: implement

    /* Octets 3 to 253 contain the SMS message (i.e. CP DATA, CP ACK or CP ERROR)
     * as defined in subclause 7.2 of 3GPP TS 24.011 [10]
     */
    add_generic_msg_elem_body(d, ctx);
    return d.length;
}
