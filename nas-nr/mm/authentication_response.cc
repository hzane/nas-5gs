#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.2.2    Authentication response */
int dissect_authentication_response(dissector d, context* ctx) {
    const use_context uc(ctx, "authentication-response", d, 0);


    return uc.length;
}
