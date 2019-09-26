#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.2.4 Authentication failure */
int dissect_authentication_failure(dissector d, context* ctx) {
    const use_context uc(ctx, "authentication-failure", d, 0);
    // UE to network
    up_link(d.pinfo);

    return uc.length;
}
