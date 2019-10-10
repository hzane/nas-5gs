#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

// PDU session status   9.11.3.44
result_t die_pdu_session_status(dissector d, context* ctx, pdu_session_status_t* ret) {
    const use_context uc(&d, ctx, "pdu-session-reactivation-result",30);

    ret->psi_a = d.uint8(true);
    ret->psi_b = d.uint8(true);
    // All bits in octet 5 to 34 are spare and shall be coded as zero,
    // if the respective octet is included in the information element
    return {2};
}
