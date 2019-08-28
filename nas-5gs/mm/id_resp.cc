#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_id_resp {

}
/*
 * 8.2.22 Identity response
 */
int mm::id_resp(dissector d, context* ctx) {
    use_context uc(ctx, "identity-response");

    using namespace mm_id_resp;
    /* Mobile identity  5GS mobile identity 9.11.3.4    M    LV-E    3-n  */
    // ELEM_MAND_LV_E(DE_NAS_5GS_MM_5GS_MOBILE_ID, ei_nas_5gs_missing_mandatory_elemen);
    auto consumed = dissect_elem_lv_e(nullptr, &mobile_id, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);
    return d.tvb->reported_length;
}

namespace mm_id_resp {

}
