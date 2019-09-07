#include "../dissect_mm_msg.hh"

// 9.11.3.19	Daylight saving time
// See subclause 10.5.3.12 in 3GPP TS 24.008 [12].
int mm::dissect_day_saving_time(dissector d, context* ctx) {
    const use_context uc(ctx, "daylight-saving-time", d, -1);

    auto i = d.add_item(1, &hf_dst_adjustment, enc::be);
    d.step(1);

    unused(i);
    return 1;
}

// 9.11.3.19
extern const element_meta mm::day_saving_time = {
    0x49,
    "Network daylight saving time",
    dissect_day_saving_time,
    nullptr,

};
