#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.3.11	PDU session modification command reject */
int dissect_pdu_session_modification_command_reject(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "pdu-session-modification-command-reject", 0);

    /* Direction: UE to network */
    up_link(d.pinfo);

    return uc.length;
}
