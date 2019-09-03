#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_de_reg {
extern const element_meta de_reg_type;
extern const element_meta t3346_gprs_timer2;
} // namespace mm_de_reg_req

/*  8.2.14 De-registration request (UE terminated de-registration) */
int mm::dissect_registration_req_ue_term(dissector d, context* ctx) {
    const auto  len = d.length;
    use_context uc(ctx, "de-registration-request");

    using namespace mm_de_reg;

    /* De-registration type    De-registration type 9.11.3.20   M   V   1 */
    /*ELEM_MAND_V(DE_NAS_5GS_MM_DE_REG_TYPE,ei_nas_5gs_missing_mandatory_elemen);  */
    auto consumed = dissect_elem_v(nullptr, &de_reg_type, d, ctx);
    d.step(consumed);

    /* Spare half octet    Spare half octet 9.5    M    V    1/2 */
    /* 58 5GMM cause   5GMM cause     9.11.3.2  O   TV   2 */
    // ELEM_OPT_TV(0x58, , DE_NAS_5GS_MM_5GMM_CAUSE, NULL);
    consumed = dissect_opt_elem_tv(nullptr, &mm_cause, d, ctx);
    d.step(consumed);

    /* 5F  T3346 value GPRS timer 2     9.11.2.4   O   TLV 3 */
    // ELEM_OPT_TLV(0x5F, , DE_GPRS_TIMER_2, " - T3346 value");
    consumed = dissect_opt_elem_tlv(nullptr, &t3346_gprs_timer2, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);
    return len;
}

namespace mm_de_reg {

int dissect_t3346_gprs_timer2(dissector d, context*);

extern const element_meta t3346_gprs_timer2 = {
    0x5f,
    "GPRS timer 2 - T3346 value",
    dissect_t3346_gprs_timer2,
    nullptr,
};

// 24.008 g10 
int dissect_t3346_gprs_timer2(dissector d, context* ctx) {
    // no dissector
    return d.length;
}
} // namespace mm_de_reg_req
