#include "../base/ber.hh"
#include "../common/dissect_mm_msg.hh"

using namespace cmn;
using namespace nas;

/*  8.2.9 Registration reject */
int mm::dissect_registration_reject(dissector d, context* ctx) {
    const use_context uc(ctx, "registration-reject", d, 0);
    //network to UE
    down_link(d.pinfo);

    /* 5GMM cause   9.11.3.2  M   V   1 */
    auto consumed = dissect_nrmm_cause(d, ctx);
    d.step(consumed);

    /* 5F  T3346 value GPRS timer 2     9.11.2.4   O   TLV 3 */
    // ELEM_OPT_TLV(0x5F, , DE_GPRS_TIMER_2, " - T3346 value");
    consumed = dissect_opt_tlv(nullptr, &t3346_gprs_timer2, d, ctx);
    d.step(consumed);

    /* 16    T3502 value    GPRS timer 2 9.11.2.4    O    TLV    3 */
    // ELEM_OPT_TLV(0x16, , DE_GPRS_TIMER_2, " - T3502 value");
    consumed = dissect_opt_tlv(nullptr, &t3502_gprs_timer_2, d, ctx);
    d.step(consumed);

    /* 78    EAP message  9.11.2.2    O    TLV-E    7-1503 */
    consumed = dissect_opt_tlv_e(nullptr, &eap_message, d, ctx);
    d.step(consumed);

    return uc.length;
}
