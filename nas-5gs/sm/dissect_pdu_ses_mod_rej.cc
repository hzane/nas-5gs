#include "../dissect_nas5g.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"
#include "pdu_ses.hh"
#include "pdu_ses_mod.hh"

/*  8.3.8    PDU session modification reject */
int sm::dissect_pdu_ses_mod_rej(dissector d, context* ctx) {    
    const use_context uc(ctx, "pdu-session-modification-reject", d, 0);

    /* Direction: network to UE */
    down_link(d.pinfo);    

    /* 5GSM cause 9.11.4.2    M    V    1 */
    auto consumed = dissect_elem_v(nullptr, &sm_cause, d, ctx);
    d.step(consumed);

    /*37    Back-off timer value    GPRS timer 3 9.11.2.5    O    TLV    3 */
    // ELEM_OPT_TLV(0x37, , DE_GPRS_TIMER_3, " - Back-off timer value");
    consumed = dissect_opt_elem_tlv(nullptr, &backoff_gprs_timer3, d, ctx);
    d.step(consumed);

    /*7B    Extended protocol configuration options   9.11.4.6    O    TLV - E    4 - 65538*/
    // ELEM_OPT_TLV_E(0x7B, , DE_ESM_EXT_PCO, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);

    /*TBD	Re-attempt indicator 9.11.4.17	O	TLV	3    */
    d.step(3);

    /*61 5GSM congestion re-attempt indicator    9.11.4.21	O	TLV	3    */
    consumed = dissect_opt_elem_tlv(nullptr, &sm_congestion_reattempt, d, ctx);
    d.step(consumed); 

    return uc.length;
}
