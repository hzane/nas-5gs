#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_de_reg_req{
extern const element_meta de_reg_type;
extern const element_meta spare_half_oct;
extern const element_meta t3346_gprs_timer2;
}
/*
 * 8.2.14 De-registration request (UE terminated de-registration)
 */
int mm::de_registration_req_ue_term(dissector d, context* ctx) {
    using namespace mm_de_reg_req;

    /* De-registration type    De-registration type 9.11.3.20   M   V   1 */
    /*ELEM_MAND_V(NAS_5GS_PDU_TYPE_MM,
                DE_NAS_5GS_MM_DE_REG_TYPE,
                NULL,
                ei_nas_5gs_missing_mandatory_elemen);
                */
    auto consumed = dissect_elem_v(nullptr, &de_reg_type, d);
    d.offset += consumed;
    d.length -= consumed;

    /* Spare half octet    Spare half octet 9.5    M    V    1/2 */
    /* 58 5GMM cause   5GMM cause     9.11.3.2  O   TV   2 */
    // ELEM_OPT_TV(0x58, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_5GMM_CAUSE, NULL);
    consumed = dissect_opt_elem_tv(nullptr, &spare_half_oct, d);
    d.offset += consumed;
    d.length -= consumed;

    /* 5F  T3346 value GPRS timer 2     9.11.2.4   O   TLV 3 */
    // ELEM_OPT_TLV(0x5F, GSM_A_PDU_TYPE_GM, DE_GPRS_TIMER_2, " - T3346 value");
    consumed = dissect_opt_elem_tlv(nullptr, &t3346_gprs_timer2, d);
    d.offset += consumed;
    d.length -= consumed;

    // EXTRANEOUS_DATA_CHECK(curr_len, 0, pinfo, &ei_nas_5gs_extraneous_data);
    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    return d.tvb->reported_length;
}


namespace mm_de_reg_req{
extern const element_meta de_reg_type = {
    -1,
    "De-registration type",
    dissect_de_reg_type,
};
extern const element_meta spare_half_oct = {
    0x58,
    "Spare half octet",
    dissect_sparse_half_oct,
};
extern const element_meta t3346_gprs_timer2 = {
    0x5f,
    "T3346 value GPRS timer 2",
    dissect_t3346_gprs_timer2,
};
}
