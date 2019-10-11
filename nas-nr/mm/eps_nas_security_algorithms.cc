#include "../common/context.hh"
#include "../common/core.hh"
#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

result_t die_eps_nas_security_algorithms(dissector                      d,
                                         context*                       ctx,
                                         eps_nas_security_algorithms_t* ret) {
    de_uint8(d, ctx, &ret->integrity_algo, 0x07);

    de_uint8(d, ctx, &ret->ciphering_algo, 0x70);

    return {1};
}
