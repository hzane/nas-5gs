#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"


using namespace mm;

const octet_field hf_sres = {
    "SRES value",
};

/* 9.11.3.17	Authentication response parameter */
//  9.9.3.4 in 3GPP TS 24.301 [15].
int mm::dissect_authentication_response_parameter(dissector d, context* ctx) {
    const use_context uc(ctx, "auth-response-param", d, -1);

    /* This IE contains either the SRES or the 4 most significant octets of the RES */
    (void) d.set_item(16, hstring(d.ptr(), d.safe_length(16)));
    d.step(16);

    return 16;
}
