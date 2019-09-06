#include "../dissect_nas5g.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"
#include "../packet_info.hh"

/* * 8.3.10 PDU session modification complete */
int sm::dissect_pdu_ses_modification_cmpl(dissector d, context* ctx) {    
    const use_context uc(ctx, "pdu-session-modification-complete", d, 2);

    /* Direction: UE to network */
    up_link(d.pinfo);    

    /*7B Extended protocol configuration options 9.11.4.6    O    TLV - E    4 - 65538*/
    // ELEM_OPT_TLV_E(0x7B, , DE_ESM_EXT_PCO, NULL);
    const auto consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);

    /*59    5GSM cause    5GSM cause 9.11.4.2    O    TV    2*/
    // consumed = dissect_opt_elem_tv(nullptr, &sm_cause, d, ctx);
    // d.step(consumed);

    /*It is possible for UEs compliant with earlier versions of this specification to
     * include the 5GSM cause IE with IEI 59 in the PDU SESSION MODIFICATION COMPLETE
     * message, and therefore the IEI 59 cannot be used for other optional IEs other than
     * the 5GSM cause IE for future extensions of the PDU SESSION MODIFICATION COMPLETE
     * message.*/

    return uc.length;
}
