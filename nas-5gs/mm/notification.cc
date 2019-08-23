#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_notification{
extern const element_meta access_type;
}
/*
 * 8.2.23 Notification
 */
int mm::notification(dissector d, context* ctx) {
    use_context uc(ctx, "notification");

    using namespace mm_notification;

    /* Access type    Access type 9.11.3.11    M    V    1/2 DE_NAS_5GS_MM_ACCESS_TYPE */
    /* Spare half octet    Spare half octet 9.5    M    V    1/2  */
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_spare_half_octet, enc::be);

    // ELEM_MAND_V(DE_NAS_5GS_MM_ACCESS_TYPE,ei_nas_5gs_missing_mandatory_elemen);
    auto consumed = dissect_elem_v(nullptr, &access_type, d, ctx);
    d.step(consumed);

    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    return d.tvb->reported_length;
}
namespace mm_notification {
int dissect_access_type(dissector d, context*);
extern const element_meta access_type = {0xff, "Access type", dissect_access_type, };
}
