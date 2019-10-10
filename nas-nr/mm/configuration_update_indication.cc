#include "../common/dissector.hh"
#include "../common/use_context.hh"
#include "../common/ies.hh"

/* 9.11.3.18    Configuration update indication */
result_t die_configuration_update_indication(dissector                          d,
                                             context*                           ctx,
                                             configuration_update_indication_t* ret) {
    de_uint8(d, ctx, &ret->ack, 0x01);
    de_uint8(d, ctx, &ret->red, 0x02).step(d);

    return {1};
}
