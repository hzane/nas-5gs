#include "../dissect_mm_msg.hh"


extern const element_meta mm::access_type = {
    0xff,
    "Access type",
    dissect_access_type,
    nullptr,
};

/*  9.11.3.11    Access type */
static const value_string nas_5gs_mm_acc_type_vals[] = {
    {0x1, "3GPP access"},
    {0x2, "Non-3GPP access"},
    {0x3, "3GPP access and non-3GPP access"},
    {0, nullptr},
};

const field_meta mm::hf_acc_type = {
    "Access type",
    "nas_5gs.mm.acc_type",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_acc_type_vals,
    nullptr,
    nullptr,
    0x03,
};

int mm::dissect_access_type(dissector d, context*) {
    // spare_b3
    // spare_b2
    d.add_item(1, &hf_acc_type, enc::be);
    return 1;
}
