#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_id {
extern const element_meta id_type;
}
using namespace nas;
using namespace mm;

/*
 * 8.2.21 Identity request
 */
int mm::dissect_id_req(dissector d, context* ctx) {
    const auto        len = d.length;
    use_context uc(ctx, "identity-request", d);

    using namespace mm_id;

    /* Identity type    5GS identity type 9.11.3.3    M    V    1/2 */
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_spare_half_octet, enc::be);
    // ELEM_MAND_V(,ei_nas_5gs_missing_mandatory_elemen);
    const auto consumed = dissect_elem_v(nullptr, &id_type, d, ctx);
    /* Spare half octet    Spare half octet 9.5    M    V    1/2 */
    d.step(consumed);

    d.extraneous_data_check(0);
    return len;
}


namespace mm_id {

} // namespace mm_id_req
