#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

// 9.11.3.53
extern const element_meta mm::timezone_time= {
    0x47,
    "Time zone and time - Universal time and local time zone",
    dissect_timezone_time_set,
};
const utc_field hf_timezone_time = {
    "Time Zone and Time",
};

/* [3] 10.5.3.9 Time Zone and Time in 3GPP TS 24.008 [12].*/
int mm::dissect_timezone_time_set(dissector d, context* ctx) {
    const use_context uc(ctx, "time-zone-time", d, -1);

    d.set_item(7, utc_string(d.ptr(), d.safe_length(7)));
    d.step(7);

    /* no length check possible */
    return 7;
}
