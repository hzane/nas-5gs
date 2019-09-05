#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"
#include "../gsm.hh"

using namespace cmn;


/*  8.2.14 De-registration request (UE terminated de-registration) */
int mm::dissect_registration_req_ue_term(dissector d, context* ctx) {    
    use_context uc(ctx, "de-registration-request", d, 0);

    /* De-registration type    De-registration type 9.11.3.20   M   V   1 */
    auto consumed = dissect_elem_v(nullptr, &de_reg_type, d, ctx);
    d.step(consumed);

    /* Spare half octet    Spare half octet 9.5    M    V    1/2 */

    /* 58 5GMM cause  9.11.3.2  O   TV   2 */
    consumed = dissect_opt_elem_tv(nullptr, &mm_cause, d, ctx);
    d.step(consumed);

    /* 5F  T3346 value GPRS timer 2     9.11.2.4   O   TLV 3 */
    // ELEM_OPT_TLV(0x5F, , DE_GPRS_TIMER_2, " - T3346 value");
    consumed = dissect_opt_elem_tlv(nullptr, &t3346_gprs_timer2, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);
    return uc.length;
}


extern const element_meta mm::t3346_gprs_timer2 = {
    0x5f,
    "GPRS timer 2 - T3346 value",
    dissect_gprs_timer2,
    nullptr,
};
