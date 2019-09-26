#include "../common/dissector.hh"
#include "../common/use_context.hh"

// 9.11.3.2	5GMM cause
int dissect_nrmm_cause(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "5gmm-cause", -1);

    return 1;
}
