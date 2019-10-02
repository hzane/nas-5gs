#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.3.2 PDU session establishment accept */
int dissect_pdu_session_establishment_accept(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "pdu-session-establishment-accept", -1);

    /* Direction: network to UE */
    down_link(d.pinfo);


    return uc.length;
}
