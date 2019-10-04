#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/*  8.2.14 De-registration request (UE terminated de-registration) */
result_t de_deregistration_request_ue_term(dissector                         d,
                                           context*                          ctx,
                                           deregistration_request_ue_term_t* ret) {
    const use_context uc(&d, ctx, "deregistration-request-ue-term", 0);
    // network to UE
    down_link(d.pinfo);

    de_nmm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.2.14.1.1: DEREGISTRATION REQUEST message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        De-registration request message identity	Message type	9.7	M	V	1

    */

    // De-registration type	De-registration type	9.11.3.20	M	V	1/2
    de_nibble(d, ctx, &ret->type).step(d);

    // Spare half octet	Spare half octet	9.5	M	V	1/2

    // 58	5GMM cause	5GMM cause	9.11.3.2	O	TV	2
    de_t_uint8(d, ctx, 0x58, &ret->nmm_cause).step(d);

    // 5F T3346 value GPRS timer 2 9.11.2.4 O TLV 3
    de_tl_uint8(d, ctx, 0x5f, &ret->t3346);
    return {uc.consumed()};
}