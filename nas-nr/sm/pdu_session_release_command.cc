#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* * 8.3.14 PDU session release command */
int dissect_pdu_session_release_command(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-release-command", d, 0);

    /* Direction: network to UE */
    down_link(d.pinfo);

    /* 5GSM cause 9.11.4.2    M    V    1 */

    return uc.length;
}
