#include "../dissect_mm_msg.hh"

namespace mm {
/* * 9.11.3.4    5GS mobile identity */
const val_string type_id_values[] = {
    {0x0, "No identity"},
    {0x1, "SUCI"},
    {0x2, "5G-GUTI"},
    {0x3, "IMEI"},
    {0x4, "5G-S-TMSI"},
    {0x5, "IMEISV"},
    {0, nullptr},
};

/* * 9.11.3.3 5GS identity type */
const field_meta hf_id_type = {
    "Type of identity",
    "nas_5gs.mm.type_id",
    ft::ft_uint8,
    fd::base_dec,
    type_id_values,
    nullptr,
    nullptr,
    0x07,
};
} // namespace


extern const element_meta mm::id_type = {
    0xff,
    "Identity type",
    dissect_5gs_id_type,
    nullptr,
};


/* * 9.11.3.3 5GS identity type */
int mm::dissect_5gs_id_type(dissector d, context* ctx) {
    d.add_item(1, &hf_id_type, enc::be);
    return 1;
}
