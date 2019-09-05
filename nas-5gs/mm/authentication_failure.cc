#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_authentication_failure {
extern const element_meta auth_fail_param;
}

/*
 * 8.2.4 Authentication failure
 */
int mm::authentication_failure(dissector d, context* ctx) {
    auto        len = d.length;
    use_context uc(ctx, "authentication-failure", d);

    using namespace mm_authentication_failure;

    /* 5GMM cause   5GMM cause     9.11.3.2  M   V   1 */
    auto consumed = dissect_elem_v(nullptr, &mm_cause, d, ctx);
    d.step(consumed);

    /* 30    Authentication failure parameter   9.11.3.14    O    TLV    16 */
    // ELEM_OPT_TLV(0x30, GSM_A_PDU_TYPE_DTAP, DE_AUTH_FAIL_PARAM, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &auth_fail_param, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);
    return len;
}
namespace mm {

} // namespace mm_authentication_failure
