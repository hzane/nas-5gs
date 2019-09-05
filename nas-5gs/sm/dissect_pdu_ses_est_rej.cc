#include "../dissect_nas5g.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"
#include "pdu_ses.hh"
#include "pdu_ses_est.hh"

using namespace nas;
using namespace sm;

/*  8.3.3 PDU session establishment reject */
int sm::dissect_pdu_ses_est_rej(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-establishment-reject", d, 0);

    /* Direction: network to UE */
    d.pinfo->dir = pi_dir::dl;

    /*  5GSM cause 9.11.4.2    M    V    1 */
    // ELEM_MAND_V(,DE_NAS_5GS_SM_5GSM_CAUSE, " - ESM cause",);
    auto consumed = dissect_elem_v(nullptr, &sm_cause, d, ctx);
    d.step(consumed);

    /*37    Back-off timer value    GPRS timer 3 9.11.2.5    O    TLV    3 */
    // ELEM_OPT_TLV(0x37, , DE_GPRS_TIMER_3, " - Back-off timer value");
    consumed = dissect_opt_elem_tlv(nullptr, &backoff_gprs_timer3, d, ctx);
    d.step(consumed);

    /*F-  Allowed SSC mode 9.11.4.5    O    TV    1*/
    // ELEM_OPT_TV_SHORT( 0xF0, , DE_NAS_5GS_SM_5GSM_ALLOWED_SSC_MODE, );
    consumed = dissect_opt_elem_tv_short(nullptr, &allowed_ssc_mode, d, ctx);
    d.step(consumed);

    /*78  EAP message 9.11.2.2    O    TLV - E    7 - 1503*/
    // ELEM_OPT_TLV_E(0x78, , DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eap_msg, d, ctx);
    d.step(consumed);

    /*7B    Extended protocol configuration options   9.11.4.6    O    TLV - E    4 - 65538*/
    // ELEM_OPT_TLV_E(0x7B, , DE_ESM_EXT_PCO, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);

    /* TBD	Re-attempt indicator 9.11.4.17	O	TLV	3     */
    d.step(3);

    /*61	5GSM congestion re-attempt indicator  9.11.4.21	O	TLV	3    */
    consumed = dissect_opt_elem_tlv(nullptr, &sm_congestion_reattempt, d, ctx);
    d.step(consumed);
        
    return uc.length;
}

