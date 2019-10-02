#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*  8.3.3 PDU session establishment reject */
int dissect_pdu_session_establishment_reject(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "pdu-session-establishment-reject", 0);

    /* Direction: network to UE */
    down_link(d.pinfo);

    return uc.length;
}
