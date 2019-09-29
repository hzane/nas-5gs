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

/*  9.11.3.11    Access type */
const value_string access_type_values[] = {
    {0x1, "3GPP access"},
    {0x2, "Non-3GPP access"},
    {0x3, "3GPP access and non-3GPP access"},
    {0, nullptr},
};

const tag_field mm::hf_access_type = {
    "Access type",
    0x03,
    access_type_values,
};
