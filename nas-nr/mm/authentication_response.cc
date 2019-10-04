#include "../common/definitions.hh"
#include "../common/dissector.hh"
#include "../common/use_context.hh"
#include "../common/messages.hh"

/* 8.2.2    Authentication response */
result_t de_authentication_response(dissector                  d,
                                    context*                   ctx,
                                    authentication_response_t* ret) {
    const use_context uc(&d, ctx, "authentication-response", 0);

    de_nmm_header(d, ctx, &ret->header).step(d);
    /*
    Table 8.2.2.1.1: AUTHENTICATION RESPONSE message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        Authentication response message identity	Message type	9.7	M	V	1
    */

    // 2D	Authentication response parameter	9.11.3.17 O TLV	18
    de_tl_fixed(d, ctx, 0x2d, &ret->parameter).step(d);

    // 78	EAP message	9.11.2.2	O	TLV-E	7-1503
    de_tle_octet(d, ctx, 0x78, &ret->eap).step(d);
    return {d.offset - uc.offset};
}
