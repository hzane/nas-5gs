#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace mm;

const octet_field hf_sres = {
    "SRES value",
};

/* 9.11.3.17	Authentication response parameter */
int mm::dissect_authentication_response_parameter(dissector d, context* ctx) {
    const use_context uc(ctx, "auth-response-param", d, -1);
    //  9.9.3.4 in 3GPP TS 24.301 [15].
    /* This IE contains either the SRES or the 4 most significant octets of the RES */
    (void) d.add_item(&hf_sres, 4);
    d.step(4);

    return 4;
}



