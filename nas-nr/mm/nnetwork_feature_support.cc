#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 9.11.3.5     5GS network feature support*/
int dissect_network_feature_support(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "5gs-network-feature-support", 1);

    // oct 5 is optional
    return uc.length; // 1-3
}
