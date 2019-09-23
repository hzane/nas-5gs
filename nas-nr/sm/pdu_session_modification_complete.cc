#include "../common/ber.hh"
#include "../common/dissect_sm_msg.hh"
#include "../common/packet_info.hh"

/* * 8.3.10 PDU session modification complete */
int sm::dissect_pdu_session_modification_complete(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-modification-complete", d, 2);

    /* Direction: UE to network */
    up_link(d.pinfo);

    /*7B Extended protocol configuration options 9.11.4.6    O    TLV - E    4 - 65538*/
    const auto consumed = dissect_opt_tlv_e(nullptr, &extended_pco, d, ctx);
    d.step(consumed);

    /*59    5GSM cause    5GSM cause 9.11.4.2    O    TV    2*/
    // consumed = dissect_opt_tv(nullptr, &nrsm_cause, d, ctx);
    // d.step(consumed);

    /*It is possible for UEs compliant with earlier versions of this specification to
     * include the 5GSM cause IE with IEI 59 in the PDU SESSION MODIFICATION COMPLETE
     * message, and therefore the IEI 59 cannot be used for other optional IEs other than
     * the 5GSM cause IE for future extensions of the PDU SESSION MODIFICATION COMPLETE
     * message.*/

    return uc.length;
}
