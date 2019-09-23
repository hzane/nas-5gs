#include "../common/ber.hh"
#include "../common/dissect_sm_msg.hh"
#include "../common/packet_info.hh"

/* 8.3.6	PDU session authentication result */
int sm::dissect_pdu_session_authentication_result(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-authentication-result", d, 0);

    /* Direction: network to UE */
    down_link(d.pinfo);

    /*78  EAP message 9.10.2.2    O    TLV-E    7 - 1503*/
    auto consumed = dissect_opt_tlv_e(nullptr, &cmn::eap_message, d, ctx);
    d.step(consumed);

    /* 7B    Extended protocol configuration options  9.11.4.6 O TLV-E    4 - 65538*/
    consumed = dissect_opt_tlv_e(nullptr, &extended_pco, d, ctx);
    d.step(consumed);

    return uc.length;
}
