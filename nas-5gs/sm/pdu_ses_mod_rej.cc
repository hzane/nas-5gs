#include "../dissect_nas_5gs.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"


/*
 * 8.3.8    PDU session modification reject
 */
int sm::pdu_ses_mod_rej(dissector d, context* ctx) {
    use_context uc(ctx, "pdu-session-modification-reject");

    /* Direction: network to UE */
    d.pinfo->dir = pi_dir::dl;

    /* 5GSM cause    5GSM cause 9.11.4.1    M    V    1 */
    // ELEM_MAND_V(,DE_NAS_5GS_SM_5GSM_CAUSE,);
    auto consumed = dissect_elem_v(nullptr, &sm_cause, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*37    Back-off timer value    GPRS timer 3 9.11.3.21    O    TLV    3 */
    // ELEM_OPT_TLV(0x37, GSM_A_PDU_TYPE_GM, DE_GPRS_TIMER_3, " - Back-off timer value");
    consumed = dissect_opt_elem_tlv(nullptr, &backoff_gprs_timer3, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*7B    Extended protocol configuration options    Extended protocol configuration
     * options    9.11.4.2    O    TLV - E    4 - 65538*/
    // ELEM_OPT_TLV_E(0x7B, NAS_PDU_TYPE_ESM, DE_ESM_EXT_PCO, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);

    return d.tvb->reported_length;
}

