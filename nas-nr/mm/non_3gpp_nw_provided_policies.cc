#include "../common/dissector.hh"
#include "../common/use_context.hh"

// 9.11.3.58	Non-3GPP NW provided policies
int dissect_n3gpp_nw_provided_policies(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "non-3gpp-nw-provided-policies", -1);

    // See subclause 10.5.5.37 in 3GPP TS 24.008

    /* no length check possible */
    return 1;
}
