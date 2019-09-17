#include "mm_dissects.hh"
#include "../field_meta.hh"

const v_string ma_pdu_session_information_values[]={
    {0x01, "MA PDU session network upgrade is allowed"},
    {0, nullptr,},
};
const field_meta hf_ma_pdu_session_information = {
    "MA PDU session information",
    "nas.nr.ma.pdu.session.information",
    ft::ft_uint8, fd::base_dec, ma_pdu_session_information_values, nullptr, nullptr, 0x0fu,
};
// 9.11.3.63	MA PDU session information
int mm::dissect_ma_pdu_session_information(dissector d, context* ctx){
    const use_context uc(ctx, "ma-pdu-session-information", d, -1);

    d.add_item(1, &hf_ma_pdu_session_information, enc::be);
    return 1;
}