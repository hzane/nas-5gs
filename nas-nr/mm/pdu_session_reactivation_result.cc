#include "../common/dissector.hh"
#include "../common/use_context.hh"


// PDU session reactivation result   9.11.3.42
int dissect_pdu_session_reactive_result(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "pdu-session-reactivation-result", 30);

    // 5-34 is optional

    return uc.length;
}
