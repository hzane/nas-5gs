#include "../dissect_nas5g.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"

/*
 * 8.3.4 PDU session authentication command
 */
int sm::pdu_ses_auth_cmd(dissector d, context* ctx) {
    auto        len = d.length;
    use_context uc(ctx, "pdu-session-authentication-command");

    /* Direction: network to UE */
    d.pinfo->dir = pi_dir::dl;

    /*EAP message    EAP message 9.11.2.2    M    LV-E    6-1502 */
    // ELEM_MAND_LV_E(, DE_NAS_5GS_CMN_EAP_MESSAGE,);
    auto consumed = dissect_elem_lv_e(nullptr, &eap_msg, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*7B    Extended protocol configuration options    Extended protocol configuration
     * options    9.11.4.2    O    TLV - E    4 - 65538*/
    // ELEM_OPT_TLV_E(0x7B, , , NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);

    return len;
}
