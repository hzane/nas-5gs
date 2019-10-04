#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.3.15 PDU session release complete */
result_t de_pdu_session_release_complete(dissector                       d,
                                         context*                        ctx,
                                         pdu_session_release_complete_t* ret) {
    const use_context uc(&d, ctx, "pdu-session-release-complete", 0);
    /* Direction: UE to network */
    up_link(d.pinfo);
    de_nsm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.3.15.1.1: PDU SESSION RELEASE COMPLETE message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        PDU session ID	PDU session identity	9.4	M	V	1
        PTI	Procedure transaction identity	9.6	M	V	1
        PDU SESSION RELEASE COMPLETE message identity	Message type	9.7	M	V	1
    59	5GSM cause	5GSM cause	9.11.4.2	O	TV	2
    7B	Extended protocol configuration options	9.11.4.6	O	TLV-E	4-65538
    */
    de_nsm_header(d, ctx, &ret->header);

    de_t_uint8(d, ctx, 0x59, &ret->cause).step(d);
    de_tle_octet(d, ctx, 0x7b, &ret->extended_pco).step(d);
    return {uc.consumed()};
}