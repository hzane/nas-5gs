#include "../common/dissector.hh"
#include "../common/use_context.hh"

// 9.11.3.63	MA PDU session information
int dissect_ma_pdu_session_information(dissector d, context* ctx){
    const use_context uc(&d, ctx, "ma-pdu-session-information", -1);

    return 1;
}
