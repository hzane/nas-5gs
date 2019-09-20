#include "../dissect_mm_msg.hh"

using namespace nas;
using namespace mm;

/* * 9.11.3.3 5GS identity type */
int mm::dissect_identity_type(dissector d, context* ctx) {
    const use_context uc(ctx, "5gs-identity-type", d, -1);

    (void) d.add_item(1, &hf_identity_type, enc::be);
    d.step(1);

    return 1;
}


/*5GS mobile identity     5GS mobile identity 9.11.3.4    */
const val_string mm::identity_type_values[] = {
    {0x0, "No identity"},
    {0x1, "SUCI"},
    {0x2, "5G-GUTI"},
    {0x3, "IMEI"},
    {0x4, "5G-S-TMSI"},
    {0x5, "IMEISV"},
    {0x6, "MAC address"},
    {0, nullptr},
};


/* 9.11.3.3 5GS identity type */
const field_meta mm::hf_identity_type = {
    "Type of identity",
    "nas.nr.mm.type.identity",
    ft::ft_uint8,
    fd::base_dec,
    identity_type_values,
    nullptr,
    nullptr,
    0x07,
};
