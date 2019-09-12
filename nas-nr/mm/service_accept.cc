#include "../dissect_mm_msg.hh"
#include "../ber.hh"

using namespace nas;
using namespace mm;

/*  8.2.17 Service accept */
int mm::dissect_service_accept(dissector d, context* ctx) {    
    const use_context uc(ctx, "service-accept", d, 3);
    // network to UE
    down_link(d.pinfo);

    /*50  PDU session status     9.11.3.44    O    TLV    4-34*/
    // ELEM_OPT_TLV(0x50, , DE_NAS_5GS_MM_PDU_SES_STATUS, NULL);
    auto consumed = dissect_opt_tlv(nullptr, &pdu_ses_status, d, ctx);
    d.step(consumed);

    /*26    PDU session reactivation result 9.11.3.42 O    TLV    4-32*/
    // ELEM_OPT_TLV(0x26, , DE_NAS_5GS_MM_PDU_SES_REACT_RES, NULL);
    consumed = dissect_opt_tlv(nullptr, &pdu_ses_react_res, d, ctx);
    d.step(consumed);


    /*72 PDU session reactivation result error cause 9.11.3.43    O    TLV-E    5-515 */
    // ELEM_OPT_TLV_E(  0x72, , DE_NAS_5GS_MM_PDU_SES_REACT_RES_ERR_C, NULL);
    consumed = dissect_opt_tlv_e(nullptr, &pdu_session_reactive_result_error_cause, d, ctx);
    d.step(consumed);


    /*78    EAP message 9.11.2.2    O    TLV-E    7-1503*/
    // ELEM_OPT_TLV_E(0x78, , DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_tlv_e(nullptr, &cmn::eap_msg, d, ctx);
    d.step(consumed);

    // XX	T3448 value	GPRS timer 3  9.11.2.4 O TLV 3
    (void)  t3348_gprs_timer3;
    // consumed = dissect_opt_tlv(nullptr, &t3348_gprs_timer3, d, ctx);
    // d.step(consumed);


    return uc.length;
}

