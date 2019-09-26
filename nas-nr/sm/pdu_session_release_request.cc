#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.3.12 PDU session release request */
int dissect_pdu_session_release_request(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-release-request", d, 0);

    /* Direction: UE to network */
    up_link(d.pinfo);


    return uc.length;
}
