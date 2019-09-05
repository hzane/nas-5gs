#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_de_reg {
extern const element_meta de_reg_type;
extern const element_meta key_set_id;
} // namespace mm_de_reg_req_ue_orig

/*
 * 8.2.12 De-registration request (UE originating de-registration)
 */
int mm::dissect_reg_req_ue_orig(dissector d, context* ctx) {
    auto        len = d.length;
    use_context uc(ctx, "ue-originating-de-registration", d);

    using namespace mm_de_reg;

    /* De-registration type   9.11.3.20   M   V   1 */
    /*ELEM_MAND_V(DE_NAS_5GS_MM_DE_REG_TYPE,);*/
    auto consumed = dissect_elem_v(nullptr, &de_reg_type, d, ctx);

    /* ngKSI    NAS key set identifier 9.11.3.32    M    V    1/2 H1 */
    d.step(consumed);

    /* 5GS mobile identity  9.11.3.4    M    LV-E    6-n */
    /*ELEM_MAND_LV_E(DE_NAS_5GS_MM_5GS_MOBILE_ID,); */
    consumed = dissect_elem_lv_e(nullptr, &key_set_id, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);
    return len;
}

namespace mm {

} // namespace mm_de_reg_req_ue_orig
