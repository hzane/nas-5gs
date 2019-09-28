#include "../common/ber.hh"
#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

/*  8.2.12 De-registration request (UE originating de-registration)  */
int mm::dissect_deregistration_request_ue_origin(dissector d, context* ctx) {
    const use_context uc(ctx, "de-reg-ue-orig", d, 0);
    // UE to network
    up_link(d.packet);

    /* De-registration type   9.11.3.20   M   V   1/2 */
    (void) dissect_deregistration_type(d, ctx);

    /* ngKSI    NAS key set identifier 9.11.3.32    M    V    1/2 H1 */
    (void) dissect_v( &nas_ksi, d, ctx);
    d.step(1);

    /* 5GS mobile identity  9.11.3.4    M    LV-E    6-n */
    const auto consumed = dissect_lv_e( &mobile_id, d, ctx);
    d.step(consumed);

    return uc.length;
}

struct deregistration_type_t {};
struct deregistration_request_ue_origin_t{
    deregistration_type_t type;
    uint8_t nas_ksi;
    // mobile_id_t  mobile_id;
};
