#include "../common/dissector.hh"
#include "../common/use_context.hh"

// PDU session status   9.11.3.44
int dissect_pdu_session_status(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-status", d, 30);

    // All bits in octet 5 to 34 are spare and shall be coded as zero,
    // if the respective octet is included in the information element
    return uc.length;
}
