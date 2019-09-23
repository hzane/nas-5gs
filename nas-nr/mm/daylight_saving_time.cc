#include "../common/dissect_mm_msg.hh"

using namespace cmn;
using namespace mm;

// 9.11.3.19	Daylight saving time
// See subclause 10.5.3.12 in 3GPP TS 24.008 [12].
int mm::dissect_daylight_saving_time(dissector d, context* ctx) {
    const use_context uc(ctx, "daylight-saving-time", d, -1);

    (void) d.add_item(1, &hf_dst_adjustment, enc::be);
    d.step(1);

    return 1;
}

// 9.11.3.19
extern const element_meta mm::daylight_saving_time = {
    0x49,
    "Network daylight saving time",
    dissect_daylight_saving_time,
    nullptr,

};

struct daylight_saving_time_t {
    uint8_t adjustment;
};
