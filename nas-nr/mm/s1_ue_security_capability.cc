#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 9.11.3.54    UE security capability*/
int dissect_ue_security_capability(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "ue-security-capability", 4);

    return 4 + d.length;
}

/*  9.11.3.54    UE security capability  */
int dissect_replayed_ue_security_capability(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "ue-security-capability", 0);

    return uc.length;
}
