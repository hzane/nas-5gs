#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"
#include "../gsm.hh"


using namespace cmn;
using namespace nas;

/*  8.2.9 Registration reject */
int mm::dissect_registration_rej(dissector d, context* ctx) {    
    const use_context uc(ctx, "registration-reject", d, 0);

    /* 5GMM cause   9.11.3.2  M   V   1 */
    auto consumed = dissect_elem_v(nullptr, &mm_cause, d, ctx);
    d.step(consumed);

    /* 5F  T3346 value GPRS timer 2     9.11.2.4   O   TLV 3 */
    // ELEM_OPT_TLV(0x5F, , DE_GPRS_TIMER_2, " - T3346 value");
    consumed = dissect_opt_elem_tlv(nullptr, &t3346_gprs_timer2, d, ctx);
    d.step(consumed);

    /* 16    T3502 value    GPRS timer 2 9.11.2.4    O    TLV    3 */
    // ELEM_OPT_TLV(0x16, , DE_GPRS_TIMER_2, " - T3502 value");
    consumed = dissect_opt_elem_tlv(nullptr, &t3502_gprs_timer_2, d, ctx);
    d.step(consumed);

    /* 78    EAP message  9.11.2.2    O    TLV-E    7-1503 */
    // ELEM_OPT_TLV_E(0x78, , DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eap_msg, d, ctx);
    d.step(consumed);    

    return uc.length;
}

