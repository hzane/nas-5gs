#include "../dissect_mm_msg.hh"

/* 9.11.3.17	Authentication response parameter */
int mm::dissect_auth_resp_param(dissector d, context* ctx) {
    const use_context uc(ctx, "auth-response-param", d, -1);
    //  9.9.3.4 in 3GPP TS 24.301 [15].
    /* This IE contains either the SRES or the 4 most significant octets of the RES */
    auto i = d.add_item(4, &hf_dtap_sres, enc::be);
    d.step(4);

    unused(i);
    return 4;
}

// 9.11.3.17
extern const element_meta mm::auth_resp_param = {
    0x2d,
    "Authentication response parameter",
    dissect_auth_resp_param,
    nullptr,
};

extern const field_meta mm::hf_dtap_sres = {
    "SRES value",
    "gsm.dtap.sres",
    ft::ft_bytes,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x00,
};

