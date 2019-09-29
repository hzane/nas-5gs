#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

/*  9.11.3.50A    SMS indication */
int mm::dissect_sms_indication(dissector d, context* ctx) {
    const use_context uc(ctx, "sms-indication", d, -1);

    (void) d.add_item(1, &hf_sms_over_nas_ind);
    d.step(1);

    return 1;
}

const bool_field mm::hf_sms_over_nas_ind = {
    "SMS over NAS",
    0x01,
    "SMS over NAS not available",
    "SMS over NAS available",
};
