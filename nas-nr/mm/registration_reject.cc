#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/*  8.2.9 Registration reject */
result_t de_registration_reject(dissector d, context* ctx, registration_reject_t* ret) {
    const use_context uc(&d, ctx, "registration-reject", 0);
    down_link(d.pinfo);

    de_nmm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.2.9.1.1: REGISTRATION REJECT message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        Registration reject message identity	Message type	9.7	M	V	1
    */

    // 5GMM cause	5GMM cause	9.11.3.2	M	V	1
    de_uint8(d, ctx, &ret->cause).step(d);

    // 5F	T3346 value	GPRS timer 2	9.11.2.4	O	TLV	3
    de_tl_uint8(d, ctx, 0x5f, &ret->t3346).step(d);

    // 16	T3502 value	GPRS timer 2	9.11.2.4	O	TLV	3
    de_tl_uint8(d, ctx, 0x16, &ret->t3502).step(d);

    // 78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503
    de_tle_octet(d, ctx, 0x78, &ret->eap).step(d);
    return {uc.consumed()};
}