#include "../common/dissector.hh"
#include "../common/use_context.hh"

// 9.11.3.61	Mobile station classmark 2
// See subclause 10.5.1.6 in 3GPP TS 24.008 [12].
int dissect_mobile_station_classmark2(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "mobile-station-classmark2", 0);

    d.step(1);
    return d.offset - uc.offset;
}
