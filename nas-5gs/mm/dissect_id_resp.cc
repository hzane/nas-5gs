#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

/* 8.2.22 Identity response  */
int mm::dissect_id_resp(dissector d, context* ctx) {    
    const use_context uc(ctx, "identity-response", d, 0);

    /* Mobile identity  5GS mobile identity 9.11.3.4    M    LV-E    3-n  */    
    const auto consumed = dissect_elem_lv_e(nullptr, &mobile_id, d, ctx);
    d.step(consumed);
    
    return uc.length;
}
