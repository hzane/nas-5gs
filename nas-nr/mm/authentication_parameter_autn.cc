#include "../common/definitions.hh"
#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

/* 9.11.3.15	Authentication parameter AUTN
 * [9] 10.5.3.1.1 Authentication Parameter AUTN (UMTS and EPS authentication challenge) */
result_t dissect_authentication_parameter_autn(dissector                       d,
                                               context*                        ctx,
                                               authentication_parameter_autn_t ret) {
    return de_fixed(d, ctx, ret);
}
