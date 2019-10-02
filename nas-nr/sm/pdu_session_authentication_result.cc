#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.3.6	PDU session authentication result */
int dissect_pdu_session_authentication_result(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "pdu-session-authentication-result", 0);

    /* Direction: network to UE */
    down_link(d.pinfo);

    /*78  EAP message 9.10.2.2    O    TLV-E    7 - 1503*/

    /* 7B    Extended protocol configuration options  9.11.4.6 O TLV-E    4 - 65538*/

    return uc.length;
}
