#include "../dissect_mm_msg.hh"
#include "../ber.hh"


using namespace nas;

/* 8.2.18 Service reject */
int mm::dissect_service_reject(dissector d, context* ctx) {
    const use_context uc(ctx, "service-reject", d, 3);
    // network to UE
    down_link(d.pinfo);

    /* 5GMM cause  9.11.3.2  M   V   1 */
    NASNR_AUTO(int) consumed = dissect_mm_cause(d, ctx);
    d.step(consumed);

    /*50  PDU session status 9.11.3.44    O    TLV    4 - 34*/
    consumed = dissect_opt_tlv(nullptr, &pdu_ses_status, d, ctx);
    d.step(consumed);

    /* 5F  T3346 value GPRS timer 2     9.11.2.4   O   TLV 3 */
    consumed = dissect_opt_tlv(nullptr, &t3346_gprs_timer2, d, ctx);
    d.step(consumed);

    /* 78   EAP message 9.11.2.2    O    TLV-E    7-1503 */
    consumed = dissect_opt_tlv_e(nullptr, &cmn::eap_msg, d, ctx);
    d.step(consumed);

    // XX	T3448 value	GPRS timer 3    9.11.2.4 O TLV 3
    (void)  t3348_gprs_timer3;

    return uc.length;
}


