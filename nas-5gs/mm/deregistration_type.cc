#include "../dissect_mm_msg.hh"


/* De-registration type    De-registration type     9.11.3.18   M   V   1 */
int mm::dissect_de_reg_type(dissector d, context* ctx) {
    const use_context uc(ctx, "de-registration-type", d, -1);

    /* Switch off   Re-registration required    Access type */
    d.add_item(1, &hf_switch_off, enc::be);
    d.add_item(1, &hf_re_reg_req, enc::be);
    d.add_item(1, &hf_acc_type, enc::be);
    d.step(1);

    return 1;
}

// De-registration type   9.11.3.20
const element_meta mm::de_reg_type = {
    0xff,
    "De-registration type",
    dissect_de_reg_type,
    nullptr,
};



/* 9.11.3.20    De-registration type */
const true_false_string nas_5gs_mm_switch_off_tfs = {
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
const field_meta mm::hf_switch_off = {
    "Switch off",
    "nas_5gs.mm.switch_off",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &nas_5gs_mm_switch_off_tfs,
    nullptr,
    0x08,
};
const field_meta mm::hf_re_reg_req = {
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

