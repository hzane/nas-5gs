#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* [3] 10.5.3.9 Time Zone and Time in 3GPP TS 24.008 [12].*/
int dissect_timezone_time_set(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "time-zone-time", -1);

    /* no length check possible */
    return 7;
}
