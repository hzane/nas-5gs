#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 9.11.3.17	Authentication response parameter */
int dissect_authentication_response_parameter(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "auth-response-param", -1);

    return 4;
}
