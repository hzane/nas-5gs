#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_notification {
extern const element_meta access_type;
}

using namespace nas;

/*
 * 8.2.23 Notification
 */
int mm::dissect_notification(dissector d, context* ctx) {
    const auto        len = d.length;
    use_context uc(ctx, "notification", d);

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
namespace mm {

} // namespace mm_notification
