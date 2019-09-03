#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"
#include "../gsm.hh"

namespace mm_reg_rej {

extern const element_meta t3346_gprs_timer2;
extern const element_meta t3502_gprs_timer_2;

} // namespace mm_reg_rej

using namespace nas;
using namespace mm_reg_rej;

/*  8.2.9 Registration reject */
int mm::registration_rej(dissector d, context* ctx) {
    auto        len = d.length;
    use_context uc(ctx, "registration-reject");

    /* 5GMM cause   9.11.3.2  M   V   1 */
    /*ELEM_MAND_V(,DE_NAS_5GS_MM_5GMM_CAUSE, );  */
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

    d.extraneous_data_check(0);

    return len;
}

namespace mm_reg_rej {
/* 5F  T3346 value GPRS timer 2     9.11.2.4   O   TLV 3 */
int dissect_t3346_gprs_timer2(dissector d, context* ctx);

/* 5F  T3346 value GPRS timer 2     9.11.2.4   O   TLV 3 */
extern const element_meta t3346_gprs_timer2 = {
    0x5f,
    "T3346 value GPRS timer 2",
    dissect_t3346_gprs_timer2,
};

// T3502 value    GPRS timer 2 9.11.2.4
int dissect_t3502_gprs_timer_2(dissector d, context* ctx);

// T3502 value    GPRS timer 2 9.11.2.4
extern const element_meta t3502_gprs_timer_2 = {
    0x16,
    "T3502 value    GPRS timer 2",
    dissect_t3502_gprs_timer_2,
};

/* 5F  T3346 value GPRS timer 2     9.11.2.4   O   TLV 3 */
int dissect_t3346_gprs_timer2(dissector d, context* ctx) {
    return dissect_gprs_timer2(d, ctx);
}

// T3502 value    GPRS timer 2 9.11.2.4
int dissect_t3502_gprs_timer_2(dissector d, context* ctx) {
    return dissect_gprs_timer2(d, ctx);
}

} // namespace mm_reg_rej
