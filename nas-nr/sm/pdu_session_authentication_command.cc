#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.3.4 PDU session authentication command */
int dissect_pdu_session_authentication_command(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "pdu-session-authentication-command", 0);

    /* Direction: network to UE */
    down_link(d.pinfo);

    /* EAP message 9.11.2.2    M    LV-E    6-1502 */

    return uc.length;
}
