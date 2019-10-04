#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.2.5 Authentication reject */
result_t de_authentication_reject(dissector                d,
                                  context*                 ctx,
                                  authentication_reject_t* ret) {
    const use_context uc(&d, ctx, "authentication-reject", 0);

    de_nmm_header(d, ctx, &ret->header).step(d);
    /*
    Table 8.2.5.1.1: AUTHENTICATION REJECT message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        Authentication reject message identity	Message type	9.7	M	V	1
    */

    // 78	EAP message	9.11.2.2	O	TLV-E	7-1503
    de_tle_octet(d, ctx, 0x78, &ret->eap).step(d);

    return {d.offset - uc.offset};
}