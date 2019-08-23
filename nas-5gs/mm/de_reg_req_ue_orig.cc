#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm{

}

namespace mm_de_reg_req_ue_orig {
extern const element_meta de_reg_type;
extern const element_meta key_set_id;
} // namespace mm_de_reg_req_ue_orig
/*
 * 8.2.12 De-registration request (UE originating de-registration)
 */
int mm::de_reg_req_ue_orig(dissector d, context* ctx) {
    use_context uc(ctx, "ue-originating-de-registration");

    using namespace mm_de_reg_req_ue_orig;

    /* De-registration type    De-registration type     9.11.3.18   M   V   1 */
    /*ELEM_MAND_V(DE_NAS_5GS_MM_DE_REG_TYPE,ei_nas_5gs_missing_mandatory_elemen);*/

    auto consumed = dissect_elem_v(nullptr, &de_reg_type, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /* ngKSI    NAS key set identifier 9.11.3.32    M    V    1/2 H1 */

    /*5GS mobile identity     5GS mobile identity 9.11.3.4    M    LV-E    6-n */
    /*ELEM_MAND_LV_E(DE_NAS_5GS_MM_5GS_MOBILE_ID,ei_nas_5gs_missing_mandatory_elemen); */

    consumed = dissect_elem_lv_e(nullptr, &key_set_id, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    //EXTRANEOUS_DATA_CHECK(curr_len, 0, pinfo, &ei_nas_5gs_extraneous_data);
    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    return d.tvb->reported_length;
}

namespace mm_de_reg_req_ue_orig{
int                dissect_de_reg_type(dissector d, context* ctx);
const element_meta de_reg_type = {
    0xff,
    "De-registration type",
    dissect_de_reg_type,
};

int                dissect_key_set_id(dissector d, context* ctx);
const element_meta key_set_id = {
    0xff,
    "5GS mobile identity",
    dissect_key_set_id,
};
}
