#include "../dissect_nas5g.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"

/* 8.3.16 5GSM status */
int sm::dissect_sm_status(dissector d, context* ctx) {    
    use_context uc(ctx, "5gsm-status", d, 0);

    /* Direction: both */
    both_link(d.pinfo);    

    /* 5GSM cause    5GSM cause 9.11.4.1    M    V    1 */
    // ELEM_MAND_V(, DE_NAS_5GS_SM_5GSM_CAUSE,);
    const auto consumed = dissect_elem_v(nullptr, &sm_cause, d, ctx);
    d.step(consumed);
    
    return uc.length;
}
