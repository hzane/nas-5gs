#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.3.6	PDU session authentication result */
result_t de_pdu_session_authentication_result(dissector                            d,
                                              context*                             ctx,
                                              pdu_session_authentication_result_t* ret) {
    const use_context uc(&d, ctx, "pdu-session-authentication-result", 0);
    /* Direction: network to UE */
    down_link(d.pinfo);

    de_nsm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.3.6.1.1: PDU SESSION AUTHENTICATION RESULT message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        PDU session ID	PDU session identity	9.4	M	V	1
        PTI	Procedure transaction identity	9.6	M	V	1
        PDU SESSION AUTHENTICATION RESULT message identity	Message type	9.7	M	V	1
    */
    // 78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503
    de_tle_octet(d, ctx, 0x78, &ret->eap).step(d);

    // 7B	Extended protocol configuration options	9.11.4.6	O	TLV-E	4-65538
    de_tle_octet(d, ctx, 0x7b, &ret->extended_pco).step(d);

    return {uc.consumed()};
}
