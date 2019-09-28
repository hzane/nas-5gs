#include "../common/ber.hh"
#include "../common/dissect_mm_msg.hh"
#include "../common/gsm.hh"
#include "../common/use_context.hh"

using namespace cmn;


/*  8.2.14 De-registration request (UE terminated de-registration) */
int mm::dissect_deregistration_request_ue_terminate(dissector d, context* ctx) {
    const use_context uc(ctx, "de-registration-request-ue-term", d, 0);
    // network to UE
    down_link(d.pinfo);

    /* De-registration type    De-registration type 9.11.3.20   M   V   1 */
    auto consumed = dissect_deregistration_type(d, ctx);
    d.step(consumed);

    /* Spare half octet    Spare half octet 9.5    M    V    1/2 */

    /* 58 5GMM cause  9.11.3.2  O   TV   2 */
    consumed = dissect_opt_tv(nullptr, &nrmm_cause, d, ctx);
    d.step(consumed);

    /* 5F  T3346 value GPRS timer 2     9.11.2.4   O   TLV 3 */
    // ELEM_OPT_TLV(0x5F, , DE_GPRS_TIMER_2, " - T3346 value");
    consumed = dissect_opt_tlv(nullptr, &t3346_gprs_timer2, d, ctx);
    d.step(consumed);

    return uc.length;
}


extern const element_meta mm::t3346_gprs_timer2 = {
    0x5f,
    "GPRS timer 2 - T3346 value",
    dissect_gprs_timer2_set,
    nullptr,
};
