#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* * 9.11.3.16	Authentication parameter RAND */
result_t dissect_authentication_parameter_rand(dissector                       d,
                                               context*                        ctx,
                                               authentication_parameter_rand_t ret) {
    return de_fixed(d, ctx, ret);
}
