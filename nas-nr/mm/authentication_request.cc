#include "../common/ber.hh"
#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace nas;

/* 8.2.1.1    Authentication request */
int mm::dissect_authentication_request(dissector d, context* ctx) {
    const use_context uc(ctx, "authentication-request", d, 0);
    // network to UE
    down_link(d.packet);

    /* Spare half octet    Spare half octet     9.5    M    V    1/2 H1 */

    /*ngKSI     NAS key set identifier 9.11.3.32    M    V    1/2  */
    // ELEM_MAND_V(DE_NAS_5GS_MM_NAS_KEY_SET_ID, " - ngKSI",);
    dissect_v( &nas_ksi, d, ctx);
    d.step(1);

    /* ABBA    ABBA 9.11.3.10    M    LV    3-n */
    auto consumed = dissect_lv( &abba, d, ctx);
    d.step(consumed);

    /*21    Authentication parameter RAND (5G authentication challenge)    Authentication
     * parameter RAND     9.11.3.16    O    TV    17*/
    // ELEM_OPT_TV(0x21, , DE_AUTH_PARAM_RAND, " - 5G authentication challenge");
    consumed = dissect_opt_tv( &authentication_parameter_rand, d, ctx);
    d.step(consumed);

    /*20    Authentication parameter AUTN (5G authentication challenge)    Authentication
     * parameter AUTN     9.11.3.15    O    TLV    18*/
    // ELEM_OPT_TLV(0x20, , DE_AUTH_PARAM_AUTN, " - 5G authentication challenge");
    consumed = dissect_opt_tlv( &authentication_parameter_autn, d, ctx);
    d.step(consumed);

    /*78  EAP message 9.11.2.2    O    TLV-E    7-1503 */
    consumed = dissect_opt_tlv_e( &eap_message, d, ctx);
    d.step(consumed);

    return uc.length;
}

namespace mm {



} // namespace
