#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.3.9 PDU session modification command */
int dissect_pdu_session_modification_command(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "pdu-session-modification-command", 8);

    /* Direction: network to UE */
    down_link(d.pinfo);



    return uc.length;
}
