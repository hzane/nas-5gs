#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

// PDU address 9.11.4.10 15 octets
result_t die_pdu_address(dissector d, context*ctx, pdu_address_t*ret){
    const use_context uc(&d, ctx, "pdu-address", 0);
    de_uint8(d, ctx, &ret->type, 0x07u).step(d);
    de_fixed(d, ctx, ret->address).step(d);
    return {uc.consumed()};
}