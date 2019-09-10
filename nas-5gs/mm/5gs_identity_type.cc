#include "../dissect_mm_msg.hh"


/* * 9.11.3.3 5GS identity type */
int mm::dissect_5gs_id_type(dissector d, context* ctx) {
    const use_context uc(ctx, "5gs-identity-type", d, -1);

    auto i = d.add_item(1, &hf_id_type, enc::be);
    d.step(1);

    unused(i);
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



/* * 9.11.3.3 5GS identity type */
const field_meta mm::hf_id_type = {
    "Type of identity",
    "nas_5gs.mm.type_id",
    ft::ft_uint8,
    fd::base_dec,
    identity_type_values,
    nullptr,
    nullptr,
    0x07,
};

extern const element_meta mm::id_type = {
    0xff,
    "Identity type",
    dissect_5gs_id_type,
    nullptr,
};

