#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*  9.11.4.3 Always-on PDU session indication */
int dissect_always_on_pdu_session_indication(dissector d, context* ctx) {
    const use_context uc(ctx, "always-on-pdu-session-indication", d, -1);


    return 1;
}
