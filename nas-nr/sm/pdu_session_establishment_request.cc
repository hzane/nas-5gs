#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.3.1 PDU session establishment request */
int dissect_pdu_session_establishment_request(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-establishment-request", d, 0);

    /* Direction: UE to network*/
    up_link(d.pinfo);


    return uc.length;
}
