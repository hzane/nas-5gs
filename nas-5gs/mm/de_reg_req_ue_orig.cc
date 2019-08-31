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
    use_context uc(ctx, "ue-originating-de-registration");

    using namespace mm_de_reg;

    /* De-registration type    De-registration type     9.11.3.18   M   V   1 */
    /*ELEM_MAND_V(DE_NAS_5GS_MM_DE_REG_TYPE,ei_nas_5gs_missing_mandatory_elemen);*/
    auto consumed = dissect_elem_v(nullptr, &de_reg_type, d, ctx);
    d.step(consumed);

    /* ngKSI    NAS key set identifier 9.11.3.32    M    V    1/2 H1 */

    /*5GS mobile identity     5GS mobile identity 9.11.3.4    M    LV-E    6-n */
    /*ELEM_MAND_LV_E(DE_NAS_5GS_MM_5GS_MOBILE_ID,ei_nas_5gs_missing_mandatory_elemen); */
    consumed = dissect_elem_lv_e(nullptr, &key_set_id, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);
    return len;
}

namespace mm_de_reg {
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


/*
 *   9.11.3.20    De-registration type
 */
static const true_false_string nas_5gs_mm_switch_off_tfs = {
    "Switch off",
    "Normal de-registration",
};

static const true_false_string nas_5gs_mm_re_reg_req_tfs = {
    "re-registration required",
    "re-registration not required"};

static const value_string nas_5gs_mm_acc_type_vals[] = {
    {0x1, "3GPP access"},
    {0x2, "Non-3GPP access"},
    {0x3, "3GPP access and non-3GPP access"},
    {0, nullptr},
};
const field_meta hf_switch_off = {
    "Switch off",
    "nas_5gs.mm.switch_off",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &nas_5gs_mm_switch_off_tfs,
    nullptr,
    0x08,
};
const field_meta hf_re_reg_req = {
    "Re-registration required",
    "nas_5gs.mm.re_reg_req",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &nas_5gs_mm_re_reg_req_tfs,
    nullptr,
    0x04,
};
const field_meta hf_acc_type = {
    "Access type",
    "nas_5gs.mm.acc_type",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_acc_type_vals,
    nullptr,
    nullptr,
    0x03,
};

/* De-registration type    De-registration type     9.11.3.18   M   V   1 */
int dissect_de_reg_type(dissector d, context* ctx) {
    /* Switch off   Re-registration required    Access type */
    d.add_item(1, &hf_switch_off, enc::be);
    d.add_item(1, &hf_re_reg_req, enc::be);
    d.add_item(1, &hf_acc_type, enc::be);
    return 1;
}

/*5GS mobile identity     5GS mobile identity 9.11.3.4    M    LV-E    6-n */
int dissect_key_set_id(dissector d, context* ctx) { return mm::dissect_mobile_id(d, ctx); }
} // namespace mm_de_reg_req_ue_orig
