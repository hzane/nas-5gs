#include "../dissect_nas_5gs.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"

/*
 * 8.3.13 PDU session release reject
 */
int sm::pdu_ses_rel_rej(dissector d, context* ctx) {
    use_context uc(ctx, "pdu-session-release-reject");

    /* Direction: network to UE */
    d.pinfo->dir = pi_dir::dl;

    /* 5GSM cause    5GSM cause 9.11.4.1    M    V    1 */
    // ELEM_MAND_V(,DE_NAS_5GS_SM_5GSM_CAUSE,);
    auto consumed = dissect_elem_v(nullptr, &sm_cause, d, ctx);
    d.step(consumed);

    /*7B    Extended protocol configuration options    Extended protocol configuration
     * options    9.11.4.2    O    TLV - E    4 - 65538*/
    // ELEM_OPT_TLV_E(0x7B, , DE_ESM_EXT_PCO, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);

    return d.tvb->reported_length;
}
