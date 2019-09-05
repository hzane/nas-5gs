#include "../dissect_mm_msg.hh"

// int                       dissect_pdu_ses_react_res_err_c(dissector d, context*);


extern const element_meta mm::pdu_ses_react_res_error_c = {
    0x72,
    "PDU session reactivation result error cause",
    dissect_pdu_ses_react_res_err_c,
    nullptr,
};

//  *   9.11.3.43    PDU session reactivation result error cause
int mm::dissect_pdu_ses_react_res_err_c(dissector d, context*) {
    auto len = d.length;
    /*Partial service area list*/
    while (d.length > 0) {
        d.add_item(1, &hf_pdu_session_id, enc::be);
        d.step(1);
        d.add_item(1, &hf_mm_cause, enc::be);
        d.step(1);
    }
    return len;
}

