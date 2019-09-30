#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"


using namespace mm;

const octet_field hf_gsm_result = {
    "SRES value",
};

// See sub-clause 10.5.3.2.2 in 3GPP TS 24.008 [12].
// Authentication failure parameter
int mm::dissect_authentication_failure_parameter(dissector d, context* ctx) {
    const use_context uc(ctx, "authentication-failure-param", d, -1);

    /* This IE contains either the SRES or the 4 most significant octets of the RES */
    (void) d.add_item(&hf_gsm_result, 4);
    d.step(4);

    return 4;
}



