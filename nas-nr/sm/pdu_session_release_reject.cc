#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*  8.3.13 PDU session release reject */
int dissect_pdu_session_release_reject(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-release-reject", d, 0);

    /* Direction: network to UE */
    down_link(d.pinfo);


    return uc.length;
}
