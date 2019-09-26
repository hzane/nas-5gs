#include "../common/dissector.hh"
#include "../common/use_context.hh"

// 9.11.3.19	Daylight saving time
// See subclause 10.5.3.12 in 3GPP TS 24.008 [12].
int dissect_daylight_saving_time(dissector d, context* ctx) {
    const use_context uc(ctx, "daylight-saving-time", d, -1);

    return 1;
}
