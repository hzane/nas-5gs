#include "../common/dissector.hh"
#include "../common/use_context.hh"

//* 9.11.3.8     5GS tracking area identity
int dissect_last_visited_tai(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "5gs-tracking area identity", -1);

    return 6;
}
