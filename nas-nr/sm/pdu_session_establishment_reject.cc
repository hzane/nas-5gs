#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/*  8.3.3 PDU session establishment reject */
result_t de_pdu_session_establishment_reject(dissector                           d,
                                             context*                            ctx,
                                             pdu_session_establishment_reject_t* ret) {
    const use_context uc(&d, ctx, "pdu-session-establishment-reject", 0);
    /* Direction: network to UE */
    down_link(d.pinfo);

    de_nsm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.3.3.1.1: PDU SESSION ESTABLISHMENT REJECT message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        PDU session ID	PDU session identity	9.4	M	V	1
        PTI	Procedure transaction identity	9.6	M	V	1
        PDU SESSION ESTABLISHMENT REJECT message identity	Message type	9.7	M	V	1
    */
    // 5GSM cause	5GSM cause	9.11.4.2	M	V	1
    de_uint8(d, ctx, &ret->nsm_cause);

    // 37	Back-off timer value	GPRS timer 3	9.11.2.5	O	TLV	3
    de_tl_uint8(d, ctx, 0x37, &ret->backoff_timer).step(d);

    // F-	Allowed SSC mode	Allowed SSC mode	9.11.4.5	O	TV	1
    de_tv_short(d, ctx, 0xf0, &ret->allowed_ssc_mode).step(d);

    // 78	EAP message	EAP message	9.11.2.2	O	TLV-E	7-1503
    de_tle_octet(d, ctx, 0x78, &ret->eap).step(d);

    // 7B	Extended protocol configuration options	9.11.4.6	O	TLV-E	4-65538
    de_tle_octet(d, ctx, 0x7b, &ret->extended_pco).step(d);

    // TBD	Re-attempt indicator	9.11.4.17	O	TLV	3
    // 61	5GSM congestion re-attempt indicator	9.11.4.21	O	TLV	3
    de_tl_uint8(d, ctx, 0x61, &ret->reattempt_ind).step(d);
    return {uc.consumed()};
}
