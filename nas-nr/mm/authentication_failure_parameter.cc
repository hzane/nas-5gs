#include "../dissect_mm_msg.hh"

using namespace cmn;
using namespace mm;

// See sub-clause 10.5.3.2.2 in 3GPP TS 24.008 [12].
// Authentication failure parameter
int mm::dissect_auth_fail_param(dissector d, context* ctx) {
    const use_context uc(ctx, "authentication-failure-param", d, -1);

    /* This IE contains either the SRES or the 4 most significant octets of the RES */
    auto i = d.add_item(4, &hf_gsm_result, enc::na);
    d.step(4);

    unused(i);
    return 4;
}

extern const element_meta mm::auth_fail_param = {
    0x30,
    "Authentication failure parameter",
    dissect_auth_fail_param,
    nullptr,
};

const field_meta mm::hf_gsm_result = {
    "SRES value",
    "gsm.sres.result",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0x00,
};
