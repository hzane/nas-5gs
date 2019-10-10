#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

//  9.11.3.43    PDU session reactivation result error cause
result_t die_pdu_session_reactivation_result_error_cause(
    dissector                                      d,
    context*                                       ctx,
    pdu_session_reactivation_result_error_cause_t* ret) {
    const use_context uc(&d, ctx, "pdu-session-reactivation-result-error-cause", 0);
    while (d.length > 0) {
        pdu_session_reactivation_result_error_cause_t::cause_t v = {};
        de_uint8(d, ctx, &v.pdu_session_id).step(d);
        de_uint8(d, ctx, &v.cause).step(d);
        ret->causes.push_back(v);
    }
    return {uc.length};
}
