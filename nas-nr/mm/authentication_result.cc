#include "../common/ber.hh"
#include "../common/common.hh"
#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace nas;

/* 8.2.3 Authentication result */
int mm::dissect_authentication_result(dissector d, context* ctx) {
    const use_context uc(ctx, "authentication-result", d, 0);
    // network to UE
    down_link(d.packet);

    /* ngKSI    NAS key set identifier 9.11.3.32    M    V    1/2*/
    (void) dissect_v( &nas_ksi, d, ctx);

    /*Spare half octet    Spare half octet 9.5    M    V    1/2  H1 */
    d.step(1);

    /* EAP message  9.11.2.2    M    LV-E    7-1503 */
    auto consumed = dissect_lv_e( &eap_message, d, ctx);
    d.step(consumed);

    /* 38 ABBA 9.11.3.10    O    TLV    4-n */
    consumed = dissect_opt_tlv( &abba, d, ctx);
    d.step(consumed);

    return uc.length;
}


