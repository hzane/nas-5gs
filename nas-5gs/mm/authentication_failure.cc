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
namespace mm_authentication_failure {
int dissect_auth_fail_param(dissector d, context* ctx);

extern const element_meta auth_fail_param = {
    0x30,
    "Authentication failure parameter",
    dissect_auth_fail_param,
    nullptr,
};

const field_meta hf_gsma_dtap_res = {
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
int dissect_auth_fail_param(dissector d, context* ctx) {
    /* This IE contains either the SRES or the 4 most significant octets of the RES */
    d.add_item(4, &hf_gsma_dtap_res, enc::na);
    return 4;
}
} // namespace mm_authentication_failure
