#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 9.11.3.15	Authentication parameter AUTN
 * [9] 10.5.3.1.1 Authentication Parameter AUTN (UMTS and EPS authentication challenge) */
int dissect_authentication_parameter_autn(dissector d, context* ctx) {
    const use_context uc(ctx, "auth-param-autn", d, 0);

    return uc.length;
}
