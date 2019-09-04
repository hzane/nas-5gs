#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_authentication_resp {
extern const element_meta auth_resp_par;
}

using namespace nas;

/*
 *8.2.2    Authentication response
 */
int mm::authentication_resp(dissector d, context* ctx) {
    auto        len = d.length;
    use_context uc(ctx, "authentication-response", d);

    using namespace mm_authentication_resp;

    /* 2D    Authentication response parameter    Authentication response
     * parameter 9.11.3.17    O    TLV    18 */
    // ELEM_OPT_TLV(0x2d, NAS_PDU_TYPE_EMM, DE_EMM_AUTH_RESP_PAR, NULL);
    auto consumed = dissect_opt_elem_tlv(nullptr, &auth_resp_par, d, ctx);
    d.step(consumed);

    /* 78 EAP message    EAP message     9.11.2.2    O    TLV-E    7-1503 */
    // ELEM_OPT_TLV_E(0x78, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eap_msg, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);
    return len;
}
namespace mm_authentication_resp {

int dissect_auth_resp_param(dissector d, context* ctx);

// 9.11.3.17
extern const element_meta auth_resp_par = {
    0x2d,
    "Authentication response parameter",
    dissect_auth_resp_param,
    nullptr,
};

extern const field_meta hf_dtap_sres = {
    "SRES value",
    "gsm_a.dtap.sres",
    ft::ft_bytes,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x00,
};

/* 9.11.3.17	Authentication response parameter
 * 9.9.3.4 in 3GPP TS 24.301 [15].
 */
int dissect_auth_resp_param(dissector d, context* ctx) {

    /* This IE contains either the SRES or the 4 most significant octets of the RES */
    d.add_item(4, &hf_dtap_sres, enc::be);

    /* no length check possible */
    return 4;
}

} // namespace mm_authentication_resp
