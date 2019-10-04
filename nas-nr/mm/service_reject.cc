#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.2.18 Service reject */
result_t de_service_reject(dissector d, context* ctx, service_reject_t* ret) {
    const use_context uc(&d, ctx, "service-reject", 0);
    // network to UE
    down_link(d.pinfo);

    de_nmm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.2.18.1.1: SERVICE REJECT message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        Service reject message identity	Message type	9.7	M	V	1
    */
    // 5GMM cause	5GMM cause	9.11.3.2	M	V	1
    de_uint8(d, ctx, &ret->cause).step(d);

    // 50	PDU session status	PDU session status	9.11.3.44	O	TLV	4-34
    de_tl_octet(d, ctx, 0x50, &ret->pdu_session_status).step(d);

    // 5F	T3346 value	GPRS timer 2	9.11.2.4	O	TLV	3
    de_tl_uint8(d, ctx, 0x5f, &ret->t3346).step(d);

    // 78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503
    de_tle_octet(d, ctx, 0x78, &ret->eap).step(d);

    //    XX	T3448 value	GPRS timer 3	9.11.2.4	O	TLV	3
    return {uc.consumed()};
}
