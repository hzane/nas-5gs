#include "../dissect_mm_msg.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

// 9.11.3.53
extern const element_meta mm::timezone_time= {
    0x47,
    "Time zone and time - Universal time and local time zone",
    dissect_timezone_time_set,
    nullptr,

};
const field_meta hf_timezone_time = {
    "Time Zone and Time",
    "nas_5gs.time",
    ft::ft_bytes,
    fd::timezone_time,
    nullptr,
    nullptr,
    nullptr,
    0,
};

/* [3] 10.5.3.9 Time Zone and Time in 3GPP TS 24.008 [12].*/
int mm::dissect_timezone_time_set(dissector d, context* ctx) {
    const use_context uc(ctx, "time-zone-time", d, -1);

    d.tree->set_item(7, &hf_timezone_time, enc::be);
    d.step(7);

    /* no length check possible */
    return 7;
}
