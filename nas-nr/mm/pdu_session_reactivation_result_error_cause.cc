#include "../dissect_mm_msg.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

const element_meta mm::pdu_session_reactive_result_error_cause = {
    0x72,
    "PDU session reactivation result error cause",
    dissect_pdu_session_reactive_result_error_cause,
    nullptr,
};

//  9.11.3.43    PDU session reactivation result error cause
int mm::dissect_pdu_session_reactive_result_error_cause(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-reactivation-result-error", d, 0);
    
    /*Partial service area list*/
    while (d.length > 0) {
        (void) d.add_item(1, &hf_pdu_session_id, enc::be);
        d.step(1);
        (void) d.add_item(1, &hf_mm_cause, enc::be);
        d.step(1);
    }
    return uc.length;
}

