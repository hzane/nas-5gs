#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace mm;

/* De-registration type    De-registration type     9.11.3.20   M   V   1 */
int mm::dissect_deregistration_type(dissector d, context* ctx) {
    const use_context uc(ctx, "de-registration-type", d, -1);

    /* Switch off   Re-registration required    Access type */
    auto i = d.add_item(1, &hf_switch_off);
    i = d.add_item(1, &hf_reregistration_request);
    i = d.add_item(1, &hf_access_type);
    d.step(1);

    unused(i);
    return 1;
}
struct deregistration_type_t {
    uint8_t switch_off;
    uint8_t reregistration_request;
    uint8_t access_type;
};

/* 9.11.3.20    De-registration type */
const tf_string nas_5gs_mm_switch_off_tfs = {
    "Switch off",
    "Normal de-registration",
};

const tf_string tfs_reregistration_required = {
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
