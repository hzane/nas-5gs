#include "../dissect_mm_msg.hh"
#include "../ber.hh"

using namespace nas;

/* 8.2.5 Authentication reject */
int mm::authentication_reject(dissector d, context* ctx) {
    const use_context uc(ctx, "authentication-reject", d, 0);

    /* 78    EAP message  9.11.2.2    O    TLV-E    7-1503 */
    const auto consumed = dissect_opt_tlv_e(nullptr, &cmn::eap_message, d, ctx);
    d.step(consumed);

    return uc.length;
}


