#include "../common/dissector.hh"
#include "../common/use_context.hh"


// 9.11.3.48 S1 UE network capability page.391
// See subclause 9.9.3.34 in 3GPP TS 24.301 [15].
int dissect_s1_ue_net_capability(dissector d, context* ctx) {
    const use_context        uc(ctx, "s1-ue-network-capablility", d, 0);

    return uc.length;
}
// 9.11.3.48A S1 UE security capability page.391
// See subclause 9.9.3.36 in 3GPP TS 24.301 [15].
int dissect_reported_s1_ue_security_capability(dissector d, context* ctx) {
    const use_context uc(ctx, "s1-ue-security-capability", d, 0);

    return uc.length;
}
