#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace mm;

const bool_field hf_switch_off = {
    "Switch off",
    0x08,
    "Switch off",
    "Normal de-registration",
};

extern const tag_field hf_access_type;

/* 9.11.3.20    De-registration type */
const bool_field hf_reregistration_request = {
    "Re-registration required",
    0x04,
    "re-registration not required"
    "re-registration required",
};

/* De-registration type    De-registration type     9.11.3.20   M   V   1 */
int mm::dissect_deregistration_type(dissector d, context* ctx) {
    const use_context uc(ctx, "de-registration-type", d, -1);

    /* Switch off   Re-registration required    Access type */
    auto i = d.add_item( &hf_switch_off);
    i = d.add_item(&hf_reregistration_request);
    i = d.add_item(&hf_access_type);
    d.step(1);

    unused(i);
    return 1;
}


