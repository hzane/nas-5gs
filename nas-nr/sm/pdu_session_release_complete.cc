#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.3.15 PDU session release complete */
int dissect_pdu_session_release_complete(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-release-complete", d, 0);

    /* Direction: UE to network */
    up_link(d.pinfo);


    return uc.length;
}
