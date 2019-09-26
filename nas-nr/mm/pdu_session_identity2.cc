#include "../common/dissector.hh"
#include "../common/use_context.hh"

// PDU session ID 2 9.11.3.41
int dissect_pdu_session_id_set(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-identity2", d, -1);

    // identity value as defined in 3GPP TS 24.007 [11]
    return 1;
}
