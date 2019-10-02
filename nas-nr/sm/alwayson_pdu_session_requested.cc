#include "../common/dissector.hh"
#include "../common/use_context.hh"


// 9.11.4.4 Always-on PDU session requested
int dissect_alwayson_pdu_session_requested(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "alwayson-pdu-session-requested", -1);


    return 1;
}
