#include "../dissect_nas5g.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"

/* * 8.3.10 PDU session modification complete */
int sm::pdu_ses_mod_comp(dissector d, context* ctx) {
    auto        len = d.length;
    use_context uc(ctx, "pdu-session-modification-complete");

    /* Direction: UE to network */
    d.pinfo->dir = pi_dir::ul;

    /*7B Extended protocol configuration options 9.11.4.6    O    TLV - E    4 - 65538*/
    // ELEM_OPT_TLV_E(0x7B, , DE_ESM_EXT_PCO, NULL);
    auto consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);

    /*59    5GSM cause    5GSM cause 9.11.4.2    O    TV    2*/
    // ELEM_OPT_TV(0x59, , DE_NAS_5GS_SM_5GSM_CAUSE, NULL);
    // consumed = dissect_opt_elem_tv(nullptr, &sm_cause, d, ctx);
    // d.step(consumed);

    /*It is possible for UEs compliant with earlier versions of this specification to
     * include the 5GSM cause IE with IEI 59 in the PDU SESSION MODIFICATION COMPLETE
     * message, and therefore the IEI 59 cannot be used for other optional IEs other than
     * the 5GSM cause IE for future extensions of the PDU SESSION MODIFICATION COMPLETE
     * message.*/

    // extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    d.extraneous_data_check(0);

    return len;
}
