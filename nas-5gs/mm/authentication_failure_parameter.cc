#include "../dissect_mm_msg.hh"


extern const element_meta mm::auth_fail_param = {
    0x30,
    "Authentication failure parameter",
    dissect_auth_fail_param,
    nullptr,
};

const field_meta mm::hf_gsma_dtap_res = {
    "SRES value",
    "gsm_a.dtap.sres",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0x00,
};

// See subclause 10.5.3.2.2 in 3GPP TS 24.008 [12].
// Authentication failure parameter
int mm::dissect_auth_fail_param(dissector d, context* ctx) {
    /* This IE contains either the SRES or the 4 most significant octets of the RES */
    d.add_item(4, &hf_gsma_dtap_res, enc::na);
    return 4;
}
