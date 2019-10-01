#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace nas;
using namespace mm;

/* 9.11.3.3 5GS identity type */
extern const tag_field hf_identity_type = {
    "Type of identity",
    0x07,
    (const v_string[]){
        {0x0, "No identity"},
        {0x1, "SUCI"},
        {0x2, "5G-GUTI"},
        {0x3, "IMEI"},
        {0x4, "5G-S-TMSI"},
        {0x5, "IMEISV"},
        {0x6, "MAC address"},
        {0, nullptr},
    },
};

/* * 9.11.3.3 5GS identity type */
int mm::dissect_identity_type(dissector d, context* ctx) {
    const use_context uc(ctx, "5gs-identity-type", d, -1);

    (void) d.add_item(&hf_identity_type);
    d.step(1);

    return 1;
}

