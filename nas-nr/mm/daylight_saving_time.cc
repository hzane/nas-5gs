#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"


using namespace mm;


/*[3] 10.5.3.12 Daylight Saving Time */
const tag_field hf_dst_adjustment = {
    "DST Adjustment",
    0x03,
    (const v_string[]){
        {0, "No adjustment for Daylight Saving Time"},
        {1, "+1 hour adjustment for Daylight Saving Time"},
        {2, "+2 hours adjustment for Daylight Saving Time"},
        {3, "Reserved"},
        {0, nullptr},
    },
};


// 9.11.3.19	Daylight saving time
// See subclause 10.5.3.12 in 3GPP TS 24.008 [12].
int mm::dissect_daylight_saving_time(dissector d, context* ctx) {
    const use_context uc(ctx, "daylight-saving-time", d, -1);

    (void) d.add_item( &hf_dst_adjustment);
    d.step(1);

    return 1;
}
