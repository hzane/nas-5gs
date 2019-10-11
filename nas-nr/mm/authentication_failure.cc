#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.2.4 Authentication failure */
result_t de_authentication_failure(dissector                 d,
                                   context*                  ctx,
                                   authentication_failure_t* ret) {
    const use_context uc(&d, ctx, "authentication-failure", 0);
    // UE to network
    d.uplink();

    de_nmm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.2.4.1.1: AUTHENTICATION FAILURE message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        Authentication failure message identity	Message type	9.7	M	V	1
    */

    // 5GMM cause	5GMM cause	9.11.3.2	M	V	1
    de_uint8(d, ctx, &ret->cause).step(d);

    // 30	Authentication failure parameter	9.11.3.14 O TLV	16
    de_tl_fixed(d, ctx, 0x30, &ret->parameter).step(d);
    return {d.offset - uc.offset};
}