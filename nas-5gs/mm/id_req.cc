#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_id_req{
extern const element_meta id_type;
}
/*
 * 8.2.21 Identity request
 */
int mm::id_req(dissector d, context* ctx) {
    using namespace mm_id_req;

    /*     Identity type    5GS identity type 9.11.3.3    M    V    1/2 */
    /* Spare half octet    Spare half octet 9.5    M    V    1/2 */
    // proto_tree_add_item(        tree, hf_nas_5gs_spare_half_octet, tvb, curr_offset, 1, ENC_BIG_ENDIAN);
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_spare_half_octet, enc::be);

    // ELEM_MAND_V(NAS_5GS_PDU_TYPE_MM,
    //             DE_NAS_5GS_MM_5GS_IDENTITY_TYPE,
    //             NULL,
    //             ei_nas_5gs_missing_mandatory_elemen);
    auto consumed = dissect_elem_v(nullptr, &id_type, d);
    d.offset += consumed;
    d.length -= consumed;

    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    return d.tvb->reported_length;
}

namespace mm_id_req {
int dissect_id_type(dissector d, context* ctx);
extern const element_meta id_type = {
    -1,
    "Identity type",
    dissect_id_type,
};
}
