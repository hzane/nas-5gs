#include "../common/ies.hh"
#include "context.hh"
#include "dissector.hh"
#include "use_context.hh"

// 9.11.2.9
result_t die_s1_mode_to_n1_mode_containers(dissector                       d,
                                           context*                        ctx,
                                           s1_mode_to_n1_mode_container_t* ret) {
    const use_context uc(&d, ctx, "s1-mode-to-n1-mode-container", 2);

    de_fixed(d, ctx, ret->auth_code).step(d);

    de_uint8(d, ctx, &ret->integrity_algo, 0x0f);
    de_uint8(d, ctx, &ret->ciphering_algo, 0xf0u).step(d);

    de_uint8(d, ctx, &ret->nksi, 0x07u);
    de_uint8(d, ctx, &ret->tsc, 0x04);
    de_uint8(d, ctx, &ret->ncc, 0x70u).step(d);

    return {uc.length};
}
