#include "../dissect_nas5g.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"

namespace sm_pdu_ses_est {

}
using namespace nas;
using namespace sm;
/*
 * 8.3.3 PDU session establishment reject
 */
int sm::pdu_ses_est_rej(dissector d, context* ctx) {
    const auto  len = d.length;
    use_context uc(ctx, "pdu-session-establishment-reject");

    using namespace sm_pdu_ses_est;

    /* Direction: network to UE */
    d.pinfo->dir = pi_dir::dl;

    /* 5GSM cause    5GSM cause 9.11.4.2    M    V    1 */
    // ELEM_MAND_V(,DE_NAS_5GS_SM_5GSM_CAUSE, " - ESM cause",);
    auto consumed = dissect_elem_v(nullptr, &sm_cause, d, ctx);
    d.step(consumed);

    /*37    Back-off timer value    GPRS timer 3 9.10.2.5    O    TLV    3 */
    // ELEM_OPT_TLV(0x37, GSM_A_PDU_TYPE_GM, DE_GPRS_TIMER_3, " - Back-off timer value");
    consumed = dissect_opt_elem_tlv(nullptr, &backoff_gprs_timer3, d, ctx);
    d.step(consumed);

    /*F-    Allowed SSC mode    Allowed SSC mode 9.11.4.3    O    TV    1*/
    // ELEM_OPT_TV_SHORT(
    //     0xF0, , DE_NAS_5GS_SM_5GSM_ALLOWED_SSC_MODE, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &allowed_ssc_mode, d, ctx);
    d.step(consumed);

    /*78    EAP message    EAP message 9.11.3.14    O    TLV - E    7 - 1503*/
    // ELEM_OPT_TLV_E(0x78, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eap_msg, d, ctx);
    d.step(consumed);

    /*7B    Extended protocol configuration options    Extended protocol configuration
     * options    9.11.4.2    O    TLV - E    4 - 65538*/
    // ELEM_OPT_TLV_E(0x7B, NAS_PDU_TYPE_ESM, DE_ESM_EXT_PCO, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);

    // extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    d.extraneous_data_check(0);

    return len;
}
namespace sm_pdu_ses_est {

} // namespace sm_pdu_ses_est
