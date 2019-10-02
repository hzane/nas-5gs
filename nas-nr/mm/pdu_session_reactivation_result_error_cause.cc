#include "../common/dissector.hh"
#include "../common/use_context.hh"

//  9.11.3.43    PDU session reactivation result error cause
int dissect_pdu_session_reactive_result_error_cause(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "pdu-session-reactivation-result-error", 0);

    return uc.length;
}
