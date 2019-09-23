#include "../common/ber.hh"
#include "../common/dissect_mm_msg.hh"

/* 8.2.22 Identity response  */
int mm::dissect_identity_response(dissector d, context* ctx) {
    const use_context uc(ctx, "identity-response", d, 0);
    // UE to AMF
    up_link(d.pinfo);

    /* Mobile identity  5GS mobile identity 9.11.3.4    M    LV-E    3-n  */
    const auto consumed = dissect_lv_e(nullptr, &mobile_id, d, ctx);
    d.step(consumed);

    return uc.length;
}

struct identity_response_t {
    payload_t mobile_id;
};
