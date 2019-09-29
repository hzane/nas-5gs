#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace mm;

/* 9.11.3.17	Authentication response parameter */
int mm::dissect_authentication_response_parameter(dissector d, context* ctx) {
    const use_context uc(ctx, "auth-response-param", d, -1);
    //  9.9.3.4 in 3GPP TS 24.301 [15].
    /* This IE contains either the SRES or the 4 most significant octets of the RES */
    auto i = d.add_item(4, &hf_sres);
    d.step(4);

    unused(i);
    return 4;
}


// 9.11.3.17
extern const element_meta mm::authentication_response_parameter = {
    0x2d,
    "Authentication response parameter",
    dissect_authentication_response_parameter,
};

extern const octet_field mm::hf_sres = {
    "SRES value",
};
