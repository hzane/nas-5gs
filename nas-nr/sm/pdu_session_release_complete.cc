#include "../common/ber.hh"
#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"
#include "common/packet.hh"

/* 8.3.15 PDU session release complete */
int sm::dissect_pdu_session_release_complete(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-release-complete", d, 0);

    /* Direction: UE to network */
    up_link(d.pinfo);

    /* 59 5GSM cause 9.11.4.2    O    TV    2 */
    auto consumed = dissect_opt_tv(nullptr, &nrsm_cause, d, ctx);
    d.step(consumed);

    /* 7B    Extended protocol configuration options  9.11.4.6 O TLV-E    4 - 65538*/
    consumed = dissect_opt_tlv_e(nullptr, &extended_pco, d, ctx);
    d.step(consumed);

    return uc.length;
}
