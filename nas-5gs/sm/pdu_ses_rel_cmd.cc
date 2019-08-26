#include "../dissect_nas_5gs.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"

/* * 8.3.14 PDU session release command */
int sm::pdu_ses_rel_cmd(dissector d, context* ctx) {
    use_context uc(ctx, "pdu-session-release-command");

    /* Direction: network to UE */
    d.pinfo->dir = pi_dir::dl;

    /* 5GSM cause    5GSM cause 9.11.4.2    M    V    1 */
    // ELEM_MAND_V(, DE_NAS_5GS_SM_5GSM_CAUSE,);
    auto consumed = dissect_elem_v(nullptr, &sm_cause, d, ctx);
    d.step(consumed);

    /*37    Back-off timer value    GPRS timer 3 9.11.3.21    O    TLV    3 */
    // ELEM_OPT_TLV(0x37, GSM_A_PDU_TYPE_GM, DE_GPRS_TIMER_3, " - Back-off timer value");
    consumed = dissect_opt_elem_tlv(nullptr, &backoff_gprs_timer3, d, ctx);
    d.step(consumed);

    /*78    EAP message    EAP message 9.10.2.2    O    TLV - E    7 - 1503*/
    // ELEM_OPT_TLV_E(0x78, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eap_msg, d, ctx);
    d.step(consumed);

    /*7B    Extended protocol configuration options    Extended protocol configuration
     * options    9.11.4.2    O    TLV - E    4 - 65538*/
    // ELEM_OPT_TLV_E(0x7B, NAS_PDU_TYPE_ESM, DE_ESM_EXT_PCO, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);

    return d.tvb->reported_length;
}
