#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.2.3 Authentication result */
int dissect_authentication_result(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "authentication-result", 0);
    // network to UE
    down_link(d.pinfo);

    return uc.length;
}
