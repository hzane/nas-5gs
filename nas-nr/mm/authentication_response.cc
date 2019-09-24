#include "../base/ber.hh"
#include "../common/dissect_mm_msg.hh"

using namespace nas;

/* 8.2.2    Authentication response */
int mm::dissect_authentication_response(dissector d, context* ctx) {
    const use_context uc(ctx, "authentication-response", d, 0);

    /* 2D    Authentication response parameter 9.11.3.17    O    TLV    18 */
    auto consumed = dissect_opt_tlv(nullptr, &authentication_response_parameter, d, ctx);
    d.step(consumed);

    /* 78 EAP message    EAP message     9.11.2.2    O    TLV-E    7-1503 */
    consumed = dissect_opt_tlv_e(nullptr, &cmn::eap_message, d, ctx);
    d.step(consumed);

    return uc.length;
}
