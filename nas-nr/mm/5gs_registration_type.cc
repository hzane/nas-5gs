#include "../common/ber.hh"
#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace mm;

/* 9.11.3.7    5GS registration type */
int mm::dissect_registration_requestuest_type(dissector d, context* ctx) {
    const use_context uc(ctx, "5gs-registration-type", d, -1);

    d.add_item(&hf_follow_on_request);
    d.add_item(&hf_registration_type);

    return 1;
}
struct registration_request_type_t{
    uint8_t follow_on_request;
    uint8_t registration_type;
};

// 9.11.3.7	5GS registration type
extern const v_string mm::values_registration_type[] = {
    {0x1, "initial registration"},
    {0x2, "mobility registration updating"},
    {0x3, "periodic registration updating"},
    {0x4, "emergency registration"},
    {0x7, "reserved"},
    {0, nullptr},
};
const tag_field mm::hf_registration_type = {
    "5GS registration type",
    0x07,
    values_registration_type,
};

const element_meta mm::nc_native_nas_ksi = {
    0xc0,
    "NAS key set identifier - Non-current native NAS KSI",
    mm::dissect_nas_ksi,
};

const element_meta mm::ue_security_capability = {
    0x2e,
    "UE security capability",
    dissect_ue_security_capability,
};

/*2F    Requested NSSAI    NSSAI 9.11.3.37    O    TLV    4-74*/
const element_meta mm::requested_nssai = {
    0x2f,
    "NSSAI - Requested",
    mm::dissect_requested_nssai,
};

const element_meta mm::last_visited_tai = {
    0x52,
    "5GS tracking area identity - Last visited registered TAI",
    dissect_last_visited_tai,
};

const element_meta mm::s1_ue_network_capability = {
    0x17,
    "S1 UE network capability",
    dissect_s1_ue_net_capability,
};


const element_meta mm::ue_status = {
    0x2b,
    "UE status",
    dissect_ue_status,
};


const element_meta mm::aguti_mobile_id = {
    0x77,
    "5GS mobile identity - Additional GUTI",
    dissect_mobile_id,
};

// UE's usage setting         9.11.3.55
const element_meta mm::ue_usage_setting = {
    0x18,
    "UE's usage setting",
    dissect_usage_setting,
};


const element_meta mm::requested_drx_parameter = {
    0x51,
    "5GS DRX parameters - Requested",
    dissect_drx_parameter,
};

const element_meta mm::eps_nas_message_container = {
    0x70,
    "EPS NAS message container",
    dissect_eps_nas_msg_container,
};


const element_meta mm::ladn_indication = {
    0x74,
    "LADN indication",
    dissect_ladn_indication,
};
