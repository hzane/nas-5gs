#include "../common/dissector.hh"
#include "../common/use_context.hh"

// See sub-clause 10.5.3.2.2 in 3GPP TS 24.008 [12].
// Authentication failure parameter
int dissect_authentication_failure_parameter(dissector d, context* ctx) {
    const use_context uc(ctx, "authentication-failure-param", d, -1);

    /* This IE contains either the SRES or the 4 most significant octets of the RES */

    return 4;
}
