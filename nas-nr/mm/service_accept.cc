#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/*  8.2.17 Service accept */
result_t de_service_accept(dissector d, context* ctx, service_accept_t* ret) {
    const use_context uc(&d, ctx, "service-accept", 3);
    // network to UE
    down_link(d.pinfo);

    de_nmm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.2.17.1.1: SERVICE ACCEPT message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        Service accept message identity	Message type	9.7	M	V	1
    */

    // 50	PDU session status	PDU session status	9.11.3.44	O	TLV	4-34
    de_tl_octet(d, ctx, 0x50, &ret->pdu_session_status).step(d);

    // 26	PDU session reactivation result	9.11.3.42	O TLV 4-34
    de_tl_octet(d, ctx, 0x26, &ret->pdu_session_reactivation_result).step(d);

    // 72	PDU session reactivation result error cause	9.11.3.43	O	TLV-E	5-515
    de_tle_octet(d, ctx, 0x72, &ret->result_error_cause).step(d);

    // 78	EAP message	EAP message	9.11.2.2	O	TLV-E 7-1503
    de_tle_octet(d, ctx, 0x78, &ret->eap).step(d);

    // XX	T3448 value	GPRS timer 3	9.11.2.4	O	TLV	3
    return {uc.consumed()};
}