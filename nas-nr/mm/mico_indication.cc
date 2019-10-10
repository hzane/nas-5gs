#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/*  9.11.3.31    MICO indication */
result_t die_mico_indication(dissector d, context* ctx, mico_indication_t* ret) {
    de_uint8(d, ctx, &ret->raai, 0x01);

    de_uint8(d, ctx, &ret->sprti, 0x02).step(d);

    return {1};
}
