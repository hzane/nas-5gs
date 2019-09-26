#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.3.7 PDU session modification request */
int dissect_pdu_session_modification_request(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-modification-request", d, 0);

    /* Direction: UE to network */
    up_link(d.pinfo);


    // It is possible for UEs compliant with earlier versions of this specification
    // to send the Mapped EPS bearer contexts IE with IEI of value "7F" for this message.
    return uc.length;
}
