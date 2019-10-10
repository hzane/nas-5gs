#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

// PDU session reactivation result   9.11.3.42
result_t die_pdu_session_reactivation_result(dissector                          d,
                                             context*                           ctx,
                                             pdu_session_reactivation_result_t* ret) {
    const use_context uc(&d, ctx, "pdu-session-reactivation-result", 30);

    ret->psi_a = d.uint8(true);
    ret->psi_b = d.uint8(true);

    // 5-34 is optional

    return {2};
}
