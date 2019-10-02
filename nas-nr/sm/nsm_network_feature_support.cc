#include "../common/dissector.hh"
#include "../common/use_context.hh"


// 5GSM network feature support 9.11.4.18
int dissect_sm_network_feature_support(dissector d, context* ctx){
    const use_context uc(&d, ctx, "5gsm-network-feature-support", 12);

    return uc.length;
}
