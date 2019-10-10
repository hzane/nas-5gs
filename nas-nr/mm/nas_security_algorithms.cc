#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* *   9.11.3.34    NAS security algorithms */
result_t die_nas_security_algorithm(dissector                 d,
                                    context*                  ctx,
                                    nas_security_algorithm_t* ret) {
    de_uint8(d, ctx, &ret->integrity_algo);
    de_uint8(d, ctx, &ret->ciphering_algo, 0xf0u).step(d);

    return {1};
}
