#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.2.3 Authentication result */
result_t de_authentication_result(dissector                d,
                                  context*                 ctx,
                                  authentication_result_t* ret) {
    const use_context uc(&d, ctx, "authentication-result", 0);

    de_nmm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.2.3.1.1: AUTHENTICATION RESULT message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        Authentication result message identity	Message type	9.7	M	V	1

    */

    // ngKSI 	NAS key set identifier	9.11.3.32	M	V	1/2
    de_nibble(d, ctx, &ret->nksi).step(d);

    // Spare half octet	Spare half octet	9.5	M	V	1/2

    // EAP message	EAP message	9.11.2.2	M	LV-E	6-1502
    de_le_octet(d, ctx, &ret->eap).step(d);

    // 38	ABBA	ABBA	9.11.3.10	O	TLV	4-n
    de_tl_octet(d, ctx, 0x38, &ret->abba).step(d);
    return {d.offset - uc.offset};
}