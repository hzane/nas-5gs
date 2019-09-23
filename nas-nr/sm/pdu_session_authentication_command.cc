#include "../common/ber.hh"
#include "../common/common.hh"
#include "../common/dissect_nas5g.hh"
#include "../common/dissect_sm_msg.hh"

/* 8.3.4 PDU session authentication command */
int sm::dissect_pdu_session_authentication_command(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-authentication-command", d, 0);

    /* Direction: network to UE */
    down_link(d.pinfo);

    /* EAP message 9.11.2.2    M    LV-E    6-1502 */
    auto consumed = dissect_lv_e(nullptr, &cmn::eap_message, d, ctx);
    d.step(consumed);

    /*7B    Extended protocol configuration options  9.11.4.6 O TLV-E 4-65538*/
    consumed = dissect_opt_tlv_e(nullptr, &extended_pco, d, ctx);
    d.step(consumed);

    return uc.length;
}
