#include "../dissect_mm_msg.hh"

using namespace cmn;
using namespace mm;

/* De-registration type    De-registration type     9.11.3.20   M   V   1 */
int mm::dissect_deregistration_type(dissector d, context* ctx) {
    const use_context uc(ctx, "de-registration-type", d, -1);

    /* Switch off   Re-registration required    Access type */
    auto i = d.add_item(1, &hf_switch_off, enc::be);
    i = d.add_item(1, &hf_reregistration_request, enc::be);
    i = d.add_item(1, &hf_acc_type, enc::be);
    d.step(1);

    unused(i);
    return 1;
}

/* 9.11.3.20    De-registration type */
const true_false_string nas_5gs_mm_switch_off_tfs = {
    "Switch off",
    "Normal de-registration",
};

const true_false_string tfs_reregistration_required = {
    "re-registration required",
    "re-registration not required"};

const field_meta mm::hf_switch_off = {
    "Switch off",
    "nas.nr.mm.switch.off",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &nas_5gs_mm_switch_off_tfs,
    nullptr,
    0x08,
};
const field_meta mm::hf_reregistration_request = {
    "Re-registration required",
    "nas.nr.mm.re.registration.required",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_reregistration_required,
    nullptr,
    0x04,
};
