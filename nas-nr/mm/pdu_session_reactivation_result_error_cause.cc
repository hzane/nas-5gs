#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"


using namespace nas;
using namespace mm;

extern const tag_field hf_pdu_session_id;
extern const tag_field hf_nrmm_cause;

//  9.11.3.43    PDU session reactivation result error cause
int mm::dissect_pdu_session_reactive_result_error_cause(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-reactivation-result-error", d, 0);

    /*Partial service area list*/
    while (d.length > 0) {
        (void) d.add_item(&hf_pdu_session_id);
        d.step(1);
        (void) d.add_item( &hf_nrmm_cause);
        d.step(1);
    }
    return uc.length;
}
