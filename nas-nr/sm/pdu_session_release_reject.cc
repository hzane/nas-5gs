#include "../common/ber.hh"
#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"
#include "common/packet.hh"

/*  8.3.13 PDU session release reject */
int sm::dissect_pdu_session_release_reject(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-release-reject", d, 0);

    /* Direction: network to UE */
    down_link(d.packet);

    /* 5GSM cause 9.11.4.2    M    V    1 */
    auto consumed = dissect_nrsm_cause(d, ctx);
    d.step(consumed);

    /* 7B    Extended protocol configuration options   9.11.4.6    O    TLV - E    4 - 65538*/
    consumed = dissect_opt_tlv_e( &extended_pco, d, ctx);
    d.step(consumed);

    return uc.length;
}
