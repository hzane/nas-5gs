#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

// 9.11.3.35	Network name
result_t die_network_name(dissector d, context* ctx, network_name_t* ret) {
    const use_context uc(&d, ctx, "network-name", 0);

    de_uint8(d, ctx, &ret->unused_bits, 0x07);
    de_uint8(d, ctx, &ret->add_ci, 0x08u);
    de_uint8(d, ctx, &ret->coding_scheme, 0x70u);
    de_uint8(d, ctx, &ret->ext, 0x80u).step(d);

    ret->text = octet_t(d.safe_ptr(), d.safe_ptr() + d.safe_length(d.length));

    return {uc.consumed()};
}
