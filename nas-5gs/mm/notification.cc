#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_notification {
extern const element_meta access_type;
}

using namespace nas;

/*
 * 8.2.23 Notification
 */
int mm::notification(dissector d, context* ctx) {
    const auto        len = d.length;
    use_context uc(ctx, "notification");

    using namespace mm_notification;

    /* Access type    Access type 9.11.3.11    M    V    1/2  */
    // ELEM_MAND_V(DE_NAS_5GS_MM_ACCESS_TYPE,);
    const auto consumed = dissect_elem_v(nullptr, &access_type, d, ctx);

    /* Spare half octet    Spare half octet 9.5    M    V    1/2  */
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_spare_half_octet, enc::be);
    d.step(consumed);

    d.extraneous_data_check(0);
    return len;
}
namespace mm_notification {
int                       dissect_access_type(dissector d, context*);
extern const element_meta access_type = {
    0xff,
    "Access type",
    dissect_access_type,
    nullptr,
};
/*
 * 9.11.3.11    Access type
 */
static const value_string nas_5gs_mm_acc_type_vals[] = {
    {0x1, "3GPP access"},
    {0x2, "Non-3GPP access"},
    {0x3, "3GPP access and non-3GPP access"},
    {0, nullptr},
};
const field_meta hf_acc_type = {
    "Access type",
    "nas_5gs.mm.acc_type",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_acc_type_vals,nullptr, nullptr,
    0x03,
};
int dissect_access_type(dissector d, context*) {
    // spare_b3
    // spare_b2
    d.add_item(1, &hf_acc_type, enc::be);
    return 1;
}
} // namespace mm_notification
