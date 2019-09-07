#include "../dissect_mm_msg.hh"

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

/* [3] 10.5.3.9 Time Zone and Time */
// TODO: add display type
int dissect_time_zone_time(dissector d, context* ctx) {
    const use_context uc(ctx, "time-zone-time", d, -1);

    (void) d.add_item( 6, time_string(d.safe_ptr()).c_str());
    d.step(6);

    auto       oct  = d.tvb->uint8(d.offset);
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
