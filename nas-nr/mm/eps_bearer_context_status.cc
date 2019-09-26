#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*  9.11.3.59  EPS bearer context status
 * See subclause 9.9.2.1 in 3GPP TS 24.301 [15]. */
int dissect_eps_bearer_context_status(dissector d, context* ctx) {
    const use_context uc(ctx, "eps-bearer-context-status", d, 0);

    return 2;
}
