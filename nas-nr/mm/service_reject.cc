#include "../dissect_mm_msg.hh"
#include "../ber.hh"


using namespace nas;

/* 8.2.18 Service reject */
int mm::dissect_service_reject(dissector d, context* ctx) {
    const use_context uc(ctx, "service-reject", d, 3);
    // network to UE
    down_link(d.pinfo);

    /* 5GMM cause  9.11.3.2  M   V   1 */
    /*    ELEM_MAND_V(,DE_NAS_5GS_MM_5GMM_CAUSE, );*/    
    auto consumed = dissect_mm_cause(d, ctx);
    d.step(consumed);

    /*50  PDU session status 9.11.3.44    O    TLV    4 - 34*/
    // ELEM_OPT_TLV(0x50, , DE_NAS_5GS_MM_PDU_SES_STATUS, NULL);
    consumed = dissect_opt_tlv(nullptr, &pdu_ses_status, d, ctx);
    d.step(consumed);

    /* 5F  T3346 value GPRS timer 2     9.11.2.4   O   TLV 3 */
    // ELEM_OPT_TLV(0x5F, , DE_GPRS_TIMER_2, " - T3346 value");
    consumed = dissect_opt_tlv(nullptr, &t3346_gprs_timer2, d, ctx);
    d.step(consumed);

    /* 78   EAP message 9.11.2.2    O    TLV-E    7-1503 */
    // ELEM_OPT_TLV_E(0x78, , DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_tlv_e(nullptr, &cmn::eap_msg, d, ctx);
    d.step(consumed);

    // XX	T3448 value	GPRS timer 3    9.11.2.4 O TLV 3
    
    return uc.length;
}


