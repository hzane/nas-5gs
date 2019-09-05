#include "../dissect_nas5g.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"

/* 8.3.4 PDU session authentication command */
int sm::dissect_pdu_ses_auth_cmd(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-authentication-command", d, 0);    

    /* Direction: network to UE */
    down_link(d.pinfo);

    /* EAP message 9.11.2.2    M    LV-E    6-1502 */
    auto consumed = dissect_elem_lv_e(nullptr, &eap_msg, d, ctx);
    d.step(consumed);

    /*7B    Extended protocol configuration options  9.11.4.6 O TLV-E 4-65538*/
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed); 

    return uc.length;
}
