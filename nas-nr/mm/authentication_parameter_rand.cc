#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* * 9.11.3.16	Authentication parameter RAND */
int dissect_authentication_parameter_rand(dissector d, context* ctx) {
    const use_context uc(ctx, "authentication-parameter-rand", d, -1);

    return 16;
}
