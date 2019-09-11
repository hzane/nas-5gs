#include "../dissect_mm_msg.hh"

using namespace cmn;
using namespace mm;

/* De-registration type    De-registration type     9.11.3.20   M   V   1 */
int mm::dissect_deregistration_type(dissector d, context* ctx) {
    const use_context uc(ctx, "de-registration-type", d, -1);

    /* Switch off   Re-registration required    Access type */
    auto i = d.add_item(1, &hf_switch_off, enc::be);
    i = d.add_item(1, &hf_re_reg_req, enc::be);
    i = d.add_item(1, &hf_acc_type, enc::be);
    d.step(1);

    unused(i);
    return 1;
}

// De-registration type   9.11.3.20
const element_meta mm::de_reg_type = {
    0xff,
    "De-registration type",
    dissect_deregistration_type,
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

const field_meta mm::hf_switch_off = {
    "Switch off",
    "nas.nr.mm.switch_off",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &nas_5gs_mm_switch_off_tfs,
    nullptr,
    0x08,
};
const field_meta mm::hf_re_reg_req = {
    "Re-registration required",
    "nas.nr.mm.re_reg_req",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &nas_5gs_mm_re_reg_req_tfs,
    nullptr,
    0x04,
};
