#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_service_rej {
extern const element_meta t3346_gprs_timer2;
}

using namespace nas;

/*
 * 8.2.18 Service reject
 */
int mm::service_rej(dissector d, context* ctx) {
    use_context uc(ctx, "service-reject");

    using namespace mm_service_rej;
    /* 5GMM cause   5GMM cause     9.11.3.2  M   V   1 */
    /*    ELEM_MAND_V(,DE_NAS_5GS_MM_5GMM_CAUSE, );*/
    auto consumed = dissect_elem_v(nullptr, &mm_cause, d, ctx);
    d.step(consumed);

    /*50    PDU session status    PDU session status 9.11.3.44    O    TLV    4*/
    // ELEM_OPT_TLV(0x50, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_PDU_SES_STATUS, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &pdu_ses_status, d, ctx);
    d.step(consumed);

    /* 5F  T3346 value GPRS timer 2     9.11.2.4   O   TLV 3 */
    // ELEM_OPT_TLV(0x5F, GSM_A_PDU_TYPE_GM, DE_GPRS_TIMER_2, " - T3346 value");
    consumed = dissect_opt_elem_tlv(nullptr, &t3346_gprs_timer2, d, ctx);
    d.step(consumed);

    /* 78    EAP message    EAP message 9.11.2.2    O    TLV-E    7-1503 */
    // ELEM_OPT_TLV_E(0x78, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eap_msg, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);

    return d.tvb->reported_length;
}

namespace mm_service_rej {
int                       dissect_t3346_gprs_timer2(dissector d, context* ctx);
extern const element_meta t3346_gprs_timer2 = {
    0x5F,
    "T3346 value GPRS timer 2",
    dissect_t3346_gprs_timer2,
};

int dissect_t3346_gprs_timer2(dissector d, context* ctx) {
    bug("no dissect\n");
    return d.length;
}

} // namespace mm_service_rej
