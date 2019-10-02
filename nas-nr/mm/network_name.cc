#include "../common/dissector.hh"
#include "../common/use_context.hh"


// 9.11.3.35	Network name
int dissect_full_name_network(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "network-name", 0);


    return uc.length;
}
// 9.11.3.35	Network name
int dissect_short_name_network(dissector d, context* ctx) {
    return dissect_full_name_network(d, ctx);
}