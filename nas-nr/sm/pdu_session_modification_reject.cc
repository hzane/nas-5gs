#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*  8.3.8    PDU session modification reject */
int dissect_pdu_session_modification_reject(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-modification-reject", d, 3);

    /* Direction: network to UE */
    down_link(d.pinfo);

    /* 5GSM cause 9.11.4.2    M    V    1 */

    /*37    Back-off timer value    GPRS timer 3 9.11.2.5    O    TLV    3 */
    // ELEM_OPT_TLV(0x37, , DE_GPRS_TIMER_3, " - Back-off timer value");

    return uc.length;
}
