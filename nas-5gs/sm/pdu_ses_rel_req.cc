#include "../dissect_nas_5gs.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"

/*
 * 8.3.12 PDU session release request
 */
int sm::pdu_ses_rel_req(dissector d, context* ctx) {
    use_context uc(ctx, "pdu-session-release-request");
    /* Direction: UE to network */
    d.pinfo->dir = pi_dir::ul;

    /* 59    5GSM cause    5GSM cause 9.11.4.2    O    TV    2 */
    // ELEM_OPT_TV(0x59, , DE_NAS_5GS_SM_5GSM_CAUSE, NULL);
    auto consumed = dissect_opt_elem_tv(nullptr, &sm_cause, d, ctx);
    d.step(consumed);

    /* 7B    Extended protocol configuration options    Extended protocol configuration
     * options    9.11.4.2    O    TLV - E    4 - 65538*/
    // ELEM_OPT_TLV_E(0x7B, , DE_ESM_EXT_PCO, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);

    return d.tvb->length;
}
