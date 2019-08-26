#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_reg_rej {

extern const element_meta t3346_gprs_timer2;
extern const element_meta t3502_gprs_timer_2;

} // namespace mm_reg_rej

using namespace nas;

/*
 * 8.2.9 Registration reject
 */
int mm::registration_rej(dissector d, context* ctx) {
    use_context uc(ctx, "registration-reject");

    using namespace mm_reg_rej;

    /* 5GMM cause   5GMM cause     9.11.3.2  M   V   1 */
    /*ELEM_MAND_V(,DE_NAS_5GS_MM_5GMM_CAUSE, ei_nas_5gs_missing_mandatory_elemen);  */

    auto consumed = dissect_elem_v(nullptr, &mm_cause, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /* 5F  T3346 value GPRS timer 2     9.11.3.16   O   TLV 3 */
    // ELEM_OPT_TLV(0x5F, GSM_A_PDU_TYPE_GM, DE_GPRS_TIMER_2, " - T3346 value");
    consumed = dissect_opt_elem_tlv(nullptr, &t3346_gprs_timer2, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /* 16    T3502 value    GPRS timer 2 9.10.2.4    O    TLV    3 */
    // ELEM_OPT_TLV(0x16, GSM_A_PDU_TYPE_GM, DE_GPRS_TIMER_2, " - T3502 value");
    consumed = dissect_opt_elem_tlv(nullptr, &t3502_gprs_timer_2, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /* 78    EAP message    EAP message 9.10.2.2    O    TLV-E    7-1503 */
    // ELEM_OPT_TLV_E(0x78, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eap_msg, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    d.extraneous_data_check(0);

    return d.tvb->reported_length;
}

namespace mm_reg_rej {

int                       dissect_t3346_gprs_timer2(dissector d, context* ctx);
extern const element_meta t3346_gprs_timer2 = {
    0x5f,
    "T3346 value GPRS timer 2",
    dissect_t3346_gprs_timer2,
};

int                       dissect_t3502_gprs_timer_2(dissector d, context* ctx);
extern const element_meta t3502_gprs_timer_2 = {
    0x16,
    "T3502 value    GPRS timer 2",
    dissect_t3502_gprs_timer_2,
};

int dissect_t3346_gprs_timer2(dissector d, context* ctx) { return 0; }

int dissect_t3502_gprs_timer_2(dissector d, context* ctx) { return 0; }

} // namespace mm_reg_rej
