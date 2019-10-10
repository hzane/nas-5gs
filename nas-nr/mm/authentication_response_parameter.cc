#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 9.11.3.17	Authentication response parameter */
int dissect_authentication_response_parameter(dissector                            d,
                                              context*                             ctx,
                                              authentication_response_parameter_t* ret) {
    return de_octet(d, ctx, ret);
}
