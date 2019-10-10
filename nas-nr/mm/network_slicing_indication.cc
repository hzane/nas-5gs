#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

//  9.11.3.36    Network slicing indication
result_t die_network_slicing_indication(dissector                     d,
                                        context*                      ctx,
                                        network_slicing_indication_t* ret) {
    de_uint8(d, ctx, &ret->nssci, 0x01);

    de_uint8(d, ctx, &ret->dcni, 0x02).step(d);

    return {1};
}
