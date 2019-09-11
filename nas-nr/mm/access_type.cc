#include "../dissect_mm_msg.hh"

/*  9.11.3.11    Access type */
int mm::dissect_access_type(dissector d, context* ctx) {
    const use_context uc(ctx, "access-type", d, -1);

    auto i = d.add_item(1, &hf_acc_type, enc::be);
    d.step(1);

    unused(i);
    return 1;
}

extern const element_meta mm::access_type = {
    0xff,
    "Access type",
    dissect_access_type,
    nullptr,
};

/*  9.11.3.11    Access type */
static const value_string access_type_vals[] = {
    {0x1, "3GPP access"},
    {0x2, "Non-3GPP access"},
    {0x3, "3GPP access and non-3GPP access"},
    {0, nullptr},
};

const field_meta mm::hf_acc_type = {
    "Access type",
    "nas_5gs.mm.access.type",
    ft::ft_uint8,
    fd::base_dec,
    access_type_vals,
    nullptr,
    nullptr,
    0x03,
};

