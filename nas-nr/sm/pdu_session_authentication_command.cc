#include "../dissect_nas5g.hh"
#include "../dissect_sm_msg.hh"
#include "../ber.hh"
#include "../common.hh"

/* 8.3.4 PDU session authentication command */
int sm::dissect_pdu_ses_authentication_cmd(dissector d, context* ctx) {
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
