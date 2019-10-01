#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"



// TAC, Tracking area code
extern const uint24_field hf_tracking_area_code = {
    "TAC, Tracking area code",
    0x0,
};

//* 9.11.3.8     5GS tracking area identity
int mm::dissect_last_visited_tai(dissector d, context* ctx) {
    const use_context uc(ctx, "5gs-tracking area identity", d, -1);

    dissect_e212_mcc_mnc(d, ctx);
    d.step(3);

    /* TAC Octet 5 - 7 */
    (void) d.add_item(&hf_tracking_area_code);

    return 6;
}



