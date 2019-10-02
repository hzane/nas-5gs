#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 9.11.3.1     5GMM capability*/
int dissect_mm_capability(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "5gmm-capability", 12);


    // 5-15 octets is spare
    return uc.length;
}
