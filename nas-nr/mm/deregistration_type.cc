#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

/* De-registration type    De-registration type     9.11.3.20   M   V   1 */
result_t die_deregistration_type(dissector d, context* ctx, deregistration_type_t* ret) {
    de_uint8(d, ctx, &ret->access_type, 0x03);
    de_uint8(d, ctx, &ret->reregistration_required, 0x04);
    de_uint8(d, ctx, &ret->switch_off, 0x08).step(d);

    return {1};
}
