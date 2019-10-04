#include "../common/ber.hh"
#include "../common/dissector.hh"
#include "../common/dissects.hh"
#include "../common/ies.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.2.1.1    Authentication request */
result_t de_authentication_request(dissector                 d,
                                   context*                  ctx,
                                   authentication_request_t* ret) {
    const use_context uc(&d, ctx, "authentication-request", 0);

    de_nmm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.2.1.1.1: AUTHENTICATION REQUEST message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        Authentication request message identity	Message type	9.7	M	V	1
    */
    // ngKSI 	NAS key set identifier	9.11.3.32	M	V	1/2
    de_nibble(d, ctx, &ret->nksi).step(d);

    // Spare half octet	Spare half octet	9.5	M	V	1/2

    // ABBA	ABBA	9.11.3.10	M	LV	3-n
    de_l_octet(d, ctx, &ret->abba).step(d);

    // 21 Authentication parameter RAND (5G authentication challenge) 9.11.3.16 O TV 17
    de_t_fixed(d, ctx, 0x21, &ret->rand).step(d);

    // 20 Authentication parameter AUTN (5G authentication challenge) 9.11.3.15 O TLV	18
    de_tl_fixed(d, ctx, 0x20, &ret->autn).step(d);

    // 78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503
    de_tle_octet(d, ctx, 0x78, &ret->eap).step(d);
    return {d.offset - uc.offset};
}

