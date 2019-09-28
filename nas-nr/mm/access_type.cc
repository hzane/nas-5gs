#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace mm;

/*  9.11.3.11    Access type */
int mm::dissect_access_type(dissector d, context* ctx) {
    const use_context uc(ctx, "access-type", d, -1);

    (void) d.add_item(1, &hf_access_type);
    d.step(1);

    return 1;
}
struct access_type_t {
    uint8_t _;
};

/*  9.11.3.11    Access type */
const value_string access_type_values[] = {
    {0x1, "3GPP access"},
    {0x2, "Non-3GPP access"},
    {0x3, "3GPP access and non-3GPP access"},
    {0, nullptr},
};

const field_meta mm::hf_access_type = {
    "Access type",
    "nas.nr.mm.access.type",
    ft::ft_uint8,
    fd::base_dec,
    access_type_values,
    nullptr,
    nullptr,
    0x03,
};
