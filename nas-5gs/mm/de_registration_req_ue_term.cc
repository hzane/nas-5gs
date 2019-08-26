#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_de_reg_req {
extern const element_meta de_reg_type;
extern const element_meta t3346_gprs_timer2;
} // namespace mm_de_reg_req
/*
 * 8.2.14 De-registration request (UE terminated de-registration)
 */
int mm::de_registration_req_ue_term(dissector d, context* ctx) {
    use_context uc(ctx, "de-registration-request");

    using namespace mm_de_reg_req;

    /* De-registration type    De-registration type 9.11.3.20   M   V   1 */
    /*ELEM_MAND_V(DE_NAS_5GS_MM_DE_REG_TYPE,ei_nas_5gs_missing_mandatory_elemen);  */

    auto consumed = dissect_elem_v(nullptr, &de_reg_type, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /* Spare half octet    Spare half octet 9.5    M    V    1/2 */
    /* 58 5GMM cause   5GMM cause     9.11.3.2  O   TV   2 */
    // ELEM_OPT_TV(0x58, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_5GMM_CAUSE, NULL);
    consumed = dissect_opt_elem_tv(nullptr, &mm_cause, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /* 5F  T3346 value GPRS timer 2     9.11.2.4   O   TLV 3 */
    // ELEM_OPT_TLV(0x5F, GSM_A_PDU_TYPE_GM, DE_GPRS_TIMER_2, " - T3346 value");
    consumed = dissect_opt_elem_tlv(nullptr, &t3346_gprs_timer2, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    d.extraneous_data_check(0);
    return d.tvb->reported_length;
}

namespace mm_de_reg_req {
int                       dissect_de_reg_type(dissector d, context*);
extern const element_meta de_reg_type = {
    0xff,
    "De-registration type",
    dissect_de_reg_type,
};

int                       dissect_t3346_gprs_timer2(dissector d, context*);
extern const element_meta t3346_gprs_timer2 = {
    0x5f,
    "T3346 value GPRS timer 2",
    dissect_t3346_gprs_timer2,
};
int dissect_de_reg_type(dissector d, context*) { return 0; }
int dissect_t3346_gprs_timer2(dissector d, context*) { return 0; }
} // namespace mm_de_reg_req
