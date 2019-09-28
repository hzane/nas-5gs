#include "../common/ber.hh"
#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

/* 8.2.4 Authentication failure */
int mm::dissect_authentication_failure(dissector d, context* ctx) {
    const use_context uc(ctx, "authentication-failure", d, 0);
    // UE to network
    up_link(d.packet);

    /* 5GMM cause   5GMM cause     9.11.3.2  M   V   1 */
    auto consumed = dissect_nrmm_cause(d, ctx);
    d.step(consumed);

    /* 30    Authentication failure parameter   9.11.3.14    O    TLV    16 */
    consumed = dissect_opt_tlv( &authentication_failure_parameter, d, ctx);
    d.step(consumed);

    return uc.length;
}

struct authentication_failure_parameter_t{
    uint8_t result[4];
};

struct authentication_failure_t{
    uint8_t cause;
    authentication_failure_parameter_t parameter;
};
