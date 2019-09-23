#include "../common/ber.hh"
#include "../common/common.hh"
#include "../common/dissect_sm_msg.hh"

/*  8.3.5 PDU session authentication complete */
int sm::dissect_pdu_session_authentication_complete(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-authentication-complete", d, 0);

    /* Direction: UE to network */
    up_link(d.pinfo);

    /* EAP message 9.11.2.2    M    LV-E    6-1502 */
    auto consumed = dissect_lv_e(nullptr, &cmn::eap_message, d, ctx);
    d.step(consumed);

    /*7B    Extended protocol configuration options 9.11.4.6    O    TLV - E    4 - 65538*/
    consumed = dissect_opt_tlv_e(nullptr, &extended_pco, d, ctx);
    d.step(consumed);

    return uc.length;
}
