#include "../common/use_context.hh"
#include "mm_dissects.hh"

const tag_field hf_ma_pdu_session_information = {
    "MA PDU session information",
    0x0fu,
    (const v_string[]){
        {0x01, "MA PDU session network upgrade is allowed"},
        {0, nullptr},
    },
};
// 9.11.3.63	MA PDU session information
int mm::dissect_ma_pdu_session_information(dissector d, context* ctx) {
    const use_context uc(ctx, "ma-pdu-session-information", d, -1);

    d.add_item(&hf_ma_pdu_session_information);
    return 1;
}