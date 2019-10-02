#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*  8.3.5 PDU session authentication complete */
int dissect_pdu_session_authentication_complete(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "pdu-session-authentication-complete", 0);

    /* Direction: UE to network */
    up_link(d.pinfo);

    /* EAP message 9.11.2.2    M    LV-E    6-1502 */

    /*7B    Extended protocol configuration options 9.11.4.6    O    TLV - E    4 - 65538*/

    return uc.length;
}
