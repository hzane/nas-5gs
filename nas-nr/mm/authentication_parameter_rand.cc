#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

const octet_field hf_dtap_rand = {
    "RAND value",
    nullptr,
    nullptr,
};

/* * 9.11.3.16	Authentication parameter RAND */
int mm::dissect_authentication_parameter_rand_set(dissector d, context* ctx) {
    const use_context uc(ctx, "authentication-parameter-rand", d, -1);

    // See subclause 10.5.3.1 in 3GPP TS 24.008 [12].
    /* The RAND value is 16 octets long */
    auto v = hstring(d.ptr(), d.safe_length(16));
    d.set_item(16, v);

    return 16;
}
