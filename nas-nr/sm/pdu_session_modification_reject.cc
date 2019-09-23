#include "../common/ber.hh"
#include "../common/dissect_sm_msg.hh"
#include "../common/packet_info.hh"

/*  8.3.8    PDU session modification reject */
int sm::dissect_pdu_session_modification_reject(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-modification-reject", d, 3);

    /* Direction: network to UE */
    down_link(d.pinfo);

    /* 5GSM cause 9.11.4.2    M    V    1 */
    dissect_nrsm_cause(d, ctx);
    d.step(1);

    /*37    Back-off timer value    GPRS timer 3 9.11.2.5    O    TLV    3 */
    // ELEM_OPT_TLV(0x37, , DE_GPRS_TIMER_3, " - Back-off timer value");
    auto consumed = dissect_opt_tlv(nullptr, &backoff_gprs_timer3, d, ctx);
    d.step(consumed);

    /*7B    Extended protocol configuration options   9.11.4.6    O    TLV - E    4 - 65538*/
    consumed = dissect_opt_tlv_e(nullptr, &extended_pco, d, ctx);
    d.step(consumed);

    /*TBD	Re-attempt indicator 9.11.4.17	O	TLV	3    */
    // d.step(3);

    /*61 5GSM congestion re-attempt indicator    9.11.4.21	O	TLV	3    */
    consumed = dissect_opt_tlv(nullptr, &congestion_reattempt, d, ctx);
    d.step(consumed);

    return uc.length;
}
