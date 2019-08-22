#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_notification{
extern const field_meta* hf_spare_half_octet;
}
/*
 * 8.2.23 Notification
 */
int mm::notification(dissector d, context* ctx) {
    using namespace mm_notification;

    /* Access type    Access type 9.11.3.11    M    V    1/2 DE_NAS_5GS_MM_ACCESS_TYPE */
    /* Spare half octet    Spare half octet 9.5    M    V    1/2  */
    // proto_tree_add_item(
    //     tree, hf_nas_5gs_spare_half_octet, tvb, curr_offset, 1, ENC_BIG_ENDIAN);
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_spare_half_octet, enc::be);

    // ELEM_MAND_V(NAS_5GS_PDU_TYPE_MM,
    //             DE_NAS_5GS_MM_ACCESS_TYPE,
    //             NULL,
    //             ei_nas_5gs_missing_mandatory_elemen);

    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    return d.tvb->reported_length;
}
namespace mm_notification {
}
