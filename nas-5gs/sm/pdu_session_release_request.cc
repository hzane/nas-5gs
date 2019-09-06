#include "../dissect_nas5g.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"
#include "../packet_info.hh"

/* 8.3.12 PDU session release request */
int sm::dissect_pdu_ses_release_req(dissector d, context* ctx) {    
    const use_context uc(ctx, "pdu-session-release-request", d, 0);

    /* Direction: UE to network */
    up_link(d.pinfo);    

    /* 59 5GSM cause 9.11.4.2    O    TV    2 */
    auto consumed = dissect_opt_elem_tv(nullptr, &sm_cause, d, ctx);
    d.step(consumed);

    /* 7B    Extended protocol configuration options   9.11.4.6    O    TLV - E    4 - 65538*/
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);

    return uc.length;
}
