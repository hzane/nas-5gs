#include "../dissect_nas5g.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"

/* 8.3.4 PDU session authentication command */
int sm::dissect_pdu_ses_auth_cmd(dissector d, context* ctx) {
    use_context uc(ctx, "pdu-session-authentication-command", d);
    auto        len = d.length;

    /* Direction: network to UE */
    down_link(d.pinfo);

    /* EAP message 9.11.2.2    M    LV-E    6-1502 */
    // ELEM_MAND_LV_E(, DE_NAS_5GS_CMN_EAP_MESSAGE,);
    auto consumed = dissect_elem_lv_e(nullptr, &eap_msg, d, ctx);
    d.step(consumed);

    /*7B    Extended protocol configuration options  9.11.4.6 O TLV-E 4-65538*/
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);

    return len;
}
