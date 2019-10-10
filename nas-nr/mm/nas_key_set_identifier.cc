#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

// 9.11.3.32	NAS key set identifier
result_t die_nas_key_set_identifier(dissector                 d,
                                    context*                  ctx,
                                    nas_key_set_identifier_t* ret) {
    de_uint8(d, ctx, &ret->nksi, 0x07);

    de_uint8(d, ctx, &ret->tsc, 0x08).step(d);

    return {1};
}
