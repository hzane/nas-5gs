#include "../dissect_nas5g.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"

/*  8.3.11 PDU session modification command reject */
int sm::dissect_pdu_ses_mod_com_rej(dissector d, context* ctx) {    
    use_context uc(ctx, "pdu-session-modification-command-reject", d, 0);

    /* Direction: UE to network */
    up_link(d.pinfo);    

    /* 5GSM cause 9.11.4.2    M    V    1 */
    auto consumed = dissect_elem_v(nullptr, &sm_cause, d, ctx);
    d.step(consumed);

    /*7B    Extended protocol configuration options    9.11.4.6    O    TLV - E    4 - 65538*/
    // ELEM_OPT_TLV_E(0x7B, , DE_ESM_EXT_PCO, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);

    return uc.length;
}
