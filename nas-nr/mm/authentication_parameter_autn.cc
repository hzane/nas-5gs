#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

extern const octet_field hf_dtap_autn = {
    "AUTN value",
    nullptr,
    nullptr,
};

extern const octet_field hf_dtap_autn_sqn = {
    "SQN xor AK",
    nullptr,
    nullptr,
};

extern const octet_field hf_dtap_autn_amf = {
    "AMF",
    nullptr,
    nullptr,
};

extern const octet_field hf_dtap_autn_mac = {
    "MAC",
    ":",
    nullptr,
};

// 9.11.3.15	Authentication parameter AUTN
// See subclause 10.5.3.1 in 3GPP TS 24.008 [12].
// [9] 10.5.3.1.1 Authentication Parameter AUTN (UMTS and EPS authentication challenge)
int mm::dissect_authentication_parameter_autn(dissector d, context* ctx) {
    const use_context uc(ctx, "auth-param-autn", d, 0);

    (void) d.add_item(&hf_dtap_autn_sqn, 6);
    d.step(6);

    (void) d.add_item(&hf_dtap_autn_amf, 2);
    d.step(2);

    (void) d.add_item(&hf_dtap_autn_mac, 8);
    d.step(8);

    return uc.length;
}
