#include "../common/ies.hh"
#include "../common/context.hh"
#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*
9.11.2.6	Intra N1 mode NAS transparent container
*/
result_t die_intra_n1_mode_container(dissector                  d,
                                     context*                   ctx,
                                     intra_n1_mode_container_t* ret) {
    const use_context uc(&d, ctx, "intra-n1-mode-container", 0);

    // Message authentication code	octet 3  octet 6
    de_fixed(d, ctx, ret->auth_code).step(d);

    // Type of ciphering algorithm	Type of integrity protection algorithm	octet 7
    de_nibble(d, ctx, &ret->integrity_algo);
    de_uint8(d, ctx, &ret->ciphering_algo, 0xf0u).step(d);

    // 0	0 Spare	0	KACF	TSC	Key set identifier in 5G	octet 8
    de_uint8(d, ctx, &ret->kacf, 0x10u);
    de_uint8(d, ctx, &ret->tsc, 0x10u);
    de_uint8(d, ctx, &ret->nksi, 0x07u).step(d);

    // Sequence number	octet 9
    de_uint8(d, ctx, &ret->seq_no).step(d);

    return {uc.consumed()};
}
