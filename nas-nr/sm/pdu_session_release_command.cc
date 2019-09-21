#include "../dissect_sm_msg.hh"
#include "../ber.hh"
#include "../common.hh"
#include "../packet_info.hh"

using namespace nas;
using namespace sm;

/* * 8.3.14 PDU session release command */
int sm::dissect_pdu_session_release_command(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-release-command", d, 0);

    /* Direction: network to UE */
    down_link(d.pinfo);

    /* 5GSM cause 9.11.4.2    M    V    1 */
    (void) dissect_nrsm_cause(d, ctx);
    d.step(1);

    /*37    Back-off timer value    GPRS timer 3 9.11.2.25    O    TLV    3 */
    // ELEM_OPT_TLV(0x37, , DE_GPRS_TIMER_3, " - Back-off timer value");
    auto consumed = dissect_opt_tlv(nullptr, &backoff_gprs_timer3, d, ctx);
    d.step(consumed);

    /*78  EAP message 9.10.2.2    O    TLV-E    7 - 1503*/
    // ELEM_OPT_TLV_E(0x78, , DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_tlv_e(nullptr, &cmn::eap_message, d, ctx);
    d.step(consumed);

    /*61	5GSM congestion re-attempt indicator 9.11.4.21	O	TLV	3 */
    consumed = dissect_opt_tlv(nullptr, &congestion_reattempt, d, ctx);
    d.step(consumed);

    /*7B    Extended protocol configuration options 9.11.4.6 O TLV-E 4-65538*/
    // ELEM_OPT_TLV_E(0x7B, , DE_ESM_EXT_PCO, NULL);
    consumed = dissect_opt_tlv_e(nullptr, &extended_pco, d, ctx);
    d.step(consumed);

    return uc.length;
}
