#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

/*  9.11.3.59  EPS bearer context status
 * See subclause 9.9.2.1 in 3GPP TS 24.301 [15]. */
result_t die_eps_bearer_context_status(dissector d, context*ctx, eps_bearer_context_status_t*ret){
    ret->ebi_a = d.uint8(true);
    ret->ebi_b = d.uint8(true);

    return {2};
}