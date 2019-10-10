#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* [3] 10.5.3.9 Time Zone and Time in 3GPP TS 24.008 [12].*/
result_t die_timezone_time(dissector d, context* ctx, time_zone_time_t* ret) {
    auto year   = d.uint8(true);
    auto month  = d.uint8(true);
    auto day    = d.uint8(true);
    auto hour   = d.uint8(true);
    auto minute = d.uint8(true);
    auto second = d.uint8(true);
    auto tz     = d.uint8(true);

    ret->year   = mask_u8(year, 0x0fu) * 10 + mask_u8(year, 0xf0u) + 2000;
    ret->month  = mask_u8(month, 0x0fu) * 10 + mask_u8(month, 0xf0u);
    ret->mday   = mask_u8(day, 0x0fu) * 10 + mask_u8(day, 0xf0u);
    ret->hour   = mask_u8(hour, 0x0fu) * 10 + mask_u8(hour, 0xf0u);
    ret->minute = mask_u8(minute, 0x0fu) * 10 + mask_u8(minute, 0xf0u);
    ret->second = mask_u8(second, 0x0fu) * 10 + mask_u8(second, 0xf0u);

    ret->gmt = mask_u8(tz, 0x07u) * 10 + mask_u8(tz, 0xf0u);
    if (tz & 0x08u) ret->gmt = -ret->gmt;
    return {7};
}
