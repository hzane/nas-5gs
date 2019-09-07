#include "../dissect_mm_msg.hh"
#include <ctime>

// See subclause 10.5.3.9 in 3GPP TS 24.008 [12].

extern const element_meta mm::local_time_zone = {
    0x46,
    "Local time zone",
    dissect_local_time_zone,
    nullptr,

};

// 9.11.3.53
extern const element_meta mm::u_time_zone_time = {
    0x47,
    "Time zone and time - Universal time and local time zone",
    dissect_time_zone_time,
    nullptr,

};

string abs_time_str(tm t) {
    const char* ts = asctime(&t);
    return ts ? string(ts) : string();
}

/* [3] 10.5.3.9 Time Zone and Time */
// TODO: add display type
int mm::dissect_time_zone_time(dissector d, context* ctx) {
    const use_context uc(ctx, "time-zone-time", d, -1);

    tm t = {0, 0, 0, 0, 0, 0, 0, 0, -1};

    auto oct  = static_cast< int >(d.tvb->uint8(d.offset));
    t.tm_year = (oct & 0x0f) * 10 + ((oct & 0xf0) >> 4) * 100;

    oct      = d.tvb->uint8(d.offset + 1);
    t.tm_mon = (oct & 0x0f) * 10 + ((oct & 0xf0) >> 4) - 1;

    oct       = d.tvb->uint8(d.offset + 2);
    t.tm_mday = (oct & 0x0f) * 10 + ((oct & 0xf0) >> 4);

    oct       = d.tvb->uint8(d.offset + 3);
    t.tm_hour = (oct & 0x0f) * 10 + ((oct & 0xf0) >> 4);

    oct      = d.tvb->uint8(d.offset + 4);
    t.tm_min = (oct & 0x0f) * 10 + ((oct & 0xf0) >> 4);

    oct      = d.tvb->uint8(d.offset + 5);
    t.tm_sec = (oct & 0x0f) * 10 + ((oct & 0xf0) >> 4);

    d.tree->add_subtree(d.pinfo, d.tvb, d.offset, 6, abs_time_str(t).c_str());
    d.step(6);

    oct             = d.tvb->uint8(d.offset);
    const auto sign = (oct & 0x08) ? '-' : '+';
    oct             = (oct >> 4) + (oct & 0x07) * 10;
    d.tree->add_subtree(d.pinfo,
                        d.tvb,
                        d.offset,
                        1,
                        "GMT %c %d hours %d minutes",
                        sign,
                        oct / 4,
                        oct % 4 * 15);
    d.step(1);

    /* no length check possible */
    return 7;
}
