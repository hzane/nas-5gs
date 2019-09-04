#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_id_resp {

}
/*
 * 8.2.22 Identity response
 */
int mm::id_resp(dissector d, context* ctx) {
    const auto  len = d.length;
    use_context uc(ctx, "identity-response");

    /* Mobile identity  5GS mobile identity 9.11.3.4    M    LV-E    3-n  */
    // ELEM_MAND_LV_E(DE_NAS_5GS_MM_5GS_MOBILE_ID, );
    auto consumed = dissect_elem_lv_e(nullptr, &mobile_id, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);
    return len;
}

namespace mm_id_resp {

}
